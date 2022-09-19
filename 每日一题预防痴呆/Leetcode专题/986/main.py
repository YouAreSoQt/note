class Solution:
    def intervalIntersection(self, firstList: List[List[int]], secondList: List[List[int]]) -> List[List[int]]:
        ans, n1, n2 = [], len(firstList), len(secondList)
        i = j = 0
        while i < n1 and j < n2:
            left = max(firstList[i][0], secondList[j][0])
            right = min(firstList[i][1], secondList[j][1])
            if left <= right:
                ans.append([left, right])
            if firstList[i][1] > secondList[j][1]:
                j += 1
            else:
                i += 1
        return ans