#include "nk.h"
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

