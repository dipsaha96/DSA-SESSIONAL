#include <bits/stdc++.h>
#include"MST.h"
using namespace std;


int main()
{
    int n,m;
    cin>>n>>m;
    vector<pair<int,pair<int,int>>> edges;
    vector<pair<int,pair<int,int>>> graph;
    vector<int> criticalEdge;
    vector<int> pseudoEdge;
    int index=0;
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
            criticalEdge.push_back(index);
        }
        else if(count!=0)
        {
            pseudoEdge.push_back(index);
        }
        index++;
    }
    cout<<"Critical edges: [";
    for(int i=0;i<criticalEdge.size();i++)
    {
        if(i!=0) cout<<",";
        cout<<criticalEdge[i];
    }
    cout<<"],"<<endl;
    cout<<"Pseudo critical edges: [";
    for(int i=0;i<pseudoEdge.size();i++)
    {
        if(i!=0) cout<<",";
        cout<<pseudoEdge[i];
    }
    cout<<"]"<<endl;

    return 0;
}




