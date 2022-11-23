#include "lc.h"
// 283 lc  --myway-1
void moveZeroes(vector<int> &nums)
{
    size_t size = nums.size();
    for (size_t i = 0; i < size; ++i)
    {
        if (nums[i] == 0)
        {
            --size;
            for (size_t j = i; j < size; ++j)
            {
                swap(nums[j], nums[j + 1]);
            }
            if (nums[i] == 0)
                --i;
        }
    }
}

//  --myway-2
void moveZeroes2(vector<int> &nums)
{
    size_t size = nums.size();
    for (size_t i = 0; i < size;)
    {
        if (nums[i] == 0)
        {
            nums.erase(nums.begin() + i);
            nums.push_back(0);
            --size;
        }
        else
        {
            ++i;
        }
    }
}

//  --othersway 双指针
// leftp 的 左边是符合要求的序列（即按原相对序列排序的非零数字序列）/
// leftp总是指向需要覆盖的值，因为movep总是指向序列右边的第一个非零数字
void moveZeroes3(vector<int> &nums)
{
    size_t size = nums.size();
    int leftp = 0, movep = 0;
    while (leftp < size)
    {
        /* code */
        if (movep >= size)
        {
            nums[leftp++] = 0;
        }
        else if (nums[movep])
        {
            nums[leftp] = nums[movep];
            ++leftp;
        }
        ++movep;
    }
}
