#include "nk.h"

// BM63 跳台阶
// https://www.nowcoder.com/practice/8c82a5b80378478f9484d87d1c5f12a4?tpId=295&tqId=23255&ru=%2Fexam%2Foj&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
// 由于青蛙一次只能跳一阶或者跳两阶，所第n次的跳法就是第n-1次的跳法与第n-2次的跳法之和
// 其实就是斐波那契数列除去第一项
int jumpFloor(int number)
{
    int res = 0, tmp = 0;
    int fir = 1, sec = 2;
    res = number == 1 ? fir : sec;
    for (int i = 3; i <= number; ++i)
    {
        tmp = fir;
        fir = sec;
        sec = tmp + sec;
    }
    res = number < 3 ? res : sec;
    return res;
}
