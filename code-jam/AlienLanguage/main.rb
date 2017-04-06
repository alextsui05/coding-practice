# Convert a alien word into a bit list representation.
# Each item in the bit list is a bitfield that represents a single letter if it
# contains a single 1-bit, or the possible letters if multiple bits are on.
# 
# Complexity: O(L) where L is the length of the word.
# We make a single pass through the characters of the word to build the bit list.
def to_bit_list(word)
    i = 0
    bit_list = []
    while i < word.size
        if word[i] == ')'
            i = i + 1
            next
        elsif word[i] == '('
            i = i + 1
            entry = 0
            while word[i] != ')'
                ch = word[i].each_byte.to_a[0] - 'a'.each_byte.to_a[0]
                entry |= (1 << ch)
                i = i + 1
            end
            #puts entry.to_s(2)
            bit_list.push(entry)
        else # single char
            ch = word[i].each_byte.to_a[0] - 'a'.each_byte.to_a[0]
            entry = (1 << ch)
            bit_list.push(entry)
            #puts entry.to_s(2)
            i = i + 1
        end
    end
    bit_list
end

# Count the number of entries in the dictionary dict that can possibly match
# the query.
#
# Complexity: O(L*D)
# L - length of a word
# D - number of entries in the dictionary
# For each dictionary word, we do a bitwise AND of the word with the query,
# with an early exit if all bits are zero.
def count( query, dict )
    res = 0
    dict.each do |word|
        0.upto(word.size - 1) do |i|
            if (word[i] & query[i]) == 0
                break
            end
            if i == word.size - 1
                res = res + 1
            end
        end
    end
    res
end

if __FILE__ == $0
    L, D, N = ARGF.readline.split.map { |x| x.to_i }
    #puts L, D, N
    dict = []
    1.upto(D) do |d|
        word = ARGF.readline.chomp
        #puts word
        dict.push( to_bit_list(word) )
    end
    1.upto(N) do |n|
        query = to_bit_list( ARGF.readline.chomp )
        #puts query.to_s
        res = count( query, dict )
        puts "Case ##{n}: #{res}"
    end
end
