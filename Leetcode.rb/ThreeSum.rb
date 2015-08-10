require 'set'

# Return all unique triplets that sum to 0.
#
# @param {Integer[]} nums
# @return {Integer[][]}
def three_sum(nums)
    nums.sort!
    # precompute first index of value
    seen = {}
    0.upto(nums.size-1) do |i|
        if seen.include? nums[i]
            next
        end
        seen[nums[i]] = i
    end
    
    res = []
    0.upto(nums.size-1) do |i|
        if i > 0 and nums[i-1] == nums[i]
            next
        end
        (i+1).upto(nums.size-1) do |j|
            if j > (i+1) and nums[j-1] == nums[j]
                next
            end
            # invariant: i and j always point to the first element in a run of
            # repeated values. If i and j index the same value, then j is the
            # second element in that run of repeated values.
            target = -(nums[i] + nums[j])
            k = -1
            if seen.include? target
                k = seen[target]
                while k <= j and nums[k] == nums[j]
                    k = k + 1
                end
            end
            if k <= j or k >= nums.size or nums[k] != target
                next
            end
            # invariant: i < j < k
            puts "%d %d %d" % [i, j, k]
            res.push([nums[i], nums[j], nums[k]])
        end
    end
    return res
end

if __FILE__ == $0
    #res = three_sum([-1, 0, 1, 2, -1, -4])
    res = three_sum([1, 2, -2, -1])
    res.each do |tup|
        puts "%d %d %d" % tup
    end
end
