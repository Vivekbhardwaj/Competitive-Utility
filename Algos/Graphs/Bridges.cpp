#include<bits/stdc++.h>
using namespace std;

int id[100005],min_id_reachable[100005];

void dfs(int curr,int parent,int curr_id,vector<bool>&visited,vector<vector<int>> &v,vector<pair<int,int>> &bridges){
    visited[curr]=true;
    id[curr]=min_id_reachable[curr]=curr_id;
    for(auto i : v[curr]){
        if(i==parent)continue;
        if(visited[i]){
            min_id_reachable[curr]=min(min_id_reachable[curr],min_id_reachable[i]);
        }
        else{
            dfs(i,curr,curr_id+1,visited,v,bridges);
            min_id_reachable[curr]=min(min_id_reachable[curr],min_id_reachable[i]);
            if(min_id_reachable[i]>id[curr]){
                bridges.push_back({curr,i});
            }
        }
    }
}

vector<pair<int,int>> find_bridges(vector<vector<int>> &v){
    memset(id,-1,sizeof(id));
    memset(min_id_reachable,-1,sizeof(min_id_reachable));
    vector<pair<int,int>> bridges;
    vector<bool> visited(v.size(),false);
    dfs(0,-1,0,visited,v,bridges);
    return bridges;
}

int main(){
    int n,m;cin>>n>>m;
    vector<vector<int>> v(n);
    for(int i=0,x,y;i<m;i++){
        cin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    vector<pair<int,int>> bridges=find_bridges(v);
    for(auto i : bridges) cout<<i.first<<"-->"<<i.second<<"\n";
    return 0;
}