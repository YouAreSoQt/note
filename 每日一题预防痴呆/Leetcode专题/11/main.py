class Solution:
    def maxArea(self, height: List[int]) -> int:
        i, j, ans = 0, len(height) - 1, 0
        while i < j:
            if height[i] > height[j]:
                ans = max(ans, (j - i) * height[j])
                j -= 1
            else:
                ans = max(ans, (j - i) * height[i])
                i += 1
        return ans