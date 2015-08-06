class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        // product of the first i elements
        int forward = 1;
        // product of the last i elements
        int backward = 1;

        // res[i] = product of first i-1 * product of last n-i
        const int n = nums.size();
        vector<int> res(n, 1);
        for (int i = 0; i < n; ++i) {
            forward *= nums[i];
            backward *= nums[n - 1 - i];
            if (i + 1 < n)
                res[i+1] *= forward;
            if (n - 2 - i >= 0)
                res[n - 2 - i] *= backward;
        }
        return res;
    }
};
