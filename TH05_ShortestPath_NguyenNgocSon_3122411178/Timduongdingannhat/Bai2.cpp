#include <bits/stdc++.h>
using namespace std;
const long long INF = (long long)1e15;

void dijkstra(int n, int src, const vector<vector<pair<int,int>>>& adj,
              vector<long long>& dist, vector<int>& parent) {
    dist.assign(n+1, INF);
    parent.assign(n+1, -1);
    dist[src] = 0;
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
    pq.push({0, src});
    while (!pq.empty()) {
        long long du = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (du != dist[u]) continue;
        for (size_t i=0;i<adj[u].size();++i) {
            int v = adj[u][i].first;
            int w = adj[u][i].second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    // Dòng đầu: n m s t x
    int s, t, x;
    if (!(cin >> n >> m >> s >> t >> x)) return 0;
    vector<vector<pair<int,int>>> adj(n+1);
    for (int i=0;i<m;i++){
        int u,v,w; cin >> u >> v >> w;
        // vô hướng:
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    vector<long long> dist_s, dist_x;
    vector<int> parent_s, parent_x;
    dijkstra(n, s, adj, dist_s, parent_s);
    dijkstra(n, x, adj, dist_x, parent_x);

    if (dist_s[x] >= INF || dist_x[t] >= INF) {
        cout << "Khong co duong di thoa man (qua dinh " << x << ")\n";
        return 0;
    }

    long long total = dist_s[x] + dist_x[t];
    cout << total << "\n";

    // Truy vết s -> x
    vector<int> path1;
    for (int cur = x; cur != -1; cur = parent_s[cur]) path1.push_back(cur);
    reverse(path1.begin(), path1.end()); // s ... x

    // Truy vết x -> t bằng parent_x (lưu: parent_x xây từ x)
    vector<int> path2;
    for (int cur = t; cur != -1; cur = parent_x[cur]) path2.push_back(cur);
    // path2: t ... x  -> cần đảo để thành x ... t
    reverse(path2.begin(), path2.end()); // x ... t

    // Ghép: path1 (s..x) + path2 (x..t) nhưng tránh lặp x
    vector<int> full = path1;
    for (size_t i = 1; i < path2.size(); ++i) full.push_back(path2[i]);

    for (int v : full) cout << v << " ";
    cout << "\n";
    return 0;
}
