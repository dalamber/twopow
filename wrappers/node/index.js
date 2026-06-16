'use strict';

const native = require('./build/Release/twopow.node');

/**
 * Returns 2 ** n as a BigInt, for n in [0, 63].
 * Throws RangeError when n exceeds 63.
 * @param {number} n
 * @returns {bigint}
 */
function twoPow(n) {
  return native.twoPow(n);
}

module.exports = {
  twoPow,
  MAX_EXPONENT: native.MAX_EXPONENT,
};
