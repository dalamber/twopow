# twopow for Ruby

A native C-extension gem wrapping the `twopow` C++ core (compiled from vendored
source on install). Published to GitHub Packages (RubyGems).

## Install

```bash
gem install twopow --source "https://rubygems.pkg.github.com/dalamber"
```

Building the extension requires a C++ toolchain.

## Use

```ruby
require 'twopow'

Twopow.two_pow(10)     # => 1024
Twopow::MAX_EXPONENT   # => 63
Twopow.two_pow(64)     # raises RangeError
```

Results are Ruby Integers (arbitrary precision), so `two_pow(63)` is exact.

## Test locally

```bash
cd wrappers/ruby/ext/twopow && ruby extconf.rb && make
cd ../../ && ruby -I lib -I ext/twopow test/test_twopow.rb
```
