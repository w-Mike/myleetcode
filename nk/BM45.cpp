#include "nk.h"


// BM45 滑动窗口的最大值
// https://www.nowcoder.com/practice/1624bc35a45c42c0bc17d17fa0cba788?tpId=295&tqId=23458&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
// 自己写的  半暴力求解
vector<int> maxInWindows(const vector<int> &num, unsigned int size)
{
    if (!size)
        return {};
    int maxIndex = 0, max = -1e5;
    int winBegin = 0, winEnd = size - 1;
    int numSize = num.size();

    vector<int> res{};
    while (winEnd < numSize)
    {
        if (!(maxIndex <= winEnd && maxIndex >= winBegin && max > num[winEnd]))
        {
            max = num[winBegin];
            for (int i = winBegin + 1; i <= winEnd; ++i)
            {
                if (num[i] > max)
                {
                    max = num[i];
                    maxIndex = i;
                }
            }
        }
        res.push_back(max);
        ++winBegin;
        ++winEnd;
    }
    return res;
}

// 方法2--优先队列法（大根堆）
vector<int> maxInWindows_2(const vector<int> &num, unsigned int size)
{
    int numsize = num.size();
    if (numsize < size || !size)
        return {};
    priority_queue<pair<int, int>> que;
    for (int i = 0; i < size; ++i)
    {
        que.emplace(num[i], i);
    }
    vector<int> res{que.top().first};

    for (int k = size; k < numsize; ++k)
    {
        que.emplace(num[k], k);
        while (que.top().second <= k - size)
        {
            que.pop();
        }
        res.push_back(que.top().first);
    }
    return res;
}

// 方法三  单调队列
vector<int> maxInWindows_3(const vector<int> &num, unsigned int size)
{
    int numsize = num.size();
    if (size == 0 || size > numsize)
        return {};

    deque<int> dq;
    // 对第一个窗口进行初始化
    for (int i = 0; i < size; ++i)
    {
        // 判断单调队列尾部元素 和 新添加的元素的大小
        while (!dq.empty() && num[i] > num[dq.back()])
        {
            dq.pop_back();
        }
        dq.push_back(i);
    }
    vector<int> res{num[dq.front()]};
    for (int i = size; i < numsize; ++i)
    {
        // 如果最大元素对应位置不在窗口内了,将其弹出队列
        if (dq.front() <= i - size)
        {
            dq.pop_front();
        }
        // 如果右移到的元素比队列中后端元素大，就将后端元素弹出
        while (!dq.empty() && num[i] > num[dq.back()])
        {
            dq.pop_back();
        }
        dq.push_back(i);
        res.push_back(num[dq.front()]);
    }
    return res;
}

