#include "nk.h"

// BM85 验证IP地址
// https://www.nowcoder.com/practice/55fb3c68d08d46119f76ae2df7566880?tpId=295&tqId=1024725&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
vector<string> split(const string &IP, char splitter)
{
    vector<string> res;
    string str;
    int size = IP.size();
    // for (int i = 0; i <= size; ++i)
    // {
    //     if (i == size || IP[i] == splitter)
    //     {
    //         res.push_back(str);
    //         str = "";
    //     }
    //     else
    //     {
    //         str += IP[i];
    //     }
    // }
    int i = 0;
    while (i <= size)
    {
        str = "";
        while (i < size && IP[i] != splitter)
        {
            str += IP[i];
            ++i;
        }
        ++i;
        res.push_back(str);
    }
    return res;
}

bool IPv4(const string &IP)
{
    vector<string> strs = split(IP, '.');
    if (strs.size() != 4)
        return false;
    for (auto str : strs)
    {
        if (str.size() > 3 || str.size() == 0 || (str.size() != 1 && str[0] == '0'))
            return false;
        for (auto c : str)
        {
            if (!isdigit(c))
                return false;
        }
        int num = stoi(str);
        if (num > 255 || num < 0)
            return false;
    }
    return true;
}

bool IPv6(const string &IP)
{
    vector<string> strs = split(IP, ':');
    if (strs.size() != 8)
        return false;
    for (auto str : strs)
    {
        if (str.size() == 0 || str.size() > 4)
            return false;
        for (char c : str)
        {
            if (!(isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')))
                return false;
        }
    }
    return true;
}

string solve(string IP)
{
    if (IP.size() == 0)
        return "Neither";
    if (IPv4(IP))
        return "IPv4";
    else if (IPv6(IP))
        return "IPv6";
    else
        return "Neither";
}