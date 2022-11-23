#include "nk.h"

// BM6 判断链表中是否有环
// https://www.nowcoder.com/practice/650474f313294468a4ded3ce0f7898b9?tpId=295&tqId=605&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
bool hasCycle(ListNode *head)
{
    if (!head)
        return false;

    ListNode *slow = head, *fast = head;
    while (slow && fast)
    {
        slow = slow->next;
        if (!slow)
        {
            return false;
        }
        fast = fast->next->next;
        if (fast == slow)
        {
            return true;
        }
    }
    return false;
}