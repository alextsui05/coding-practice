# @param {Integer[]} digits
# @return {Integer[]}
def plus_one(digits)
    res = digits.join.to_i + 1
    res.to_s.chars.map { |d| Integer(d) }
end

if __FILE__ == $0
    input = ARGV[0].chars.map { |d| Integer(d) }
    puts plus_one(input)
end
