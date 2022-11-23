#include "nk.h"
// BM21 旋转数组的最小数字
// https://www.nowcoder.com/practice/9f3231a991af4f55b95579b44b7a01ba?tpId=295&tqId=23269&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
// 分別判斷 rotateArray[mid]和 rotateArray[end] 的值的大小，來確定縮減的範圍
//  如果 rotateArray[mid] == rotateArray[end] 则应该直接 --end
int minNumberInRotateArray(vector<int> rotateArray)
{
    auto size = rotateArray.size();
    int begin = 0, end = size - 1;
    while (begin < end)
    {
        int mid = (begin + end) >> 1;
        if (rotateArray[mid] > rotateArray[end])
        {
            begin = mid + 1;
        }
        else if (rotateArray[mid] < rotateArray[end])
        {
            end = mid;
        }
        else
        {
            --end;
        }
    }
    return rotateArray[begin];
}
// 如果二分比较难于理解，不如直接上迭代法，哪个好理解好记就用哪个
int minNumberInRotateArray_diedai(vector<int> rotateArray)
{
    for (int i = 1; i < rotateArray.size(); ++i)
    {
        if (rotateArray[i] < rotateArray[i - 1])
        {
            return rotateArray[i];
        }
    }
    return rotateArray[0];
}


