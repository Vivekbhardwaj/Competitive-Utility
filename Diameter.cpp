#include<bits/stdc++.h>
using namespace std;

void dfs(vector<vector<int>> &tree,int index,int curr_distance,vector<bool> &visited,pair<int,int>&p){
    if(curr_distance>p.second){p.first=index;p.second=curr_distance;}
    visited[index]=true;
    for(auto i : tree[index]){
        if(!visited[i])
            dfs(tree,i,curr_distance+1,visited,p);
    }
}

int diameter(vector<vector<int>> &tree){
    vector<bool> visited(tree.size(),false);
    pair<int,int> p=make_pair(0,0);
    dfs(tree,0,0,visited,p);
    p.second=0;
    fill(visited.begin(),visited.end(),false);
    dfs(tree,p.first,0,visited,p);
    return p.second;
}

int main(){
    cout<<"Enter the no. of nodes in tree ";
    int n;cin>>n;
    vector<vector<int>> tree(n); 
    cout<<"Enter the no of edges in tree ";
    int m;cin>>m;
    cout<<"Enter the to and from of edge ";
    for(int i=0,from,to,weight;i<m;i++){
        cin>>from>>to;
        tree[from].push_back(to);
        tree[to].push_back(from);
    }
    int d=diameter(tree);
    cout<<d<<"\n";

    return 0;
}