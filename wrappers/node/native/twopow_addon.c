#include <node_api.h>
#include <stdint.h>

#include "twopow/twopow_c.h"

static napi_value TwoPow(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    uint32_t n = 0;
    napi_get_value_uint32(env, args[0], &n);

    uint64_t out = 0;
    const twopow_status status = twopow_two_pow((unsigned)n, &out);
    if (status != TWOPOW_OK) {
        napi_throw_range_error(env, NULL,
                               "twopow: exponent exceeds supported maximum 63");
        return NULL;
    }

    napi_value result;
    napi_create_bigint_uint64(env, out, &result);
    return result;
}

static napi_value Init(napi_env env, napi_value exports) {
    napi_value fn;
    napi_create_function(env, NULL, 0, TwoPow, NULL, &fn);
    napi_set_named_property(env, exports, "twoPow", fn);

    napi_value max_exponent;
    napi_create_uint32(env, twopow_max_exponent(), &max_exponent);
    napi_set_named_property(env, exports, "MAX_EXPONENT", max_exponent);

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
