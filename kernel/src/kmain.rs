#![no_std]
#![no_main]

use core::panic::PanicInfo;

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}

#[no_mangle]
pub extern "C" fn add_2(x: i32) -> i32 {
    x + 2
}
extern "C" {
    static cpos: *mut u16;
}
extern "C" {
    fn idt_load();
    fn idt_init();
    fn vga_print(s: &[u8]);
}

#[no_mangle]
pub extern "C" fn kernel_main() -> ! {
    unsafe {
        vga_print(b"hey man TESTING!!\0");
        *(0xb8000 as *mut u8) = 65; // ASCII for 'A'
        *(0xb8001 as *mut u8) = 0x0F;
    }
    loop {}
}
