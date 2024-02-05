#include<bits/stdc++.h>
#include"Ford_Fulkerson.cpp"
using namespace std;
int main()
{
    //freopen("in.txt", "r",stdin);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v, capacity;
        cin >> u >> v >> capacity;
        graph[u].push_back({v, capacity});
    }

    int src, sink;
    cin >> src >> sink;
    pair<int, int> result = findMaximumNodeFlow(src, sink, n);
    int nodemax = result.first;
    int flowmax = result.second;
    cout << nodemax << " " << flowmax << endl;
    return 0;
}
