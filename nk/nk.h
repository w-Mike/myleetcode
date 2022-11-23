#pragma once
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
using namespace std;

#pragma region funcs

struct Interval
{
    int start;
    int end;

    Interval() : start(0), end(0) {}

    Interval(int s, int e) : start(s), end(e) {}
};

struct ListNode
{
    int val;
    struct ListNode *next;

    ListNode(int x) : val(x), next(NULL)
    {
    }
};

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

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
