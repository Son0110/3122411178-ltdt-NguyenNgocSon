#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;

void printState(int n, const vector<int>& dist, const vector<int>& pre, const vector<int>& vis) {
    cout << "dist: ";
    for (int i = 1; i <= n; ++i) {
        if (dist[i] >= INF) cout << i << ":INF ";
        else cout << i << ":" << dist[i] << " ";
    }
    cout << "\npre:  ";
    for (int i = 1; i <= n; ++i) {
        if (pre[i] == -1) cout << i << ":- ";
        else cout << i << ":" << pre[i] << " ";
    }
    cout << "\nvis:  ";
    for (int i = 1; i <= n; ++i) cout << vis[i] << " ";
    cout << "\n-------------------------\n";
}

int main() {
    int n, m, s, t;
    // Ví dụ: 6 7 1 4
    // followed by edges
    if (!(cin >> n >> m >> s >> t)) return 0;
    vector<vector<pair<int,int>>> adj(n+1);
    for (int i = 0; i < m; ++i) {
        int u,v,w; cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    vector<int> dist(n+1, INF), pre(n+1, -1), vis(n+1, 0);
    dist[s] = 0;

    cout << "Initial state:\n";
    printState(n, dist, pre, vis);

    for (int iter = 1; iter <= n; ++iter) {
        int u = -1;
        int best = INF;
        for (int i = 1; i <= n; ++i) {
            if (!vis[i] && dist[i] < best) { best = dist[i]; u = i; }
        }
        if (u == -1) break;
        vis[u] = 1;
        cout << "Iteration " << iter << ": choose u = " << u << " (dist=" << dist[u] << ")\n";

        for (auto e : adj[u]) {
            int v = e.first, w = e.second;
            if (!vis[v] && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pre[v] = u;
            }
        }
        printState(n, dist, pre, vis);
    }

    if (dist[t] >= INF) {
        cout << "Khong co duong di\n";
        return 0;
    }

    cout << "Khoang cach ngan nhat: " << dist[t] << "\n";
    vector<int> path;
    for (int cur = t; cur != -1; cur = pre[cur]) path.push_back(cur);
    reverse(path.begin(), path.end());
    cout << "Duong di: ";
    for (int x : path) cout << x << " ";
    cout << "\n";
    return 0;
}
