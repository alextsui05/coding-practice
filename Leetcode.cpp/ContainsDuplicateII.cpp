class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        map<int, int> seen;
        for (int i = 0; i < nums.size(); ++i) {
            if (!seen.count(nums[i])) {
                seen[nums[i]] = i;
            } else {
                int j = seen[nums[i]];
                if (i - j <= k)
                    return true;
                else
                    seen[nums[i]] = i;
            }
        }
        return false;
    }
};
