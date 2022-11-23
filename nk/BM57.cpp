#include "nk.h"


// BM57 岛屿数量
// https://www.nowcoder.com/practice/0c9664d1554e466aa107d899418e814e?tpId=295&tqId=1024684&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
// DFS
void dfs(vector<vector<char>> &grid, int i, int j)
{
    int m = grid.size();
    int n = grid[0].size();
    if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == '0')
    {
        return;
    }
    grid[i][j] = '0';
    dfs(grid, i - 1, j);
    dfs(grid, i + 1, j);
    dfs(grid, i, j - 1);
    dfs(grid, i, j + 1);
}

// BFS
void bfs(vector<vector<char>> &grid, int i, int j)
{
    int m = grid.size();
    int n = grid[0].size();
    int node = i * n + j;
    queue<int> nodes;
    nodes.push(node);
    while (!nodes.empty())
    {
        node = nodes.front();
        nodes.pop();
        int row = node / n;
        int col = node % n;
        grid[row][col] = 0;
        if ((row - 1) >= 0 && grid[row - 1][col] == '1')
        {
            node = n * (row - 1) + col;
            nodes.push(node);
        }
        if ((row + 1) < m && grid[row + 1][col] == '1')
        {
            node = n * (row + 1) + col;
            nodes.push(node);
        }
        if ((col - 1) >= 0 && grid[row][col - 1] == '1')
        {
            node = n * row + col - 1;
            nodes.push(node);
        }
        if ((col + 1) < n && grid[row][col + 1] == '1')
        {
            node = n * row + col + 1;
            nodes.push(node);
        }
    }
}

int solve(vector<vector<char>> &grid)
{
    // write code here
    if (grid.empty())
        return 0;
    int m = grid.size();
    int n = grid[0].size();
    int res = 0;
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (grid[i][j] == '1')
            {
                ++res;
                // dfs(grid, i, j);
                bfs(grid, i, j);
            }
        }
    }
    return res;
}
