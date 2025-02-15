#[allow(clippy::non_std_lazy_statics)]
mod cbinds;
mod meta;

use std::{
    path::{Path, PathBuf},
    sync::LazyLock,
};

use anyhow::Result;
use walkdir::WalkDir;

use lazy_static::lazy_static;
lazy_static! {
    pub static ref C_INCLUDE_DIR: PathBuf = PathBuf::from("../include");
    pub static ref RUST_DIR: PathBuf = PathBuf::from("../kernel");
    pub static ref RUST_BINDS_DIR: PathBuf = RUST_DIR.join("src/c");
    pub static ref BUILD_DIR: PathBuf = PathBuf::from("../build");
}

fn main() -> Result<()> {
    cbinds::generate()?;

    Ok(())
}
