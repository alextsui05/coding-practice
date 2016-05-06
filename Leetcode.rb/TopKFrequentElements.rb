#!/usr/bin/env ruby
#
require 'test/unit'

# Return the top k most frequently occurring elements in a list of integers.
#
# The approach is to tally up the occurrences in a hash, then turning the hash
# into a heap sorted by frequency, and finally extracting k elements from the
# top of the heap.
# The approach is not necessarily O(n) complexity, but it does better than 
# O(n log n) for a list of n integers.
#
class TopKFrequentElements
    def most_frequent(arr, k)
        # Tally up the integers and convert to array representation in linear time
        counts = arr.each_with_object(Hash.new(0)) { |val, obj| obj[val] += 1 }.each_entry.to_a

        # Sort by most frequent, then break ties by smallest integer
        cmp = lambda { |x, y| (x[1] < y[1]) or (x[1] == y[1] and x[0] > y[0]) }

        # Build the heap -- in linear time
        build_heap(counts, cmp)

        res = []
        1.upto(k) do
            # extract_max is O(log n) where n is the size of the heap, but each
            # time it decreases the size of the heap by 1, so you have a sum that is
            # bounded above by O(n log n).
            x = extract_max(counts, cmp)
            res.push x
        end
    end

    def extract_max(heap, cmp)
        res = heap[0][0]
        heap[0], heap[heap.size-1] = heap[heap.size-1], heap[0]
        heap.pop
        heapify(0, heap, cmp)
        res
    end

    def build_heap(arr, cmp)
        n = arr.size / 2
        n.downto(0) do |i|
            heapify(i, arr, cmp)
        end
    end

    def heapify(i, arr, cmp)
        l = left(i)
        r = right(i)
        if l >= arr.size and r >= arr.size
            return
        end
        if r >= arr.size 
            if cmp.call(arr[i], arr[l])
                arr[i], arr[l] = arr[l], arr[i]
                heapify(l, arr, cmp)
            end
        else
            if cmp.call(arr[i], arr[l]) and cmp.call(arr[r], arr[l])
                arr[i], arr[l] = arr[l], arr[i]
                heapify(l, arr, cmp)
            end
            if cmp.call(arr[i], arr[r]) and cmp.call(arr[l], arr[r])
                arr[i], arr[r] = arr[r], arr[i]
                heapify(r, arr, cmp)
            end
        end
    end

    def height(heap)
        n = heap.size
        h = 0
        i = 0
        while left(i) < n do
            h += 1
            i = left(i)
        end
        h
    end

    def left(i)
        2*i + 1
    end

    def right(i)
        2*i + 2
    end
end

class TopKFrequentElementsTest < Test::Unit::TestCase
    def test_most_frequent
        input = [1,1,1,2,2,3]
        expected = [1,2]
        soln = TopKFrequentElements.new
        res = soln.most_frequent(input, 2)
        assert_equal(expected, res)

        input = [2,2,2,2,2,5,6,10,10,10,1,1,1,1,1,1,2,2,3]
        expected = [1,2]
        res = soln.most_frequent(input, 2)
        assert_equal(expected, res)
    end
end
