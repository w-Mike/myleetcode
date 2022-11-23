#include "lc.h"

// 36
bool isValidSudoku(vector<vector<char>> &board)
{
    int row[9][10]{0};
    int column[9][10]{0};
    int box[9][10]{0};
    int boxIndex = 0;

    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            boxIndex = j / 3 + (i / 3) * 3;
            if (board[i][j] != '.')
            {
                if (row[i][board[i][j] - '0'] == 1 || column[j][board[i][j] - '0'] == 1 ||
                    box[boxIndex][board[i][j] - '0'] == 1)
                {
                    return false;
                }
                else
                {
                    row[i][board[i][j] - '0'] = 1;
                    column[j][board[i][j] - '0'] = 1;
                    box[boxIndex][board[i][j] - '0'] = 1;
                }
            }
        }
    }
    return true;
}