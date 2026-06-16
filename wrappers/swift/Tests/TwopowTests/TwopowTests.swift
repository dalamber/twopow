import XCTest

@testable import Twopow

final class TwopowTests: XCTestCase {
    func testComputesPowers() throws {
        XCTAssertEqual(try Twopow.twoPow(0), 1)
        XCTAssertEqual(try Twopow.twoPow(2), 4)
        XCTAssertEqual(try Twopow.twoPow(10), 1024)
        XCTAssertEqual(try Twopow.twoPow(63), 9_223_372_036_854_775_808)
    }

    func testMaxExponent() {
        XCTAssertEqual(Twopow.maxExponent, 63)
    }

    func testOverflowThrows() {
        XCTAssertThrowsError(try Twopow.twoPow(64)) { error in
            XCTAssertEqual(error as? Twopow.Error, .overflow(exponent: 64))
        }
    }
}
