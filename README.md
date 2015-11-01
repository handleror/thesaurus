# Thesaurus

Look up English words in a thesaurus.

The thesaurus included is Grady Ward's [Moby Project](http://icon.shef.ac.uk/Moby/mthes.html).

## Installation

Add this line to your application's Gemfile:

```ruby
gem 'thesaurus'
```

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install thesaurus

## Usage

`Thesarus.lookup(word)`: return a list of thesaurus entries that contain the word, either as their root or in the body.

`entry.root`: The root word (as a `String`)

`entry.words`: The entry body, as an array of `String`.

```ruby
require 'thesaurus'

entries = Thesaurus.lookup("bacon")
entries.each do |entry|
  puts "Root word: #{entry.root}"
  puts "Words: #{entry.words.join(", ")}"
end
```


## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/pbevin/thesaurus.


## License

The gem is available as open source under the terms of the [MIT License](http://opensource.org/licenses/MIT).

