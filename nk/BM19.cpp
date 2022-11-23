#include "nk.h"

// BM19 寻找峰值
// https://www.nowcoder.com/practice/fcf87540c4f347bcb4cf720b5b350c76?tpId=295&tqId=2227748&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int divFind(const vector<int> &nums, const int &begin, const int &end)
{
    int mid = begin + (end - begin) / 2;
    if (begin > end)
        return -1;
    if (mid == 0)
    {
        if (nums[mid] > nums[mid + 1])
        {
            return mid;
        }
    }
    else if (mid == nums.size() - 1)
    {
        if (nums[mid] > nums[mid - 1])
        {
            return mid;
        }
    }
    else if (nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1])
    {
        return mid;
    }
    int res = divFind(nums, begin, mid - 1);
    int res2 = divFind(nums, mid + 1, end);
    if (res != -1)
        return res;
    else if (res2 != -1)
        return res2;
    else
        return -1;
}

int findPeakElement(vector<int> &nums)
{
    // write code here
    int begin = 0;
    int end = nums.size() - 1;
    int res = 0;
    res = divFind(nums, begin, end);
    return res;
}

// 更好的解法，官方题解：
int findPeakElement_2(vector<int> &nums)
{
    // write code here4
    int begin = 0, end = nums.size() - 1;
    int mid = 0;
    // 记住， mid 总是靠左的，所以最终结果只能是 begin == end，退出循环
    while (begin < end)
    {
        mid = (begin + end) / 2; // 因为 begin < end， 所以 mid+1 必不可能越界
        if (nums[mid] < nums[mid + 1])
        {
            begin = mid + 1;
        }
        else
        {
            end = mid;
        }
    }
    return begin;
}
