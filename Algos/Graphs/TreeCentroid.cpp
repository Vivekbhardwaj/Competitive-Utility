#include<bits/stdc++.h>
using namespace std;

int sz_of_subtree[100005],centroid;
const int INF=1e9+42;

int find_sz(int curr,int parent,vector<bool> &visited,vector<vector<pair<int,int>>> &g){
    visited[curr]=true;
    sz_of_subtree[curr]++;
    for(auto i : g[curr]){
        if(visited[i.first]||i.first==parent) continue;
        sz_of_subtree[curr]+=find_sz(i.first,curr,visited,g);
    }
    return sz_of_subtree[curr];
}

void dfs2(int curr,int parent,vector<bool> &visited,vector<vector<pair<int,int>>> &g){
    visited[curr]=true;
    bool can_be_centroid=true;
    for(auto i : g[curr]){
        if(!visited[i.first]&&i.first!=parent){
            if(sz_of_subtree[i.first]>(int)g.size()/2){ can_be_centroid=false; dfs2(i.first,curr,visited,g);}
        }
    }
    if(can_be_centroid) centroid=curr;
}

int main(){

	return 0;
}
