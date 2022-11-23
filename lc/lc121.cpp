#include "lc.h"
// leetcode 121  看了动态规划题解
int maxProfit(vector<int> &prices)
{
    vector<int> minDay = {0};
    int size = prices.size();
    int maxPrice = 0;

    for (int i = 1; i < size; ++i)
    {
        minDay.push_back(prices[i] < prices[minDay[i - 1]] ? i : minDay[i - 1]);
        maxPrice = max(prices[i] - prices[minDay[i - 1]], maxPrice);
    }
    return maxPrice;
}

int maxProfit2(vector<int> &prices)
{
    vector<int> minPrice{prices[0]};
    int size = prices.size();
    int res = 0;
    for (int i = 1; i < size; ++i)
    {
        minPrice.push_back(min(prices[i], minPrice[i - 1]));
        res = max(res, prices[i] - minPrice[i - 1]);
    }
    return res;
}

int maxProfit3(vector<int> &prices)
{
    int minPrice = prices[0];
    int size = prices.size();
    int res = 0;
    for (int i = 1; i < size; ++i)
    {
        res = max(res, prices[i] - minPrice);
        minPrice = prices[i] < minPrice ? prices[i] : minPrice;
    }
    return res;
}
