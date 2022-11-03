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

// BM3 链表中的节点每k个一组翻转
// https://www.nowcoder.com/practice/b49c3dc907814e9bbfa8437c251b028e?tpId=295&tqId=722&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
ListNode *reverseKGroup(ListNode *head, int k)
{
    
}

// BM4 合并两个排序的链表
// https://www.nowcoder.com/practice/d8b6b4358f774294a89de2a6ac4d9337?tpId=295&tqId=23267&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
ListNode *Merge(ListNode *pHead1, ListNode *pHead2)
{
    ListNode *dummy = new ListNode(-1);
    ListNode *p = dummy;

    while(pHead1 && pHead2)
    {
        if(pHead1 -> val < pHead2->val){
            p->next = pHead1;
            pHead1 = pHead1->next;
        }else{
            p->next = pHead2;
            pHead2 = pHead2->next;
        }
        p = p->next;
        p->next = nullptr;
    }
    if(pHead1)
        p->next = pHead1;
    else if(pHead2)
        p->next = pHead2;
    p = dummy->next;
    delete dummy;
    return p;
}   

// BM17: https://www.nowcoder.com/practice/d3df40bd23594118b57554129cadf47b?tpId=295&tqId=1499549&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int search(vector<int> &nums, int target)
{
    // write code here
    size_t size = nums.size();
    if (!size)
        return -1;
    int begin = 0;
    int end = size - 1;
    int mid;
    while (end >= begin)
    {
        mid = begin + (end - begin) / 2;
        if (nums[mid] == target)
            return mid;
        if (nums[mid] > target)
        {
            end = mid - 1;
        }
        else if (nums[mid] < target)
        {
            begin = mid + 1;
        }
    }
    return -1;
}

// BM18 https://www.nowcoder.com/practice/abc3fe2ce8e146608e868a70efebf62e?tpId=295&tags=&title=&difficulty=0&judgeStatus=0&rp=0&sourceUrl=%2Fexam%2Foj
// 二维的二分查找
bool Find(int target, vector<vector<int>> array)
{
    if (array.empty())
    {
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
    while (row < m && col >= 0)
    {
        if (val == target)
        {
            return true;
        }
        if (val < target)
        {
            ++row;
        }
        else if (val > target)
        {
            --col;
        }
        val = array[row][col];
    }
    return false;
}

// BM23--二叉树前序遍历
// https://www.nowcoder.com/practice/5e2135f4d2b14eb8a5b06fab4c938635?tpId=295&tqId=2291302&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
// 递归
void func(TreeNode *root, vector<int> &vec)
{
    if (!root)
        return;
    vec.push_back(root->val);
    if (root->left)
        func(root->left, vec);
    if (root->right)
        func(root->right, vec);
}

vector<int> preorderTraversal(TreeNode *root)
{
    vector<int> res{};
    func(root, res);
    return res;
}

// 非递归--所有递归都可以用 Stack 实现
vector<int> preorderTraversal_stack(TreeNode *root)
{
    vector<int> res{};
    TreeNode *ptr = root;
    TreeNode *node = nullptr;
    stack<TreeNode *> nodeStack;
    while (ptr || !nodeStack.empty())
    {
        while (ptr)
        {
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
vector<int> preorderTraversal_stack1(TreeNode *root)
{
    vector<int> res{};
    stack<TreeNode *> nstack;
    TreeNode *ptr = root, *node = nullptr;
    while (!(!ptr && nstack.empty()))
    {
        if (ptr)
        {
            nstack.push(ptr);
            res.push_back(ptr->val);
            ptr = ptr->left;
        }
        else
        {
            node = nstack.top();
            nstack.pop();
            ptr = node->right;
        }
    }
    return res;
}

// BM24 二叉树的中序遍历
// https://www.nowcoder.com/practice/0bf071c135e64ee2a027783b80bf781d?tpId=295&tqId=2291302&ru=%2Fexam%2Foj&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
void inorderfunc(TreeNode *root, vector<int> &vec)
{
    if (!root)
        return;
    if (root->left)
        inorderfunc(root->left, vec);
    vec.push_back(root->val);
    if (root->right)
        inorderfunc(root->right, vec);
}

vector<int> inorderTraversal(TreeNode *root)
{
    // write code here
    vector<int> res{};
    inorderfunc(root, res);
    return res;
}

// stack 实现
vector<int> inorderTraversal_stack(TreeNode *root)
{
    vector<int> res{};
    TreeNode *ptr = root, *node = nullptr;
    stack<TreeNode *> nodestack;

    while (ptr || !nodestack.empty())
    {
        while (ptr)
        {
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
vector<int> postorderTraversal(TreeNode *root)
{
    // write code here
    stack<TreeNode *> nodestack;
    vector<int> res{};
    TreeNode *node = nullptr, *ptr = root, *temp = nullptr;
    int visrtime = 1;
    while (ptr || !nodestack.empty())
    {
        while (ptr)
        {
            nodestack.push(ptr);
            ptr = ptr->left;
        }
        node = nodestack.top();
        if (temp == node)
        {
            res.push_back(node->val);
            nodestack.pop();
            node = nodestack.top();
        }
        temp = node;
        ptr = node->right;
    }
    return res;
}

vector<int> postorderTraversal1(TreeNode *root)
{
    vector<int> res{};
    stack<TreeNode *> nstack;
    TreeNode *ptr = root, *node = nullptr, *visedr = nullptr;
    while (!(!ptr && nstack.empty()))
    {
        if (ptr)
        {
            nstack.push(ptr);
            ptr = ptr->left;
        }
        else
        {
            node = nstack.top();
            if (node->right && visedr != node->right)
            {
                ptr = node->right;
            }
            else
            {
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
vector<int> postorderTraversal_stack2(TreeNode *root)
{
    vector<int> res;
    stack<int> revres;
    stack<TreeNode *> nstack;
    TreeNode *ptr = root, *node = nullptr;
    while (!(!ptr && nstack.empty()))
    {
        if (ptr)
        {
            nstack.push(ptr);
            revres.push(ptr->val);
            ptr = ptr->right;
        }
        else
        {
            node = nstack.top();
            nstack.pop();
            ptr = node->left;
        }
    }
    while (!revres.empty())
    {
        res.push_back(revres.top());
        revres.pop();
    }
    return res;
}

// BM42 用两个栈实现队列
// https://www.nowcoder.com/practice/54275ddae22f475981afa2244dd448c6?tpId=295&tqId=23281&ru=%2Fpractice%2F1291064f4d5d4bdeaefbf0dd47d78541&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
class myqueue
{
public:
    void push(int node)
    {
        stack1.push(node);
    }

    int pop()
    {
        int node(0);
        if (stack2.empty())
        {
            while (!stack1.empty())
            {
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
class minstack
{
public:
    void push(int value)
    {
        nstack.push(value);
        if (minstack.empty() || value < minstack.top())
        {
            minstack.push(value);
        }
        else
        {
            minstack.push(minstack.top());
        }
    }

    void pop()
    {
        nstack.pop();
        minstack.pop();
    }

    int top()
    {
        return nstack.top();
    }

    int min()
    {
        return minstack.top();
    }

private:
    stack<int> nstack;
    stack<int> minstack;
};

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

// BM50 两数之和
// https://www.nowcoder.com/practice/20ef0972485e41019e39543e8e895b7f?tpId=295&tqId=745&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
vector<int> twoSum(vector<int> &numbers, int target)
{
    // write code here
    unordered_map<int, int> numap;
    for (int i = 0; i < numbers.size(); ++i)
    {
        if (numap.find(target - numbers[i]) != numap.end())
        {
            return {numap[target - numbers[i]] + 1, i + 1};
        }
        numap[numbers[i]] = i;
    }
    return {};
}

// BM51 数组中出现次数超过一半的数字
// https://www.nowcoder.com/practice/e8a1b01a2df14cb2b228b30ee6a92163?tpId=295&tqId=745&ru=%2Fexam%2Foj&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
int MoreThanHalfNum_Solution(vector<int> numbers)
{
    unordered_map<int, int> numcount;
    int boudary(numbers.size() / 2);
    int res(-1);
    for (int num : numbers)
    {
        ++numcount[num];
        if (numcount[num] > boudary)
            res = num;
    }
    return res;
}
//  消消乐算法（额。。。）
int MoreThanHalfNum_Solution_stack(vector<int> numbers)
{
    stack<int> nstack;
    for (int num : numbers)
    {
        if (!nstack.empty() && nstack.top() != num)
        {
            nstack.pop();
        }
        else
        {
            nstack.push(num);
        }
    }
    return nstack.top();
}

// BM52 数组中只出现一次的两个数字
// https://www.nowcoder.com/practice/389fc1c3d3be4479a154f63f495abff8?tpId=295&tqId=1375231&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
vector<int> FindNumsAppearOnce(vector<int> &array)
{
    // write code here
    vector<int> res{};
    map<int, int> numap;
    for (int i : array)
    {
        ++numap[i];
    }
    for (auto num : numap)
    {
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
vector<int> FindNumsAppearOnce_bit(vector<int> &array)
{
    int tmp = 0;
    for (int num : array)
    {
        tmp ^= num;
    }
    int mask = 1;
    while (!(tmp & mask))
    {
        mask <<= 1;
    }
    int a = 0, b = 0;
    for (int num : array)
    {
        if (!(mask & num))
        {
            a ^= num;
        }
        else
        {
            b ^= num;
        }
    }
    tmp = a;
    a = a < b ? a : b;
    b = a == tmp ? b : tmp;
    return {a, b};
}
// BM55 没有重复项数字的全排列
// https://www.nowcoder.com/practice/4bcf3081067a4d028f95acee3ddcd2b1?tpId=295&tqId=701&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
// 递归回溯法
void permute_recursion(vector<vector<int>> &res, const vector<int> &num, vector<int> &list)
{
    if (list.size() == num.size())
    {
        res.push_back(list);
        return;
    }
    for (int i = 0; i < num.size(); ++i)
    {
        vector<int>::iterator iter = find(list.begin(), list.end(), num[i]);
        if (iter != list.end())
            continue;
        list.push_back(num[i]);
        permute_recursion(res, num, list);
        list.pop_back();
    }
}

vector<vector<int>> permute(vector<int> &num)
{
    vector<vector<int>> res{};
    vector<int> list{};
    permute_recursion(res, num, list);
    return res;
}

// BM56 有重复项数字的全排列
// https://www.nowcoder.com/practice/a43a2b986ef34843ac4fdd9159b69863?tpId=295&tags=&title=&difficulty=0&judgeStatus=0&rp=0&sourceUrl=%2Fexam%2Foj

void permuteUnique_recursion(const vector<int> &num, vector<vector<int>> &res, vector<int> &list, vector<int> mark)
{
    if (list.size() == num.size())
    {
        res.push_back(list);
        return;
    }
    unordered_set<int> nset{};
    for (int i = 0; i < num.size(); ++i)
    {
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
vector<vector<int>> permuteUnique(vector<int> &num)
{
    sort(num.begin(), num.end());
    vector<vector<int>> res{};
    vector<int> list{};
    vector<int> mark(num.size(), 0);
    permuteUnique_recursion(num, res, list, mark);
    return res;
}

// BM62 斐波那契数列
// https://www.nowcoder.com/practice/c6c7742f5ba7442aada113136ddea0c3?tpId=295&tqId=23255&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int Fibonacci(int n)
{
    int fir = 1, sec = 1;
    int tmp = 0;
    for (int i = 3; i <= n; ++i)
    {
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
int jumpFloor(int number)
{
    int res = 0, tmp = 0;
    int fir = 1, sec = 2;
    res = number == 1 ? fir : sec;
    for (int i = 3; i <= number; ++i)
    {
        tmp = fir;
        fir = sec;
        sec = tmp + sec;
    }
    res = number < 3 ? res : sec;
    return res;
}
// BM83 字符串变形
//  https://www.nowcoder.com/practice/c3120c1c1bc44ad986259c0cf0f0b80e?tpId=295&tqId=44664&ru=%2Fpractice%2F8c82a5b80378478f9484d87d1c5f12a4&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
string trans(string s, int n)
{
    stack<string> strstack;
    string str = "", res = "";
    int j = 0;
    for (int i = 0; i < n;)
    {
        j = i;
        while (j < n && s[j] != ' ')
        {
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
    while (!strstack.empty())
    {
        res += strstack.top();
        strstack.pop();
        if (!strstack.empty())
            res += " ";
    }
    return res;
}

// BM84 最长公共前缀
// https://www.nowcoder.com/practice/28eb3175488f4434a4a6207f6f484f47?tpId=295&tqId=732&ru=%2Fpractice%2Fc3120c1c1bc44ad986259c0cf0f0b80e&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
string longestCommonPrefix(vector<string> &strs)
{
    string res = "";
    int istr = 0;
    bool popflag = true;
    while (true)
    {
        if (!strs.empty() && strs[0][istr])
            res += strs[0][istr];
        else
            break;
        for (string str : strs)
        {
            if (str[istr])
            {
                if (res[istr] == str[istr])
                    popflag = false;
                else
                    popflag = true;
            }
            else
            {
                popflag = true;
                break;
            }
        }
        if (popflag)
        {
            res.pop_back();
            break;
        }
        ++istr;
    }
    return res;
}
// 横向遍历
string longestCommon(const string &commStr, const string &compareStr)
{
    int len = min(commStr.size(), compareStr.size()); // 防止访问越界
    int index = 0;
    while (index < len && (commStr[index] == compareStr[index]))
    {
        index++;
    }
    return commStr.substr(0, index);
}
string longestCommonPrefix_sec(vector<string> &strs)
{
    if (strs.empty())
        return "";
    string longestComStr = strs[0];
    for (int i = 1; i < strs.size(); ++i)
    {
        longestComStr = longestCommon(longestComStr, strs[i]);
        if (longestComStr.empty())
            break;
    }
    return longestComStr;
}
// 纵向遍历
string longestCommonPrefix_thrd(vector<string> &strs)
{
    int strnum = strs.size();
    if (!strnum)
        return "";
    string res = strs[0];
    int strlen = res.size();
    for (int i = 0; i < strlen; ++i)
    {
        for (int count = 1; count < strnum; ++count)
        {
            if (i == strs[count].size() || res[i] != strs[count][i])
                return res.substr(0, i);
        }
    }
    return res;
}
// BM85 验证IP地址
// https://www.nowcoder.com/practice/55fb3c68d08d46119f76ae2df7566880?tpId=295&tqId=1024725&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
vector<string> split(const string &IP, char splitter)
{
    vector<string> res;
    string str;
    int size = IP.size();
    for (int i = 0; i <= size; ++i)
    {
        if (i == size || IP[i] == splitter)
        {
            res.push_back(str);
            str = "";
        }
        else
        {
            str += IP[i];
        }
    }
    return res;
}
bool IPv4(const string &IP)
{
    vector<string> strs = split(IP, '.');
    if (strs.size() != 4)
        return false;
    for (auto str : strs)
    {
        if (str.size() > 3 || str.size() == 0 || (str.size() != 1 && str[0] == '0'))
            return false;
        for (auto c : str)
        {
            if (!isdigit(c))
                return false;
        }
        int num = stoi(str);
        if (num > 255 || num < 0)
            return false;
    }
    return true;
}
bool IPv6(const string &IP)
{
    vector<string> strs = split(IP, ':');
    if (strs.size() != 8)
        return false;
    for (auto str : strs)
    {
        if (str.size() == 0 || str.size() > 4)
            return false;
        for (char c : str)
        {
            if (!(isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')))
                return false;
        }
    }
    return true;
}
string solve(string IP)
{
    if (IP.size() == 0)
        return "Neither";
    if (IPv4(IP))
        return "IPv4";
    else if (IPv6(IP))
        return "IPv6";
    else
        return "Neither";
}

// BM87 合并两个有序的数组
// https://www.nowcoder.com/practice/89865d4375634fc484f3a24b7fe65665?tpId=295&tqId=658&ru=%2Fpractice%2F11ae12e8c6fe48f883cad618c2e81475&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
void merge(int A[], int m, int B[], int n)
{
    int aptr = m - 1, bptr = n - 1;
    int index = m + n - 1;
    while (aptr >= 0 && bptr >= 0)
    {
        if (A[aptr] > B[bptr])
        {
            A[index] = A[aptr];
            --aptr;
        }
        else
        {
            A[index] = B[bptr];
            --bptr;
        }
        --index;
    }
    if (aptr < 0)
    {
        while (bptr >= 0)
        {
            A[index] = B[bptr];
            --index;
            --bptr;
        }
    }
}
// BM88 判断是否为回文字符串
// https://www.nowcoder.com/practice/e297fdd8e9f543059b0b5f05f3a7f3b2?tpId=295&tqId=658&ru=%2Fpractice%2F11ae12e8c6fe48f883cad618c2e81475&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
bool judge(string str)
{
    int pre = 0, last = str.size() - 1;
    while (pre < last)
    {
        if (str[pre] != str[last])
            return false;
        ++pre;
        --last;
    }
    return true;
}
// BM95 分糖果问题
// https://www.nowcoder.com/practice/76039109dd0b47e994c08d8319faa352?tpId=295&tqId=1008104&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int candy(vector<int> &arr)
{
    int size = arr.size();
    vector<int> res(size, 1);
    for (int i = 1; i < size; ++i)
    {
        if (arr[i - 1] < arr[i])
        {
            res[i] = res[i - 1] + 1;
        }
    }
    for (int i = size - 2; i >= 0; --i)
    {
        if (arr[i] > arr[i + 1] && res[i] <= res[i + 1])
        {
            res[i] = res[i + 1] + 1;
        }
    }
    int num = 0;
    for (auto i : res)
    {
        num += i;
    }
    return num;
}

// BM96 主持人调度（二）
// https://www.nowcoder.com/practice/4edf6e6d01554870a12f218c94e8a299?tpId=295&tqId=1267319&ru=%2Fpractice%2Fe19927a8fd5d477794dac67096862042&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
int minmumNumberOfHost(int n, vector<vector<int>> &startEnd)
{
    vector<int> start;
    vector<int> end;
    for (const auto time : startEnd)
    {
        start.push_back(time[0]);
        end.push_back(time[1]);
    }
    sort(start.begin(), start.end());
    sort(end.begin(), end.end());
    int num = 0;
    int endindex = 0;
    for (int i = 0; i < n; ++i)
    {
        if (start[i] >= end[endindex])
        {
            ++endindex;
        }
        else
        {
            ++num;
        }
    }
    return num;
}

// BM97 旋转数组
// https://www.nowcoder.com/practice/e19927a8fd5d477794dac67096862042?tpId=295&tqId=1024689&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
vector<int> solve(int n, int m, vector<int> &a)
{
    int offset = m % n;
    if (!offset)
        return a;
    reverse(a.begin(), a.end());
    reverse(a.begin(), a.begin() + offset);
    reverse(a.begin() + offset, a.end());
    return a;
}

ListNode *initList(ListNode *head);
TreeNode *initTree(TreeNode *root);
void printVec(const vector<int> &vec);

int main()
{
    cout << "123" << endl;
    return 1;
}

#pragma region funcs
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

TreeNode *initTree(TreeNode *root)
{
    root->val = 1;
    TreeNode *rleft = new TreeNode(2);
    root->left = rleft;
    TreeNode *rright = new TreeNode(3);
    root->right = rright;
    TreeNode *rrright = new TreeNode(4);
    rright->right = rrright;
    return root;
}

void printVec(const vector<int> &vec)
{
    for (auto num : vec)
    {
        cout << num << " ";
    }
    cout << endl;
}

#pragma endregion
