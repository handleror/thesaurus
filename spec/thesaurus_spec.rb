require 'spec_helper'

describe Thesaurus do
  it 'has a version number' do
    expect(Thesaurus::VERSION).not_to be nil
  end

  describe "Low level API" do
    it "yields matches for a word" do
      headwords = []
      Thesaurus.lookup("bacon") do |match|
        headwords << match.split(",").first
      end

      expect(headwords).to eq(["bacon", "butt", "fat back", "gammon", "ham", "lard", "pig", "pork", "spareribs", "trotter"])
    end

    it "does not yield if a word is not found" do
      Thesaurus.lookup("xyzzy") do |match|
        fail "Yielded #{match}; should not have yielded!"
      end
    end
  end

  describe "High level API" do
    it "returns a list of entries" do
      entries = Thesaurus.lookup("bacon")
      expect(entries.map(&:root)).to eq(["bacon", "butt", "fat back", "gammon", "ham", "lard", "pig", "pork", "spareribs", "trotter"])

      expect(entries.first).to have_attributes(
        root: "bacon",
        words: ["butt","chitterlings","cochon de lait","cracklings","fat back","flitch","gammon","ham","ham steak","haslet","headcheese","jambon","jambonneau","lard","picnic ham","pieds de cochon","pig","pork","porkpie","salt pork","side of bacon","small ham","sowbelly","suckling pig","trotters"]
      )
    end
  end
end
