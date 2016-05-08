#!/usr/bin/env ruby

require 'test/unit'

# Return the maximum product of multiplying a set of at least two numbers that
# add up to n.
class IntegerBreak
    def initialize
        @memo = Hash.new(0)
    end

    # Use memoization to compute the integer break.
    #
    # Suppose T(n) be the integer break for integer n. This recursion gives the
    # solution:
    #
    # T(2) = 1
    # T(n) = max_{i = 1...n-1} { i * T(n - i) }
    #
    # This gives an O(n) space, O(n^2) time solution.
    def integer_break(n)
        if n < 2
            return 1
        end
        if @memo.include? n
            return @memo[n]
        end
        hi = (n % 2 == 0)? (n/2)**2 : (n/2)*(n/2 + 1)
        1.upto(n-1) do |i|
            hi = [hi, i * integer_break(n-i)].max
        end
        @memo[n] = hi
        return hi
    end
end

class IntegerBreakTest < Test::Unit::TestCase
    def test_integer_break
        ib = IntegerBreak.new
        assert_equal(1, ib.integer_break(2))
        assert_equal(36, ib.integer_break(10))
        2.upto(10) do |i|
            puts ib.integer_break(i)
        end
    end
end
