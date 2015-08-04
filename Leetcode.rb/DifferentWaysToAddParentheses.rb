#!/usr/bin/env ruby
require 'set'

class Solution
    # designated operators
    OPERATORS = Set.new "+-*".each_char

    # Given an arithmetic expression with +, -, and *, return all possible
    # answers if we ignore order of operations.
    def diff_ways_to_compute(input)
        # base case empty string
        if input.empty?
            return []
        end

        # base case single number
        has_op = false
        input.each_char { |ch|
            if OPERATORS.include? ch
                has_op = true
                break
            end
        }
        if !has_op
            return [input.to_i]
        end

        # for each operator in the expression
        res = []
        0.upto(input.size-1).each { |i| 
            if OPERATORS.include? input[i]
                # split the expression into l and r
                l, r = [input.slice(0, i), input.slice(i+1, input.size)]
                l = diff_ways_to_compute(l)
                r = diff_ways_to_compute(r)
                l.each { |subl| 
                    r.each { |subr| 
                        case input[i]
                        when "+"
                            res.push(subl + subr)
                        when "-"
                            res.push(subl - subr)
                        else
                            res.push(subl * subr)
                        end
                    }
                }
            end
        }
        return res
    end
end

if __FILE__ == $0
    soln = Solution.new
    res = soln.diff_ways_to_compute("2*3-4*5")
    res.each { |k| puts k }
end
