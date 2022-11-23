#include "nk.h"


// BM52 数组中只出现一次的两个数字
// https://www.nowcoder.com/practice/389fc1c3d3be4479a154f63f495abff8?tpId=295&tqId=1375231&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
vector<int> FindNumsAppearOnce(vector<int> &array)
{
    // write code here
    vector<int> res{};
    map<int, int> numap;
    for (int i : array)
    {
        ++numap[i];
    }
    for (auto num : numap)
    {
        if (num.second == 1)
            res.push_back(num.first);
    }
    return res;
}
// 利用了 题目中的限制条件， 只有两个数出现了一次，所以可以用更高效的方式
// 别忘了按位运算。 异或可以从一组 只有一个存在一次的数 的数组 中找到这个数
// 但是这道题 有两个数出现了一次，所以要把这俩数给分组，分成两个组。
// 这样两个组分别做异或运算就得到了这两个数了。
// 所以该如何进行分组呢，如果把所有的数都进行异或运算 结果就是 要找的两个数字的异或
// 按位观察结果，两个不相同的数字的二进制必然有几个位不同。
// 找出最低位，然后让每个数都与这一位进行&运算，这样必然能将这俩数分开，

// warn！！： 注意 移位运算符不会改变运算数的值，所以需要 使用 mask <<= 1 而不是 mask<<1,这个不会改变mask的值
vector<int> FindNumsAppearOnce_bit(vector<int> &array)
{
    int tmp = 0;
    for (int num : array)
    {
        tmp ^= num;
    }
    int mask = 1;
    while (!(tmp & mask))
    {
        mask <<= 1;
    }
    int a = 0, b = 0;
    for (int num : array)
    {
        if (!(mask & num))
        {
            a ^= num;
        }
        else
        {
            b ^= num;
        }
    }
    tmp = a;
    a = a < b ? a : b;
    b = a == tmp ? b : tmp;
    return {a, b};
}
