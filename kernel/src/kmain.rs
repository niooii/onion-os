#![no_std]
mod binds;

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
        binds::vga_print(c"HEYH MAN!!!".as_ptr());
        for n in 0..10 {
            binds::vga_print(format!("{}"));
        }
    }

    // erm,
    loop {}
}
