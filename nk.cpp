#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
using namespace std;

// BM1: https://www.nowcoder.com/practice/75e878df47f24fdc9dc3e400ec6058ca?tpId=295&tqId=23286&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj%3Fpage%3D1%26tab%3D%25E7%25AE%2597%25E6%25B3%2595%25E7%25AF%2587%26topicId%3D295
struct ListNode
{
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL)
    {
    }
};
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
//更好的题解  思路清晰
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
// BM17: https://www.nowcoder.com/practice/d3df40bd23594118b57554129cadf47b?tpId=295&tqId=1499549&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int search(vector<int> &nums, int target)
{
    // write code here
    
}

ListNode *initList(ListNode *head)
{
    int num = 5;
    ListNode *p = head;
    while (num--)
    {
        ListNode *node = new ListNode(num);
        p->next = node;
        p = node;
    }
    return head;
}
int main()
{
    ListNode *head = new ListNode(6);
    head = initList(head);
    reverseBetween(head, 2, 4);
    return 1;
}