#include "nk.h"

// BM18 https://www.nowcoder.com/practice/abc3fe2ce8e146608e868a70efebf62e?tpId=295&tags=&title=&difficulty=0&judgeStatus=0&rp=0&sourceUrl=%2Fexam%2Foj
// 二维的二分查找
bool Find(int target, vector<vector<int>> array)
{
    if (array.empty())
    {
        return false;
    }
    int m = array.size();
    int n = array[0].size();

    int row = 0;
    int col = n - 1;
    int val = array[row][col];

    // 初始值为数组右上角的值，其左边的元素都比他小，下边的元素都比他大
    // 查找范围永远是以 val为右上角的数组
    // 比较target 与初始值val的大小，如果 target小于val，说明 val这一列上的数据都可以排除了，反之val那一行就可以排除了

    // 关于循环条件，col是递减的，row是递增的 所以判断条件就是
    while (row < m && col >= 0)
    {
        if (val == target)
        {
            return true;
        }
        if (val < target)
        {
            ++row;
        }
        else if (val > target)
        {
            --col;
        }
        val = array[row][col];
    }
    return false;
}