#include <bits/stdc++.h>
using namespace std;
const int N = 1000;
const int INF = 1e9 + 10;
vector<vector<pair<int, int> > > graph(N);
vector<int> parent(N, 0);
vector<int> inflow(N, 0);
vector<int> outflow(N, 0);
vector<bool> bfs_visited(N, false);
bool bfs(int src, int sink)
{
    bfs_visited.assign(N, 0);
    queue<int> q;
    q.push(src);
    bfs_visited[src] = true;
    parent[src] = -1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < (int)graph[u].size(); i++)
        {
            int v = graph[u][i].first;
            int w = graph[u][i].second;

            if (!bfs_visited[v] && w!=0)
            {
                q.push(v);
                bfs_visited[v] = true;
                parent[v] = u;
            }
        }
    }
    return bfs_visited[sink];
}

void findMinPathFlow(int src, int sink, int &minPathFlow)
{
    for (int v = sink; v != src; v = parent[v])
            {
                int u = parent[v];
                for (int i = 0; i < (int)graph[u].size(); i++)
                {
                    if (graph[u][i].first == v)
                    {
                        int capacity = graph[u][i].second;
                        minPathFlow = min(minPathFlow, capacity);
                        break;
                    }
                }
            }

}

int ford_Fulkerson(int src, int sink)
{
    {
        int maxFlow = 0;
        while (bfs(src, sink))
        {
            int minPathFlow = INF;
            findMinPathFlow(src,sink,minPathFlow);
            for (int v = sink; v != src; v = parent[v])
            {
                int u = parent[v];
                for (int i = 0; i < (int)graph[u].size(); i++)
                {
                    if (graph[u][i].first == v)
                    {
                        inflow[v] += graph[u][i].second;
                        outflow[u] += minPathFlow;
                        break;
                    }
                }
            }

            for (int v = sink; v != src; v = parent[v])
            {
                int u = parent[v];
                for (int i = 0; i < (int)graph[u].size(); i++)
                {
                    if (graph[u][i].first == v)
                    {
                        graph[u][i].second -= minPathFlow;
                        break;
                    }
                }

                bool foundBackEdge = false;
                for (int i = 0; i < (int)graph[u].size(); i++)
                {
                    if (graph[u][i].first == u)
                    {
                        graph[u][i].second += minPathFlow;
                        foundBackEdge = true;
                        break;
                    }
                }

                if (!foundBackEdge)
                {
                    graph[v].push_back({u, minPathFlow});
                }
            }
            maxFlow += minPathFlow;
        }
        return maxFlow;
    }
}
pair<int,int> findMaximumNodeFlow(int src, int sink, int vertices)
{
    pair<int,int> result;
    int max_flow = ford_Fulkerson(src, sink);
    int max_InOutFlow = INT_MIN;
    int max_NodeFlow;
    for (int i = 1; i <= vertices; i++)
    {
        if (i == src || i == sink) continue;
        else
        {
            if (inflow[i] + outflow[i] > max_InOutFlow)
            {
                max_InOutFlow = inflow[i] + outflow[i];
                max_NodeFlow = i;
            }
        }
    }
    max_InOutFlow = max(inflow[max_NodeFlow], outflow[max_InOutFlow]);
    result={max_NodeFlow, max_InOutFlow};
    return result;
}
