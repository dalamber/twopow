#include <ruby.h>
#include <stdint.h>

#include "twopow/twopow_c.h"

static VALUE rb_two_pow(VALUE self, VALUE n_val) {
    (void)self;
    const unsigned n = NUM2UINT(n_val);
    uint64_t out = 0;
    const twopow_status status = twopow_two_pow(n, &out);
    if (status != TWOPOW_OK) {
        rb_raise(rb_eRangeError,
                 "twopow: exponent exceeds supported maximum 63");
    }
    return ULL2NUM((unsigned long long)out);
}

void Init_twopow_ext(void) {
    VALUE mod = rb_define_module("Twopow");
    rb_define_singleton_method(mod, "two_pow", rb_two_pow, 1);
    rb_define_const(mod, "MAX_EXPONENT", UINT2NUM(twopow_max_exponent()));
}
