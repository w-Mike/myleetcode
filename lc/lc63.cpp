#include "lc.h"
// 63. 不同路径 II
// https://leetcode.cn/problems/unique-paths-ii/
int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
{
    if (obstacleGrid.empty())
        return 0;
    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();
    vector<vector<int>> dp(obstacleGrid);
    int i = -1;
    while (++i < m)
    {
        if (obstacleGrid[i][0])
            break;
        else
            dp[i][0] = 1;
    }
    while (i < m)
    {
        dp[i][0] = 0;
        ++i;
    }
    int j = -1;
    while (++j < n)
    {
        if (obstacleGrid[0][j])
            break;
        else
            dp[0][j] = 1;
    }
    while (j < n)
    {
        dp[0][j] = 0;
        ++j;
    }
    for (i = 1; i < m; ++i)
    {
        for (j = 1; j < n; ++j)
        {
            if (obstacleGrid[i][j])
                dp[i][j] = 0;
            else
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    return dp[m - 1][n - 1];
}