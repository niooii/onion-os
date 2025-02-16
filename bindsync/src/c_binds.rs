use std::{
    collections::HashSet,
    fs,
    io::Write,
    path::{Path, PathBuf},
};

use anyhow::Result;
use bindgen::{Builder, EnumVariation};
use walkdir::WalkDir;

use crate::{
    C_INCLUDE_DIR, RUST_BINDS_DIR,
    tracker::{ChangeKind, FileTracker},
};

const C_SAVE: &str = "cb_headers";
const R_SAVE: &str = "r_binds";

fn header_to_rust(header: &Path) -> PathBuf {
    let s = header.to_string_lossy();
    PathBuf::from(s.replace(
        &C_INCLUDE_DIR.to_string_lossy().into_owned(),
        &RUST_BINDS_DIR.to_string_lossy(),
    ))
    .with_extension("rs")
}

fn rust_to_header(header: &Path) -> PathBuf {
    todo!()
}

/// Returns the path the bindings were written to
fn gen_binds(include: &Path) -> Result<Option<PathBuf>> {
    let binds = Builder::default()
        .header(include.to_string_lossy().into_owned())
        .clang_arg("-I../include")
        .default_enum_style(EnumVariation::Rust {
            non_exhaustive: false,
        })
        .allowlist_function(".*")
        .blocklist_function("_.*")
        .use_core()
        .disable_header_comment()
        .generate()?;

    let mut buf = Vec::new();
    binds.write(Box::new(&mut buf))?;

    let content = String::from_utf8_lossy(&buf);
    if content.trim().is_empty() {
        Ok(None)
    } else {
        let out = header_to_rust(include);
        fs::create_dir_all(out.parent().unwrap_or(Path::new("/")))?;
        let mut file = fs::File::create(&out)?;
        file.write_all(&buf)?;
        Ok(Some(out))
    }
}

/// For individual .rs files
fn mod_name_from_file(path: &Path) -> Option<String> {
    path.file_stem()
        .map(|ostr| ostr.to_string_lossy().into_owned())
}

/// The module name of the directory as seen by other modules. Basically just the directory's name.
fn mod_name_from_dir(dir: &Path) -> Option<String> {
    dir.file_name()
        .map(|ostr| ostr.to_string_lossy().into_owned())
}

/// Removes a module from the folder's mod.rs, then propogates changes up the module tree
fn remove_mod_recursive(dir: &Path, mod_name: &str) -> Result<()> {
    let mod_file = dir.join("mod.rs");
    let mod_path = dir.join(format!("{mod_name}.rs"));
    let mod_str = format!("pub mod {mod_name};");

    if !mod_file.exists() {
        return Ok(());
    }
    let content = fs::read_to_string(&mod_file)?;

    let new_content = content
        .lines()
        .filter(|line| *line != mod_str)
        .collect::<Vec<_>>()
        .join("\n");

    // if its empty delete the entire module directory
    if new_content.contains("mod") {
        fs::write(&mod_file, new_content)?;
        // TODO! ehh
        let _ = std::fs::remove_file(&mod_path);
        Ok(())
    } else {
        // TODO! ehh
        if fs::remove_dir_all(dir).is_ok() {
            remove_mod_recursive(
                dir.parent().expect("yawn"),
                &mod_name_from_dir(dir).expect("yawn"),
            )
        } else {
            Ok(())
        }
    }
}

/// (Re)creates all mod.rs files
/// TODO! if this project grows bigger maybe implement something actually good
fn update_mods(dir: &Path) -> Result<()> {
    for dir in WalkDir::new(dir)
        .into_iter()
        .map(|e| e.expect("Failed to get directory entry"))
        .filter(|e| e.file_type().is_dir())
    {
        let mod_path = dir.path().join("mod.rs");

        let mut mod_file = fs::File::create(&mod_path)?;

        writeln!(&mut mod_file, "#![allow(dead_code)]")?;

        std::fs::read_dir(dir.path())?
            .map(|e| e.expect("Failed to get file"))
            .filter_map(|e| {
                let name = e
                    .path()
                    .file_stem()
                    .expect("Could not extract file stem")
                    .to_string_lossy()
                    .into_owned();
                (name != "mod").then_some(name)
            })
            .for_each(|mod_name| {
                writeln!(&mut mod_file, "pub mod {mod_name};").expect("Failed to write to mod.rs");
            });
        println!("Write to module {}.", mod_path.to_string_lossy());
    }
    Ok(())
}

pub fn generate() -> Result<()> {
    let mut headers = FileTracker::read(&C_INCLUDE_DIR, C_SAVE)?;
    // let mut bindings: FileTracker = FileTracker::read(&RUST_BINDS_DIR, R_SAVE)?;
    let mut to_remove: Vec<PathBuf> = Vec::new();
    let mut mod_change = false;
    {
        // Check if any headers changed
        for (path, meta) in headers.changed() {
            match meta.change {
                ChangeKind::Created | ChangeKind::Modified => {
                    let out = gen_binds(path)?;
                    if let Some(outp) = out {
                        println!(
                            "Generate bindings for {} at {}.",
                            path.to_string_lossy(),
                            outp.to_string_lossy()
                        );
                        //
                        mod_change = meta.change == ChangeKind::Created;
                    } else {
                        println!("No bindings for {}, discard.", path.to_string_lossy());
                    }
                }
                ChangeKind::Deleted => {
                    let rpath = header_to_rust(path);
                    to_remove.push(rpath);
                    mod_change = true;
                }
                // should never run this branch
                ChangeKind::Same => {}
            }
        }

        // Next check if any rust binding files have changed (maybe by accident idk!)
        // So we can regen them
        // TODO!
    }

    if mod_change {
        // (Re)create mod.rs files
        update_mods(&RUST_BINDS_DIR)?;
        // After the mod files are finalized, sweep away the ones from the removed headers.
        for deleted in to_remove {
            remove_mod_recursive(
                deleted.parent().expect("No parents??"),
                &mod_name_from_file(&deleted).expect("????"),
            )?;
        }
    }

    headers
        .save(C_SAVE)
        .expect("Bindings have been generated but failed to save metadata");
    // bindings
    //     .save(R_SAVE)
    //     .expect("Bindings have been generated but failed to save metadata");
    Ok(())
}
