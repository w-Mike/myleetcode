#include "lc.h"

// 118 杨辉三角
vector<vector<int>> generate(int numRows)
{
    vector<vector<int>> res{};
    if (numRows == 0)
    {
        return res;
    }
    for (int row = 0; row < numRows; ++row)
    {
        res.push_back(vector<int>(row + 1));
        res[row][0] = 1;
        res[row][row] = 1;
        for (int i = 1; i < row; ++i)
        {
            res[row][i] = res[row - 1][i - 1] + res[row - 1][i];
        }
    }
    return res;
}