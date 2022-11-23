#include "lc.h"

// 39. 组合总和
// https://leetcode.cn/problems/combination-sum/
void comb(const vector<int> &candidates, vector<vector<int>> &res, vector<int> &oneres, int target, int index)
{
    if (target < 0)
        return;
    if (target == 0)
    {
        res.push_back(oneres);
        return;
    }
    int size = candidates.size();
    for (int i = index; i < size; ++i)
    {
        oneres.push_back(candidates[i]);
        comb(candidates, res, oneres, target - candidates[i], i);
        oneres.pop_back();
    }
}

vector<vector<int>> combinationSum(vector<int> &candidates, int target)
{
    vector<vector<int>> res;
    vector<int> oneres;
    comb(candidates, res, oneres, target, 0);
    return res;
}
