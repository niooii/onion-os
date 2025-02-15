unsafe extern "C" {
    pub fn inb(port: u16) -> u8;
}
unsafe extern "C" {
    pub fn inw(port: u16) -> u16;
}
unsafe extern "C" {
    pub fn outb(port: u16, val: u8);
}
unsafe extern "C" {
    pub fn outw(port: u16, val: u16);
}
