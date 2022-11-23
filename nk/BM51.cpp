#include "nk.h"

// BM51 数组中出现次数超过一半的数字
// https://www.nowcoder.com/practice/e8a1b01a2df14cb2b228b30ee6a92163?tpId=295&tqId=745&ru=%2Fexam%2Foj&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
int MoreThanHalfNum_Solution(vector<int> numbers)
{
    unordered_map<int, int> numcount;
    int boudary(numbers.size() / 2);
    int res(-1);
    for (int num : numbers)
    {
        ++numcount[num];
        if (numcount[num] > boudary)
            res = num;
    }
    return res;
}

//  消消乐算法（额。。。）
int MoreThanHalfNum_Solution_stack(vector<int> numbers)
{
    stack<int> nstack;
    for (int num : numbers)
    {
        if (!nstack.empty() && nstack.top() != num)
        {
            nstack.pop();
        }
        else
        {
            nstack.push(num);
        }
    }
    return nstack.top();
}
