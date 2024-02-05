#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
const int INF=1e9+10;


int Bellmanford(vector<pair<int, pair<int, int>>> graph, int n, int src, int dest)
{
    vector<int> Distance(N,INF);
    Distance[src]=0;
    for(int i=0;i<n-1;i++)
    {
        for(auto &edge:graph)
        {
            int u=edge.second.first;
            int v=edge.second.second;
            int wt=edge.first;

            if(Distance[u]+wt<Distance[v])
            {
                Distance[v]=Distance[u]+wt;
            }
        }
    }

    for(auto &edge:graph)
        {
            int u=edge.second.first;
            int v=edge.second.second;
            int wt=edge.first;
            if(Distance[u]+wt<Distance[v])
            {
               return INF;
            }
        }

        return Distance[dest];
}


int main()
{
    int n,m;
    cin>>n>>m;
    vector<pair<int,pair<int,int>>> graph;
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
       graph.push_back({w,{u,v}});

    }
    int A,B;
    cin>>A>>B;
    int L,H;
    cin>>L>>H;
    int S,D;
    cin>>S>>D;
    int initial_shortest_distance=Bellmanford(graph,n,S,D);
    int min_distance=INF;
    int min_weight=INF;
    for(int i=L;i<=H;i++)
    {
        graph.push_back({i,{A,B}});
        int mini=Bellmanford(graph,n+1,S,D);
        if(mini<initial_shortest_distance)
        {
            min_distance=mini;
            min_weight=i;
            break;
        }
        graph.pop_back();
    }
    if(min_distance==INF)
    {
        cout<<"impossible"<<endl;
    }
    else cout<<min_weight<<" "<< min_distance<<endl;

}
/*
test case -1
4 4
1 2 10
2 3 10
1 4 20
4 2 30
4 3
-50 50
1 3
test case -2
5 6
1 2 1
2 3 2
3 5 1
3 4 2
4 5 5
1 4 3
4 2
-10 5
1 5
test case-3
4 4
1 2 10
2 3 10
1 4 20
4 2 30
4 3
1 20
1 3

test case-4
4 4
1 2 10
2 3 12
3 4 -5
4 1 15
2 4
-40 -30
1 4

test case-5
4 4
1 2 10
2 3 12
3 4 -5
4 1 -5
2 4
5 10
1 4

test case -6
4 4
1 2 10
2 3 12
3 4 -5
4 1 -5
2 4
-10 10
1 4
*/
