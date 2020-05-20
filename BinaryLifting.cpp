#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>tree;
vector<vector<int>> lifting_table;
vector<bool> visited;
int tme;
vector<int> in;
vector<int> out;

void dfs(int curr=0,int parent=0){
    in[curr]=tme++;
    visited[curr]=true;
    lifting_table[curr][0]=parent;
    for(int k=1;k<lifting_table[curr].size();k++){
        lifting_table[curr][k]=lifting_table[lifting_table[curr][k-1]][k-1];
    }

    for(auto i : tree[curr]){
        if(i!=parent) dfs(i,curr);
    }
    out[curr]=tme++;
}

void lcs_util(){
    int n=tree.size();
    lifting_table.resize(tree.size());
    visited.resize(tree.size(),false);
    in.resize(tree.size());
    out.resize(tree.size());
    int range_of_k;
    for(int i=30;i>=0;i--){
        if(n&(1<<i)) {range_of_k=i;break;}
    }
    for(int i=0;i<lifting_table.size();i++){
        lifting_table[i].resize(range_of_k);
    }
    if(n!=(1<<range_of_k))range_of_k+=1;
    dfs();
    for(int i=0;i<n;i++){cout<<i<<"----->";for(auto j : lifting_table[i]) cout<<j<<" ";cout<<"\n";}

    cout<<"In times :";
    for(auto i : in) cout<<i<<" ";cout<<"\n";
    cout<<"Out times : ";
    for(auto i : out) cout<<i<<" ";cout<<"\n";
}


bool isAncestor(int x,int y){
    return (in[x]<in[y]&&out[x]>out[y]);
}

int lca(int x,int y){
    if(isAncestor(x,y)) {cout<<x<<" is ancestor of "<<y<<"\n";return x;}
    else if(isAncestor(y,x)) {cout<<y<<" is ancestor of "<<x<<"\n";return y;}
    x=lifting_table[x][0];
    for(int i=lifting_table[0].size()-1;i>=0;i--){
        if(isAncestor(lifting_table[x][i],y)) {cout<<lifting_table[x][i]<<" is an ancestor of "<<y<<" so we will check if there is some ancestor below it \n";}
        else {cout<<"Since "<<lifting_table[x][i]<<" is not ancestor of "<<y<<" so we will check if is is ";x=lifting_table[lifting_table[x][i]][0];
                cout<<x<<" is ancestor or it is above it "<<"\n";}
    }

    return x;
}



int main(){
    int n;cin>>n;
    tree.resize(n);
    for(int i=0,x,y;i<n-1;i++){
        cin>>x>>y;
        tree[x].push_back(y);
        tree[y].push_back(x);
    }
    lcs_util();
    int q;cin>>q;
    while(q--){
        int x,y;
        cin>>x>>y;
        cout<<lca(x,y)<<"\n";
    }
    return 0;
}