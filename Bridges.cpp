#include<bits/stdc++.h>
using namespace std;

bool visited[100005];
int id[100005];
int min_id_reachable[100005];
int curr_id=0;
vector<vector<int>>v;

void dfs(int node,int parent){
    id[node]=++curr_id;
    visited[node]=true;
    min_id_reachable[node]=id[node];

    for(auto i : v[node]){
        if(i==parent) continue;
        else if(visited[i]) min_id_reachable[node]=min(min_id_reachable[node],min_id_reachable[i]);
        else {
            dfs(i,node);
            min_id_reachable[node]=min(min_id_reachable[node],min_id_reachable[i]);
            if(min_id_reachable[i]>id[node]){
                cout<<"Edge "<<node<<" to "<<i<<" is a bridge \n";
            }
        }
    }
}

int main(){
    memset(visited,false,sizeof(visited));
    int n,m;cin>>n>>m;
    v.resize(n);
    for(int i=0,x,y;i<m;i++){
        cin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    dfs(0,-1);
    return 0;
}