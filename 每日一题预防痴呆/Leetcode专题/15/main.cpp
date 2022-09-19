class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        for (int first = 0, n = nums.size(); first < n; first++) {
            if (first > 0 && nums[first] == nums[first - 1])
                continue;
            for (int second = first + 1, third = n - 1; second < third; second++) {
                if (second > first + 1 && nums[second] == nums[second - 1])
                    continue;
                while (second < third && nums[second] + nums[third] > -nums[first])
                    third--;
                if (second == third)
                    break;
                if (nums[first] + nums[second] + nums[third] == 0)
                    ans.push_back({nums[first], nums[second], nums[third]});
            }
        }
        return ans;
    }
};