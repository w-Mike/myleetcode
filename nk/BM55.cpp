#include "nk.h"

// BM55 没有重复项数字的全排列
// https://www.nowcoder.com/practice/4bcf3081067a4d028f95acee3ddcd2b1?tpId=295&tqId=701&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
// 递归回溯法
void permute_recursion(vector<vector<int>> &res, const vector<int> &num, vector<int> &list)
{
    if (list.size() == num.size())
    {
        res.push_back(list);
        return;
    }
    for (int i = 0; i < num.size(); ++i)
    {
        vector<int>::iterator iter = find(list.begin(), list.end(), num[i]);
        if (iter != list.end())
            continue;
        list.push_back(num[i]);
        permute_recursion(res, num, list);
        list.pop_back();
    }
}

vector<vector<int>> permute(vector<int> &num)
{
    vector<vector<int>> res{};
    vector<int> list{};
    permute_recursion(res, num, list);
    return res;
}

