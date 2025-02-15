use std::path::PathBuf;

use anyhow::Result;

use crate::{
    BUILD_DIR, C_INCLUDE_DIR, RUST_BINDS_DIR,
    meta::{ChangeKind, FileTracker},
};

const C_SAVE: &str = "cb_headers";
const R_SAVE: &str = "r_binds";

pub fn generate() -> Result<()> {
    let mut headers = FileTracker::read(&C_INCLUDE_DIR, C_SAVE)?;
    let mut bindings: FileTracker = FileTracker::read(&RUST_BINDS_DIR, R_SAVE)?;
    {
        // Check if any headers changed
        for (path, meta) in headers.changed() {
            match meta.change {
                ChangeKind::Created => {
                    println!("created: {path:?}");
                }
                ChangeKind::Modified => {
                    println!("modified: {path:?}");
                }
                ChangeKind::Deleted => {
                    println!("deleted: {path:?}");
                }
                ChangeKind::Same => {}
            }
        }
        // Next check if any rust binding files have changed (maybe by accident idk!)
        // So we can regen them
        for (path, meta) in bindings.changed() {
            match meta.change {
                ChangeKind::Created => {
                    println!("r created: {path:?}");
                }
                ChangeKind::Modified => {
                    println!("r modified: {path:?}");
                }
                ChangeKind::Deleted => {
                    println!("r deleted: {path:?}");
                }
                ChangeKind::Same => {}
            }
        }
    }
    headers
        .save(C_SAVE)
        .expect("Bindings have been generated but failed to save metadata");
    bindings
        .save(R_SAVE)
        .expect("Bindings have been generated but failed to save metadata");
    Ok(())
}
