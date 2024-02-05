#include<bits/stdc++.h>
#include"Ford_Fulkerson.cpp"
vector<bool> dfs_visited(N, false);
bool dfs(int vertex)
{
    dfs_visited[vertex] = true;
    for (int i = 0; i < (int)graph[vertex].size(); i++)
    {
        int v = graph[vertex][i].first;
        int w = graph[vertex][i].second;

        if (!dfs_visited[v]&& w!=0)
        {
            dfs_visited[v] = true;
            dfs(v);
        }
    }
}
int findMinCut(int src, int sink, int vertices, vector<int>&cut1, vector<int>&cut2)
    {
        int maxflow=ford_Fulkerson(src,sink);
        dfs(src);
        cut1.push_back(src);
        for (int i = 1; i <= vertices; i++)
        {
            if (i == src || i == sink) continue;
            else
            {
                if (dfs_visited[i])
                {
                    cut1.push_back(i);
                }

                else
                {
                    cut2.push_back(i);
                }
            }
        }
        cut2.push_back(sink);
        return  maxflow;
    }
    int main()
    {
    //freopen("in.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    int u, v, capacity;
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> capacity;
        graph[u].push_back({v, capacity});
    }

    int src, sink;
    cin >> src >> sink;
    vector<int>cut1,cut2;
    int cutflow=findMinCut(src,sink,n,cut1,cut2);
    cout<<"[{";
    for(int i = 0; i<cut1.size(); i++)
    {
        if(i==cut1.size()-1)
        {
            cout<<cut1[i]<<"}";
        }
        else
        cout<<cut1[i]<<",";
    }
    cout<<",{";
    for(int i = 0; i<cut2.size(); i++)
    {
        if(i==cut2.size()-1)
        {
            cout<<cut2[i]<<"}";
        }
        else
        cout<<cut2[i]<<",";
    }
    cout<<"]"<<endl;
    cout<<cutflow<<endl;
    return 0;
    }
