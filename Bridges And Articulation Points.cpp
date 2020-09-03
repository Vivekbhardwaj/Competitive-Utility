#include<bits/stdc++.h>
using namespace std;

class cuts{

    vector<vector<int>> g;
    vector<int> discovery , low ,children;
    vector<bool> visited;
    int n;

    
    void articulation(int curr,int parent){

        visited[curr] = true;

        static int timer = 0;

        discovery[curr] = low[curr] = timer++;


        for(int i : g[curr]){

            if(i == parent) continue;

            if(!visited[i]){
                children[curr]++;

                articulation(i,curr);
                low[curr] = min(low[curr],low[i]);

                if(low[i] > discovery[curr]) {
                    articulation_points.insert(curr);
                    bridges.emplace(curr,i);
                }  

                if(low[i] == discovery[curr])  
                    articulation_points.insert(curr);

            }
            else{
                low[curr] = min(low[curr],discovery[i]);        //very important condition
            }
        }
    }
    

    public : 

    set<int> articulation_points;
    set<pair<int,int>> bridges;

    cuts(vector<vector<int>> &g){
        this -> g = g;
        this -> n = g.size();
        discovery.resize(n);
        low.resize(n);
        visited.resize(n,false);
        children.assign(n,0);

        for(int i=0;i<n;i++)

            if(!visited[i]){
                articulation(i,i);
                //if it was unnecessarily added remove it ( it would have been added because of some wierd cycle like 1-->2-->3-->1) in this case
                //i is not a articulation point
                if(articulation_points.find(i) != articulation_points.end()) articulation_points.erase(i);
                if(children[i]>1) 
                    // root node if cut vertex only if it has two independent children that were visited independently         
                    articulation_points.insert(i);  
            }

    }

};

//Use :

int main(){
    int n;
    cin>>n;

    vector<vector<int>> graph(n);

    int m;
    cin>>m;

    for(int i=0 ; i<m ; i++){
        int u,v;
        cin>>u>>v;
        u--;v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    cuts c(graph);

    for(auto i : c.articulation_points)
        cout<<i<<" ";
    cout<<"\n";

    for(auto j : c.bridges)
        cout<<j.first<<" "<<j.second<<" | ";

    cout<<"\n";

}


/** Refrence : https://codeforces.com/blog/entry/71146 
 * https://www.quora.com/q/competitiveprogramming2/Cut-Vertex-Articulation-point
 **/
