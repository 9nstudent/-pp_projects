#include <iostream>

using namespace std;

void null_func(int N, vector<int> ans, vector<bool> used);
void write_answer(vector<int> ans);
void dfs(int v, vector<int> ans, vector<bool> used, vector<vector<int>> graf);
void bfs(int v, vector<int> ans, vector<bool> used, vector<int> h, vector<vector<int>> graf);