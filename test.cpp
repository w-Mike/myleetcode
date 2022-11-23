#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <string>
#include <queue>
using namespace std;


int main()
{
    return 1;
}

// unordered_map<char, int> umap_letter;
// unordered_map<int, char> umap_digit;

// bool isTen(const string &str)
// {
//     for (const auto &c : str)
//     {
//         if (c < '0' || c > '9')
//             return false;
//     }
//     return true;
// }
// bool isFive(const string &str)
// {
//     for (const auto &c : str)
//     {
//         // o y e a s
//         if (c != 'o' && c != 'y' && c != 'e' && c != 'a' && c != 's')
//             return false;
//     }
//     return true;
// }

// string trans(const string &str)
// {
//     string res = "";
//     int intRes = 0;
//     auto size = str.size();
//     if (isTen(str))
//     {
//         int toInt = 0, pow = 1;
//         for (int i = size - 1; i >= 0; --i)
//         {
//             toInt += (pow * (str[i] - '0'));
//             pow *= 10;
//         }
//         stack<char> bitStack;
//         while (toInt)
//         {
//             bitStack.push(umap_digit[toInt % 5]);
//             toInt /= 5;
//         }
//         while (!bitStack.empty())
//         {
//             res += bitStack.top();
//             bitStack.pop();
//         }
//     }
//     else if (isFive(str))
//     {
//         int pow = 1;
//         for (int i = size - 1; i >= 0; --i)
//         {
//             intRes += (umap_letter[str[i]] * pow);
//             pow *= 5;
//         }
//         stack<char> reStack;
//         while (intRes)
//         {
//             char c = intRes % 10 + '0';
//             reStack.push(c);
//             intRes /= 10;
//         }
//         while (!reStack.empty())
//         {
//             res += reStack.top();
//             reStack.pop();
//         }
//     }
//     return res;
// }

// int main()
// {
//     // init
//     umap_letter['o'] = 0;
//     umap_letter['y'] = 1;
//     umap_letter['e'] = 2;
//     umap_letter['a'] = 3;
//     umap_letter['s'] = 4;
//     umap_digit[0] = 'o';
//     umap_digit[1] = 'y';
//     umap_digit[2] = 'e';
//     umap_digit[3] = 'a';
//     umap_digit[4] = 's';

//     // input
//     int n;
//     cin >> n;
//     vector<string> input;
//     vector<string> res;
//     string str;
//     for (int i = 0; i < n; ++i)
//     {
//         cin >> str;
//         input.push_back(str);
//     }

//     // output
//     for (const auto &str : input)
//     {
//         res.push_back(trans(str));
//         cout << res.back() << endl;
//     }
//     return 0;
// }

// int test(const int &x, const int &d, const int &n) {
//     int res = 0;
//     int i = 0;
//     double comRes = (double) 1 / x;
//     while (i < (n + d - 1)) {
//         comRes *= 10;
//         ++i;
//     }
//     int tmp = int(comRes);
//     i = 0;
//     stack<int> tmpStack;
//     while (i < n) {
//         tmpStack.push(tmp % 10);
//         tmp /= 10;
//         ++i;
//     }
//     while(!tmpStack.empty()){
//         res *= 10;
//         res += tmpStack.top();
//         tmpStack.pop();
//     }
//     return res;
// }

// int main() {
//     char c = '0' + 12;
//     cout << c;
//     return 1;
// }

// char lower(const char &c) {
//     char res = c;
//     if (c >= 'A' && c <= 'Z') {
//         res = 'a' + (c - 'A');
//     }
//     return res;
// }
//
// string test(const string &sentence) {
//     string res = "";
//     int size = sentence.size();
//     string str = "";
//     queue<string> words_Que;
//     for (int i = 0; i < size; ++i) {
//         str += sentence[i];
//         if (i == size - 1 || sentence[i] == ' ') {
//             if (!words_Que.empty()) {
//                 string cmp = words_Que.front();
//                 int index = 0;
//                 if (str.size() == cmp.size() || str.size() == cmp.size() - 1) {
//                     while (index < str.size()) {
//                         char cstr = lower(str[index]), ccmp = lower(cmp[index]);
//                         if (cstr != ccmp) break;
//                         ++index;
//                     }
//                 }
//                 if (index < str.size()) {
//                     res += cmp;
//                     words_Que.pop();
//                     words_Que.push(str);
//                 }
//             } else {
//                 words_Que.push(str);
//             }
//             str = "";
//         }
//     }
//     if (!words_Que.empty()) {
//         res += words_Que.front();
//         words_Que.pop();
//     }
//     return res;
// }
//
// int main() {
//     string sentence;
//
//     getline(cin, sentence);
//     cout << test(sentence);
// }