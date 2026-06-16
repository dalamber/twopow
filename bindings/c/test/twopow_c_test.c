#include "twopow/twopow_c.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
    uint64_t out = 0;

    assert(twopow_two_pow(0, &out) == TWOPOW_OK && out == UINT64_C(1));
    assert(twopow_two_pow(2, &out) == TWOPOW_OK && out == UINT64_C(4));
    assert(twopow_two_pow(10, &out) == TWOPOW_OK && out == UINT64_C(1024));
    assert(twopow_two_pow(63, &out) == TWOPOW_OK &&
           out == UINT64_C(9223372036854775808));
    assert(twopow_two_pow(64, &out) == TWOPOW_ERR_OVERFLOW);
    assert(twopow_two_pow(10, NULL) == TWOPOW_ERR_NULL);
    assert(twopow_max_exponent() == 63u);

    printf("C API OK\n");
    return 0;
}
