# Reverse the vowels of a string.
#
# Find the position of the vowels and then reverse that subsequence -- O(n)
# time and space.
#
# One thing that got me was the vowels are case-sensitive.
#
# @param {String} s
# @return {String}
def reverse_vowels(s)
    vowel_positions = s.each_char.each_with_index.to_a.find_all do |e|
        "aeiouAEIOU".include? e[0]
    end.map { |e| e[1] }
    if vowel_positions.size == 0
        return s
    end
    i, j = 0, vowel_positions.size - 1
    while i < j do
        ii = vowel_positions[i]
        jj = vowel_positions[j]
        s[ii], s[jj] = s[jj], s[ii]
        i = i + 1
        j = j - 1
    end
    s
end
