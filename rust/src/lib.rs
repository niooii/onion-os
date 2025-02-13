#![no_std]
#![feature(fn_align)]

use core::panic::PanicInfo;

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}

#[no_mangle]
#[repr(align(16))]
pub extern "C" fn add_2(x: i32) -> i32 {
    x + 2
}
