package io.github.dalamber.twopow;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

public class TwopowTest {

    @Test
    public void computesPowers() {
        assertEquals(1L, Twopow.twoPow(0));
        assertEquals(4L, Twopow.twoPow(2));
        assertEquals(1024L, Twopow.twoPow(10));
        assertEquals(4611686018427387904L, Twopow.twoPow(62));
    }

    @Test
    public void upperBoundaryWrapsToUnsigned() {
        // 2^63 does not fit a positive signed long; it is the bit pattern of
        // Long.MIN_VALUE. toUnsignedString recovers the decimal value.
        assertEquals(Long.MIN_VALUE, Twopow.twoPow(63));
        assertEquals("9223372036854775808",
            Long.toUnsignedString(Twopow.twoPow(63)));
    }

    @Test(expected = ArithmeticException.class)
    public void overflowThrows() {
        Twopow.twoPow(64);
    }

    @Test(expected = IllegalArgumentException.class)
    public void negativeThrows() {
        Twopow.twoPow(-1);
    }
}
