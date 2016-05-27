#!/usr/bin/env ruby

require 'test/unit'

class Interval
    include Comparable
    attr_accessor :start, :end
    def initialize(s=0, e=0)
        @start = s
        @end = e
    end

    def ==(o)
        if not o.is_a? Interval
            return nil
        end
        @start == o.start and @end == o.end
    end

    def <=>(o)
        if not o.is_a? Interval
            return nil
        end
        if @start < o.start
            return -1
        end
        if @start > o.start
            return 1
        end
        if @end < o.end
            return -1
        end
        if @end > o.end
            return 1
        end
        return 0
    end

    def to_s
        "[#{@start}, #{@end}]"
    end
end

class MergeInterval
    def insert(intervals, new_interval)
        if intervals.empty?
            return intervals.push new_interval
        end

        intervals.sort!
        l = 0
        r = intervals.size
        while l < r
            m = (l + r)/2
            if intervals[m] > new_interval
                r = m
            else
                l = m + 1
            end
        end

        if (l > 0 and intervals[l-1] == new_interval) or
        (l < intervals.size and intervals[l].start == new_interval.start)
            return intervals
        end

        i = -1
        if (l > 0 and intervals[l-1].end == new_interval.start)
            intervals[l-1].end = new_interval.end
            i = l - 1
        else
            intervals.insert(l, new_interval)
            i = l
            l = l + 1
        end

        while l < intervals.size and intervals[l].start <= new_interval.end
            if new_interval.end <= intervals[l].end
                intervals[i].end = intervals[l].end
                intervals.delete_at(l)
                break
            else
                intervals.delete_at(l)
            end
        end
        intervals
    end
end

if __FILE__ == $0
    class MergeIntervalTest < Test::Unit::TestCase
        def setup
            @mi = MergeInterval.new
        end

        def test_eq
            a = Interval.new(1, 2)
            b = Interval.new(1, 2)
            c = Interval.new(1, 3)
            assert_true( a == b )
            assert_false( a == c )
        end

        def test_to_s
            assert_equal "[1, 10]", Interval.new(1, 10).to_s
        end

        def test_sort
            arr = []
            arr.push Interval.new(10, 12)
            arr.push Interval.new(1, 12)
            arr.push Interval.new(1, 1)
            arr.push Interval.new(5, 10)
            arr.push Interval.new(3, 7)
            arr.sort!
            assert_equal arr.shift, Interval.new(1, 1)
            assert_equal arr.shift, Interval.new(1, 12)
            assert_equal arr.shift, Interval.new(3, 7)
            assert_equal arr.shift, Interval.new(5, 10)
            assert_equal arr.shift, Interval.new(10, 12)
        end

        def test_insert
            res = @mi.insert([], Interval.new(1, 2))
            assert_not_equal [], res, "res shouldn't be empty"
            assert_equal [Interval.new(1, 2)], res
        end

        def test_insert_overlap
            res = @mi.insert([Interval.new(1, 2)], Interval.new(1, 2))
            assert_equal [Interval.new(1, 2)], res

            res = @mi.insert(res, Interval.new(2, 3))
            assert_equal [Interval.new(1, 3)], res

            res = @mi.insert(res, Interval.new(0, 4))
            assert_equal [Interval.new(0, 4)], res

            res = @mi.insert(res, Interval.new(5, 7))
            assert_equal [Interval.new(0, 4), Interval.new(5, 7)], res

            res = @mi.insert(res, Interval.new(11, 17))
            assert_equal [Interval.new(0, 4), Interval.new(5, 7), Interval.new(11, 17)], res

            res = @mi.insert(res, Interval.new(8, 16))
            assert_equal [Interval.new(0, 4), Interval.new(5, 7), Interval.new(8, 17)], res

            res = @mi.insert(res, Interval.new(7, 8))
            assert_equal [Interval.new(0, 4), Interval.new(5, 17)], res

            res = @mi.insert([Interval.new(1, 2), Interval.new(10, 30)], Interval.new(7, 8))
            assert_equal [Interval.new(1, 2), Interval.new(7, 8), Interval.new(10, 30)], res

            res = @mi.insert(res, Interval.new(0, 60))
            assert_equal [Interval.new(0, 60)], res
        end
    end
end
