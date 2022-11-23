#include "lc.h"
// lc 136
int singleNumber(vector<int> &nums)
{
    int res = 0;
    for (auto num : nums)
    {
        res ^= num;
    }
    return res;
}

// 排序后查找
int singleNumber2(vector<int> &nums)
{
    // sort(nums.begin(), nums.end());
    return 1;
}
