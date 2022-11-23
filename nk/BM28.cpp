#include "nk.h"

// BM28 二叉树的最大深度
// https://www.nowcoder.com/practice/8a2b2bf6c19b4f23a9bdb9b233eefa73?tpId=295&tqId=642&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj

int getMax(TreeNode *root, int dep)
{
    if (!root)
    {
        return dep-1;
    }
    int lDep = getMax(root->left, dep + 1);
    int rDep = getMax(root->right, dep + 1);
    if(lDep > rDep){
        return lDep;
    }else{
        return rDep;
    }
}
int maxDepth(TreeNode *root)
{
    int maxDepth = getMax(root, 1);
    return maxDepth;
}
