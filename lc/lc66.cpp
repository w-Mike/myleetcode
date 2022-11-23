#include "lc.h"
// 66
vector<int> plusOne(vector<int> &digits)
{
    auto iter = digits.end() - 1;
    while (iter != digits.begin() && (*iter) == 9)
    {
        *iter = 0;
        --iter;
    }
    ++(*iter);
    if ((*iter) == 10 && iter == digits.begin())
    {
        *iter = 0;
        digits.insert(iter, 1);
    }
    return digits;
}


