pub type bool_ = u8;
unsafe extern "C" {
    pub fn vga_print(str_: *const ::core::ffi::c_char);
}
unsafe extern "C" {
    pub fn vga_println(str_: *const ::core::ffi::c_char);
}
unsafe extern "C" {
    pub fn vga_putchar(c: ::core::ffi::c_char);
}
unsafe extern "C" {
    pub fn vga_delchar();
}
unsafe extern "C" {
    pub fn vga_clear();
}
unsafe extern "C" {
    pub fn vga_cset(active: bool_);
}
unsafe extern "C" {
    pub fn vga_cpos(x: u8, y: u8);
}
