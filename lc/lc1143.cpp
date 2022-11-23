#include "lc.h"

// 1143. 最长公共子序列
// https://leetcode.cn/problems/longest-common-subsequence/description/
int longestCommonSubsequence(string text1, string text2)
{
    int m = text1.size() + 1;
    int n = text2.size() + 1;
    vector<vector<int>> dp(m, vector<int>(n, 0));
    for (int i = 1; i < m; ++i)
    {
        for (int j = 1; j < n; ++j)
        {
            if (text1[i - 1] == text2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[m - 1][n - 1];
}
