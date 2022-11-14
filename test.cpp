#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

int test(const int &x, const int &d, const int &n) {
    int res = 0;
    int i = 0;
    double comRes = (double) 1 / x;
    while (i < (n + d - 1)) {
        comRes *= 10;
        ++i;
    }
    int tmp = int(comRes);
    i = 0;
    stack<int> tmpStack;
    while (i < n) {
        tmpStack.push(tmp % 10);
        tmp /= 10;
        ++i;
    }
    while(!tmpStack.empty()){
        res *= 10;
        res += tmpStack.top();
        tmpStack.pop();
    }
    return res;
}

int main() {
    char c = '0' + 12;
    cout << c;
    return 1;
}




//char lower(const char &c) {
//    char res = c;
//    if (c >= 'A' && c <= 'Z') {
//        res = 'a' + (c - 'A');
//    }
//    return res;
//}
//
//string test(const string &sentence) {
//    string res = "";
//    int size = sentence.size();
//    string str = "";
//    queue<string> words_Que;
//    for (int i = 0; i < size; ++i) {
//        str += sentence[i];
//        if (i == size - 1 || sentence[i] == ' ') {
//            if (!words_Que.empty()) {
//                string cmp = words_Que.front();
//                int index = 0;
//                if (str.size() == cmp.size() || str.size() == cmp.size() - 1) {
//                    while (index < str.size()) {
//                        char cstr = lower(str[index]), ccmp = lower(cmp[index]);
//                        if (cstr != ccmp) break;
//                        ++index;
//                    }
//                }
//                if (index < str.size()) {
//                    res += cmp;
//                    words_Que.pop();
//                    words_Que.push(str);
//                }
//            } else {
//                words_Que.push(str);
//            }
//            str = "";
//        }
//    }
//    if (!words_Que.empty()) {
//        res += words_Que.front();
//        words_Que.pop();
//    }
//    return res;
//}
//
//int main() {
//    string sentence;
//
//    getline(cin, sentence);
//    cout << test(sentence);
//}