#include "nk.h"

// BM27 按之字形顺序打印二叉树
// https://www.nowcoder.com/practice/91b69814117f4e8097390d107d2efbe0?tpId=295&tqId=23454&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
vector<vector<int>> Print(TreeNode *pRoot)
{
    if (!pRoot)
        return {};
    queue<TreeNode *> nodeQue;
    nodeQue.push(pRoot);
    int nextLayerNodeNum = 1;
    vector<vector<int>> res;
    int flag = true;

    while (pRoot && !nodeQue.empty())
    {
        int layerNodeNum = nextLayerNodeNum;
        vector<int> layer{};
        deque<int> deqLayer{};
        nextLayerNodeNum = 0;

        while (layerNodeNum)
        {
            pRoot = nodeQue.front();
            deqLayer.push_back(pRoot->val);

            nodeQue.pop();
            if (pRoot->left)
            {
                nodeQue.push(pRoot->left);
                ++nextLayerNodeNum;
            }
            if (pRoot->right)
            {
                nodeQue.push(pRoot->right);
                ++nextLayerNodeNum;
            }
            --layerNodeNum;
        }
        // 将 deqlayer 填充到layer
        if (flag)
        {
            while (!deqLayer.empty())
            {
                layer.push_back(deqLayer.front());
                deqLayer.pop_front();
            }
        }
        else
        {
            while (!deqLayer.empty())
            {
                layer.push_back(deqLayer.back());
                deqLayer.pop_back();
            }
        }
        flag = !flag;

        res.push_back(layer);
    }
    return res;
}
// 可以直接不用双端队列 ，翻转就好
vector<vector<int>> Print_2(TreeNode *pRoot)
{
    if (!pRoot)
    {
        return {};
    }

    int layer = 0;
    int numLayerNodes = 1, numNexLayerNodes = 1;
    vector<vector<int>> res;
    queue<TreeNode *> queNodes;
    queNodes.push(pRoot);
    // 每次循环代表一层
    while (pRoot && !queNodes.empty())
    {
        numLayerNodes = numNexLayerNodes;
        numNexLayerNodes = 0;
        vector<int> layerNodes{};

        //每次循环代表从队列中取出一个节点
        while (numLayerNodes)
        {
            // 取出一个节点并放入 该层的vector中
            pRoot = queNodes.front();
            queNodes.pop();
            layerNodes.push_back(pRoot->val);

            if (pRoot->left)
            {
                queNodes.push(pRoot->left);
                ++numNexLayerNodes;
            }
            if (pRoot->right)
            {
                queNodes.push(pRoot->right);
                ++numNexLayerNodes;
            }
            --numLayerNodes;
        }

        if (layer % 2 != 0)
        {
            reverse(layerNodes.begin(), layerNodes.end());
        }
        res.push_back(layerNodes);
        ++layer;
    }
    return res;
}

