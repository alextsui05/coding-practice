#!/usr/bin/env ruby

require 'test/unit'
require './close_match'

class CloseMatchTest < Test::Unit::TestCase
    def test_close_match
        cm = CloseMatch.new
        expected = File.open('small.out').readlines.map { |line| line.chomp }
        File.open('small.in') do |fp|
            num_examples = fp.readline.to_i
            1.upto(num_examples) do |n|
                s = fp.readline
                s1, s2 = cm.get_score(s)
                res = "Case ##{n}: #{s1} #{s2}"
                assert_equal(res, expected[n-1])
            end
        end
    end
end
