package io.github.dalamber.twopow;

/**
 * Deterministic base-2 exponentiation.
 *
 * <p>Java has no unsigned 64-bit integer type. Results in {@code [0, 2^62]} fit
 * in a positive {@code long}; {@code twoPow(63)} returns {@code 2^63} as its
 * two's-complement bit pattern ({@link Long#MIN_VALUE}). Use
 * {@link Long#toUnsignedString(long)} to render such values.
 */
public final class Twopow {

    static {
        NativeLoader.load();
    }

    private Twopow() {}

    /** The largest supported exponent. */
    public static final int MAX_EXPONENT = 63;

    /**
     * Returns 2 raised to the power {@code n}.
     *
     * @param n exponent in the closed interval {@code [0, 63]}
     * @return {@code 2^n} (as an unsigned 64-bit value held in a {@code long})
     * @throws IllegalArgumentException if {@code n} is negative
     * @throws ArithmeticException if {@code n > 63}
     */
    public static long twoPow(int n) {
        if (n < 0) {
            throw new IllegalArgumentException("exponent must be non-negative");
        }
        return twoPowNative(n);
    }

    private static native long twoPowNative(int n);
}
