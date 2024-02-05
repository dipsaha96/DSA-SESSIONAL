#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10;
const int INF=1e9+10;
int dist[N][N];

void floyd_warshall(vector<pair<int,pair<int,int>>> graph,int vertices)
{
     for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            if(i==j)
            {
                dist[i][j]=0;
            }
            else
                dist[i][j]=INF;
        }
    }
    for(auto &edge:graph)
    {
        int x=edge.second.first;
        int y=edge.second.second;
        int wt=edge.first;
        dist[x][y]=wt;
        dist[y][x]=wt;
    }
    for(int k=1; k<=vertices; k++)
    {
        for(int i=1; i<=vertices; i++)
        {
            for(int j=1; j<=vertices; j++)
            {
                dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
            }
        }
    }
}
void smallest_numberof_cities(vector<pair<int,int>> &result,int vertices, int &minterm, int threshold_cost)
{
    for(int i=1; i<=vertices; i++)
    {
        int count=0;
        for(int j=1; j<=vertices; j++)
        {
            if(i!=j&& dist[i][j]<=threshold_cost)
            {
                count++;
            }
        }
        if(count<minterm)
        {
            minterm=count;
        }
        result.push_back({i,count});
    }
}
int main()
{


    int n,m;
    cin>>n>>m;
    vector<pair<int,pair<int,int>>> graph;
    for(int i=0; i<m; i++)
    {
        int x,y,wt;
        cin>>x>>y>>wt;
        graph.push_back({wt,{x,y}});
    }
    int t_cost;
    cin>>t_cost;
    floyd_warshall(graph,n);
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            if(dist[i][j]==INF)
            {
                cout<<"I ";
            }
            else
                cout<<dist[i][j]<<" ";
        }
        cout<<endl;
    }

    vector<pair<int,int>> result;
    int minterm=INF;
    smallest_numberof_cities(result,n,minterm,t_cost);
    for(int i=0; i<result.size(); i++)
    {
        if(result[i].second==minterm)
        {
            cout<<result[i].first<<" ";
        }
    }
    return 0;
}
