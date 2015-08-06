class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        if (!nums.size() || k == 0)
            return res;

        // index into nums
        // front should always be the max in the current window
        deque<int> candidates;
        for (int i = 0; i < k; ++i) {
            int& val = nums[i];
            while (candidates.size() && nums[ candidates.front() ] < val) {
                candidates.pop_front();
            }
            while (candidates.size() && nums[ candidates.back() ] < val) {
                candidates.pop_back();
            }
            candidates.push_back(i);
        }

        for (int i = 0; i <= nums.size() - k; ++i) {
            res.push_back(nums[candidates.front()]);

            // remove expired candidates
            while (candidates.size() &&
                candidates.front() <= i) {
                candidates.pop_front();
            }
            if (i + k >= nums.size())
                break;
            int& val = nums[i + k];
            while (candidates.size() && nums[ candidates.front() ] < val) {
                candidates.pop_front();
            }
            while (candidates.size() && nums[ candidates.back() ] < val) {
                candidates.pop_back();
            }
            candidates.push_back(i + k);
        }

        return res;
    }
};
