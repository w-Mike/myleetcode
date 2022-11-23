#include "nk.h"
// BM88 判断是否为回文字符串
// https://www.nowcoder.com/practice/e297fdd8e9f543059b0b5f05f3a7f3b2?tpId=295&tqId=658&ru=%2Fpractice%2F11ae12e8c6fe48f883cad618c2e81475&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
bool judge(string str)
{
    int pre = 0, last = str.size() - 1;
    while (pre < last)
    {
        if (str[pre] != str[last])
            return false;
        ++pre;
        --last;
    }
    return true;
}
