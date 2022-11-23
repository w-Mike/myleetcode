#include "lc.h"

// 73 看了官方题解
void setZeroes(vector<vector<int>> &matrix)
{
    int m = matrix.size();
    int n = matrix[0].size();
    vector<bool> row(m, false);
    vector<bool> col(n, false);
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (!matrix[i][j])
            {
                row[i] = col[j] = true;
            }
        }
    }
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (row[i] || col[j])
            {
                matrix[i][j] = 0;
            }
        }
    }
}

void setZeroes2(vector<vector<int>> &matrix)
{
    int r = matrix.size();
    int c = matrix[0].size();
    bool rowFlag = false, colFlag = false;
    for (int i = 0; i < r; ++i)
    {
        if (!matrix[i][0])
        {
            colFlag = true;
            break;
        }
    }
    for (int i = 0; i < c; ++i)
    {
        if (!matrix[0][i])
        {
            rowFlag = true;
            break;
        }
    }
    for (int i = 1; i < r; ++i)
    {
        for (int j = 1; j < c; ++j)
        {
            if (!matrix[i][j])
            {
                matrix[i][0] = matrix[0][j] = 0;
            }
        }
    }
    for (int i = 1; i < r; ++i)
    {
        for (int j = 1; j < c; ++j)
        {
            if (!(matrix[i][0] && matrix[0][j]))
            {
                matrix[i][j] = 0;
            }
        }
    }
    if (rowFlag)
    {
        for (int i = 0; i < c; ++i)
        {
            matrix[0][i] = 0;
        }
    }
    if (colFlag)
    {
        for (int i = 0; i < r; ++i)
        {
            matrix[i][0] = 0;
        }
    }
}
