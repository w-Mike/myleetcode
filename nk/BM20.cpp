#include "nk.h"


// BM20 数组中的逆序对
// https://www.nowcoder.com/practice/96bd6684e04a44eb80e6a68efc0ec6c5?tpId=295&tqId=2227748&ru=%2Fexam%2Foj&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj

//

void merge(vector<int> &data, vector<int> &tmp, int begin, int end, int mid, unsigned int &res)
{
    // 两个vec 一个 [begin, mid]  一个 [mid+1, end]
    int i = begin, j = mid + 1, k = 0;
    while (i <= mid && j <= end)
    {
        if (data[i] > data[j])
        {
            tmp[k++] = data[j++];
            res += (mid - i + 1);
        }
        else
        {
            tmp[k++] = data[i++];
        }
    }
    while (i <= mid)
    {
        tmp[k++] = data[i++];
    }
    while (j <= end)
    {
        tmp[k++] = data[j++];
    }
    i = begin, k = 0;
    while (i <= end)
    {
        data[i++] = tmp[k++];
    }
}

void merge_sort(vector<int> &data, vector<int> &tmp, int begin, int end, unsigned int &res)
{
    if (begin == end)
        return;
    int mid = (begin + end) >> 1;
    merge_sort(data, tmp, begin, mid, res);
    merge_sort(data, tmp, mid + 1, end, res);
    merge(data, tmp, begin, end, mid, res);
}

int InversePairs(vector<int> data)
{
    const int mod = 1000000007;
    vector<int> tmp(data.size());
    unsigned int res = 0;
    merge_sort(data, tmp, 0, data.size() - 1, res);
    return res % mod;
}
