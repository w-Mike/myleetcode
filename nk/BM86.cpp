#include "nk.h"

// BM86 大数!!!加法
// https://www.nowcoder.com/practice/11ae12e8c6fe48f883cad618c2e81475?tpId=295&tqId=1061819&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj

// 虽然思路正确，但是代码重复太多了，需要精简一些。
string solve(string s, string t)
{
    int slstIndex = s.size() - 1;
    int tlstIndex = t.size() - 1;
    stack<char> stkRes;
    bool addflag = false;
    int tmp = 0;
    int i = slstIndex, j = tlstIndex;
    for (; i >= 0 && j >= 0; --i, --j)
    {
        int snum = s[i] - '0', tnum = t[j] - '0';
        tmp = snum + tnum;
        if (addflag)
            tmp += 1;
        stkRes.push('0' + (tmp % 10));
        addflag = tmp >= 10 ? true : false;
    }
    if (i < 0)
    {
        while (j >= 0)
        {
            tmp = t[j] - '0';
            if (addflag)
                tmp += 1;
            stkRes.push('0' + (tmp % 10));
            addflag = tmp >= 10 ? true : false;
            --j;
        }
    }
    else if (j < 0)
    {
        while (i >= 0)
        {
            tmp = s[i] - '0';
            if (addflag)
                tmp += 1;
            stkRes.push('0' + (tmp % 10));
            addflag = tmp >= 10 ? true : false;
            --i;
        }
    }
    if (i < 0 && j < 0)
    {
        if (addflag)
            stkRes.push('1');
    }
    string res;
    while (!stkRes.empty())
    {
        res += stkRes.top();
        stkRes.pop();
    }
    return res;
}

// 精简代码版本：
string solve_sim(string s, string t)
{
    int slen = s.size();
    int tlen = t.size();
    int placeSum = 0;
    stack<char> resStk;
    for (int i = slen - 1, j = tlen - 1; i >= 0 || j >= 0; --i, --j)
    {
        placeSum += i >= 0 ? s[i] - '0' : 0;
        placeSum += j >= 0 ? t[j] - '0' : 0;
        resStk.push(placeSum % 10 + '0');
        placeSum /= 10;
    }
    if (placeSum)
    {
        resStk.push('1');
    }
    string res = "";
    while (!resStk.empty())
    {
        res += resStk.top();
        resStk.pop();
    }
    return res;
}
