#include "nk.h"

// BM3 链表中的节点每k个一组翻转
// https://www.nowcoder.com/practice/b49c3dc907814e9bbfa8437c251b028e?tpId=295&tqId=722&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
ListNode *reverse(ListNode *head)
{
    ListNode *prev = head;
    ListNode *cur = prev->next;

    while (cur)
    {
        ListNode *nextNode = cur->next;
        cur->next = prev;

        prev = cur;
        cur = nextNode;
    }
    return prev;
}

ListNode *reverseKGroup(ListNode *head, int k)
{
    ListNode *dummy = new ListNode(-1);
    dummy->next = head;
    ListNode *seqHead = dummy->next, *seqEnd = dummy;
    ListNode *nextSeqHead = nullptr, *preSeqNode = dummy;

    while (seqEnd->next)
    {
        seqEnd = preSeqNode;
        for (int i = 0; i < k && seqEnd; ++i)
        {
            seqEnd = seqEnd->next;
        }
        if (!seqEnd)
            break;
        nextSeqHead = seqEnd->next;
        seqEnd->next = nullptr;

        // 翻转长度为k的序列
        // 翻转后 原序列的 seqHead 成为尾部， seqEnd成为头部
        // 将 preSeqNode->next 指向 头部(seqEnd)
        // 尾部(seqHead)的next 指向nextSeqHead
        preSeqNode->next = reverse(seqHead);
        seqHead->next = nextSeqHead;
        // 到这里完成一次k序列的翻转

        // 为待翻转序列做准备，所以这里的 preSeqNode 和 seqHead都是对于 待翻转序列的
        preSeqNode = seqHead;
        seqHead = nextSeqHead;
    }
    head = dummy->next;
    delete dummy;
    return head;
}