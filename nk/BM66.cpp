#include "nk.h"
// BM66 最长公共子串
// https://www.nowcoder.com/practice/f33f5adc55f444baa0e0ca87ad8a6aac?tpId=295&tqId=991075&ru=%2Fexam%2Foj&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj

// 垃圾做法，按照最长公共子序列的思路来做的，直接报废，不能AC
string LCS_substr(string str1, string str2)
{
    // write code here
    string res = "-1";
    int m = str1.size();
    int n = str2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    vector<vector<int>> mark(dp);
    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (str1[i - 1] == str2[j - 1])
            {
                if (i == 1 || j == 1 || str1[i - 2] == str2[j - 2])
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    mark[i][j] = 1;
                    continue;
                }
            }
            if (dp[i - 1][j] >= dp[i][j - 1])
            { // 来自上 赋值为 2
                dp[i][j] = dp[i - 1][j];
                mark[i][j] = 2;
            }
            else
            { // 来自左  赋值为 3
                dp[i][j] = dp[i][j - 1];
                mark[i][j] = 3;
            }
        }
    }
    int resSize = dp[m][n];
    cout << resSize << endl;
    // 以下是输出最长子串部分， 由于子串是连续的所以相比于最长公共子序列，子串的输出更简单，只要找出最长公共子串的最后一个字符的下标即可
    if (!resSize)
        return res;
    res = "";
    stack<char> rstack;
    int i = m, j = n;
    while (mark[i][j] != 1)
    {
        if (mark[i][j] == 2)
        {
            i -= 1;
        }
        if (mark[i][j] == 3)
        {
            j -= 1;
        }
    }
    int end = i;
    int begin = end - resSize;
    for (int i = begin; i < end; ++i)
    {
        res += str1[i];
    }
    return res;
}
// 正确解法： 理解 该dp数组与 BM65 的dp数组含以上的不同！！
// 动态规划的关键就是理解dp数据的含义啊啊

// 该题的dp数组的含义是：dp[i][j] 表示str1中以字符str1[i]为结尾的和str2中以str2[j]结尾的公共子串的长度！！
// 所以如果 str1[i] != str2[j], 那么公共子串的长度为0
//    如果 str1[i] == str2[j], 那么公共子串的长度为 以 str1[i-1]和str2[j-1]为结尾的公共子串的长度+1，即 dp[i-1][j-1] + 1
// 关于初始化： 仍然是0行和0列的公共子串长度为0；
string LCS_substr2(string str1, string str2)
{
    int m = str1.size(), n = str2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    int maxStrLen = 0, lstIndex = 0;

    for (int i = 0; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (str1[i - 1] == str2[j - 1])
            {
                if ((dp[i][j] = dp[i - 1][j - 1] + 1) > maxStrLen)
                {
                    maxStrLen = dp[i][j];
                    lstIndex = i;
                }
            }
            else
            {
                dp[i][j] = 0;
            }
        }
    }
    return str1.substr(lstIndex - maxStrLen, maxStrLen);
}
