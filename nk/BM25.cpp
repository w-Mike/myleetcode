#include "nk.h"

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
