#include "nk.h"
// **!!**BM43 包含min函数的栈
// https://www.nowcoder.com/practice/4c776177d2c04c2494f2555c9fcc1e49?tpId=295&tqId=23281&ru=%2Fexam%2Foj&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
// 一个存储数据的栈（可以实现除min()以外的功能），一个辅助栈(辅助栈的栈顶永远是min,实现min功能)
// 如果 value > 辅助栈的栈顶元素，就将辅助栈的栈顶元素（即最小值）再压入栈一次。
class minstack
{
public:
    void push(int value)
    {
        nstack.push(value);
        if (minstack.empty() || value < minstack.top())
        {
            minstack.push(value);
        }
        else
        {
            minstack.push(minstack.top());
        }
    }

    void pop()
    {
        nstack.pop();
        minstack.pop();
    }

    int top()
    {
        return nstack.top();
    }

    int min()
    {
        return minstack.top();
    }

private:
    stack<int> nstack;
    stack<int> minstack;
};
