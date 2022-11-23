#include "lc.h"

// lc189
void myrotate(vector<int> &nums, int k)
{
    vector<int> temp(nums);
    int size = nums.size();
    k = k % (size);
    for (int i = 0; i < size; ++i)
    {
        nums[(i + k) % size] = temp[i];
    }
}

// way2
void reversenums(vector<int> &nums, int begin, int end)
{
    for (int i = begin; i <= begin + (end - begin) / 2; ++i)
    {
        swap(nums[i], nums[begin + (end - i)]);
    }
}

void myrotate2(vector<int> &nums, int k)
{
    int size = nums.size();
    reversenums(nums, 0, size - 1);
    reversenums(nums, 0, k % size - 1);
    reversenums(nums, k % size, size - 1);
}


