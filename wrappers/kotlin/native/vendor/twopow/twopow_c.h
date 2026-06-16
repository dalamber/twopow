#ifndef TWOPOW_TWOPOW_C_H
#define TWOPOW_TWOPOW_C_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Status codes returned by the twopow C API. */
typedef enum twopow_status {
    TWOPOW_OK = 0,           /* Computation succeeded. */
    TWOPOW_ERR_OVERFLOW = 1, /* Exponent exceeded the supported maximum. */
    TWOPOW_ERR_NULL = 2      /* The output pointer was NULL. */
} twopow_status;

/*
 * Compute 2 raised to the power n.
 *
 * On success, returns TWOPOW_OK and writes 2^n to *out.
 * If n exceeds the supported maximum (see twopow_max_exponent), returns
 * TWOPOW_ERR_OVERFLOW and leaves *out unchanged.
 * If out is NULL, returns TWOPOW_ERR_NULL.
 */
twopow_status twopow_two_pow(unsigned n, uint64_t* out);

/* Return the largest supported exponent (63). */
unsigned twopow_max_exponent(void);

#ifdef __cplusplus
}
#endif

#endif /* TWOPOW_TWOPOW_C_H */
