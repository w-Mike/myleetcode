#include "nk.h"

// BM83 字符串变形
//  https://www.nowcoder.com/practice/c3120c1c1bc44ad986259c0cf0f0b80e?tpId=295&tqId=44664&ru=%2Fpractice%2F8c82a5b80378478f9484d87d1c5f12a4&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
string trans(string s, int n)
{
    stack<string> strstack;
    string str = "", res = "";
    int j = 0;
    for (int i = 0; i < n;)
    {
        j = i;
        while (j < n && s[j] != ' ')
        {
            if ((s[j] >= 'A') && (s[j] <= 'Z'))
                s[j] = s[j] - 'A' + 'a';
            else if ((s[j] >= 'a') && (s[j] <= 'z'))
                s[j] = s[j] - 'a' + 'A';
            ++j;
        }
        str = s.substr(i, j - i);
        strstack.push(str);
        i = j + 1;
    }
    res = s[n - 1] == ' ' ? " " : "";
    while (!strstack.empty())
    {
        res += strstack.top();
        strstack.pop();
        if (!strstack.empty())
            res += " ";
    }
    return res;
}