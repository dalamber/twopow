import CTwopow

/// Deterministic base-2 exponentiation.
public enum Twopow {

    /// The largest supported exponent.
    public static let maxExponent = UInt32(twopow_max_exponent())

    /// An error raised when an exponent exceeds the supported range.
    public enum Error: Swift.Error, Equatable {
        case overflow(exponent: UInt32)
    }

    /// Returns 2 raised to the power `n`.
    ///
    /// - Parameter n: exponent in the closed interval `[0, 63]`.
    /// - Returns: `2^n` as a `UInt64`.
    /// - Throws: `Twopow.Error.overflow` when `n > 63`.
    public static func twoPow(_ n: UInt32) throws -> UInt64 {
        var out: UInt64 = 0
        let status = twopow_two_pow(n, &out)
        if status == TWOPOW_OK {
            return out
        }
        throw Error.overflow(exponent: n)
    }
}
