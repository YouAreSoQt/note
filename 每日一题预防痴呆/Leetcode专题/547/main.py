class Solution:
    def findCircleNum(self, isConnected: List[List[int]]) -> int:
        n, visited, ans = len(isConnected), set(), 0

        def dfs(i):
            for j in range(n):
                if isConnected[i][j] == 1 and j not in visited:
                    visited.add(j)
                    dfs(j)

        for i in range(n):
            if i not in visited:
                dfs(i)
                ans += 1
        
        return ans