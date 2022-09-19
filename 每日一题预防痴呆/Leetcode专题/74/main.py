class Solution:
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
        m, n = len(matrix), len(matrix[0])
        left, right = 0, m * n - 1
        while left <= right:
            mid = (left + right) // 2
            # 把索引映射成矩阵下标
            value = matrix[mid // n][mid % n]
            if value == target:
                return True
            elif value > target:
                right = mid - 1
            else:
                left = mid + 1
        return False