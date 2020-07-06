#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>


#include "lib.h"

using namespace std;

int N;
vector<vector<int>> graf;
vector<bool> used;
vector<int> ans;
vector<int> h;

const int inf = 2147483647;

void connected_component();
void way_existence(int v1, int v2);
void short_way(int v1, int v2);
void prim();
void warshall();


int main() {
    string path;
    cout << "Specify the path to the file to write\n";
    getline(cin, path);
    ifstream fin(path, ios::binary);
    if (!fin) {
        cout << "File not found\n";
        return 1;
    }
    fin >> N;
    used.resize(N);
    graf.resize(N);
    h.resize(N);
    int v;
    int u;
    char c;
    int t;
    int s;
main_line:
    cout << "�������� ���������� ��������:" << endl
        << "1) ������ � �� ���������� �������" << endl
        << "2) ������ �� ����������� �������" << endl
        << "0) �����" << endl;
    cin >> s;
    switch (s) {
    case 0:
        break;
    case 1:
        for (int i = 0; i < N; i++) {
            int ver;
            fin >> ver;
            while (ver != -1) {
                fin >> ver;
                if (ver == -1) {
                    break;
                }
                graf[i].push_back(ver);
            }
        }
    g_line:
        cout << "�������� ���������� ��������:" << endl
            << "1) ����� � �������" << endl
            << "2) ����� � ������" << endl
            << "3) ����� ���������� ����������" << endl
            << "4) ��������� ������������� ���� ����� ����� ���������" << endl
            << "5) ����� ���������� ���������� ����� ����� ���������" << endl
            << "9) ��������� � ����������� ������" << endl
            << "0) �����" << endl;
        cin >> t;
        null_func(N, ans, used);
        switch (t) {
        case 9:
            goto main_line;
            break;
        case 0:
            goto exit_line;
            break;
        case 1:
            bool tmp;
            cout << "�������� ���������� ��������:" << endl
                << "0) ����� � ������� � ������������ �������" << endl
                << "1) ����� � ������� ����� �����" << endl;
            cin >> tmp;
            if (tmp) {
                for (int i = 0; i < N; ++i) {
                    if (!used[i]) {
                        ans.clear();
                        dfs(i, ans, used, graf);
                        write_answer(ans);
                    }
                }
            }
            else {
                cout << "������� ����� �������" << endl;
                cin >> v;
                dfs(v, ans, used, graf);
                write_answer(ans);
            }
            break;
        case 2:
            cout << "������� ����� �������" << endl;
            cin >> v;
            bfs(v, ans, used, h, graf);
            write_answer(ans);
            break;
        case 3:
            connected_component();
            break;
        case 4:
            cout << "������� ������ ������. ������� �����" << endl;
            cin >> v >> u;
            way_existence(v, u);
            break;
        case 5:
            cout << "������� ������ ������. ������� �����" << endl;
            cin >> v >> u;
            short_way(v, u);
            break;
        default:
            cout << "������� ������ ��������" << endl;
            break;
        }
        cout << "������ ��������� ������ ��������? Y/N" << endl;
        cin >> c;
        if (towlower(c) == 'y') {
            goto g_line;
        }
        break;
    case 2:
        for (int i = 0; i < N; i++) {
            graf[i].resize(N);
            for (int j = 0; j < N; j++) {
                int ver;
                fin >> ver;
                graf[i][j] = ver;
            }
        }
    wg_line:
        cout << "1) ����� ������������ ��������� ������ ����� �������� �����" << endl
            << "2) ������������ ��������� ����� �������� ��������" << endl
            << "9) ��������� � ����������� ������" << endl
            << "0) �����" << endl;
        cin >> t;
        null_func(N, ans, used);
        switch (t) {
        case 9:
            goto main_line;
            break;
        case 0:
            goto exit_line;
            break;
        case 1:
            prim();
            break;
        case 2:
            warshall();
            break;
        default:
            cout << "������� ������ ��������" << endl;
            break;
        }
        cout << "������ ��������� ������ ��������? Y/N" << endl;
        cin >> c;
        if (towlower(c) == 'y') {
            goto wg_line;
        }
        break;
    default:
        cout << "������� ������ ��������" << endl;
        break;
    }
exit_line:
    return 0;
}

void connected_component() { // ����� ��������� �����
    int count = 0;
    for (int k = 0; k < N; k++) {
        if (!used[k]) {
            ans.clear();
            dfs(k, ans, used, graf);
            count++;
            cout << "���������� ����������� � " << count << ": " << endl;
            write_answer(ans);
        }
    }
    cout << "����� ���������� ��������� ����� - " << count << endl;
}

void way_existence(int v1, int v2) { // ������������� ���� ����� ����� ���������
    dfs(v1, ans, used, graf);
    used[v2] ? cout << "����� ��������� ���� ����" : cout << "����� ��������� ��� ����";
    cout << endl;
}

void short_way(int v1, int v2) { //�������� ���� ����� ����� ���������
    bfs(v1, ans, used, h, graf);
    if (!used[v2]) {
        cout << "����� ��������� ��� ����" << endl;
    }
    else {
        ans.clear();
        for (int k = v2; k != -1; k = h[k]) {
            ans.push_back(k);
        }
        vector<int> p;
        int t = (int)ans.size();
        p.resize(t);
        for (int k = 0; k < t; k++) {
            p[t - k - 1] = ans[k];
        }
        for (int k = 0; k < t; k++) {
            ans[k] = p[k];
        }
        cout << "���������� ���� ����� ���������:" << endl;
        write_answer(ans);
        cout << endl;
    }
}

void prim() {
    vector<int> min_g;
    vector<int> ver_g;
    min_g.resize(N);
    ver_g.resize(N);
    for (int i = 0; i < N; i++) {
        ver_g[i] = -1;
        min_g[i] = inf;
    }
    min_g[0] = 0;
    for (int k = 0; k < N; k++) {
        int v = -1;
        for (int i = 0; i < N; i++) {
            if (!used[i] && (v == -1 || min_g[i] < min_g[v])) {
                v = i;
            }
        }
        if (min_g[v] == inf) {
            cout << "��� ��������� ������" << endl;
            exit(0);
        }
        used[v] = true;
        if (ver_g[v] != -1) {
            cout << v << " " << ver_g[v] << " " << min_g[v] << endl;
        }
        for (int i = 0; i < N; i++) {
            if (graf[v][i] < min_g[i]) {
                min_g[i] = graf[v][i];
                ver_g[i] = v;
            }
        }
    }
}

void warshall() {
    for (int i = 0; i < N; i++) {
        graf[i][i] = 0;
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                if (graf[i][j] > (graf[i][k] + graf[k][j])) {
                    graf[i][j] = graf[i][k] + graf[k][j];
                }
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << graf[i][j] << " ";
        }
        cout << endl;
    }
}