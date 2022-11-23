#include "nk.h"



// BM7 链表中环的入口结点
// https://www.nowcoder.com/practice/253d2c59ec3e4bc68da16833f79a38e4?tpId=295&tqId=23449&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
ListNode *EntryNodeOfLoop(ListNode *pHead)
{
    unordered_set<ListNode *> nodeSet{pHead};
    ListNode *p = pHead;
    while (p)
    {
        p = p->next;
        if (nodeSet.find(p) != nodeSet.end())
        {
            return p;
        }
        else
        {
            nodeSet.insert(p);
        }
    }
    return nullptr;
}