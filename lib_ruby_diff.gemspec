# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'lib_ruby_diff/version'

Gem::Specification.new do |spec|
  spec.name          = 'lib_ruby_diff'
  spec.version       = LibRubyDiff::VERSION
  spec.authors       = ['Dave Allie']
  spec.email         = ['dave@daveallie.com']

  spec.summary       = 'Ruby bindings for librsync core methods.'
  spec.description   = 'Ruby bindings for librsync signature generation,' \
                       ' patch generation, and patch application methods.'
  spec.homepage      = 'https://github.com/daveallie/lib_ruby_diff'
  spec.license       = 'MIT'

  spec.files         = `git ls-files -z`.split("\x0").reject { |f| f.match(%r{^(test|spec|features)/}) }
  spec.bindir        = 'exe'
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ['lib']
  spec.extensions    = ['ext/lib_ruby_diff/extconf.rb']

  spec.add_development_dependency 'bundler', '~> 1.12'
  spec.add_development_dependency 'rake', '~> 10.0'
  spec.add_development_dependency 'rake-compiler', '~> 1.0'
  spec.add_development_dependency 'rspec', '~> 3.0'
  spec.add_development_dependency 'rubocop', '~> 0.46'
end
