#include "nk.h"
// BM87 合并两个有序的数组
// https://www.nowcoder.com/practice/89865d4375634fc484f3a24b7fe65665?tpId=295&tqId=658&ru=%2Fpractice%2F11ae12e8c6fe48f883cad618c2e81475&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
void merge(int A[], int m, int B[], int n)
{
    int aptr = m - 1, bptr = n - 1;
    int index = m + n - 1;
    while (aptr >= 0 && bptr >= 0)
    {
        if (A[aptr] > B[bptr])
        {
            A[index] = A[aptr];
            --aptr;
        }
        else
        {
            A[index] = B[bptr];
            --bptr;
        }
        --index;
    }
    if (aptr < 0)
    {
        while (bptr >= 0)
        {
            A[index] = B[bptr];
            --index;
            --bptr;
        }
    }
}
