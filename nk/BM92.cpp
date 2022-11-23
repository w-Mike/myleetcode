#include "nk.h" // BM92 最长无重复子数组
// https://www.nowcoder.com/practice/b56799ebfd684fb394bd315e89324fb4?tpId=295&tqId=1008889&ru=%2Fpractice%2Fc3a6afee325e472386a1c4eb1ef987f3&qru=%2Fta%2Fformat-top101%2Fquestion-ranking&sourceUrl=%2Fexam%2Foj
int maxLength(vector<int> &arr)
{
    if (arr.empty())
        return 0;
    int l = 0, r = -1, maxlen = 1;
    int size = arr.size();
    unordered_set<int> uset;
    while (++r < size)
    {
        if (!uset.insert(arr[r]).second)
        {
            if ((r - l) > maxlen)
            {
                maxlen = r - l;
            }
            do
            {
                uset.erase(arr[l++]);
            } while (!uset.insert(arr[r]).second);
        }
    }
    if ((r - l) > maxlen)
    {
        maxlen = r - l;
    }
    return maxlen;
}

// 使用 哈希表做
int maxLength_2(vector<int> &arr)
{
    unordered_map<int, int> umap;
    int l = 0, r = -1;
    auto size = arr.size();
    int maxlen = 0;
    while (++r < size)
    {
        umap[arr[r]]++;
        while (umap[arr[r]] > 1)
        {
            umap[arr[l++]]--;
        }
        maxlen = max(r - l + 1, maxlen);
    }
    return maxlen;
}
