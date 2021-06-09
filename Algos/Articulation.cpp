#include<vector>
#include<set>
using namespace std;

const int inf = 1e8;

class ArticulationPoints{
    private :
    int n;    
    vector<vector<int>> g;

    public :
    ArticulationPoints(vector<vector<int>> &g){
        this->g = g;
        n = (int)g.size();
    }


    vector<int> min_reachable,discovery,seperate_children;    //ones which are not discovered yet will have discovery = inf
    set<int> points;
    int timer;

    void find_articulation(){
        min_reachable.resize(n);
        discovery.resize(n,inf);
        seperate_children.resize(n,0);
        for(int i=0;i<n;i++)
            if(discovery[i] == inf){
                timer = 0 ,articulation(i);
                points.insert(i);
                if(seperate_children[i] < 2){  //then it isn't a articulation point
                    points.erase(i);
                }
            }
    }

    private :
    void articulation(int curr){
        
        min_reachable[curr] = discovery[curr] = timer++;

        for(int i : g[curr]){
            if(discovery[i] == inf){    //not discovered yet
                seperate_children[curr]++;
                articulation(i);
                min_reachable[curr] = min(min_reachable[curr],min_reachable[i]);
                if(min_reachable[i] >= discovery[curr]){
                    points.insert(curr);
                }
            }
            else {    
                min_reachable[curr] = min(min_reachable[curr],discovery[i]);
            }
        }

        return;
    }
};