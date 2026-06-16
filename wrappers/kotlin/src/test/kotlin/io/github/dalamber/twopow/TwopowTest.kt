package io.github.dalamber.twopow

import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFailsWith

class TwopowTest {

    @Test
    fun computesPowers() {
        assertEquals(1L, Twopow.twoPow(0))
        assertEquals(4L, Twopow.twoPow(2))
        assertEquals(1024L, Twopow.twoPow(10))
        assertEquals(4611686018427387904L, Twopow.twoPow(62))
    }

    @Test
    fun upperBoundaryWraps() {
        assertEquals(Long.MIN_VALUE, Twopow.twoPow(63))
        assertEquals("9223372036854775808", java.lang.Long.toUnsignedString(Twopow.twoPow(63)))
    }

    @Test
    fun overflowThrows() {
        assertFailsWith<ArithmeticException> { Twopow.twoPow(64) }
    }
}
