#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <map>
#include <stack>
#include <numeric>
#include <queue>

#include "nk.h"

using namespace std;

// BM1: https://www.nowcoder.com/practice/75e878df47f24fdc9dc3e400ec6058ca?tpId=295&tqId=23286&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj%3Fpage%3D1%26tab%3D%25E7%25AE%2597%25E6%25B3%2595%25E7%25AF%2587%26topicId%3D295
ListNode *ReverseList(ListNode *pHead) {
    if (!pHead)
        return pHead;
    ListNode *p = pHead;
    ListNode *pnext = pHead->next;
    ListNode *temp = NULL;

    while (pnext) {
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
ListNode *ReverseList2(ListNode *pHead) {
    ListNode *prev = nullptr;
    ListNode *curr = pHead;
    ListNode *next = nullptr;
    // 每次循环后 prev 都与以curr为头的链表断开连接，prev成为了一个单独的个体
    // prev 以及其以前的序列都是反序的，curr以及其以后的序列都是正序的(未进行反序的)
    while (curr) {
        next = curr->next;
        curr->next = prev;

        prev = curr;
        curr = next;
    }
    return prev;
}

// BM2 https://www.nowcoder.com/practice/b58434e200a648c589ca2063f1faf58c?tpId=295&tags=&title=&difficulty=0&judgeStatus=0&rp=0&sourceUrl=%2Fexam%2Foj%3Fpage%3D1%26tab%3D%25E7%25AE%2597%25E6%25B3%2595%25E7%25AF%2587%26topicId%3D295
ListNode *reverseBetween(ListNode *head, int m, int n) {
    // write code here
    ListNode *prevhead = new ListNode(-1);
    prevhead->next = head;

    ListNode *prev = prevhead;
    int rotatime = m - 1;
    // 该循环的循环次数为 m 的值
    while (rotatime--) {
        prev = prev->next;
    }
    ListNode *curr = prev->next;
    ListNode *next = nullptr;
    ListNode *seqhead = curr;
    rotatime = n - m + 1;
    while (rotatime--) {
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

// BM3 链表中的节点每k个一组翻转
// https://www.nowcoder.com/practice/b49c3dc907814e9bbfa8437c251b028e?tpId=295&tqId=722&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
ListNode *reverse(ListNode *head) {
    ListNode *prev = head;
    ListNode *cur = prev->next;

    while (cur) {
        ListNode *nextNode = cur->next;
        cur->next = prev;

        prev = cur;
        cur = nextNode;
    }
    return prev;
}

ListNode *reverseKGroup(ListNode *head, int k) {
    ListNode *dummy = new ListNode(-1);
    dummy->next = head;
    ListNode *seqHead = dummy->next, *seqEnd = dummy;
    ListNode *nextSeqHead = nullptr, *preSeqNode = dummy;

    while (seqEnd->next) {
        seqEnd = preSeqNode;
        for (int i = 0; i < k && seqEnd; ++i) {
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

// BM4 合并两个排序的链表
// https://www.nowcoder.com/practice/d8b6b4358f774294a89de2a6ac4d9337?tpId=295&tqId=23267&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
ListNode *Merge(ListNode *pHead1, ListNode *pHead2) {
    ListNode *dummy = new ListNode(-1);
    ListNode *p = dummy;

    while (pHead1 && pHead2) {
        if (pHead1->val < pHead2->val) {
            p->next = pHead1;
            pHead1 = pHead1->next;
        } else {
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

// BM17: https://www.nowcoder.com/practice/d3df40bd23594118b57554129cadf47b?tpId=295&tqId=1499549&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int search(vector<int> &nums, int target) {
    // write code here
    size_t size = nums.size();
    if (!size)
        return -1;
    int begin = 0;
    int end = size - 1;
    int mid;
    while (end >= begin) {
        mid = begin + (end - begin) / 2;
        if (nums[mid] == target)
            return mid;
        if (nums[mid] > target) {
            end = mid - 1;
        } else if (nums[mid] < target) {
            begin = mid + 1;
        }
    }
    return -1;
}

// BM18 https://www.nowcoder.com/practice/abc3fe2ce8e146608e868a70efebf62e?tpId=295&tags=&title=&difficulty=0&judgeStatus=0&rp=0&sourceUrl=%2Fexam%2Foj
// 二维的二分查找
bool Find(int target, vector<vector<int>> array) {
    if (array.empty()) {
        return false;
    }
    int m = array.size();
    int n = array[0].size();

    int row = 0;
    int col = n - 1;
    int val = array[row][col];

    // 初始值为数组右上角的值，其左边的元素都比他小，下边的元素都比他大
    // 查找范围永远是以 val为右上角的数组
    // 比较target 与初始值val的大小，如果 target小于val，说明 val这一列上的数据都可以排除了，反之val那一行就可以排除了

    // 关于循环条件，col是递减的，row是递增的 所以判断条件就是
    while (row < m && col >= 0) {
        if (val == target) {
            return true;
        }
        if (val < target) {
            ++row;
        } else if (val > target) {
            --col;
        }
        val = array[row][col];
    }
    return false;
}

// BM19 寻找峰值
// https://www.nowcoder.com/practice/fcf87540c4f347bcb4cf720b5b350c76?tpId=295&tqId=2227748&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int divFind(const vector<int> &nums, const int &begin, const int &end) {
    int mid = begin + (end - begin) / 2;
    if (begin > end)
        return -1;
    if (mid == 0) {
        if (nums[mid] > nums[mid + 1]) {
            return mid;
        }
    } else if (mid == nums.size() - 1) {
        if (nums[mid] > nums[mid - 1]) {
            return mid;
        }
    } else if (nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1]) {
        return mid;
    }
    int res = divFind(nums, begin, mid - 1);
    int res2 = divFind(nums, mid + 1, end);
    if (res != -1)
        return res;
    else if (res2 != -1)
        return res2;
    else
        return -1;
}

int findPeakElement(vector<int> &nums) {
    // write code here
    int begin = 0;
    int end = nums.size() - 1;
    int res = 0;
    res = divFind(nums, begin, end);
    return res;
}

// 更好的解法，官方题解：
int findPeakElement_2(vector<int> &nums) {
    // write code here4
    int begin = 0, end = nums.size() - 1;
    int mid = 0;
    // 记住， mid 总是靠左的，所以最终结果只能是 begin == end，退出循环
    while (begin < end) {
        mid = (begin + end) / 2; // 因为 begin < end， 所以 mid+1 必不可能越界
        if (nums[mid] < nums[mid + 1]) {
            begin = mid + 1;
        } else {
            end = mid;
        }
    }
    return begin;
}

// BM20 数组中的逆序对
// https://www.nowcoder.com/practice/96bd6684e04a44eb80e6a68efc0ec6c5?tpId=295&tqId=2227748&ru=%2Fexam%2Foj&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj

//

void merge(vector<int> &data, vector<int> &tmp, int begin, int end, int mid, unsigned int &res) {
    // 两个vec 一个 [begin, mid]  一个 [mid+1, end]
    int i = begin, j = mid + 1, k = 0;
    while (i <= mid && j <= end) {
        if (data[i] > data[j]) {
            tmp[k++] = data[j++];
            res += (mid - i + 1);
        } else {
            tmp[k++] = data[i++];
        }
    }
    while (i <= mid) {
        tmp[k++] = data[i++];
    }
    while (j <= end) {
        tmp[k++] = data[j++];
    }
    i = begin, k = 0;
    while (i <= end) {
        data[i++] = tmp[k++];
    }
}

void merge_sort(vector<int> &data, vector<int> &tmp, int begin, int end, unsigned int &res) {
    if (begin == end)
        return;
    int mid = (begin + end) >> 1;
    merge_sort(data, tmp, begin, mid, res);
    merge_sort(data, tmp, mid + 1, end, res);
    merge(data, tmp, begin, end, mid, res);
}

int InversePairs(vector<int> data) {
    const int mod = 1000000007;
    vector<int> tmp(data.size());
    unsigned int res = 0;
    merge_sort(data, tmp, 0, data.size() - 1, res);
    return res % mod;
}

// BM23--二叉树前序遍历
// https://www.nowcoder.com/practice/5e2135f4d2b14eb8a5b06fab4c938635?tpId=295&tqId=2291302&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
// 递归
void func(TreeNode *root, vector<int> &vec) {
    if (!root)
        return;
    vec.push_back(root->val);
    if (root->left)
        func(root->left, vec);
    if (root->right)
        func(root->right, vec);
}

vector<int> preorderTraversal(TreeNode *root) {
    vector<int> res{};
    func(root, res);
    return res;
}

// 非递归--所有递归都可以用 Stack 实现
vector<int> preorderTraversal_stack(TreeNode *root) {
    vector<int> res{};
    TreeNode *ptr = root;
    TreeNode *node = nullptr;
    stack<TreeNode *> nodeStack;
    while (ptr || !nodeStack.empty()) {
        while (ptr) {
            res.push_back(ptr->val);
            nodeStack.push(ptr);
            ptr = ptr->left;
        }
        node = nodeStack.top();
        nodeStack.pop();
        ptr = node->right;
    }
}

// 更清楚的写法
vector<int> preorderTraversal_stack1(TreeNode *root) {
    vector<int> res{};
    stack<TreeNode *> nstack;
    TreeNode *ptr = root, *node = nullptr;
    while (!(!ptr && nstack.empty())) {
        if (ptr) {
            nstack.push(ptr);
            res.push_back(ptr->val);
            ptr = ptr->left;
        } else {
            node = nstack.top();
            nstack.pop();
            ptr = node->right;
        }
    }
    return res;
}

// BM24 二叉树的中序遍历
// https://www.nowcoder.com/practice/0bf071c135e64ee2a027783b80bf781d?tpId=295&tqId=2291302&ru=%2Fexam%2Foj&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
void inorderfunc(TreeNode *root, vector<int> &vec) {
    if (!root)
        return;
    if (root->left)
        inorderfunc(root->left, vec);
    vec.push_back(root->val);
    if (root->right)
        inorderfunc(root->right, vec);
}

vector<int> inorderTraversal(TreeNode *root) {
    // write code here
    vector<int> res{};
    inorderfunc(root, res);
    return res;
}

// stack 实现
vector<int> inorderTraversal_stack(TreeNode *root) {
    vector<int> res{};
    TreeNode *ptr = root, *node = nullptr;
    stack<TreeNode *> nodestack;

    while (ptr || !nodestack.empty()) {
        while (ptr) {
            nodestack.push(ptr);
            ptr = ptr->left;
        }
        node = nodestack.top();
        nodestack.pop();
        res.push_back(node->val);
        ptr = node->right;
    }
    return res;
}

// BM25 二叉树的后序遍历
// https://www.nowcoder.com/practice/1291064f4d5d4bdeaefbf0dd47d78541?tpId=295&tqId=2291302&ru=%2Fexam%2Foj&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
// stack 写法
vector<int> postorderTraversal(TreeNode *root) {
    // write code here
    stack<TreeNode *> nodestack;
    vector<int> res{};
    TreeNode *node = nullptr, *ptr = root, *temp = nullptr;
    int visrtime = 1;
    while (ptr || !nodestack.empty()) {
        while (ptr) {
            nodestack.push(ptr);
            ptr = ptr->left;
        }
        node = nodestack.top();
        if (temp == node) {
            res.push_back(node->val);
            nodestack.pop();
            node = nodestack.top();
        }
        temp = node;
        ptr = node->right;
    }
    return res;
}

vector<int> postorderTraversal1(TreeNode *root) {
    vector<int> res{};
    stack<TreeNode *> nstack;
    TreeNode *ptr = root, *node = nullptr, *visedr = nullptr;
    while (!(!ptr && nstack.empty())) {
        if (ptr) {
            nstack.push(ptr);
            ptr = ptr->left;
        } else {
            node = nstack.top();
            if (node->right && visedr != node->right) {
                ptr = node->right;
            } else {
                visedr = node;
                nstack.pop();
                res.push_back(node->val);
            }
        }
    }
    return res;
}

// 巧解法
// 原理 根据 描边法来做遍历的话，会发现访问一次就输出是前序，访问两次输出是中序，访问三次输出是后序，
// 同时，如果从右子树开始描边（也就是从顺时针旋转），会发现访问一次就输出的是后序遍历的倒序，
// 而显然先序遍历是简单的，容易实现的，所以可以利用一个辅助stack存储访问序列再取出，来实现后续遍历
vector<int> postorderTraversal_stack2(TreeNode *root) {
    vector<int> res;
    stack<int> revres;
    stack<TreeNode *> nstack;
    TreeNode *ptr = root, *node = nullptr;
    while (!(!ptr && nstack.empty())) {
        if (ptr) {
            nstack.push(ptr);
            revres.push(ptr->val);
            ptr = ptr->right;
        } else {
            node = nstack.top();
            nstack.pop();
            ptr = node->left;
        }
    }
    while (!revres.empty()) {
        res.push_back(revres.top());
        revres.pop();
    }
    return res;
}

// BM26 求二叉树的层序遍历
// https://www.nowcoder.com/practice/04a5560e43e24e9db4595865dc9c63a3?tpId=295&tqId=644&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
vector<vector<int>> levelOrder(TreeNode *root) {
    // write code here
    if (!root)
        return {};
    queue<TreeNode *> nodeque;
    nodeque.push(root);
    vector<vector<int>> res;
    while (!nodeque.empty()) {
        vector<int> layer;
        int size = nodeque.size();
        while (size--) {
            root = nodeque.front();
            layer.push_back(root->val);
            if (root->left)
                nodeque.push(root->left);
            if (root->right)
                nodeque.push(root->right);
            nodeque.pop();
        }
        res.push_back(layer);
    }
    return res;
}

// BM42 用两个栈实现队列
// https://www.nowcoder.com/practice/54275ddae22f475981afa2244dd448c6?tpId=295&tqId=23281&ru=%2Fpractice%2F1291064f4d5d4bdeaefbf0dd47d78541&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
class myqueue {
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        int node(0);
        if (stack2.empty()) {
            while (!stack1.empty()) {
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

// **!!**BM43 包含min函数的栈
// https://www.nowcoder.com/practice/4c776177d2c04c2494f2555c9fcc1e49?tpId=295&tqId=23281&ru=%2Fexam%2Foj&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
// 一个存储数据的栈（可以实现除min()以外的功能），一个辅助栈(辅助栈的栈顶永远是min,实现min功能)
// 如果 value > 辅助栈的栈顶元素，就将辅助栈的栈顶元素（即最小值）再压入栈一次。
class minstack {
public:
    void push(int value) {
        nstack.push(value);
        if (minstack.empty() || value < minstack.top()) {
            minstack.push(value);
        } else {
            minstack.push(minstack.top());
        }
    }

    void pop() {
        nstack.pop();
        minstack.pop();
    }

    int top() {
        return nstack.top();
    }

    int min() {
        return minstack.top();
    }

private:
    stack<int> nstack;
    stack<int> minstack;
};

// BM44 有效括号序列
// https://www.nowcoder.com/practice/37548e94a270412c8b9fb85643c8ccc2?tpId=295&tqId=726&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
bool isValid(string s) {
    // write code here
    stack<char> nstack;
    for (char c: s) {
        switch (c) {
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

// BM45 滑动窗口的最大值
// https://www.nowcoder.com/practice/1624bc35a45c42c0bc17d17fa0cba788?tpId=295&tqId=23458&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
// 自己写的  半暴力求解
vector<int> maxInWindows(const vector<int> &num, unsigned int size) {
    if (!size) return {};
    int maxIndex = 0, max = -1e5;
    int winBegin = 0, winEnd = size - 1;
    int numSize = num.size();

    vector<int> res{};
    while (winEnd < numSize) {
        if (!(maxIndex <= winEnd && maxIndex >= winBegin && max > num[winEnd])) {
            max = num[winBegin];
            for (int i = winBegin + 1; i <= winEnd; ++i) {
                if (num[i] > max) {
                    max = num[i];
                    maxIndex = i;
                }
            }
        }
        res.push_back(max);
        ++winBegin;
        ++winEnd;
    }
    return res;
}

// 方法2--优先队列法（大根堆）
vector<int> maxInWindows_2(const vector<int> &num, unsigned int size) {
    int numsize = num.size();
    if (numsize < size || !size) return {};
    priority_queue<pair<int, int >> que;
    for (int i = 0; i < size; ++i) {
        que.emplace(num[i], i);
    }
    vector<int> res{que.top().first};

    for (int k = size; k < numsize; ++k) {
        que.emplace(num[k], k);
        while (que.top().second <= k - size) {
            que.pop();
        }
        res.push_back(que.top().first);
    }
    return res;
}

// 方法三  单调队列
vector<int> maxInWindows_3(const vector<int> &num, unsigned int size) {
    int numsize = num.size();
    if (size == 0 || size > numsize) return {};

    deque<int> dq;
    // 对第一个窗口进行初始化
    for (int i = 0; i < size; ++i) {
        // 判断单调队列尾部元素 和 新添加的元素的大小
        while (!dq.empty() && num[i] > num[dq.back()]) {
            dq.pop_back();
        }
        dq.push_back(i);
    }
    vector<int> res{num[dq.front()]};
    for (int i = size; i < numsize; ++i) {
        // 如果最大元素对应位置不在窗口内了,将其弹出队列
        if (dq.front() <= i - size) {
            dq.pop_front();
        }
        // 如果右移到的元素比队列中后端元素大，就将后端元素弹出
        while (!dq.empty() && num[i] > num[dq.back()]) {
            dq.pop_back();
        }
        dq.push_back(i);
        res.push_back(num[dq.front()]);
    }
    return res;
}


// BM50 两数之和
// https://www.nowcoder.com/practice/20ef0972485e41019e39543e8e895b7f?tpId=295&tqId=745&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
vector<int> twoSum(vector<int> &numbers, int target) {
    // write code here
    unordered_map<int, int> numap;
    for (int i = 0; i < numbers.size(); ++i) {
        if (numap.find(target - numbers[i]) != numap.end()) {
            return {numap[target - numbers[i]] + 1, i + 1};
        }
        numap[numbers[i]] = i;
    }
    return {};
}

// BM51 数组中出现次数超过一半的数字
// https://www.nowcoder.com/practice/e8a1b01a2df14cb2b228b30ee6a92163?tpId=295&tqId=745&ru=%2Fexam%2Foj&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
int MoreThanHalfNum_Solution(vector<int> numbers) {
    unordered_map<int, int> numcount;
    int boudary(numbers.size() / 2);
    int res(-1);
    for (int num: numbers) {
        ++numcount[num];
        if (numcount[num] > boudary)
            res = num;
    }
    return res;
}

//  消消乐算法（额。。。）
int MoreThanHalfNum_Solution_stack(vector<int> numbers) {
    stack<int> nstack;
    for (int num: numbers) {
        if (!nstack.empty() && nstack.top() != num) {
            nstack.pop();
        } else {
            nstack.push(num);
        }
    }
    return nstack.top();
}

// BM52 数组中只出现一次的两个数字
// https://www.nowcoder.com/practice/389fc1c3d3be4479a154f63f495abff8?tpId=295&tqId=1375231&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
vector<int> FindNumsAppearOnce(vector<int> &array) {
    // write code here
    vector<int> res{};
    map<int, int> numap;
    for (int i: array) {
        ++numap[i];
    }
    for (auto num: numap) {
        if (num.second == 1)
            res.push_back(num.first);
    }
    return res;
}
// 利用了 题目中的限制条件， 只有两个数出现了一次，所以可以用更高效的方式
// 别忘了按位运算。 异或可以从一组 只有一个存在一次的数 的数组 中找到这个数
// 但是这道题 有两个数出现了一次，所以要把这俩数给分组，分成两个组。
// 这样两个组分别做异或运算就得到了这两个数了。
// 所以该如何进行分组呢，如果把所有的数都进行异或运算 结果就是 要找的两个数字的异或
// 按位观察结果，两个不相同的数字的二进制必然有几个位不同。
// 找出最低位，然后让每个数都与这一位进行&运算，这样必然能将这俩数分开，

// warn！！： 注意 移位运算符不会改变运算数的值，所以需要 使用 mask <<= 1 而不是 mask<<1,这个不会改变mask的值
vector<int> FindNumsAppearOnce_bit(vector<int> &array) {
    int tmp = 0;
    for (int num: array) {
        tmp ^= num;
    }
    int mask = 1;
    while (!(tmp & mask)) {
        mask <<= 1;
    }
    int a = 0, b = 0;
    for (int num: array) {
        if (!(mask & num)) {
            a ^= num;
        } else {
            b ^= num;
        }
    }
    tmp = a;
    a = a < b ? a : b;
    b = a == tmp ? b : tmp;
    return {a, b};
}

// BM53 缺失的第一个正整数
// https://www.nowcoder.com/practice/50ec6a5b0e4e45348544348278cdcee5?tpId=295&tqId=2188893&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int minNumberDisappeared(vector<int> &nums) {
    // write code here
    unordered_set<int> numset;
    for (int num: nums) {
        numset.insert(num);
    }
    int i = 0;
    while (++i) {
        if (numset.find(i) == numset.end()) break;
    }
    return i;
}

int minNumberDisappeared_2(vector<int> &nums) {
    int n = nums.size();
    // 将 0 或者负数给映射到数组范围外的下标
    for (int &num: nums) {
        if (num <= 0) {
            num = n + 1;
        }
    }
    for (int i = 0; i < n; ++i) {
        int index = abs(nums[i]);
        // 注意 数组中没有重复的数字，所以该位置不会再被改变了，已经被标记为负数了
        if (index <= n) {
            nums[index - 1] = -nums[index - 1];
        }
    }
    int res = n + 1;
    for (int i = 0; i < n; ++i) {
        if (nums[i] > 0) {
            res = i + 1;
            break;
        }
    }
    return res;
}


// BM55 没有重复项数字的全排列
// https://www.nowcoder.com/practice/4bcf3081067a4d028f95acee3ddcd2b1?tpId=295&tqId=701&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
// 递归回溯法
void permute_recursion(vector<vector<int>> &res, const vector<int> &num, vector<int> &list) {
    if (list.size() == num.size()) {
        res.push_back(list);
        return;
    }
    for (int i = 0; i < num.size(); ++i) {
        vector<int>::iterator iter = find(list.begin(), list.end(), num[i]);
        if (iter != list.end())
            continue;
        list.push_back(num[i]);
        permute_recursion(res, num, list);
        list.pop_back();
    }
}

vector<vector<int>> permute(vector<int> &num) {
    vector<vector<int>> res{};
    vector<int> list{};
    permute_recursion(res, num, list);
    return res;
}

// BM56 有重复项数字的全排列
// https://www.nowcoder.com/practice/a43a2b986ef34843ac4fdd9159b69863?tpId=295&tags=&title=&difficulty=0&judgeStatus=0&rp=0&sourceUrl=%2Fexam%2Foj

void permuteUnique_recursion(const vector<int> &num, vector<vector<int>> &res, vector<int> &list, vector<int> mark) {
    if (list.size() == num.size()) {
        res.push_back(list);
        return;
    }
    unordered_set<int> nset{};
    for (int i = 0; i < num.size(); ++i) {
        if (mark[i] || (nset.find(num[i]) != nset.end()))
            continue;
        nset.insert(num[i]);
        list.push_back(num[i]);
        mark[i] = 1;

        permuteUnique_recursion(num, res, list, mark);
        list.pop_back();
        mark[i] = 0;
    }
}

vector<vector<int>> permuteUnique(vector<int> &num) {
    sort(num.begin(), num.end());
    vector<vector<int>> res{};
    vector<int> list{};
    vector<int> mark(num.size(), 0);
    permuteUnique_recursion(num, res, list, mark);
    return res;
}

// BM57 岛屿数量
// https://www.nowcoder.com/practice/0c9664d1554e466aa107d899418e814e?tpId=295&tqId=1024684&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
// DFS
void dfs(vector<vector<char>> &grid, int i, int j) {
    int m = grid.size();
    int n = grid[0].size();
    if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == '0') {
        return;
    }
    grid[i][j] = '0';
    dfs(grid, i - 1, j);
    dfs(grid, i + 1, j);
    dfs(grid, i, j - 1);
    dfs(grid, i, j + 1);
}

// BFS
void bfs(vector<vector<char>> &grid, int i, int j) {
    int m = grid.size();
    int n = grid[0].size();
    int node = i * n + j;
    queue<int> nodes;
    nodes.push(node);
    while (!nodes.empty()) {
        node = nodes.front();
        nodes.pop();
        int row = node / n;
        int col = node % n;
        grid[row][col] = 0;
        if ((row - 1) >= 0 && grid[row - 1][col] == '1') {
            node = n * (row - 1) + col;
            nodes.push(node);
        }
        if ((row + 1) < m && grid[row + 1][col] == '1') {
            node = n * (row + 1) + col;
            nodes.push(node);
        }
        if ((col - 1) >= 0 && grid[row][col - 1] == '1') {
            node = n * row + col - 1;
            nodes.push(node);
        }
        if ((col + 1) < n && grid[row][col + 1] == '1') {
            node = n * row + col + 1;
            nodes.push(node);
        }
    }
}

int solve(vector<vector<char>> &grid) {
    // write code here
    if (grid.empty()) return 0;
    int m = grid.size();
    int n = grid[0].size();
    int res = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '1') {
                ++res;
                //dfs(grid, i, j);
                bfs(grid, i, j);
            }
        }
    }
    return res;
}

// BM58 字符串的排列
// https://www.nowcoder.com/practice/fe6b651b66ae47d7acce78ffdd9a96c7?tpId=295&tqId=23291&ru=%2Fpractice%2F0c9664d1554e466aa107d899418e814e&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
void back(vector<string> &res, const string &str, string &rstr, vector<bool> &marked) {
    if (rstr.size() == str.size()) {
        res.push_back(rstr);
        return;
    }
    unordered_set<char> selected;

    for (int i = 0; i < str.size(); ++i) {
        if (selected.find(str[i]) != selected.end() || marked[i]) {
            continue;
        }
        rstr += str[i];
        marked[i] = true;
        selected.insert(str[i]);
        back(res, str, rstr, marked);
        marked[i] = false;
        rstr.pop_back();
    }
}

vector<string> Permutation(string str) {
    vector<string> res;
    string rstr;
    vector<bool> marked(str.size(), false);
    back(res, str, rstr, marked);
    return res;
}

// BM62 斐波那契数列
// https://www.nowcoder.com/practice/c6c7742f5ba7442aada113136ddea0c3?tpId=295&tqId=23255&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int Fibonacci(int n) {
    int fir = 1, sec = 1;
    int tmp = 0;
    for (int i = 3; i <= n; ++i) {
        tmp = fir;
        fir = sec;
        sec = tmp + sec;
    }
    return sec;
}

// BM63 跳台阶
// https://www.nowcoder.com/practice/8c82a5b80378478f9484d87d1c5f12a4?tpId=295&tqId=23255&ru=%2Fexam%2Foj&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
// 由于青蛙一次只能跳一阶或者跳两阶，所第n次的跳法就是第n-1次的跳法与第n-2次的跳法之和
// 其实就是斐波那契数列除去第一项
int jumpFloor(int number) {
    int res = 0, tmp = 0;
    int fir = 1, sec = 2;
    res = number == 1 ? fir : sec;
    for (int i = 3; i <= number; ++i) {
        tmp = fir;
        fir = sec;
        sec = tmp + sec;
    }
    res = number < 3 ? res : sec;
    return res;
}

// BM64 最小花费爬楼梯
// https://www.nowcoder.com/practice/6fe0302a058a4e4a834ee44af88435c7?tpId=295&tqId=2366451&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int minCostClimbingStairs(vector<int> &cost) {
    // write code here
    int n = cost.size();
    vector<int> res(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
//        int costbeftwo = res[i - 2] + cost[i - 2];
//        int costbefone = res[i - 1] + cost[i - 1];
//
//        res[i] = costbeftwo > costbefone ? costbefone : costbeftwo;
        res[i] = min(res[i - 2] + cost[i - 2], res[i - 1] + cost[i - 1]);
    }
    return res[n];
}
// BM65 最长公共子序列(二)
// https://www.nowcoder.com/practice/6d29638c85bb4ffd80c020fe244baf11?tpId=295&tqId=991075&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj

string LCS(string s1, string s2) {
    // write code here
    string resStr = "-1";
    int m = s1.size(), n = s2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    vector<vector<int>> mark(dp);
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                mark[i][j] = 1;         // 自身 mark为1
            } else {
                if (dp[i - 1][j] >= dp[i][j - 1]) {   // 上边大 mark 为 3
                    dp[i][j] = dp[i - 1][j];
                    mark[i][j] = 3;
                } else {                          // 左边大  mark 为 2
                    dp[i][j] = dp[i][j - 1];
                    mark[i][j] = 2;
                }
            }
        }
    }
    int resize = dp[m][n];
    // 获取最长公共子序列
    if (!resize) return resStr;
    stack<char> res;
    int i = m, j = n;
    while (res.size() < resize) {
        if (mark[i][j] == 1) {
            res.push(s1[i - 1]);
            i -= 1;
            j -= 1;
        }
        if (mark[i][j] == 2) {
            j -= 1;
        }
        if (mark[i][j] == 3) {
            i -= 1;
        }
    }
    resStr = "";
    while (!res.empty()) {
        resStr += res.top();
        res.pop();
    }
    return resStr;
}

// BM66 最长公共子串
// https://www.nowcoder.com/practice/f33f5adc55f444baa0e0ca87ad8a6aac?tpId=295&tqId=991075&ru=%2Fexam%2Foj&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj

// 垃圾做法，按照最长公共子序列的思路来做的，直接报废，不能AC
string LCS_substr(string str1, string str2) {
    // write code here
    string res = "-1";
    int m = str1.size();
    int n = str2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    vector<vector<int>> mark(dp);
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                if (i == 1 || j == 1 || str1[i - 2] == str2[j - 2]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    mark[i][j] = 1;
                    continue;
                }
            }
            if (dp[i - 1][j] >= dp[i][j - 1]) {     // 来自上 赋值为 2
                dp[i][j] = dp[i - 1][j];
                mark[i][j] = 2;
            } else {                                // 来自左  赋值为 3
                dp[i][j] = dp[i][j - 1];
                mark[i][j] = 3;
            }
        }
    }
    int resSize = dp[m][n];
    cout << resSize << endl;
    // 以下是输出最长子串部分， 由于子串是连续的所以相比于最长公共子序列，子串的输出更简单，只要找出最长公共子串的最后一个字符的下标即可
    if (!resSize) return res;
    res = "";
    stack<char> rstack;
    int i = m, j = n;
    while (mark[i][j] != 1) {
        if (mark[i][j] == 2) {
            i -= 1;
        }
        if (mark[i][j] == 3) {
            j -= 1;
        }
    }
    int end = i;
    int begin = end - resSize;
    for (int i = begin; i < end; ++i) {
        res += str1[i];
    }
    return res;
}
// 正确解法： 理解 该dp数组与 BM65 的dp数组含以上的不同！！
// 动态规划的关键就是理解dp数据的含义啊啊

// 该题的dp数组的含义是：dp[i][j] 表示str1中以字符str1[i]为结尾的和str2中以str2[j]结尾的公共子串的长度！！
// 所以如果 str1[i] != str2[j], 那么公共子串的长度为0
//    如果 str1[i] == str2[j], 那么公共子串的长度为 以 str1[i-1]和str2[j-1]为结尾的公共子串的长度+1，即 dp[i-1][j-1] + 1
// 关于初始化： 仍然是0行和0列的公共子串长度为0；
string LCS_substr2(string str1, string str2) {
    int m = str1.size(), n = str2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    int maxStrLen = 0, lstIndex = 0;

    for (int i = 0; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                if ((dp[i][j] = dp[i - 1][j - 1] + 1) > maxStrLen) {
                    maxStrLen = dp[i][j];
                    lstIndex = i;
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }
    return str1.substr(lstIndex - maxStrLen, maxStrLen);
}


// BM83 字符串变形
//  https://www.nowcoder.com/practice/c3120c1c1bc44ad986259c0cf0f0b80e?tpId=295&tqId=44664&ru=%2Fpractice%2F8c82a5b80378478f9484d87d1c5f12a4&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
string trans(string s, int n) {
    stack<string> strstack;
    string str = "", res = "";
    int j = 0;
    for (int i = 0; i < n;) {
        j = i;
        while (j < n && s[j] != ' ') {
            if ((s[j] >= 'A') && (s[j] <= 'Z'))
                s[j] = s[j] - 'A' + 'a';
            else if ((s[j] >= 'a') && (s[j] <= 'z'))
                s[j] = s[j] - 'a' + 'A';
            ++j;
        }
        str = s.substr(i, j - i);
        strstack.push(str);
        i = j + 1;
    }
    res = s[n - 1] == ' ' ? " " : "";
    while (!strstack.empty()) {
        res += strstack.top();
        strstack.pop();
        if (!strstack.empty())
            res += " ";
    }
    return res;
}

// BM84 最长公共前缀
// https://www.nowcoder.com/practice/28eb3175488f4434a4a6207f6f484f47?tpId=295&tqId=732&ru=%2Fpractice%2Fc3120c1c1bc44ad986259c0cf0f0b80e&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
string longestCommonPrefix(vector<string> &strs) {
    string res = "";
    int istr = 0;
    bool popflag = true;
    while (true) {
        if (!strs.empty() && strs[0][istr])
            res += strs[0][istr];
        else
            break;
        for (string str: strs) {
            if (str[istr]) {
                if (res[istr] == str[istr])
                    popflag = false;
                else
                    popflag = true;
            } else {
                popflag = true;
                break;
            }
        }
        if (popflag) {
            res.pop_back();
            break;
        }
        ++istr;
    }
    return res;
}

// 横向遍历
string longestCommon(const string &commStr, const string &compareStr) {
    int len = min(commStr.size(), compareStr.size()); // 防止访问越界
    int index = 0;
    while (index < len && (commStr[index] == compareStr[index])) {
        index++;
    }
    return commStr.substr(0, index);
}

string longestCommonPrefix_sec(vector<string> &strs) {
    if (strs.empty())
        return "";
    string longestComStr = strs[0];
    for (int i = 1; i < strs.size(); ++i) {
        longestComStr = longestCommon(longestComStr, strs[i]);
        if (longestComStr.empty())
            break;
    }
    return longestComStr;
}

// 纵向遍历
string longestCommonPrefix_thrd(vector<string> &strs) {
    int strnum = strs.size();
    if (!strnum)
        return "";
    string res = strs[0];
    int strlen = res.size();
    for (int i = 0; i < strlen; ++i) {
        for (int count = 1; count < strnum; ++count) {
            if (i == strs[count].size() || res[i] != strs[count][i])
                return res.substr(0, i);
        }
    }
    return res;
}

// BM85 验证IP地址
// https://www.nowcoder.com/practice/55fb3c68d08d46119f76ae2df7566880?tpId=295&tqId=1024725&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
vector<string> split(const string &IP, char splitter) {
    vector<string> res;
    string str;
    int size = IP.size();
    for (int i = 0; i <= size; ++i) {
        if (i == size || IP[i] == splitter) {
            res.push_back(str);
            str = "";
        } else {
            str += IP[i];
        }
    }
    return res;
}

bool IPv4(const string &IP) {
    vector<string> strs = split(IP, '.');
    if (strs.size() != 4)
        return false;
    for (auto str: strs) {
        if (str.size() > 3 || str.size() == 0 || (str.size() != 1 && str[0] == '0'))
            return false;
        for (auto c: str) {
            if (!isdigit(c))
                return false;
        }
        int num = stoi(str);
        if (num > 255 || num < 0)
            return false;
    }
    return true;
}

bool IPv6(const string &IP) {
    vector<string> strs = split(IP, ':');
    if (strs.size() != 8)
        return false;
    for (auto str: strs) {
        if (str.size() == 0 || str.size() > 4)
            return false;
        for (char c: str) {
            if (!(isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')))
                return false;
        }
    }
    return true;
}

string solve(string IP) {
    if (IP.size() == 0)
        return "Neither";
    if (IPv4(IP))
        return "IPv4";
    else if (IPv6(IP))
        return "IPv6";
    else
        return "Neither";
}

// BM86 大数!!!加法
// https://www.nowcoder.com/practice/11ae12e8c6fe48f883cad618c2e81475?tpId=295&tqId=1061819&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj

// 虽然思路正确，但是代码重复太多了，需要精简一些。
string solve(string s, string t) {
    int slstIndex = s.size() - 1;
    int tlstIndex = t.size() - 1;
    stack<char> stkRes;
    bool addflag = false;
    int tmp = 0;
    int i = slstIndex, j = tlstIndex;
    for (; i >= 0 && j >= 0; --i, --j) {
        int snum = s[i] - '0', tnum = t[j] - '0';
        tmp = snum + tnum;
        if (addflag) tmp += 1;
        stkRes.push('0' + (tmp % 10));
        addflag = tmp >= 10 ? true : false;
    }
    if (i < 0) {
        while (j >= 0) {
            tmp = t[j] - '0';
            if (addflag) tmp += 1;
            stkRes.push('0' + (tmp % 10));
            addflag = tmp >= 10 ? true : false;
            --j;
        }
    } else if (j < 0) {
        while (i >= 0) {
            tmp = s[i] - '0';
            if (addflag) tmp += 1;
            stkRes.push('0' + (tmp % 10));
            addflag = tmp >= 10 ? true : false;
            --i;
        }
    }
    if (i < 0 && j < 0) {
        if (addflag) stkRes.push('1');
    }
    string res;
    while (!stkRes.empty()) {
        res += stkRes.top();
        stkRes.pop();
    }
    return res;
}

// 精简代码版本：
string solve_sim(string s, string t) {
    int slen = s.size();
    int tlen = t.size();
    int placeSum = 0;
    stack<char> resStk;
    for (int i = slen - 1, j = tlen - 1; i >= 0 || j >= 0; --i, --j) {
        placeSum += i >= 0 ? s[i] - '0' : 0;
        placeSum += j >= 0 ? t[j] - '0' : 0;
        resStk.push(placeSum % 10 + '0');
        placeSum /= 10;
    }
    if (placeSum) {
        resStk.push('1');
    }
    string res = "";
    while (!resStk.empty()) {
        res += resStk.top();
        resStk.pop();
    }
    return res;
}

// BM87 合并两个有序的数组
// https://www.nowcoder.com/practice/89865d4375634fc484f3a24b7fe65665?tpId=295&tqId=658&ru=%2Fpractice%2F11ae12e8c6fe48f883cad618c2e81475&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
void merge(int A[], int m, int B[], int n) {
    int aptr = m - 1, bptr = n - 1;
    int index = m + n - 1;
    while (aptr >= 0 && bptr >= 0) {
        if (A[aptr] > B[bptr]) {
            A[index] = A[aptr];
            --aptr;
        } else {
            A[index] = B[bptr];
            --bptr;
        }
        --index;
    }
    if (aptr < 0) {
        while (bptr >= 0) {
            A[index] = B[bptr];
            --index;
            --bptr;
        }
    }
}

// BM88 判断是否为回文字符串
// https://www.nowcoder.com/practice/e297fdd8e9f543059b0b5f05f3a7f3b2?tpId=295&tqId=658&ru=%2Fpractice%2F11ae12e8c6fe48f883cad618c2e81475&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
bool judge(string str) {
    int pre = 0, last = str.size() - 1;
    while (pre < last) {
        if (str[pre] != str[last])
            return false;
        ++pre;
        --last;
    }
    return true;
}

// BM89 合并区间
// https://www.nowcoder.com/practice/69f4e5b7ad284a478777cb2a17fb5e6a?tpId=295&tqId=691&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj

// 1. 根据每个区间的左端点大小对intervals 进行排序，
// 2. 排序后再根据一定规则，对区间合并；(自己想一下，有严格的数学证明，但是靠臆想也能想得通)
bool cmp(const Interval &a, const Interval &b) {
    return a.start < b.start ? true : false;
}

vector<Interval> merge(vector<Interval> &intervals) {
    if (intervals.size() <= 1) return intervals;
    sort(intervals.begin(), intervals.end(), cmp);
    vector<Interval> res{intervals[0]};
    for (int i = 1; i < intervals.size(); ++i) {
        if (res.back().end < intervals[i].start) {
            res.push_back(intervals[i]);
        } else {
            res.back().end = max(res.back().end, intervals[i].end);
        }
    }
    return res;
}

// BM90 最小覆盖子串
// https://www.nowcoder.com/practice/c466d480d20c4c7c9d322d12ca7955ac?tpId=295&tqId=670&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
// 题解思路：https://leetcode.cn/problems/minimum-window-substring/solutions/257359/zui-xiao-fu-gai-zi-chuan-by-leetcode-solution/
bool check(unordered_map<char, int> cnt, const unordered_map<char, int> &tmap) {
    for (const auto &node: tmap) {
        if (cnt[node.first] < node.second) {
            return false;
        }
    }
    return true;
}

string minWindow(string S, string T) {
    unordered_map<char, int> tmap, cnt;
    for (const char &c: T) {
        ++tmap[c];
    }
    int l = 0, r = -1;
    int rstL = -1, minLen = S.size();
    while (r < int(S.size())) {
        if (tmap.find(S[++r]) != tmap.end()) {
            ++cnt[S[r]];
        }
        while (check(cnt, tmap) && l <= r) {
            if ((r - l + 1) <= minLen) {
                minLen = r - l + 1;
                rstL = l;
            }
            if (tmap.find(S[l]) != tmap.end()) {
                --cnt[S[l]];
            }
            ++l;
        }
    }
    return rstL == -1 ? string() : S.substr(rstL, minLen);
}


// BM95 分糖果问题
// https://www.nowcoder.com/practice/76039109dd0b47e994c08d8319faa352?tpId=295&tqId=1008104&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int candy(vector<int> &arr) {
    int size = arr.size();
    vector<int> res(size, 1);
    for (int i = 1; i < size; ++i) {
        if (arr[i - 1] < arr[i]) {
            res[i] = res[i - 1] + 1;
        }
    }
    for (int i = size - 2; i >= 0; --i) {
        if (arr[i] > arr[i + 1] && res[i] <= res[i + 1]) {
            res[i] = res[i + 1] + 1;
        }
    }
    int num = 0;
    for (auto i: res) {
        num += i;
    }
    return num;
}

// BM96 主持人调度（二）
// https://www.nowcoder.com/practice/4edf6e6d01554870a12f218c94e8a299?tpId=295&tqId=1267319&ru=%2Fpractice%2Fe19927a8fd5d477794dac67096862042&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
int minmumNumberOfHost(int n, vector<vector<int>> &startEnd) {
    vector<int> start;
    vector<int> end;
    for (const auto time: startEnd) {
        start.push_back(time[0]);
        end.push_back(time[1]);
    }
    sort(start.begin(), start.end());
    sort(end.begin(), end.end());
    int num = 0;
    int endindex = 0;
    for (int i = 0; i < n; ++i) {
        if (start[i] >= end[endindex]) {
            ++endindex;
        } else {
            ++num;
        }
    }
    return num;
}

// BM97 旋转数组
// https://www.nowcoder.com/practice/e19927a8fd5d477794dac67096862042?tpId=295&tqId=1024689&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
vector<int> solve(int n, int m, vector<int> &a) {
    int offset = m % n;
    if (!offset)
        return a;
    reverse(a.begin(), a.end());
    reverse(a.begin(), a.begin() + offset);
    reverse(a.begin() + offset, a.end());
    return a;
}


