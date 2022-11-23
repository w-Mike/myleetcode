#include "nk.h"
// BM26 求二叉树的层序遍历
// https://www.nowcoder.com/practice/04a5560e43e24e9db4595865dc9c63a3?tpId=295&tqId=644&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
vector<vector<int>> levelOrder(TreeNode *root)
{
    // write code here
    if (!root)
        return {};
    queue<TreeNode *> nodeque;
    nodeque.push(root);
    vector<vector<int>> res;
    while (!nodeque.empty())
    {
        vector<int> layer;
        int size = nodeque.size();
        while (size--)
        {
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

