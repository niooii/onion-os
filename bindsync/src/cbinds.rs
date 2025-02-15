use std::path::PathBuf;

use anyhow::Result;

use crate::{
    BUILD_DIR, C_INCLUDE_DIR,
    meta::{ChangeKind, Metamap},
};

const SAVE: &str = "headers";

pub struct CBindings {
    include_path: PathBuf,
    mm: Metamap,
}

impl CBindings {
    pub fn new(include_path: &PathBuf) -> Result<Self> {
        let include_path = include_path.into();
        Ok(Self {
            include_path,
            mm: Metamap::read(&C_INCLUDE_DIR, SAVE)?,
        })
    }

    pub fn generate(&mut self) {
        {
            let changed = self.mm.changed();
            for (path, meta) in changed {
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
        }
        self.mm
            .save(SAVE)
            .expect("Bindings have been generated but failed to save metadata");
    }
}
