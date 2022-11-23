#include "nk.h"
// BM64 最小花费爬楼梯
// https://www.nowcoder.com/practice/6fe0302a058a4e4a834ee44af88435c7?tpId=295&tqId=2366451&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int minCostClimbingStairs(vector<int> &cost)
{
    // write code here
    int n = cost.size();
    vector<int> res(n + 1, 0);
    for (int i = 2; i <= n; ++i)
    {
        //        int costbeftwo = res[i - 2] + cost[i - 2];
        //        int costbefone = res[i - 1] + cost[i - 1];
        //
        //        res[i] = costbeftwo > costbefone ? costbefone : costbeftwo;
        res[i] = min(res[i - 2] + cost[i - 2], res[i - 1] + cost[i - 1]);
    }
    return res[n];
}
