#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct test_thing {
    pub field: ::core::ffi::c_int,
}
#[allow(clippy::unnecessary_operation, clippy::identity_op)]
const _: () = {
    ["Size of test_thing"][::core::mem::size_of::<test_thing>() - 4usize];
    ["Alignment of test_thing"][::core::mem::align_of::<test_thing>() - 4usize];
    ["Offset of field: test_thing::field"][::core::mem::offset_of!(test_thing, field) - 0usize];
};
unsafe extern "C" {
    pub fn do_thing(t: test_thing);
}
unsafe extern "C" {
    pub fn idt_set(i: ::core::ffi::c_int, addr: *mut ::core::ffi::c_void);
}
unsafe extern "C" {
    pub fn idt_init();
}
unsafe extern "C" {
    pub fn idt_load();
}
unsafe extern "C" {
    pub fn disable_interrupts();
}
unsafe extern "C" {
    pub fn enable_interrupts();
}
