#include<bits/stdc++.h>
using namespace std;

vector<int> depth;
vector<int> euler;

void dfs(int curr,int parent,vector<vector<int>> &tree){
    euler.push_back(curr);
    depth[curr]=parent!=-1?depth[parent]+1:0;
    for(auto i : tree[curr]){
        if(i==parent) continue;
        dfs(i,curr,tree);
        euler.push_back(curr);
    }
}

template<class T>
class segment_tree{
    private : 
    vector<T> v;
    int size;
    T identity_element;

    T comb(T a,T b){
        //Define the combination function here
        if (a==-1) return b;
        else if(b==-1) return a;
        else return depth[a]<depth[b]?a:b;
    }

    public :
    segment_tree(int n,T element){
        size=n;
        identity_element=element;
        v.resize(2*size);
        for(auto &i : v) i=-1;
    }

    void update(int position,T value){
        position+=size;
        while(position!=0){
            v[position]=comb(v[position],value);
            position/=2;
        }
    }

    T query(int l,int r){
        l+=size;r+=size;
        T ans=-1;
        while(l<=r){
            if(l&1) {ans=comb(v[l],ans);l+=1;}
            if((r&1)==0) {ans=comb(v[r],ans);r-=1;}
            l/=2;r/=2;
        }
        return ans;
    }

    void print_tree(){
        cout<<"size is "<<size<<"\n";
        for(auto i : v) cout<<i<<" ";
    }

};





int main(){
    int n;cin>>n;
    vector<vector<int>>v(n);
    depth.resize(n);
    for(int i=0,x,y;i<n-1;i++){
        cin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    depth[0]=0;
    dfs(0,-1,v);
    segment_tree<int> s(euler.size(),INT_MAX);
    for(auto i : euler) cout<<i<<" ";cout<<endl;
    for(auto i : euler) cout<<depth[i]<<" ";cout<<endl;
    vector<int> first_occurence(n,-1);
    for(int i=0;i<euler.size();i++){
        s.update(i,euler[i]);
        if(first_occurence[euler[i]]==-1)first_occurence[euler[i]]=i;
    }
    s.print_tree();
    int q;cin>>q;
    while(q--){
        int x,y;cin>>x>>y;
        if(first_occurence[x]>first_occurence[y]) swap(x,y);
        cout<<s.query(first_occurence[x],first_occurence[y])<<"\n";
    }
}