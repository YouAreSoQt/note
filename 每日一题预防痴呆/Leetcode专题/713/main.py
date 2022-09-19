class Solution:
    def numSubarrayProductLessThanK(self, nums: List[int], k: int) -> int:
        ans, product, i = 0, 1, 0
        for j, v in enumerate(nums):
            product *= v
            while i <= j and product >= k:
                product //= nums[i]
                i += 1
            ans += j - i + 1
        return ans