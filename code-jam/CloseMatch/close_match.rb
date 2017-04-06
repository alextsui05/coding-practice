#!/usr/bin/env ruby

# Give a pair of scores that minimize the absolute difference.
#
# This solves the small input (3 digits long) by enumerating all possible pairs
# of scores in the appropriate order.
#
# The worst case is we examine a million pairs of numbers.
class CloseMatch
    def get_score(s)
        s1, s2 = s.split
        possible1 = candidates(s1)
        possible2 = candidates(s2)
        lo = 9999
        possible1.each { |i|
            possible2.each { |j|
                diff = (i.to_i - j.to_i).abs
                if diff < lo
                    lo = diff
                    s1, s2 = i, j
                end
            }
        }
        return s1, s2
    end

    # Create a list of candidates, given a partial score.
    def candidates(s)
        res = []
        candidates_helper(s, 0, res)
        res
    end

    # Use backtracking to generate candidate numbers and store them in a list.
    def candidates_helper(s, i, arr)
        if s[i] == '?'
            0.upto(9) do |k|
                s[i] = k.to_s
                if i == s.size - 1
                    arr.push(s.clone)
                else
                    candidates_helper(s, i+1, arr)
                end
            end
            s[i] = '?'
        else
            if i == s.size - 1
                arr.push(s.clone)
            else
                candidates_helper(s, i+1, arr)
            end
        end
    end
end

if __FILE__ == $0
    cm = CloseMatch.new
    N = ARGF.readline.to_i
    1.upto(N) do |n|
        s = ARGF.readline
        s1, s2 = cm.get_score(s)
        puts "Case ##{n}: #{s1} #{s2}"
    end
end
