#include "lc.h"
// 566  官方题解
// 一维数组如何转换为二维数组   根据一维下标与二维下标的关系
vector<vector<int>> matrixReshape(vector<vector<int>> &mat, int r, int c)
{
    int mr = mat.size();
    int mc = mat[0].size();
    if (mr * mc != r * c)
    {
        return mat;
    }
    vector<vector<int>> res(r, vector<int>(c));
    for (int n = 0; n < mr * mc; n++)
    {
        res[n / c][n % c] = mat[n / mc][n % mc];
    }
    return res;
}

void test556()
{
    vector<vector<int>> mat = {{1, 2},
                               {3, 4}};
    int r = 4, c = 1;
    mat = matrixReshape(mat, r, c);
    for (const auto &vec : mat)
    {
        for (const auto &num : vec)
        {
            cout << num << " ";
        }
        cout << endl;
    }
}