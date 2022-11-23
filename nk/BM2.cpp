#include "nk.h"

// BM2 https://www.nowcoder.com/practice/b58434e200a648c589ca2063f1faf58c?tpId=295&tags=&title=&difficulty=0&judgeStatus=0&rp=0&sourceUrl=%2Fexam%2Foj%3Fpage%3D1%26tab%3D%25E7%25AE%2597%25E6%25B3%2595%25E7%25AF%2587%26topicId%3D295
ListNode *reverseBetween(ListNode *head, int m, int n)
{
    // write code here
    ListNode *prevhead = new ListNode(-1);
    prevhead->next = head;

    ListNode *prev = prevhead;
    int rotatime = m - 1;
    // 该循环的循环次数为 m 的值
    while (rotatime--)
    {
        prev = prev->next;
    }
    ListNode *curr = prev->next;
    ListNode *next = nullptr;
    ListNode *seqhead = curr;
    rotatime = n - m + 1;
    while (rotatime--)
    {
        next = curr->next;
        curr->next = prev;

        prev = curr;
        curr = next;
    }
    // 循环结束后  head -> ... -> node <- [seqhead] <- node <- ... <- prev (中断) curr -> ... -> node->tail
    // 所以说循环结束后要做的就是 让 seqhead->next 指向curr
    seqhead->next->next = prev;
    seqhead->next = curr;
    // 关于返回值也有陷阱，在m=1时，要考虑的问题(必须要把新增的head前的prehead指针保存下来，不然无法确定新序列的头部在哪)
    return prevhead->next;
}