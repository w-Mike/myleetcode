#include "nk.h"
// BM56 有重复项数字的全排列
// https://www.nowcoder.com/practice/a43a2b986ef34843ac4fdd9159b69863?tpId=295&tags=&title=&difficulty=0&judgeStatus=0&rp=0&sourceUrl=%2Fexam%2Foj

void permuteUnique_recursion(const vector<int> &num, vector<vector<int>> &res, vector<int> &list, vector<int> mark)
{
    if (list.size() == num.size())
    {
        res.push_back(list);
        return;
    }
    unordered_set<int> nset{};
    for (int i = 0; i < num.size(); ++i)
    {
        if (mark[i] || (nset.find(num[i]) != nset.end()))
            continue;
        nset.insert(num[i]);
        list.push_back(num[i]);
        mark[i] = 1;

        permuteUnique_recursion(num, res, list, mark);
        list.pop_back();
        mark[i] = 0;
    }
}

vector<vector<int>> permuteUnique(vector<int> &num)
{
    sort(num.begin(), num.end());
    vector<vector<int>> res{};
    vector<int> list{};
    vector<int> mark(num.size(), 0);
    permuteUnique_recursion(num, res, list, mark);
    return res;
}

