#include "nk.h"

// BM44 有效括号序列
// https://www.nowcoder.com/practice/37548e94a270412c8b9fb85643c8ccc2?tpId=295&tqId=726&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
bool isValid(string s)
{
    // write code here
    stack<char> nstack;
    for (char c : s)
    {
        switch (c)
        {
        case ')':
            if (!nstack.empty() && nstack.top() == '(')
                nstack.pop();
            else
                nstack.push(c);
            break;
        case ']':
            if (!nstack.empty() && nstack.top() == '[')
                nstack.pop();
            else
                nstack.push(c);
            break;
        case '}':
            if (!nstack.empty() && nstack.top() == '{')
                nstack.pop();
            else
                nstack.push(c);
            break;
        default:
            nstack.push(c);
        }
    }
    return nstack.empty() ? true : false;
}
