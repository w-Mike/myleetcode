#include "lc.h"
// 242 leetcode
bool isAnagram(string s, string t)
{
    if (s.size() != t.size())
    {
        return false;
    }
    int letter[26]{0};
    for (const auto &c : s)
    {
        letter[c - 'a']++;
    }
    for (const auto &c : t)
    {
        if ((--letter[c - 'a']) < 0)
        {
            return false;
        }
    }
    return true;
}

// 官方排序法
bool isAnagram2(string s, string t)
{
    if (s.size() != t.size())
        return false;
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());
    return s == t;
}