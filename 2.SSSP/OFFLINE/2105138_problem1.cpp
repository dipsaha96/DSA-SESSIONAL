#include<bits/stdc++.h>
using namespace std;
const int N=100;
const int INF=1e9+10;
vector<pair<int,pair<int,int>>>graph[N][N];
int dijkstra(vector<pair<int,pair<int,int>>>graph[N][N],vector<int> gasPrice, int vertices, int capacity, int src, int dest)
{
    vector<vector<int>>distance(N+1,vector<int>(N+1,INF));
    for(int i=0; i<vertices; i++)
    {
        for(int j=0; j<=capacity; j++)
        {
            for(int k=j+1; k<=capacity; k++)
            {
                int wt=(k-j)*gasPrice[i];
                graph[i][j].push_back({wt,{i,k}});
            }
        }
    }
    set<pair<int,pair<int,int>>>st;
    st.insert({0,{src,0}});
    distance[src][0]=0;
    while(st.size()>0)
    {
        pair<int,pair<int,int>> mini=*st.begin();
        int u=mini.second.first;
        int reserve_gas=mini.second.second;
        int weight=mini.first;
        st.erase(st.begin());
        for(auto & edge: graph[u][reserve_gas])
        {
            int v=edge.second.first;
            int v_gas=edge.second.second;
            int v_wt=edge.first;
            if(distance[v][v_gas]>distance[u][reserve_gas]+v_wt)
            {
                distance[v][v_gas]=distance[u][reserve_gas]+v_wt;
                st.insert({distance[v][v_gas],{v,v_gas}});
            }
        }
    }
    return distance[dest][0];

}

int main()
{
    int n,m,c;
    cin>>n>>m>>c;
    vector<int> gasPrice;
    gasPrice.push_back(0);
    for(int i=0; i<n; i++)
    {
        int p;
        cin>>p;
        gasPrice.push_back(p);
    }
    //vector< vector<vector<pair<int,pair<int,int>>>>>graph(N+1,vector<vector<pair<int,pair<int,int>>>>(N+1,vector<pair<int,pair<int,int>>>()));
    for(int i=0; i<m; i++)
    {
        int u,v,wt;
        cin>>u>>v>>wt;
        if(wt<=c)
        {
            for(int j=0; j<=c; j++)
            {
                for(int k=0; k<=c; k++)
                {
                    if(wt+k<=c && wt+k-j>=0)
                    {
                        graph[u][j].push_back({(wt+k-j)*gasPrice[u],{v,k}});
                    }
                }
            }
        }
    }
    int src,dest;
    cin>>src>>dest;
    int minimum_money=dijkstra(graph,gasPrice,n,c,src,dest);
    if(minimum_money==INF)
        cout<<"impossible"<<endl;
    else
        cout<<minimum_money<<endl;
    return 0;

}
/*
TASK-1:
5 5 10
10 10 20 12 13
1 2 9
1 3 8
2 3 1
2 4 11
3 4 7
1 4
TASK-2
4 4 8
10 12 11 13
1 2 5
1 3 11
2 4 12
3 4 7
1 4
TASK-3
5 5 10
1 10 2 12 13
1 2 9
1 3 8
2 3 1
2 4 11
3 4 7
1 4
TASK-4
5 5 10
1 10 2 12 13
1 2 9
1 3 8
2 3 1
2 4 1
3 4 7
1 4
TASK-5
4 5 9
5 3 6 2
1 2 1
2 3 3
1 3 5
3 4 1
1 4 6
1 4
*/
