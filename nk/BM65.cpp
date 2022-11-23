#include "nk.h"

// BM65 最长公共子序列(二)
// https://www.nowcoder.com/practice/6d29638c85bb4ffd80c020fe244baf11?tpId=295&tqId=991075&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj

string LCS(string s1, string s2)
{
    // write code here
    string resStr = "-1";
    int m = s1.size(), n = s2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    vector<vector<int>> mark(dp);
    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                mark[i][j] = 1; // 自身 mark为1
            }
            else
            {
                if (dp[i - 1][j] >= dp[i][j - 1])
                { // 上边大 mark 为 3
                    dp[i][j] = dp[i - 1][j];
                    mark[i][j] = 3;
                }
                else
                { // 左边大  mark 为 2
                    dp[i][j] = dp[i][j - 1];
                    mark[i][j] = 2;
                }
            }
        }
    }
    int resize = dp[m][n];
    // 获取最长公共子序列
    if (!resize)
        return resStr;
    stack<char> res;
    int i = m, j = n;
    while (res.size() < resize)
    {
        if (mark[i][j] == 1)
        {
            res.push(s1[i - 1]);
            i -= 1;
            j -= 1;
        }
        if (mark[i][j] == 2)
        {
            j -= 1;
        }
        if (mark[i][j] == 3)
        {
            i -= 1;
        }
    }
    resStr = "";
    while (!res.empty())
    {
        resStr += res.top();
        res.pop();
    }
    return resStr;
}
