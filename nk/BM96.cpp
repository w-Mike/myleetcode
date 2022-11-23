#include "nk.h"
// BM96 主持人调度（二）
// https://www.nowcoder.com/practice/4edf6e6d01554870a12f218c94e8a299?tpId=295&tqId=1267319&ru=%2Fpractice%2Fe19927a8fd5d477794dac67096862042&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
int minmumNumberOfHost(int n, vector<vector<int>> &startEnd)
{
    vector<int> start;
    vector<int> end;
    for (const auto time : startEnd)
    {
        start.push_back(time[0]);
        end.push_back(time[1]);
    }
    sort(start.begin(), start.end());
    sort(end.begin(), end.end());
    int num = 0;
    int endindex = 0;
    for (int i = 0; i < n; ++i)
    {
        if (start[i] >= end[endindex])
        {
            ++endindex;
        }
        else
        {
            ++num;
        }
    }
    return num;
}