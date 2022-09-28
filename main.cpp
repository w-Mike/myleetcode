#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

// leetcode 1.
vector<int> twoSum(vector<int> &nums, int target)
{
    unordered_map<int, int> hashtable;
    for (int i = 0; i < nums.size(); ++i)
    {
        auto iter = hashtable.find(target - nums[i]);
        if (iter != hashtable.end())
        {
            return {i, hashtable[target - nums[i]]};
        }
        hashtable[nums[i]] = i;
    }
    return {};
}
// leetcode 88.
void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
{
    int p1 = m - 1, p2 = n - 1, tail = m + n - 1;
    while (p1 != -1 || p2 != -1)
    {
        if (p1 == -1)
        {
            nums1[tail] = nums2[p2];
            --p2;
        }
        else if (p2 == -1)
        {
            nums1[tail] = nums1[p1];
            --p1;
        }
        else if (nums1[p1] > nums2[p2])
        {
            nums1[tail] = nums1[p1];
            --p1;
        }
        else
        {
            nums1[tail] = nums2[p2];
            --p2;
        }
        --tail;
    }
}

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

// leetcode 121  看了动态规划题解
int maxProfit(vector<int> &prices)
{
    vector<int> minDay = {0};
    int size = prices.size();
    int maxPrice = 0;

    for (int i = 1; i < size; ++i)
    {
        minDay.push_back(prices[i] < prices[minDay[i - 1]] ? i : minDay[i - 1]);
        maxPrice = max(prices[i] - prices[minDay[i - 1]], maxPrice);
    }
    return maxPrice;
}
int maxProfit2(vector<int> &prices)
{
    vector<int> minPrice{prices[0]};
    int size = prices.size();
    int res = 0;
    for (int i = 1; i < size; ++i)
    {
        minPrice.push_back(min(prices[i], minPrice[i - 1]));
        res = max(res, prices[i] - minPrice[i - 1]);
    }
    return res;
}
int maxProfit3(vector<int> &prices)
{
    int minPrice = prices[0];
    int size = prices.size();
    int res = 0;
    for (int i = 1; i < size; ++i)
    {
        res = max(res, prices[i] - minPrice);
        minPrice = prices[i] < minPrice ? prices[i] : minPrice;
    }
    return res;
}

// 566  官方题解
// 一维数组如何转换为二维数组   根据一维下标与二维下标的关系
vector<vector<int>> matrixReshape(vector<vector<int>> &mat, int r, int c)
{
    int mr = mat.size();
    int mc = mat[0].size();
    if (mr * mc != r * c)
    {
        return mat;
    }
    vector<vector<int>> res(r, vector<int>(c));
    for (int n = 0; n < mr * mc; n++)
    {
        res[n / c][n % c] = mat[n / mc][n % mc];
    }
    return res;
}
void test556()
{
    vector<vector<int>> mat = {{1, 2}, {3, 4}};
    int r = 4, c = 1;
    mat = matrixReshape(mat, r, c);
    for (const auto &vec : mat)
    {
        for (const auto &num : vec)
        {
            cout << num << " ";
        }
        cout << endl;
    }
}

// 118 杨辉三角
vector<vector<int>> generate(int numRows)
{
    vector<vector<int>> res{};
    if (numRows == 0)
    {
        return res;
    }
    for (int row = 0; row < numRows; ++row)
    {
        res.push_back(vector<int>(row + 1));
        res[row][0] = 1;
        res[row][row] = 1;
        for (int i = 1; i < row; ++i)
        {
            res[row][i] = res[row - 1][i - 1] + res[row - 1][i];
        }
    }
    return res;
}
void test118()
{
}

// 36
bool isValidSudoku(vector<vector<char>> &board)
{
    int row[9][10]{0};
    int column[9][10]{0};
    int box[9][10]{0};
    int boxIndex = 0;

    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            boxIndex = j / 3 + (i / 3) * 3;
            if (board[i][j] != '.')
            {
                if (row[i][board[i][j] - '0'] == 1 || column[j][board[i][j] - '0'] == 1 || box[boxIndex][board[i][j] - '0'] == 1)
                {
                    return false;
                }
                else
                {
                    row[i][board[i][j] - '0'] = 1;
                    column[j][board[i][j] - '0'] = 1;
                    box[boxIndex][board[i][j] - '0'] = 1;
                }
            }
        }
    }
    return true;
}
// 73 看了官方题解
void setZeroes(vector<vector<int>> &matrix)
{
    int m = matrix.size();
    int n = matrix[0].size();
    vector<bool> row(m, false);
    vector<bool> col(n, false);
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (!matrix[i][j])
            {
                row[i] = col[j] = true;
            }
        }
    }
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (row[i] || col[j])
            {
                matrix[i][j] = 0;
            }
        }
    }
}
void setZeroes2(vector<vector<int>> &matrix)
{
    int a= 2;
    cout << !a;
}




void testAny(){
    int a= 2;
    cout << !a;
}
int main()
{
    testAny();
    return 1;
}