#include "nk.h"

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
