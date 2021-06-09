#include<vector>
#include<set>
using namespace std;

const int inf = 1e8;


class Bridges{
    private :
    int n;    
    vector<vector<int>> g;

    public :
    Bridges(vector<vector<int>> &g){
        this->g = g;
        n = (int)g.size();
    }


    vector<int> min_reachable,discovery;    //ones which are not discovered yet will have discovery = inf
    set<pair<int,int>> b;
    int timer;

    void find_bridges(){
        min_reachable.resize(n);
        discovery.resize(n,inf);
        for(int i=0;i<n;i++)
            if(discovery[i] == inf)
                timer = 0 ,bridges(i,-1);
    }

    private :
    void bridges(int curr,int parent){
        
        min_reachable[curr] = discovery[curr] = timer++;

        for(int i : g[curr]){
            if(discovery[i] == inf){    //not discovered yet
                bridges(i,curr);
                min_reachable[curr] = min(min_reachable[curr],min_reachable[i]);
                if(min_reachable[i] > discovery[curr]){
                    b.emplace(curr,i);
                }
            }
            else if(i != parent){       //just don't consider parent while evaluating 
                min_reachable[curr] = min(min_reachable[curr],discovery[i]);
            }
        }

        return;
    }
};
