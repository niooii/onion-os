#![no_std]
mod c;
extern crate alloc;

use core::{
    alloc::{GlobalAlloc, Layout},
    panic::PanicInfo,
};

use alloc::{string::String, vec::Vec};

#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    unsafe {
        c::idt::disable_interrupts();
        c::drivers::vga::vga_print(c"PANIC: ".as_ptr());
        let msg = info.message().as_str().expect("a").as_ptr().cast::<i8>();
        c::drivers::vga::vga_println(msg);
    }
    loop {}
}

// TODO! finish C implementation
struct KernelAllocator;

#[global_allocator]
static ALLOCATOR: KernelAllocator = KernelAllocator;

unsafe impl GlobalAlloc for KernelAllocator {
    unsafe fn alloc_zeroed(&self, layout: Layout) -> *mut u8 {
        todo!()
    }

    unsafe fn realloc(&self, ptr: *mut u8, layout: Layout, new_size: usize) -> *mut u8 {
        todo!()
    }

    unsafe fn alloc(&self, layout: Layout) -> *mut u8 {
        todo!()
    }

    unsafe fn dealloc(&self, ptr: *mut u8, layout: Layout) {
        todo!()
    }
}

#[no_mangle]
pub extern "C" fn kernel_main() -> ! {
    unsafe {
        c::drivers::vga::vga_println(c"HEYH MAN!!! testing yay".as_ptr());
        c::drivers::vga::vga_println(
            c"Some very long\nString that i def want to have in my kernel prints yes ".as_ptr(),
        );
    }
    // This should panic
    let mut something = Vec::<String>::new();
    something.push(String::new());
    // erm,
    loop {}
}
