class Solution:
    def minSubArrayLen(self, target: int, nums: List[int]) -> int:
        ans, start, total = 10 ** 5 + 1, 0, 0 
        for end, v in enumerate(nums):
            total += v
            while start <= end and total >= target:
                ans = min(ans, end - start + 1)
                total -= nums[start]
                start += 1
        return 0 if ans == 10 ** 5 + 1 else ans