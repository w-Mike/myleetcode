#include "nk.h"

// BM58 字符串的排列
// https://www.nowcoder.com/practice/fe6b651b66ae47d7acce78ffdd9a96c7?tpId=295&tqId=23291&ru=%2Fpractice%2F0c9664d1554e466aa107d899418e814e&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
void back(vector<string> &res, const string &str, string &rstr, vector<bool> &marked)
{
    if (rstr.size() == str.size())
    {
        res.push_back(rstr);
        return;
    }
    unordered_set<char> selected;

    for (int i = 0; i < str.size(); ++i)
    {
        if (selected.find(str[i]) != selected.end() || marked[i])
        {
            continue;
        }
        rstr += str[i];
        marked[i] = true;
        selected.insert(str[i]);
        back(res, str, rstr, marked);
        marked[i] = false;
        rstr.pop_back();
    }
}

vector<string> Permutation(string str)
{
    vector<string> res;
    string rstr;
    vector<bool> marked(str.size(), false);
    back(res, str, rstr, marked);
    return res;
}

