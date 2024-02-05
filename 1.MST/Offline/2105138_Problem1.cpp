#include <bits/stdc++.h>
#include"MST.h"
using namespace std;


int main()
{
    int n,m;
    cin>>n>>m;
    vector<pair<int,pair<int,int>>> edges;
    for(int i=0; i<m; i++)
    {
        int u,v,wt;
        cin>>u>>v>>wt;
        edges.push_back({wt,{u,v}});
    }
    set<vector<pair<int,pair<int,int>>>> allmst=allmsts(edges,n);
    cout<<"MSTs: "<<endl;
    int count=1;
    for(auto &mst: allmst)
    {
        cout<<count<<":[";
        count++;
        for(int i=0;i<mst.size();i++)
        {
            if(i==0)
            {
                cout<<"[";
            }
            else cout<<",[";
                cout<<mst[i].second.first<<","<<mst[i].second.second<<","<<mst[i].first<<"]";
        }
        cout<<"]"<<endl;
    }

    return 0;
}
