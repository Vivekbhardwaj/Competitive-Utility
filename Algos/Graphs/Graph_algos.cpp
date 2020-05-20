#include<bits/stdc++.h>
using namespace std;

const int INF=1e9;
int parent[100005];
int rnk[100005];

int find(int x){
    if(parent[x]==x) return x;
    else return parent[x]=find(parent[x]);
}

void Union(int x,int y){
    if(find(x)==find(y))return;
    else if(rnk[parent[x]]>rnk[parent[y]]) parent[y]=parent[x];
    else if(rnk[parent[x]]<rnk[parent[y]]) parent[x]=parent[y];
    else {
        parent[x]=parent[y];
        rnk[parent[x]]++;
    }
}

struct cmp{
    bool operator()(const pair<int,pair<int,int>> &a,const pair<int,pair<int,int>> &b){
        return a.second.second>b.second.second;
    }
};

vector<int> dijkstra(vector<vector<pair<int,int>>> &g,int start){
    vector<int> distance((int)g.size(),INF);distance[start]=0;
    multiset <pair<int,int>> s;
    for(int i=0;i<distance.size();i++) s.insert({distance[i],i});
    while(!s.empty()){
        int min_distant_node=s.begin()->second;s.erase(s.begin());
        for(auto i : g[min_distant_node]){
            if(s.count({distance[i.first],i.first})){
                if(distance[i.first]>distance[min_distant_node]+i.second){
                    s.erase(s.find({distance[i.first],i.first}));
                    distance[i.first]=distance[min_distant_node]+i.second;
                    s.insert({distance[i.first],i.first});
                }
            }
        }
    }
    return distance;
}

vector<int> bellman_ford(vector<vector<pair<int,int>>> &g,int start){
    vector<int> distance((int)g.size(),INF);distance[start]=0;
    vector<pair<int,pair<int,int>>> edge_list;
    for(int i=0;i<(int)g.size();i++){
        for(auto j : g[i]){
            edge_list.push_back({i,j});
        }
    }


    for(int i=0;i<(int)g.size()-1;i++){
        for(auto i : edge_list){
            if(distance[i.second.first]>distance[i.first]+i.second.second){
                distance[i.second.first]=distance[i.first]+i.second.second;
            }
        }
    }
    return distance;
}

vector<vector<int>> floyd_warshal(vector<vector<pair<int,int>>> &g){
    vector<vector<int>> dist_matrix((int)g.size(),vector<int>(g.size(),INF));
    for(int i=0;i<(int)g.size();i++){
        dist_matrix[i][i]=0;
        for(auto j : g[i]){
            dist_matrix[i][j.first]=j.second;
        }
    }

    //via
    for(int k=0;k<(int)g.size();k++){
        //from
        for(int j=0;j<(int)g.size();j++){
            //to
            for(int i=0;i<(int)g.size();i++){
                dist_matrix[i][j]=min(dist_matrix[i][j],dist_matrix[i][k]+dist_matrix[k][j]);
            }
        }
    }
    return dist_matrix;
}

vector<vector<int>> kruskals(vector<vector<pair<int,int>>> &g){
    memset(parent,-1,sizeof(parent));memset(rnk,0,sizeof(rnk));
    for(int i=0;i<(int)g.size();i++)parent[i]=i;
    vector<vector<int>> tree((int)g.size());
    vector<pair<int,pair<int,int>>> edge_list;
    for(int i=0;i<(int)g.size();i++){
        for(auto j : g[i]){
            edge_list.push_back({i,j});
        }
    }

    sort(edge_list.begin(),edge_list.end(),[](const auto &a,const auto &b){return a.second.second<b.second.second;});


    for(auto i : edge_list){
        if(find(i.first)==find(i.second.first)) continue;
        else {Union(i.first,i.second.first);tree[i.first].push_back(i.second.first);};
    }

    return tree;
}

vector<vector<int>> prims(vector<vector<pair<int,int>>> &g){
    memset(parent,-1,sizeof(parent));memset(rnk,0,sizeof(rnk));
    for(int i=0;i<(int)g.size();i++)parent[i]=i;
    vector<vector<int>> tree((int)g.size());
    priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,cmp> pq;
    for(auto i : g[0])pq.push({0,i});
    int no_of_edges=0;
    while(!pq.empty()&&no_of_edges<(int)g.size()-1){
        auto i = pq.top();pq.pop();
        if(find(i.first)==find(i.second.first)) continue;
        Union(i.first,i.second.first);
        tree[i.first].push_back(i.second.first);
        // cout<<"added edge "<<i.first<<"<-->"<<i.second.first<<"\n";
        no_of_edges++;
        for(auto it : g[i.second.first]){
            pq.push({i.second.first,it});
        }
    }
    return tree;
}

void dfs(vector<vector<pair<int,int>>> &g,int index,vector<bool> &visited,vector<int> &tsort){
    visited[index]=true;
    for(auto i : g[index]){
        if(!visited[i.first]){
            dfs(g,i.first,visited,tsort);
        }
    }
    tsort.push_back(index);
}

vector<int> topological_sort(vector<vector<pair<int,int>>> &g){
    vector<int>tsort;
    vector<bool> visited((int)g.size(),false);
    for(int i=0;i<(int)g.size();i++){
        if(!visited[i]){
            dfs(g,i,visited,tsort);
        }
    }
    reverse(tsort.begin(),tsort.end());
    return tsort;
}

int main(){
    cout<<"Enter the no. of nodes in graph ";
    int n;cin>>n;
    vector<vector<pair<int,int>>> graph(n); 
    cout<<"Enter the no of edges in graph ";
    int m;cin>>m;
    cout<<"Enter the to,from and weight of edge ";
    for(int i=0,from,to,weight;i<m;i++){
        cin>>from>>to>>weight;
        graph[from].push_back({to,weight});
    }
    int start;
    cout<<"Enter the start vertex for distance calculation ";
    cin>>start;
    vector<int> dist=dijkstra(graph,start);
    // for (auto i : dist) cout<<i<<" ";cout<<"\n";
    vector<vector<int>> dis=floyd_warshal(graph);
    // for(auto i : dis){for(auto j : i) if(j==INF)cout<<"INF ";else cout<<j<<" ";cout<<"\n";}
    vector<int> dt=bellman_ford(graph,start);
    // for (auto i : dt) cout<<i<<" ";cout<<"\n";
    vector<vector<int>> mstk=kruskals(graph);
    // for(int i=0;i<mstk.size();i++){
    //     cout<<i<<" ------->";
    //     for(auto it : mstk[i]) cout<<it<<" ";cout<<"\n";
    // }
    vector<vector<int>> mstp=prims(graph);
    // for(int i=0;i<mstp.size();i++){
    //     cout<<i<<" ------->";
    //     for(auto it : mstp[i]) cout<<it<<" ";cout<<"\n";
    // }
    vector<int> ts=topological_sort(graph);
    for(auto i : ts) cout<<i<<" ";
    return 0;
}