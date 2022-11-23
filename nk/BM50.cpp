#include "nk.h"


// BM50 两数之和
// https://www.nowcoder.com/practice/20ef0972485e41019e39543e8e895b7f?tpId=295&tqId=745&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
vector<int> twoSum(vector<int> &numbers, int target)
{
    // write code here
    unordered_map<int, int> numap;
    for (int i = 0; i < numbers.size(); ++i)
    {
        if (numap.find(target - numbers[i]) != numap.end())
        {
            return {numap[target - numbers[i]] + 1, i + 1};
        }
        numap[numbers[i]] = i;
    }
    return {};
}

