#include "lc.h"

// 看了题解  350.leetcode
vector<int> intersect(vector<int> &nums1, vector<int> &nums2)
{
    unordered_map<int, int> nums1_count;
    for (const auto &num : nums1)
    {
        ++nums1_count[num];
    }
    vector<int> result;
    for (const auto &num : nums2)
    {
        if (nums1_count.find(num) != nums1_count.end() && nums1_count[num] != 0)
        {
            --nums1_count[num];
            result.push_back(num);
        }
    }
    return result;
}

vector<int> intersect2(vector<int> &nums1, vector<int> &nums2)
{
    sort(nums1.begin(), nums1.end());
    sort(nums2.begin(), nums2.end());

    int size1 = nums1.size();
    int size2 = nums2.size();
    int p1 = 0, p2 = 0;
    vector<int> res;
    while (p1 < size1 && p2 < size2)
    {
        if (nums1[p1] == nums2[p2])
        {
            res.push_back(nums1[p1]);
            ++p1;
            ++p2;
        }
        else if (nums1[p1] > nums2[p2])
        {
            ++p2;
        }
        else if (nums1[p1] < nums2[p2])
        {
            ++p1;
        }
    }
    return res;
}

void test350()
{
    vector<int> nums1{4, 9, 5};
    vector<int> nums2{9, 4, 9, 8, 4};
    // int m = 3, n = 2;
    // merge(nums1, m, nums2, n);
    auto nums = intersect2(nums1, nums2);
    for (auto num : nums)
    {
        cout << num << endl;
    }
}

