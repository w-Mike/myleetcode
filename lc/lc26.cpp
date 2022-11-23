#include "lc.h"

// lc 26
int removeDuplicates(vector<int> &nums)
{
    size_t size = nums.size();
    if (size == 1)
    {
        return 1;
    }
    int pb = 0;
    for (size_t pf = 1; pf < nums.size(); ++pf)
    {
        if (nums[pb] != nums[pf])
        {
            nums[pb + 1] = nums[pf];
            ++pb;
        }
    }
    for (int i = 0; i < (size - pb - 1); ++i)
    {
        nums.pop_back();
    }
    return pb + 1;
}

