#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#include "lib.h"

using namespace std;

void null_func(int N, vector<int> ans, vector<bool> used) {
    for (int k = 0; k < N; k++) {
        used[k] = false;
    }
    ans.clear();
}

void write_answer(vector<int> ans) {
    for (int k = 0; k < (int)ans.size(); k++) {
        cout << ans[k] << " ";
    }
    cout << endl;
}

void dfs(int v, vector<int> ans, vector<bool> used, vector<vector<int>> graf) { // обход в глубину
    used[v] = true;
    for (int k = 0; k < (int)graf[v].size(); k++) {
        int top = graf[v][k];
        if (!used[top]) {
            dfs(top, ans, used, graf);
        }
    }
    ans.push_back(v);
}

void bfs(int v, vector<int> ans, vector<bool> used, vector<int> h, vector<vector<int>> graf) { // обход в ширину
    used[v] = true;
    queue <int> q;
    q.push(v);
    h[v] = -1;
    ans.push_back(v);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int k = 0; k < (int)graf[v].size(); k++) {
            int top = graf[v][k];
            if (!used[top]) {
                used[top] = true;
                q.push(top);
                ans.push_back(top);
                h[top] = v;
            }
        }
    }
}