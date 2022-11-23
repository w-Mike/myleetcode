#include "lc.h"
// 387 leetcode   看题解了
int firstUniqChar(string s)
{
    map<char, int> cmap;
    for (const auto &c : s)
    {
        ++cmap[c];
    }
    for (int i = 0; i < s.size(); ++i)
    {
        if (cmap[s[i]] == 1)
        {
            return i;
        }
    }
    return -1;
}

int firstUniqChar2(string s)
{
    map<char, int> cmap;
    for (int i = 0; i < s.size(); ++i)
    {
        if (cmap.find(s[i]) == cmap.end())
        {
            cmap[s[i]] = i;
        }
        else
        {
            cmap[s[i]] = -1;
        }
    }
    for (int i = 0; i < s.size(); ++i)
    {
        if (cmap[s[i]] != -1)
        {
            return i;
        }
    }
    return -1;
}
