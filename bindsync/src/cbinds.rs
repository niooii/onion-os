use std::{
    collections::HashSet,
    fs,
    path::{Path, PathBuf},
};

use anyhow::Result;
use bindgen::{Builder, EnumVariation};

use crate::{
    BUILD_DIR, C_INCLUDE_DIR, RUST_BINDS_DIR,
    meta::{ChangeKind, FileTracker},
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
fn gen_binds(include: &Path) -> Result<PathBuf> {
    let binds = Builder::default()
        .header(include.to_string_lossy().into_owned())
        .clang_arg("-I../include")
        .default_enum_style(EnumVariation::Rust {
            non_exhaustive: false,
        })
        .allowlist_function(".*")
        .use_core()
        .generate()?;

    let out = header_to_rust(include);
    fs::create_dir_all(out.parent().unwrap_or(Path::new("/")))?;

    let file = fs::File::create(&out)?;
    binds.write(Box::new(file))?;
    Ok(out)
}

pub fn generate() -> Result<()> {
    let mut headers = FileTracker::read(&C_INCLUDE_DIR, C_SAVE)?;
    let mut bindings: FileTracker = FileTracker::read(&RUST_BINDS_DIR, R_SAVE)?;
    let mut mod_dirs: HashSet<PathBuf> = HashSet::new();
    {
        // Check if any headers changed
        for (path, meta) in headers.changed() {
            match meta.change {
                ChangeKind::Created | ChangeKind::Modified => {
                    let out = gen_binds(path)?;
                    println!("Generated bindings at {}", out.to_string_lossy());
                    mod_dirs.insert(out.parent().unwrap_or(Path::new("/")).into());
                }
                ChangeKind::Deleted => {
                    println!("deleted: {path:?}");
                }
                ChangeKind::Same => {}
            }
        }
        for dir in mod_dirs {
            println!("Module directory: {}", dir.to_string_lossy());
        }
        // Next check if any rust binding files have changed (maybe by accident idk!)
        // So we can regen them (the ones we havent generated yet)
        // TODO!
    }
    // headers
    //     .save(C_SAVE)
    //     .expect("Bindings have been generated but failed to save metadata");
    // bindings
    //     .save(R_SAVE)
    //     .expect("Bindings have been generated but failed to save metadata");
    Ok(())
}
