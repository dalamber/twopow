Gem::Specification.new do |s|
  s.name        = 'twopow'
  s.version     = '0.2.0'
  s.summary     = 'Deterministic base-2 exponentiation (native extension).'
  s.description = 'A Ruby binding for the twopow C++ core: 2**n for n in [0, 63].'
  s.authors     = ['Anton Shpakovskiy']
  s.license     = 'Apache-2.0'
  s.homepage    = 'https://github.com/dalamber/twopow'

  s.files       = Dir['lib/**/*.rb'] + Dir['ext/**/*.{c,cpp,h,hpp,rb}']
  s.extensions  = ['ext/twopow/extconf.rb']
  s.require_paths = ['lib']
  s.required_ruby_version = '>= 3.0'

  s.metadata = {
    'source_code_uri' => 'https://github.com/dalamber/twopow',
    'github_repo'     => 'https://github.com/dalamber/twopow'
  }
end
