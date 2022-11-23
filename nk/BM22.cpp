#include "nk.h"


// BM22 比较版本号
// https://www.nowcoder.com/practice/2b317e02f14247a49ffdbdba315459e7?tpId=295&tqId=1024572&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int compare(string version1, string version2)
{
    // write code here
    int size1 = version1.size(), size2 = version2.size();
    int i = 0, j = 0;
    while (i < size1 || j < size2)
    {
        int num1 = 0;
        while (i < size1 && version1[i] != '.')
        {
            num1 = num1 * 10 + (version1[i] - '0');
            ++i;
        }
        ++i;

        int num2 = 0;
        while (j < size2 && version2[j] != '.')
        {
            num2 = num2 * 10 + (version2[j] - '0');
            ++j;
        }
        ++j;

        if (num1 > num2)
        {
            return 1;
        }
        else if (num1 < num2)
        {
            return -1;
        }
    }
    return 0;
}
