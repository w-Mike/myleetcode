#include "nk.h"
using namespace std;

// BM1: https://www.nowcoder.com/practice/75e878df47f24fdc9dc3e400ec6058ca?tpId=295&tqId=23286&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj%3Fpage%3D1%26tab%3D%25E7%25AE%2597%25E6%25B3%2595%25E7%25AF%2587%26topicId%3D295
ListNode *ReverseList(ListNode *pHead)
{
    if (!pHead)
        return pHead;
    ListNode *p = pHead;
    ListNode *pnext = pHead->next;
    ListNode *temp = NULL;

    while (pnext)
    {
        temp = pnext->next;
        pnext->next = p;
        p = pnext;
        pnext = temp;
    }
    pHead->next = NULL;
    pHead = p;
    return pHead;
}

// 更好的题解  思路清晰
ListNode *ReverseList2(ListNode *pHead)
{
    ListNode *prev = nullptr;
    ListNode *curr = pHead;
    ListNode *next = nullptr;
    // 每次循环后 prev 都与以curr为头的链表断开连接，prev成为了一个单独的个体
    // prev 以及其以前的序列都是反序的，curr以及其以后的序列都是正序的(未进行反序的)
    while (curr)
    {
        next = curr->next;
        curr->next = prev;

        prev = curr;
        curr = next;
    }
    return prev;
}
