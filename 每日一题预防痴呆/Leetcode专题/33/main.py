class Solution:
    def search(self, nums: List[int], target: int) -> int:
        left, right, n = 0, len(nums) - 1, len(nums)
        while left <= right:
            mid = (left + right) // 2
            if nums[mid] == target:
                return mid
            if nums[0] <= nums[mid]:
                if nums[mid] > target >= nums[0]:
                    right = mid - 1
                else:
                    left = mid + 1
            else:
                if nums[mid] < target <= nums[n - 1]:
                    left = mid + 1
                else:
                    right = mid - 1
        return -1