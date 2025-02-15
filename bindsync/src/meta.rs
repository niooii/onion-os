use std::{
    collections::HashMap,
    fs::{File, FileType},
    io::{BufReader, Read, Write},
    os::unix::fs::MetadataExt,
    path::{Path, PathBuf},
};

use serde::{Deserialize, Serialize};
use std::io::Result;
use walkdir::WalkDir;

use crate::{BUILD_DIR, C_INCLUDE_DIR};

#[derive(Deserialize, Serialize)]
pub struct Metadata {
    hash: String,
    #[serde(skip, default = "Default::default")]
    pub change: ChangeKind,
}

#[derive(Deserialize, Serialize)]
#[serde(transparent)]
pub struct Metamap {
    map: HashMap<PathBuf, Metadata>,
}

#[derive(PartialEq, Eq, Deserialize, Serialize)]
pub enum ChangeKind {
    Same,
    Modified,
    Created,
    // Idea is that by default everything is Deleted so when if i didnt visit it
    // at all while iterating thru the dir then it is gone.
    Deleted,
}

impl Default for ChangeKind {
    fn default() -> Self {
        Self::Deleted
    }
}

impl Metamap {
    fn save_name_to_path(save_name: &str) -> PathBuf {
        BUILD_DIR.join(format!("{save_name}.meta"))
    }

    /// Gets the metadata for the specified file.
    fn get_meta(&mut self, path: &Path) -> Option<&mut Metadata> {
        self.map.get_mut(path)
    }

    fn hash(path: &Path) -> Result<String> {
        let mut md5 = md5::Context::new();
        md5.write_all(&std::fs::read(path)?)?;
        md5.flush()?;
        Ok(format!("{:X}", md5.compute()))
    }

    /// Returns one if it exists, creates a new one if it doesn't.
    /// Despite the name, most of the actual processing is done here.
    pub fn read(files_dir: &Path, save_name: &str) -> Result<Self> {
        let path = Self::save_name_to_path(save_name);

        let mut mm: Metamap =
            { serde_json::from_str(&std::fs::read_to_string(path).unwrap_or("{}".into()))? };

        // TODO! vporocess changes
        for entry in WalkDir::new(files_dir) {
            let e = entry.expect("Couldn't read file");
            if e.file_type().is_dir() {
                continue;
            }

            if let Some(stored_meta) = mm.get_meta(e.path()) {
                let hash = Self::hash(e.path())?;
                if hash == stored_meta.hash {
                    stored_meta.change = ChangeKind::Same;
                } else {
                    stored_meta.hash = hash;
                    stored_meta.change = ChangeKind::Modified;
                }
            } else {
                let hash = Self::hash(e.path())?;

                mm.map.insert(
                    e.path().to_path_buf(),
                    Metadata {
                        hash,
                        change: ChangeKind::Created,
                    },
                );
            }
        }

        Ok(mm)
    }

    pub fn save(&mut self, save_name: &str) -> Result<()> {
        let path = Self::save_name_to_path(save_name);
        std::fs::create_dir_all(path.parent().expect("Root???"))?;
        self.map.retain(|p, m| m.change != ChangeKind::Deleted);
        std::fs::write(&path, serde_json::to_string(&self)?)?;
        Ok(())
    }

    /// Returns an iterator over all the files that have changed since the last time this was called.
    pub fn changed(&self) -> impl Iterator<Item = (&std::path::PathBuf, &Metadata)> {
        self.map
            .iter()
            .filter(|(_path, meta)| meta.change != ChangeKind::Same)
    }
}
