unsafe extern "C" {
    pub fn memset(
        dest: *mut ::core::ffi::c_void,
        c: ::core::ffi::c_int,
        n: ::core::ffi::c_ulong,
    ) -> *mut ::core::ffi::c_void;
}
