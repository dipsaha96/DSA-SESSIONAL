#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
const int INF = 1e9 + 10;
vector<int> dist(N, INF);
#define iPair pair<int, int>
vector<iPair> g[N];
vector<int> parent(N, INF);
void dijkstra(int source)
{
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
    dist[source] = 0;
    pq.push({0, source});
    while (!pq.empty())
    {
        int v = pq.top().second;
        pq.pop();
        for (auto x : g[v])
        {
            int child_v = x.first;
            int wt = x.second;
            if (dist[child_v] > dist[v] + wt)
            {
                dist[child_v] = dist[v] + wt;
                pq.push({dist[child_v], child_v});
                parent[child_v] = v;
            }
        }
    }
}
int main()
{
    // freopen("in.txt","r",stdin);
    int n, m;
    cin >> n >> m;
    int cost[1000];
    for (int i = 1; i <= n; i++)
    {
        cin >> cost[i];
    }
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        g[x].push_back({y, cost[y]});
        g[y].push_back({x, cost[x]});
    }

    dijkstra(1);
    cout << dist[n];
    return 0;
}
