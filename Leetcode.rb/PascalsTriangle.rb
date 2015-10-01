# Generate the first num_rows of Pascal's triangle.
#
# The approach is direct: iterate the rows from top to bottom, filling in the
# entries. We apply the definition
#
#   a[row][col] = a[row - 1][col - 1] + a[row - 1][col].
#
# Taking care to replace out-of-bounds lookups with zeroes instead.
#
# The runtime and space complexity is n^2 in the number of rows.
#
# @param {Integer} num_rows
# @return {Integer[][]}
def generate(num_rows)
    res = []
    0.upto(num_rows-1) do |i|
        if i == 0
            res.push([1])
            next
        end
        row = []
        0.upto(i) do |j|
            entry = 0
            if j - 1 >= 0
                entry += res[i-1][j-1]
            end
            if j < i
                entry += res[i-1][j]
            end
            row.push(entry)
        end
        res.push(row)
    end
    res
end

if __FILE__ == $0
    res = generate(Integer(ARGV[0]))
    res.each { |row| 
        puts row.join(' ')
    }
end
