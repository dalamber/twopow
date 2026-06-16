require 'minitest/autorun'
require 'twopow'

class TwopowTest < Minitest::Test
  def test_powers
    assert_equal 1, Twopow.two_pow(0)
    assert_equal 4, Twopow.two_pow(2)
    assert_equal 1024, Twopow.two_pow(10)
    assert_equal 9_223_372_036_854_775_808, Twopow.two_pow(63)
  end

  def test_max_exponent
    assert_equal 63, Twopow::MAX_EXPONENT
  end

  def test_overflow
    assert_raises(RangeError) { Twopow.two_pow(64) }
  end
end
