#include "lc.h"
// leetcode 1.
vector<int> twoSum(vector<int> &nums, int target)
{
    unordered_map<int, int> hashtable;
    for (int i = 0; i < nums.size(); ++i)
    {
        auto iter = hashtable.find(target - nums[i]);
        if (iter != hashtable.end())
        {
            return {i, hashtable[target - nums[i]]};
        }
        hashtable[nums[i]] = i;
    }
    return {};
}