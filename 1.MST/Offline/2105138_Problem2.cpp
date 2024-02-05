#include <bits/stdc++.h>
#include"MST.h"
using namespace std;


int main()
{
    int n,m;
    cin>>n>>m;
    vector<pair<int,pair<int,int>>> edges;
    vector<pair<int,pair<int,int>>> graph;
    for(int i=0; i<m; i++)
    {
        int u,v,wt;
        cin>>u>>v>>wt;
        graph.push_back({wt,{u,v}});
        edges.push_back({wt,{u,v}});
    }
    set<vector<pair<int,pair<int,int>>>> allmst=allmsts(edges,n);
    for(auto &edge: graph)
    {
        int count=0;
        for(auto &mst:allmst)
        {
            for(auto &mstedge:mst)
            {
                if(mstedge==edge)
                    count++;
            }
        }
        if(count==allmst.size())
        {
            cout<<"any"<<endl;
        }
        else if(count==0)
        {
            cout<<"none"<<endl;
        }
        else cout<<"at least one"<<endl;
    }

    return 0;
}



