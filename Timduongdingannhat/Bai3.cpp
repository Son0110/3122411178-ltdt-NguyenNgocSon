#include <bits/stdc++.h>
using namespace std;
const long long INF = (long long)1e15;

vector<int> reconstructPath(int u, int v, const vector<vector<int>>& next) {
    vector<int> path;
    if (next[u][v] == -1) return path;
    int cur = u;
    path.push_back(cur);
    while (cur != v) {
        cur = next[cur][v];
        path.push_back(cur);
        if ((int)path.size() > 1000000) break; // bảo vệ tránh loop
    }
    return path;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    // Dòng đầu: n m
    if (!(cin >> n >> m)) return 0;
    vector<vector<long long>> dist(n+1, vector<long long>(n+1, INF));
    vector<vector<int>> nxt(n+1, vector<int>(n+1, -1));

    for (int i=1;i<=n;i++){
        dist[i][i] = 0;
        nxt[i][i] = i;
    }

    for (int i=0;i<m;i++){
        int u,v,w; cin >> u >> v >> w;
        // nếu có nhiều cạnh giữa u-v, giữ cạnh nhỏ nhất
        if (w < dist[u][v]) {
            dist[u][v] = w;
            dist[v][u] = w; // nếu vô hướng; nếu có hướng thì bỏ dòng này
            nxt[u][v] = v;
            nxt[v][u] = u;
        }
    }

    // Floyd-Warshall
    for (int k=1;k<=n;k++){
        for (int i=1;i<=n;i++){
            if (dist[i][k] >= INF) continue;
            for (int j=1;j<=n;j++){
                if (dist[k][j] >= INF) continue;
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    nxt[i][j] = nxt[i][k];
                }
            }
        }
    }

    // In ma trận khoảng cách (n dòng, n cột)
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            if (dist[i][j] >= INF/2) cout << "INF";
            else cout << dist[i][j];
            if (j < n) cout << " ";
        }
        cout << "\n";
    }

    return 0;
}
