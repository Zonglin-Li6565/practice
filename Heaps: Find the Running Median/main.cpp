#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

void re_balance(priority_queue<int, vector<int> > & first, priority_queue<int, vector<int>, std::greater<int> > & second) {
    int half_size = (first.size() + second.size()) / 2;
    if (half_size > first.size()) {
        for (int i = 0; i < half_size - first.size(); i++) {
            first.push(second.top());
            second.pop();
        }
    } else {
        for (int i = 0; i < first.size() - half_size; i ++) {
            second.push(first.top());
            first.pop();
        }
    }
}

int main(){
    int n, in;
    priority_queue<int, vector<int> > first;
    priority_queue<int, vector<int>, std::greater<int> > second;
    freopen("input", "r", stdin);
    freopen("output", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> in;
        if (second.empty())
            second.push(in);
        else if (in >= second.top()) {
            second.push(in);
        } else {
            first.push(in);
        }
        re_balance(first, second);
        printf("%0.1f\n", (i % 2 == 0 ? (double)second.top() : (double)(second.top() + first.top()) / 2));
    }
    return 0;
}
