#![no_std]
#![no_main]

use core::panic::PanicInfo;

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}

extern "C" {
    fn cinit();
    fn vga_print(s: *const i8);
}

#[no_mangle]
pub extern "C" fn kernel_main() -> ! {
    unsafe {
        cinit();
        vga_print(c"hey man TESTING!!".as_ptr());
    }
    // erm,
    loop {}
}
