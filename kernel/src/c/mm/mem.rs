unsafe extern "C" {
    pub fn memset(
        dest: *mut ::core::ffi::c_void,
        c: ::core::ffi::c_int,
        n: ::core::ffi::c_ulong,
    ) -> *mut ::core::ffi::c_void;
}
unsafe extern "C" {
    pub fn memmove(
        dest: *mut ::core::ffi::c_void,
        src: *const ::core::ffi::c_void,
        n: ::core::ffi::c_ulong,
    ) -> *mut ::core::ffi::c_void;
}
unsafe extern "C" {
    pub fn memcpy(
        dest: *mut ::core::ffi::c_void,
        src: *const ::core::ffi::c_void,
        n: ::core::ffi::c_ulong,
    ) -> *mut ::core::ffi::c_void;
}
