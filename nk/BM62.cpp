#include "nk.h"
// BM62 斐波那契数列
// https://www.nowcoder.com/practice/c6c7742f5ba7442aada113136ddea0c3?tpId=295&tqId=23255&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int Fibonacci(int n)
{
    int fir = 1, sec = 1;
    int tmp = 0;
    for (int i = 3; i <= n; ++i)
    {
        tmp = fir;
        fir = sec;
        sec = tmp + sec;
    }
    return sec;
}
