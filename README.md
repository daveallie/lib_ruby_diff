# LibRubyDiff

[![Build Status](https://travis-ci.org/daveallie/lib_ruby_diff.svg?branch=master)](https://travis-ci.org/daveallie/lib_ruby_diff)

Simple Ruby bindings for librsync.

## Installation

Add this line to your application's Gemfile:

```ruby
gem 'lib_ruby_diff'
```

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install lib_ruby_diff

## Usage

```ruby
require 'lib_ruby_diff'

# Create a signature file
LibRubyDiff.signature(new_file_path, signature_file_path)

# Create a delta file
LibRubyDiff.delta(base_file_path, signature_file_path, delta_file_path)

# Patch base file with delta
LibRubyDiff.patch(new_file_path, delta_file_path, output_new_file_path)

# After running these three commands, the files at
# base_file_path and output_new_file_path should be
# the same.
```

To sync changes from `location_1` to `location_2`, the following must happen:
- Generate a signature on the file at `location_2`
- Use that signature to generate a delta on the file at `location_1`
- Use that delta to apply the changes back onto the file at `location_2`

## Development

After checking out the repo, run `bin/setup` to install dependencies. Then, run `rake` to run the tests. You can also run `bin/console` for an interactive prompt that will allow you to experiment.

To install this gem onto your local machine, run `bundle exec rake install`. To release a new version, update the version number in `version.rb`, and then run `bundle exec rake release`, which will create a git tag for the version, push git commits and tags, and push the `.gem` file to [rubygems.org](https://rubygems.org).

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/daveallie/lib_ruby_diff. This project is intended to be a safe, welcoming space for collaboration, and contributors are expected to adhere to the [Contributor Covenant](http://contributor-covenant.org) code of conduct.

## License

The gem is available as open source under the terms of the [MIT License](http://opensource.org/licenses/MIT).
