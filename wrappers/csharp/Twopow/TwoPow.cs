using System;
using System.Runtime.InteropServices;

namespace Dalamber.Twopow;

/// <summary>Deterministic base-2 exponentiation.</summary>
public static class TwoPow
{
    /// <summary>The largest supported exponent.</summary>
    public const int MaxExponent = 63;

    [DllImport("twopow_ffi", EntryPoint = "twopow_two_pow")]
    private static extern int NativeTwoPow(uint n, out ulong result);

    /// <summary>Returns 2 raised to the power <paramref name="n"/>.</summary>
    /// <param name="n">Exponent in the closed interval [0, 63].</param>
    /// <returns>2^n.</returns>
    /// <exception cref="OverflowException">Thrown when n &gt; 63.</exception>
    public static ulong Compute(uint n)
    {
        int status = NativeTwoPow(n, out ulong result);
        if (status != 0)
        {
            throw new OverflowException(
                $"twopow: exponent {n} exceeds maximum {MaxExponent}");
        }
        return result;
    }
}
