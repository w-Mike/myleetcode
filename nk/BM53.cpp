#include "nk.h"

// BM53 缺失的第一个正整数
// https://www.nowcoder.com/practice/50ec6a5b0e4e45348544348278cdcee5?tpId=295&tqId=2188893&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int minNumberDisappeared(vector<int> &nums)
{
    // write code here
    unordered_set<int> numset;
    for (int num : nums)
    {
        numset.insert(num);
    }
    int i = 0;
    while (++i)
    {
        if (numset.find(i) == numset.end())
            break;
    }
    return i;
}

int minNumberDisappeared_2(vector<int> &nums)
{
    int n = nums.size();
    // 将 0 或者负数给映射到数组范围外的下标
    for (int &num : nums)
    {
        if (num <= 0)
        {
            num = n + 1;
        }
    }
    for (int i = 0; i < n; ++i)
    {
        int index = abs(nums[i]);
        // 注意 数组中没有重复的数字，所以该位置不会再被改变了，已经被标记为负数了
        if (index <= n)
        {
            nums[index - 1] = -nums[index - 1];
        }
    }
    int res = n + 1;
    for (int i = 0; i < n; ++i)
    {
        if (nums[i] > 0)
        {
            res = i + 1;
            break;
        }
    }
    return res;
}
