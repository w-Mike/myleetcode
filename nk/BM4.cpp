#include "nk.h"

// BM4 合并两个排序的链表
// https://www.nowcoder.com/practice/d8b6b4358f774294a89de2a6ac4d9337?tpId=295&tqId=23267&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
ListNode *Merge(ListNode *pHead1, ListNode *pHead2)
{
    ListNode *dummy = new ListNode(-1);
    ListNode *p = dummy;

    while (pHead1 && pHead2)
    {
        if (pHead1->val < pHead2->val)
        {
            p->next = pHead1;
            pHead1 = pHead1->next;
        }
        else
        {
            p->next = pHead2;
            pHead2 = pHead2->next;
        }
        p = p->next;
        p->next = nullptr;
    }
    if (pHead1)
        p->next = pHead1;
    else if (pHead2)
        p->next = pHead2;
    p = dummy->next;
    delete dummy;
    return p;
}
