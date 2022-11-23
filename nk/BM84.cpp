#include "nk.h"
// BM84 最长公共前缀
// https://www.nowcoder.com/practice/28eb3175488f4434a4a6207f6f484f47?tpId=295&tqId=732&ru=%2Fpractice%2Fc3120c1c1bc44ad986259c0cf0f0b80e&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
string longestCommonPrefix(vector<string> &strs)
{
    string res = "";
    int istr = 0;
    bool popflag = true;
    while (true)
    {
        if (!strs.empty() && strs[0][istr])
            res += strs[0][istr];
        else
            break;
        for (string str : strs)
        {
            if (str[istr])
            {
                if (res[istr] == str[istr])
                    popflag = false;
                else
                    popflag = true;
            }
            else
            {
                popflag = true;
                break;
            }
        }
        if (popflag)
        {
            res.pop_back();
            break;
        }
        ++istr;
    }
    return res;
}

// 横向遍历
string longestCommon(const string &commStr, const string &compareStr)
{
    int len = min(commStr.size(), compareStr.size()); // 防止访问越界
    int index = 0;
    while (index < len && (commStr[index] == compareStr[index]))
    {
        index++;
    }
    return commStr.substr(0, index);
}

string longestCommonPrefix_sec(vector<string> &strs)
{
    if (strs.empty())
        return "";
    string longestComStr = strs[0];
    for (int i = 1; i < strs.size(); ++i)
    {
        longestComStr = longestCommon(longestComStr, strs[i]);
        if (longestComStr.empty())
            break;
    }
    return longestComStr;
}

// 纵向遍历
string longestCommonPrefix_thrd(vector<string> &strs)
{
    int strnum = strs.size();
    if (!strnum)
        return "";
    string res = strs[0];
    int strlen = res.size();
    for (int i = 0; i < strlen; ++i)
    {
        for (int count = 1; count < strnum; ++count)
        {
            if (i == strs[count].size() || res[i] != strs[count][i])
                return res.substr(0, i);
        }
    }
    return res;
}
