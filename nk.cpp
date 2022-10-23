#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <stack>
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

//更好的题解  思路清晰
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
//二维的二分查找
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

// BM23--二叉树前序遍历
// https://www.nowcoder.com/practice/5e2135f4d2b14eb8a5b06fab4c938635?tpId=295&tqId=2291302&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
// 递归
void func(TreeNode *root, vector<int> &vec) {
    if (!root) return;
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
    if (!root) return;
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
                if (!nstack.empty() && nstack.top() == '(') nstack.pop();
                else nstack.push(c);
                break;
            case ']':
                if (!nstack.empty() && nstack.top() == '[') nstack.pop();
                else nstack.push(c);
                break;
            case '}':
                if (!nstack.empty() && nstack.top() == '{') nstack.pop();
                else nstack.push(c);
                break;
            default:
                nstack.push(c);
        }
    }
    return nstack.empty() ? true : false;
}

// BM50 两数之和
// https://www.nowcoder.com/practice/20ef0972485e41019e39543e8e895b7f?tpId=295&tqId=745&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
vector<int> twoSum(vector<int> &numbers, int target) {
    // write code here
    unordered_map<int, int> numap;
    for (int i = 0; i < numbers.size(); ++i) {
        if (numap.find(target - numbers[i]) != numap.end()) {
            return {numap[target - numbers[i]]+1, i+1};
        }
        numap[numbers[i]] = i;
    }
    return {};
}

// BM51 数组中出现次数超过一半的数字
// https://www.nowcoder.com/practice/e8a1b01a2df14cb2b228b30ee6a92163?tpId=295&tqId=745&ru=%2Fexam%2Foj&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
int MoreThanHalfNum_Solution(vector<int> numbers) {
    unordered_map<int, int> numcount;
    int boudary(numbers.size()/2);
    int res(-1);
    for(int num : numbers){
        ++numcount[num];
        if(numcount[num] > boudary)
            res = num;
    }
    return res;
}
//  消消乐算法（额。。。）
int MoreThanHalfNum_Solution_stack(vector<int> numbers) {
    stack<int> nstack;
    for(int num:numbers){
        if(!nstack.empty() && nstack.top()!=num){
            nstack.pop();
        }else{
            nstack.push(num);
        }
    }
    return nstack.top();
}


// ------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------
int main() {
}

ListNode *initList(ListNode *head) {
    int num = 5;
    ListNode *p = head;
    while (num--) {
        ListNode *node = new ListNode(num);
        p->next = node;
        p = node;
    }
    return head;
}

TreeNode *initTree(TreeNode *root) {
    root->val = 1;
    TreeNode *rleft = new TreeNode(2);
    root->left = rleft;
    TreeNode *rright = new TreeNode(3);
    root->right = rright;
    TreeNode *rrright = new TreeNode(4);
    rright->right = rrright;
    return root;
}

void printVec(const vector<int> &vec) {
    for (auto num: vec) {
        cout << num << " ";
    }
    cout << endl;
}