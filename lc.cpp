#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

// leetcode 1.
vector<int> twoSum(vector<int> &nums, int target) {
    unordered_map<int, int> hashtable;
    for (int i = 0; i < nums.size(); ++i) {
        auto iter = hashtable.find(target - nums[i]);
        if (iter != hashtable.end()) {
            return {i, hashtable[target - nums[i]]};
        }
        hashtable[nums[i]] = i;
    }
    return {};
}

// leetcode 88.
void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
    int p1 = m - 1, p2 = n - 1, tail = m + n - 1;
    while (p1 != -1 || p2 != -1) {
        if (p1 == -1) {
            nums1[tail] = nums2[p2];
            --p2;
        } else if (p2 == -1) {
            nums1[tail] = nums1[p1];
            --p1;
        } else if (nums1[p1] > nums2[p2]) {
            nums1[tail] = nums1[p1];
            --p1;
        } else {
            nums1[tail] = nums2[p2];
            --p2;
        }
        --tail;
    }
}

// 看了题解  350.leetcode
vector<int> intersect(vector<int> &nums1, vector<int> &nums2) {
    unordered_map<int, int> nums1_count;
    for (const auto &num: nums1) {
        ++nums1_count[num];
    }
    vector<int> result;
    for (const auto &num: nums2) {
        if (nums1_count.find(num) != nums1_count.end() && nums1_count[num] != 0) {
            --nums1_count[num];
            result.push_back(num);
        }
    }
    return result;
}

vector<int> intersect2(vector<int> &nums1, vector<int> &nums2) {
    sort(nums1.begin(), nums1.end());
    sort(nums2.begin(), nums2.end());

    int size1 = nums1.size();
    int size2 = nums2.size();
    int p1 = 0, p2 = 0;
    vector<int> res;
    while (p1 < size1 && p2 < size2) {
        if (nums1[p1] == nums2[p2]) {
            res.push_back(nums1[p1]);
            ++p1;
            ++p2;
        } else if (nums1[p1] > nums2[p2]) {
            ++p2;
        } else if (nums1[p1] < nums2[p2]) {
            ++p1;
        }
    }
    return res;
}

void test350() {
    vector<int> nums1{4, 9, 5};
    vector<int> nums2{9, 4, 9, 8, 4};
    // int m = 3, n = 2;
    // merge(nums1, m, nums2, n);
    auto nums = intersect2(nums1, nums2);
    for (auto num: nums) {
        cout << num << endl;
    }
}

// leetcode 121  看了动态规划题解
int maxProfit(vector<int> &prices) {
    vector<int> minDay = {0};
    int size = prices.size();
    int maxPrice = 0;

    for (int i = 1; i < size; ++i) {
        minDay.push_back(prices[i] < prices[minDay[i - 1]] ? i : minDay[i - 1]);
        maxPrice = max(prices[i] - prices[minDay[i - 1]], maxPrice);
    }
    return maxPrice;
}

int maxProfit2(vector<int> &prices) {
    vector<int> minPrice{prices[0]};
    int size = prices.size();
    int res = 0;
    for (int i = 1; i < size; ++i) {
        minPrice.push_back(min(prices[i], minPrice[i - 1]));
        res = max(res, prices[i] - minPrice[i - 1]);
    }
    return res;
}

int maxProfit3(vector<int> &prices) {
    int minPrice = prices[0];
    int size = prices.size();
    int res = 0;
    for (int i = 1; i < size; ++i) {
        res = max(res, prices[i] - minPrice);
        minPrice = prices[i] < minPrice ? prices[i] : minPrice;
    }
    return res;
}

// 566  官方题解
// 一维数组如何转换为二维数组   根据一维下标与二维下标的关系
vector<vector<int>> matrixReshape(vector<vector<int>> &mat, int r, int c) {
    int mr = mat.size();
    int mc = mat[0].size();
    if (mr * mc != r * c) {
        return mat;
    }
    vector<vector<int>> res(r, vector<int>(c));
    for (int n = 0; n < mr * mc; n++) {
        res[n / c][n % c] = mat[n / mc][n % mc];
    }
    return res;
}

void test556() {
    vector<vector<int>> mat = {{1, 2},
                               {3, 4}};
    int r = 4, c = 1;
    mat = matrixReshape(mat, r, c);
    for (const auto &vec: mat) {
        for (const auto &num: vec) {
            cout << num << " ";
        }
        cout << endl;
    }
}

// 118 杨辉三角
vector<vector<int>> generate(int numRows) {
    vector<vector<int>> res{};
    if (numRows == 0) {
        return res;
    }
    for (int row = 0; row < numRows; ++row) {
        res.push_back(vector<int>(row + 1));
        res[row][0] = 1;
        res[row][row] = 1;
        for (int i = 1; i < row; ++i) {
            res[row][i] = res[row - 1][i - 1] + res[row - 1][i];
        }
    }
    return res;
}

void test118() {
}

// 36
bool isValidSudoku(vector<vector<char>> &board) {
    int row[9][10]{0};
    int column[9][10]{0};
    int box[9][10]{0};
    int boxIndex = 0;

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            boxIndex = j / 3 + (i / 3) * 3;
            if (board[i][j] != '.') {
                if (row[i][board[i][j] - '0'] == 1 || column[j][board[i][j] - '0'] == 1 ||
                    box[boxIndex][board[i][j] - '0'] == 1) {
                    return false;
                } else {
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
void setZeroes(vector<vector<int>> &matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    vector<bool> row(m, false);
    vector<bool> col(n, false);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!matrix[i][j]) {
                row[i] = col[j] = true;
            }
        }
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (row[i] || col[j]) {
                matrix[i][j] = 0;
            }
        }
    }
}

void setZeroes2(vector<vector<int>> &matrix) {
    int r = matrix.size();
    int c = matrix[0].size();
    bool rowFlag = false, colFlag = false;
    for (int i = 0; i < r; ++i) {
        if (!matrix[i][0]) {
            colFlag = true;
            break;
        }
    }
    for (int i = 0; i < c; ++i) {
        if (!matrix[0][i]) {
            rowFlag = true;
            break;
        }
    }
    for (int i = 1; i < r; ++i) {
        for (int j = 1; j < c; ++j) {
            if (!matrix[i][j]) {
                matrix[i][0] = matrix[0][j] = 0;
            }
        }
    }
    for (int i = 1; i < r; ++i) {
        for (int j = 1; j < c; ++j) {
            if (!(matrix[i][0] && matrix[0][j])) {
                matrix[i][j] = 0;
            }
        }
    }
    if (rowFlag) {
        for (int i = 0; i < c; ++i) {
            matrix[0][i] = 0;
        }
    }
    if (colFlag) {
        for (int i = 0; i < r; ++i) {
            matrix[i][0] = 0;
        }
    }
}

// 387 leetcode   看题解了
int firstUniqChar(string s) {
    map<char, int> cmap;
    for (const auto &c: s) {
        ++cmap[c];
    }
    for (int i = 0; i < s.size(); ++i) {
        if (cmap[s[i]] == 1) {
            return i;
        }
    }
    return -1;
}

int firstUniqChar2(string s) {
    map<char, int> cmap;
    for (int i = 0; i < s.size(); ++i) {
        if (cmap.find(s[i]) == cmap.end()) {
            cmap[s[i]] = i;
        } else {
            cmap[s[i]] = -1;
        }
    }
    for (int i = 0; i < s.size(); ++i) {
        if (cmap[s[i]] != -1) {
            return i;
        }
    }
    return -1;
}

int firstUniqChar3(string s);

// 383 d
bool canConstruct(string ransomNote, string magazine) {
    unordered_map<char, int> rmap;
    for (const auto &c: ransomNote) {
        rmap[c]++;
    }
    for (const auto &c: magazine) {
        if (rmap.find(c) != rmap.end() && rmap[c] > 0) {
            rmap[c]--;
        }
    }
    for (const auto &item: rmap) {
        if (item.second != 0) {
            return false;
        }
    }
    return true;
}

// 优化
bool canConstruct2(string ransomNote, string magazine) {
    if (ransomNote.size() > magazine.size()) {
        return false;
    }
    int letter[26]{0};

    for (const auto &c: magazine) {
        letter[c - 'a']++;
    }
    for (const auto &c: ransomNote) {
        if ((--letter[c - 'a']) < 0) {
            return false;
        }
    }
    return true;
}

// 242 leetcode
bool isAnagram(string s, string t) {
    if (s.size() != t.size()) {
        return false;
    }
    int letter[26]{0};
    for (const auto &c: s) {
        letter[c - 'a']++;
    }
    for (const auto &c: t) {
        if ((--letter[c - 'a']) < 0) {
            return false;
        }
    }
    return true;
}

// 官方排序法
bool isAnagram2(string s, string t) {
    if (s.size() != t.size())
        return false;
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());
    return s == t;
}

// lc 26
int removeDuplicates(vector<int> &nums) {
    size_t size = nums.size();
    if (size == 1) {
        return 1;
    }
    int pb = 0;
    for (size_t pf = 1; pf < nums.size(); ++pf) {
        if (nums[pb] != nums[pf]) {
            nums[pb + 1] = nums[pf];
            ++pb;
        }
    }
    for (int i = 0; i < (size - pb - 1); ++i) {
        nums.pop_back();
    }
    return pb + 1;
}

// lc 122
int maxProfit122(const vector<int> &prices) {
    int part = 0;
    size_t size = prices.size();
    vector<int> seperator{0};
    for (int i = 1; i < size; ++i) {
        if (prices[i] < prices[i - 1]) {
            seperator.push_back(i);
            auto backitem = seperator.end() - 1;
            part += (prices[*backitem - 1] - prices[*(backitem - 1)]);
        }
    }
    part += (prices[size - 1] - prices[*(seperator.end() - 1)]);
    return part;
}

// lc189
void myrotate(vector<int> &nums, int k) {
    vector<int> temp(nums);
    int size = nums.size();
    k = k % (size);
    for (int i = 0; i < size; ++i) {
        nums[(i + k) % size] = temp[i];
    }
}

// way2
void reversenums(vector<int> &nums, int begin, int end) {
    for (int i = begin; i <= begin + (end - begin) / 2; ++i) {
        swap(nums[i], nums[begin + (end - i)]);
    }
}

void myrotate2(vector<int> &nums, int k) {
    int size = nums.size();
    reversenums(nums, 0, size - 1);
    reversenums(nums, 0, k % size - 1);
    reversenums(nums, k % size, size - 1);
}

// lc 136
int singleNumber(vector<int> &nums) {
    int res = 0;
    for (auto num: nums) {
        res ^= num;
    }
    return res;
}

// 排序后查找
int singleNumber2(vector<int> &nums) {
    // sort(nums.begin(), nums.end());
    return 1;
}

// 66
vector<int> plusOne(vector<int> &digits) {
    auto iter = digits.end() - 1;
    while (iter != digits.begin() && (*iter) == 9) {
        *iter = 0;
        --iter;
    }
    ++(*iter);
    if ((*iter) == 10 && iter == digits.begin()) {
        *iter = 0;
        digits.insert(iter, 1);
    }
    return digits;
}

// 283lc  --myway-1
void moveZeroes(vector<int> &nums) {
    size_t size = nums.size();
    for (size_t i = 0; i < size; ++i) {
        if (nums[i] == 0) {
            --size;
            for (size_t j = i; j < size; ++j) {
                swap(nums[j], nums[j + 1]);
            }
            if (nums[i] == 0)
                --i;
        }
    }
}

//  --myway-2
void moveZeroes2(vector<int> &nums) {
    size_t size = nums.size();
    for (size_t i = 0; i < size;) {
        if (nums[i] == 0) {
            nums.erase(nums.begin() + i);
            nums.push_back(0);
            --size;
        } else {
            ++i;
        }
    }
}

//  --othersway 双指针
// leftp 的 左边是符合要求的序列（即按原相对序列排序的非零数字序列）/
// leftp总是指向需要覆盖的值，因为movep总是指向序列右边的第一个非零数字
void moveZeroes3(vector<int> &nums) {
    size_t size = nums.size();
    int leftp = 0, movep = 0;
    while (leftp < size) {
        /* code */
        if (movep >= size) {
            nums[leftp++] = 0;
        } else if (nums[movep]) {
            nums[leftp] = nums[movep];
            ++leftp;
        }
        ++movep;
    }
}

// 39. 组合总和
// https://leetcode.cn/problems/combination-sum/
void comb(const vector<int> &candidates, vector<vector<int>> &res, vector<int> &oneres, int target, int index) {
    if (target < 0) return;
    if (target == 0) {
        res.push_back(oneres);
        return;
    }
    int size = candidates.size();
    for (int i = index; i < size; ++i) {
        oneres.push_back(candidates[i]);
        comb(candidates, res, oneres, target - candidates[i], i);
        oneres.pop_back();
    }
}

vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
    vector<vector<int>> res;
    vector<int> oneres;
    comb(candidates, res, oneres, target, 0);
    return res;
}

// 1143. 最长公共子序列
// https://leetcode.cn/problems/longest-common-subsequence/description/
int longestCommonSubsequence(string text1, string text2) {
    int m = text1.size() + 1;
    int n = text2.size() + 1;
    vector<vector<int>> dp(m, vector<int>(n, 0));
    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[m-1][n-1];
}

void testAny();

void printVec(const vector<int> &);

int main() {
    vector<int> vec{0, 0, 1, 0, 0, 2, 9};
    moveZeroes2(vec);
    printVec(vec);
    return 1;
}

void testAny() {
    int i = 1;
    int a = (i++) + i;
    cout << a;
}

void printVec(const vector<int> &vec) {
    for (auto num: vec) {
        cout << num << " ";
    }
    cout << endl;
}