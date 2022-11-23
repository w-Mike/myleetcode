#include "nk.h"

// BM17: https://www.nowcoder.com/practice/d3df40bd23594118b57554129cadf47b?tpId=295&tqId=1499549&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int search(vector<int> &nums, int target)
{
    // write code here
    size_t size = nums.size();
    if (!size)
        return -1;
    int begin = 0;
    int end = size - 1;
    int mid;
    while (end >= begin)
    {
        mid = begin + (end - begin) / 2;
        if (nums[mid] == target)
            return mid;
        if (nums[mid] > target)
        {
            end = mid - 1;
        }
        else if (nums[mid] < target)
        {
            begin = mid + 1;
        }
    }
    return -1;
}
