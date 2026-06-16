'use strict';

const assert = require('assert');
const twopow = require('..');

assert.strictEqual(twopow.twoPow(0), 1n);
assert.strictEqual(twopow.twoPow(2), 4n);
assert.strictEqual(twopow.twoPow(10), 1024n);
assert.strictEqual(twopow.twoPow(63), 9223372036854775808n);
assert.strictEqual(twopow.MAX_EXPONENT, 63);
assert.throws(() => twopow.twoPow(64), RangeError);

console.log('node binding OK');
