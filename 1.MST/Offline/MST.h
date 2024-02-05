#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
vector<int> parent(N);
vector<int> size(N);
void make(int v)
{
    parent[v] = v;
    size[v] = 1;
}
//The function `find` is a recursive function that implements the path compression optimization technique in the Union-Find data structure. It is used to find the parent of a given vertex `v` in the disjoint set.
int find(int v)
{
    if (parent[v] == v)
    {
        return v;
    }
    return parent[v] = find(parent[v]);
}
void Union(int u, int v)
{
    u = find(u);
    v = find(v);
    if (u != v)
    {
        if (size[v] > size[u])
            swap(u, v);
        parent[v] = u;
        size[u] += size[v];
    }

}
void clear(vector<int> parent, vector<int> size)
{
    parent.resize(N);
    size.resize(N);

}
int weight(vector<pair<int,pair<int,int> > > graph)
{
    int t_wt=0;
    for(auto & v : graph)
    {
        t_wt+=v.first;
    }
    return t_wt;
}
void totalCombinations(int index, int mstEdge,set<vector<pair<int,pair<int,int> > > >&combininations,vector<pair<int,pair<int,int> > > &graph,vector<pair<int,pair<int,int> > > &singleMST)
{
    if(mstEdge==0)
    {
        combininations.insert(singleMST);
    }
    if(index>=graph.size())
    {
        return;
    }
    singleMST.push_back(graph[index]);
    totalCombinations(index+1,mstEdge-1,combininations,graph,singleMST);
    singleMST.pop_back();
    totalCombinations(index+1,mstEdge,combininations,graph,singleMST);
}
// The function `probableGraphCombination` takes in a graph, the number of edges in the minimum spanning tree (mstEdge), and the total weight of the minimum spanning tree (totalweight).
set<vector<pair<int,pair<int,int> > > > probableGraphCombination(vector<pair<int,pair<int,int> > > &graph,int mstEdge,int totalweight)
{
    set<vector<pair<int,pair<int,int> > > > mstCombinations;
    set<vector<pair<int,pair<int,int> > > > combinations;
    vector<pair<int,pair<int,int> > > singleMST;
    totalCombinations(0,mstEdge,combinations,graph,singleMST);
    for(auto &comb:combinations)
    {
        int combweight=weight(comb);
        if(combweight==totalweight)
        {
            mstCombinations.insert(comb);
        }
    }
    return mstCombinations;
}

set<vector<pair<int,pair<int,int> > > > allmsts(vector<pair<int,pair<int,int> > > graph, int n)
{
    set<vector<pair<int,pair<int,int> > > > msts;
    set<vector<pair<int,pair<int,int> > > > p_msts;
    sort(graph.begin(),graph.end());
    for(int i=0; i<=n; i++)
    {
        make(i);
    }
    int total_wt=0;
    for(auto &edge:graph)
    {
        int weight=edge.first;
        int a=edge.second.first;
        int b=edge.second.second;
        if(find(a)!=find(b))
        {
            Union(a,b);
            total_wt+=weight;
        }

    }
    p_msts=probableGraphCombination(graph,n-1,total_wt);
    for(auto &pcomb:p_msts)
    {
        clear(parent,size);
        for(int i=0; i<=n; i++)
        {
            make(i);
        }
        bool flag=true;
        for(auto &edge:pcomb)
        {
           int u=edge.second.first;
           int v=edge.second.second;
           make(u);
           make(v);
        }
        for(auto &edge:pcomb)
        {
           int u=edge.second.first;
           int v=edge.second.second;
          if(find(u)!=find(v))
          {
             Union(u,v);
          }
          else
          {
              flag=false;
              break;
          }

        }
        if(flag)
          {
              msts.insert(pcomb);
          }

    }
    return msts;

}

