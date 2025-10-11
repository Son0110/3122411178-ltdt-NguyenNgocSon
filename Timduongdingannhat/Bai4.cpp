#include <bits/stdc++.h>
using namespace std;
const long long INF = (long long)1e15;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, s, t;
    if (!(cin >> n >> m >> s >> t)) return 0;
    vector<vector<pair<int,int>>> adj(n+1);
    for (int i=0;i<m;i++){
        int u,v,w; cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w}); // vô hướng; nếu có hướng thì bỏ dòng này
    }

    vector<long long> dist(n+1, INF);
    vector<int> parent(n+1, -1);
    dist[s] = 0;
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
    pq.push({0, s});
    while (!pq.empty()){
        long long du = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (du != dist[u]) continue;
        for (size_t i=0;i<adj[u].size();++i){
            int v = adj[u][i].first;
            int w = adj[u][i].second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[t] >= INF) {
        cout << "Khong co duong di\n";
        return 0;
    }
    cout << dist[t] << "\n";
    vector<int> path;
    for (int cur = t; cur != -1; cur = parent[cur]) path.push_back(cur);
    reverse(path.begin(), path.end());
    for (int v : path) cout << v << " ";
    cout << "\n";
    return 0;
}
