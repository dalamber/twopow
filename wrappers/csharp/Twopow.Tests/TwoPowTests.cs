using System;
using Dalamber.Twopow;
using Xunit;

public class TwoPowTests
{
    [Theory]
    [InlineData(0u, 1ul)]
    [InlineData(2u, 4ul)]
    [InlineData(10u, 1024ul)]
    [InlineData(63u, 9223372036854775808ul)]
    public void Computes(uint n, ulong expected)
    {
        Assert.Equal(expected, TwoPow.Compute(n));
    }

    [Fact]
    public void OverflowThrows()
    {
        Assert.Throws<OverflowException>(() => TwoPow.Compute(64));
    }
}
