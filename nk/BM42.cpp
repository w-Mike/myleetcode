#include "nk.h"


// BM42 用两个栈实现队列
// https://www.nowcoder.com/practice/54275ddae22f475981afa2244dd448c6?tpId=295&tqId=23281&ru=%2Fpractice%2F1291064f4d5d4bdeaefbf0dd47d78541&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
class myqueue
{
public:
    void push(int node)
    {
        stack1.push(node);
    }

    int pop()
    {
        int node(0);
        if (stack2.empty())
        {
            while (!stack1.empty())
            {
                node = stack1.top();
                stack1.pop();
                stack2.push(node);
            }
        }
        node = stack2.top();
        stack2.pop();

        return node;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};

