#!/usr/bin/env ruby

# Given a matrix of ints with the properties that:
#   1. The rows are sorted left to right
#   2. The columns are sorted top to bottom
# Return whether \a target is in \a matrix.
def search_matrix(matrix, target)
    if matrix.empty?
        return false
    end

    col_width = matrix.size
    row_width = matrix[0].size
    outer_l = 0
    outer_r = row_width - 1
    while outer_l <= outer_r do
        outer_mid = (outer_l + outer_r) / 2
        if target == matrix[0][outer_mid]
            return true
        elsif target < matrix[0][outer_mid]
            outer_r = outer_mid - 1
        else
            outer_l = outer_mid + 1
        end
    end

    # if outer_r == -1
    if outer_l == 0
        return false
    end

    # outer_r and it is a valid index
    outer_r.downto(0) do |outer_mid|
        inner_l = 0
        inner_r = col_width - 1
        while inner_l <= inner_r do
            inner_mid = (inner_l + inner_r) / 2
            if target == matrix[inner_mid][outer_mid]
                return true
            elsif target < matrix[inner_mid][outer_mid]
                inner_r = inner_mid - 1
            else
                inner_l = inner_mid + 1
            end
        end
    end

    return false
end

DATA = [
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]

DATA2 = [[1,3,5,7,9],[2,4,6,8,10],[11,13,15,17,19],[12,14,16,18,20],[21,22,23,24,25]]

if __FILE__ == $0

    DATA.each do |row|
        row.each do |val|
            print " #{val}"
        end
        puts
    end

    puts search_matrix(DATA, 4)
    puts search_matrix(DATA, 5)
    puts search_matrix(DATA, 20)
    puts search_matrix(DATA2, 13)
end
