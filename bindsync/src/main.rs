#![allow(dead_code)]
#[allow(clippy::non_std_lazy_statics)]
mod c_binds;
mod rust_binds;
mod tracker;

use std::path::PathBuf;

use anyhow::Result;

use lazy_static::lazy_static;
lazy_static! {
    pub static ref C_INCLUDE_DIR: PathBuf = PathBuf::from("../include");
    pub static ref RUST_DIR: PathBuf = PathBuf::from("../kernel");
    pub static ref RUST_BINDS_DIR: PathBuf = RUST_DIR.join("src/c");
    pub static ref BUILD_DIR: PathBuf = PathBuf::from("../build");
}

fn main() -> Result<()> {
    c_binds::generate()?;

    Ok(())
}
