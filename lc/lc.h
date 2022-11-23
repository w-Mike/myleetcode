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



void testAny()
{
    int i = 1;
    int a = (i++) + i;
    cout << a;
}

void printVec(const vector<int> &vec)
{
    for (auto num : vec)
    {
        cout << num << " ";
    }
    cout << endl;
}