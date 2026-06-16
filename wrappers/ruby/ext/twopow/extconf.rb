require 'mkmf'

ext_dir = __dir__
$INCFLAGS << " -I#{File.join(ext_dir, 'vendor')}"
$CXXFLAGS << ' -std=c++20'

# Compile the C extension shim plus the vendored C++ core.
$srcs = %w[twopow_ext.c csrc_twopow.cpp csrc_twopow_c.cpp]
$objs = %w[twopow_ext.o csrc_twopow.o csrc_twopow_c.o]

# Link the C++ standard library (the core is C++).
$LIBS << (RUBY_PLATFORM =~ /darwin/ ? ' -lc++' : ' -lstdc++')

create_makefile('twopow_ext')
