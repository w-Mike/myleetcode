#include "nk.h"
// BM89 合并区间
// https://www.nowcoder.com/practice/69f4e5b7ad284a478777cb2a17fb5e6a?tpId=295&tqId=691&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj

// 1. 根据每个区间的左端点大小对intervals 进行排序，
// 2. 排序后再根据一定规则，对区间合并；(自己想一下，有严格的数学证明，但是靠臆想也能想得通)
bool cmp(const Interval &a, const Interval &b)
{
    return a.start < b.start ? true : false;
}

vector<Interval> merge(vector<Interval> &intervals)
{
    if (intervals.size() <= 1)
        return intervals;
    sort(intervals.begin(), intervals.end(), cmp);
    vector<Interval> res{intervals[0]};
    for (int i = 1; i < intervals.size(); ++i)
    {
        if (res.back().end < intervals[i].start)
        {
            res.push_back(intervals[i]);
        }
        else
        {
            res.back().end = max(res.back().end, intervals[i].end);
        }
    }
    return res;
}
