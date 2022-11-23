#include "lc.h"
// lc 122
int maxProfit122(const vector<int> &prices)
{
    int part = 0;
    size_t size = prices.size();
    vector<int> seperator{0};
    for (int i = 1; i < size; ++i)
    {
        if (prices[i] < prices[i - 1])
        {
            seperator.push_back(i);
            auto backitem = seperator.end() - 1;
            part += (prices[*backitem - 1] - prices[*(backitem - 1)]);
        }
    }
    part += (prices[size - 1] - prices[*(seperator.end() - 1)]);
    return part;
}


