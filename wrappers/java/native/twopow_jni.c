#include <jni.h>
#include <stdint.h>

#include "twopow/twopow_c.h"

JNIEXPORT jlong JNICALL
Java_io_github_dalamber_twopow_Twopow_twoPowNative(JNIEnv* env, jclass cls,
                                                   jint n) {
    (void)cls;
    uint64_t out = 0;
    const twopow_status status = twopow_two_pow((unsigned)n, &out);
    if (status == TWOPOW_OK) {
        return (jlong)out;
    }
    jclass exception = (*env)->FindClass(env, "java/lang/ArithmeticException");
    if (exception != NULL) {
        (*env)->ThrowNew(
            env, exception,
            "twopow: exponent out of supported range [0, 63]");
    }
    return 0;
}
