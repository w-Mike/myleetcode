#include "nk.h"

// BM91 反转字符串
// https://www.nowcoder.com/practice/c3a6afee325e472386a1c4eb1ef987f3?tpId=295&tqId=1024337&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
string solve(string str)
{
    int begin = 0, end = str.size() - 1;
    while (begin < end)
    {
        swap(str[begin], str[end]);
        ++begin;
        --end;
    }
    return str;
}
