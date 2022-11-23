#include "lc.h"
// 383 d
bool canConstruct(string ransomNote, string magazine)
{
    unordered_map<char, int> rmap;
    for (const auto &c : ransomNote)
    {
        rmap[c]++;
    }
    for (const auto &c : magazine)
    {
        if (rmap.find(c) != rmap.end() && rmap[c] > 0)
        {
            rmap[c]--;
        }
    }
    for (const auto &item : rmap)
    {
        if (item.second != 0)
        {
            return false;
        }
    }
    return true;
}

// 优化
bool canConstruct2(string ransomNote, string magazine)
{
    if (ransomNote.size() > magazine.size())
    {
        return false;
    }
    int letter[26]{0};

    for (const auto &c : magazine)
    {
        letter[c - 'a']++;
    }
    for (const auto &c : ransomNote)
    {
        if ((--letter[c - 'a']) < 0)
        {
            return false;
        }
    }
    return true;
}

