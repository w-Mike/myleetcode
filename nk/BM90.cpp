#include "nk.h"
// BM90 最小覆盖子串
// https://www.nowcoder.com/practice/c466d480d20c4c7c9d322d12ca7955ac?tpId=295&tqId=670&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
// 题解思路：https://leetcode.cn/problems/minimum-window-substring/solutions/257359/zui-xiao-fu-gai-zi-chuan-by-leetcode-solution/
bool check(unordered_map<char, int> cnt, const unordered_map<char, int> &tmap)
{
    for (const auto &node : tmap)
    {
        if (cnt[node.first] < node.second)
        {
            return false;
        }
    }
    return true;
}

string minWindow(string S, string T)
{
    unordered_map<char, int> tmap, cnt;
    for (const char &c : T)
    {
        ++tmap[c];
    }
    int l = 0, r = -1;
    int rstL = -1, minLen = S.size();
    while (r < int(S.size()))
    {
        if (tmap.find(S[++r]) != tmap.end())
        {
            ++cnt[S[r]];
        }
        while (check(cnt, tmap) && l <= r)
        {
            if ((r - l + 1) <= minLen)
            {
                minLen = r - l + 1;
                rstL = l;
            }
            if (tmap.find(S[l]) != tmap.end())
            {
                --cnt[S[l]];
            }
            ++l;
        }
    }
    return rstL == -1 ? string() : S.substr(rstL, minLen);
}
