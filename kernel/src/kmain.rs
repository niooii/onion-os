#![no_std]
mod c;

use core::panic::PanicInfo;

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}

extern "C" {
    fn cinit();
}

#[no_mangle]
pub extern "C" fn kernel_main() -> ! {
    unsafe {
        cinit();
        c::drivers::vga::vga_print(c"HEYH MAN!!! testing yay".as_ptr());
    }

    // erm,
    loop {}
}
