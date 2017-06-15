require 'ReverseVowelsOfAString'

describe 'reverse_vowels' do
  it 'reverses the vowels in a string' do
    expect(reverse_vowels("aeiou")).to eq "uoiea"
  end
end
