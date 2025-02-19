unsafe extern "C" {
    pub fn malloc(size: ::core::ffi::c_uint) -> *mut ::core::ffi::c_void;
}
unsafe extern "C" {
    pub fn realloc(
        block: *mut ::core::ffi::c_void,
        new: ::core::ffi::c_uint,
    ) -> *mut ::core::ffi::c_void;
}
unsafe extern "C" {
    pub fn free(block: *mut ::core::ffi::c_void);
}
