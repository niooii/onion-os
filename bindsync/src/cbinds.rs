use std::{
    collections::{HashMap, HashSet},
    fs,
    io::Write,
    path::{Path, PathBuf},
};

use anyhow::Result;
use bindgen::{Builder, EnumVariation};

use crate::{
    BUILD_DIR, C_INCLUDE_DIR, RUST_BINDS_DIR,
    tracker::{ChangeKind, FileTracker},
};

const C_SAVE: &str = "cb_headers";
const R_SAVE: &str = "r_binds";

pub struct RustModuleFile {
    contents: String,
}

impl RustModuleFile {
    pub fn new() -> Self {
        Self {
            contents: String::new(),
        }
    }

    pub fn add_file(&mut self, mod_name: &str) {
        use std::fmt::Write;
        writeln!(&mut self.contents, "{mod_name}").expect("erm");
    }
}

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

pub fn generate() -> Result<()> {
    let mut headers = FileTracker::read(&C_INCLUDE_DIR, C_SAVE)?;
    // let mut bindings: FileTracker = FileTracker::read(&RUST_BINDS_DIR, R_SAVE)?;
    let mut mod_dirs: HashSet<PathBuf> = HashSet::new();
    {
        // Check if any headers changed
        for (path, meta) in headers.changed() {
            match meta.change {
                ChangeKind::Created | ChangeKind::Modified => {
                    let out = gen_binds(path)?;
                    if let Some(outp) = out {
                        println!("Generated bindings at {}", outp.to_string_lossy());
                        mod_dirs.insert(outp.parent().unwrap_or(Path::new("/")).into());
                    } else {
                        println!("No bindings for {}, discarding.", path.to_string_lossy());
                    }
                }
                ChangeKind::Deleted => match std::fs::remove_file(path) {
                    Ok(_) => {
                        println!(
                            "Removed corresponding bindings for deleted header: {}",
                            path.to_string_lossy()
                        );
                        // TODO! remove the pub mod
                    }
                    Err(e) => {}
                },
                ChangeKind::Same => {}
            }
        }
        // Save mod.rs files
        for dir in mod_dirs {
            println!("Module directory: {}", dir.to_string_lossy());

            let mut mod_file = fs::File::create(dir.join("mod.rs"))?;

            std::fs::read_dir(&dir)?
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
                    writeln!(&mut mod_file, "pub mod {mod_name};")
                        .expect("Failed to write to mod file");
                });
            // Next check if any rust binding files have changed (maybe by accident idk!)
            // So we can regen them (the ones we havent generated yet)
            // TODO!
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
