package io.github.dalamber.twopow

/**
 * Deterministic base-2 exponentiation.
 *
 * The JVM has no unsigned 64-bit type, so [twoPow] of 63 returns `2^63` as the
 * two's-complement bit pattern (`Long.MIN_VALUE`); use
 * `java.lang.Long.toUnsignedString` to render values `>= 2^63`.
 */
object Twopow {

    init {
        NativeLoader.load()
    }

    /** The largest supported exponent. */
    const val MAX_EXPONENT: Int = 63

    /**
     * Returns 2 raised to the power [n].
     *
     * @throws IllegalArgumentException if [n] is negative.
     * @throws ArithmeticException if [n] > 63.
     */
    fun twoPow(n: Int): Long {
        require(n >= 0) { "exponent must be non-negative" }
        return twoPowNative(n)
    }

    @JvmStatic
    private external fun twoPowNative(n: Int): Long
}
