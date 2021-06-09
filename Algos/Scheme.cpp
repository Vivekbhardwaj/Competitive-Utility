#include<bits/stdc++.h>
using namespace std;

class SCC{

    vector<vector<int>> adj , rev_adj;
    int n;

    public :

    vector<vector<int>> scc;

    SCC(vector<vector<int>> &g){    //g must have 0 based indexing
        n = (int)g.size();
        adj = g;
        rev_adj.resize(n);
        for(int i=0;i<n;i++)    for(int j : g[i])   rev_adj[j].push_back(i);

        vector<int> order;
        vector<bool> visited(n,false);
        for(int i=0;i<n;i++)  if(!visited[i]) dfs1(i,visited,order);
        

        reverse(order.begin(),order.end());
        fill(visited.begin(),visited.end(),false);
        for(int i : order)
            if(!visited[i]){
                scc.push_back(vector<int>(0));
                dfs2(i,visited);
            }
        

        return;

    }

    private : 
    void dfs1(int curr,vector<bool> &visited,vector<int> &order){
        visited[curr] = true;
        for(int i : adj[curr])  if(!visited[i]) dfs1(i,visited,order);
        order.push_back(curr);
    }

    void dfs2(int curr,vector<bool> &visited){
        visited[curr] = true;
        scc.back().push_back(curr);
        for(int i : rev_adj[curr]) if(!visited[i]) dfs2(i,visited);
    }

};


int main(){

    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);

    int n;
    cin>>n;

    vector<vector<int>> g(n);
    for(int i=0;i<n;i++){
        int fi;
        cin>>fi;    fi--;
        g[i].push_back(fi);
    }

    SCC S(g);

    if(S.scc.size() == 1){  //there is only one strongly connected component
        cout<<0<<"\n";
        exit(0);
    }

    int end = S.scc.back().back();

    vector<int> indegree(n,0);
    vector<pair<int,int>> ans;

    for(vector<int> v : S.scc){
        bool reached = false;
        for(int i : v){
            for(int j : g[i])
                indegree[j]++;
            if(indegree[i] > 0){    //none of the elements in this scc is already reached by some node before
                reached = true;
            }
        }
        if(!reached){
            ans.emplace_back(end+1,v[0]+1);
        }
    }

    cout<<(int)ans.size()<<"\n";
    for(pair<int,int> p : ans){
        cout<<p.first<<" "<<p.second<<"\n";
    }

    return 0;
}