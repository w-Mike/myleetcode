#include "nk.h"
// BM95 分糖果问题
// https://www.nowcoder.com/practice/76039109dd0b47e994c08d8319faa352?tpId=295&tqId=1008104&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int candy(vector<int> &arr)
{
    int size = arr.size();
    vector<int> res(size, 1);
    for (int i = 1; i < size; ++i)
    {
        if (arr[i - 1] < arr[i])
        {
            res[i] = res[i - 1] + 1;
        }
    }
    for (int i = size - 2; i >= 0; --i)
    {
        if (arr[i] > arr[i + 1] && res[i] <= res[i + 1])
        {
            res[i] = res[i + 1] + 1;
        }
    }
    int num = 0;
    for (auto i : res)
    {
        num += i;
    }
    return num;
}
