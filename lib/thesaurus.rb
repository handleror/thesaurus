require "thesaurus/version"
require "thesaurus/thesaurus"

module Thesaurus
  extend self

  def self.lookup(word, &block)
    @dict ||= File.join(__dir__, "words.txt")

    if block_given?
      _lookup(word, &block)
    else
      to_enum("_lookup", word).map { |line| parse(line) }
    end
  end

  def parse(line)
    root, *words = line.split(",")
    Entry.new(root, words)
  end


  class Entry
    def initialize(root, words)
      @root = root
      @words = words
    end

    attr_reader :root, :words
  end
end
