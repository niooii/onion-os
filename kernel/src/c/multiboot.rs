unsafe extern "C" {
    pub fn some_callback(
        callback: ::core::option::Option<
            unsafe extern "C" fn(
                arg1: ::core::ffi::c_int,
                arg2: ::core::ffi::c_int,
            ) -> ::core::ffi::c_int,
        >,
    );
}
