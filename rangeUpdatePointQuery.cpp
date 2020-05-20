//Range Update with Point query

#include<bits/stdc++.h>
using namespace std;
#define int long long

template<typename T>
class Seg{
    private :

        T ID=0;             //comb(x,ID)=x;
        vector<T> tree;
        int n;
        T combine(T x,T y){
            return x+y;         //combination function
        }

    public : 

        Seg(int _n){
            n=_n;
            tree.resize(2*n,ID);
        }

        void update(int l,int r,int value){
            l+=n,r+=n;
            while(l<=r){
                if(l&1) {tree[l]+=value;l++;}
                if(r%2==0) {tree[r]+=value;r--;}
                l>>=1;r>>=1;
            }
        }
        T query(int pos){
            int ans=ID;
            pos+=n;
            while(pos){
                ans+=tree[pos];
                pos>>=1;
            }
            return ans;
        }

};

int32_t main(){
    int n,q;cin>>n>>q;
    vector<int> v(n);
    Seg<int> segment_tree(n);
    for(int i=0;i<n;i++){
        cin>>v[i];
    }
    while(q--){
        int type;cin>>type;
        if(type==2){
            int pos;cin>>pos;pos--;
            cout<<v[pos]+segment_tree.query(pos)<<"\n";
        }
        else{
            int l,r,value;
            cin>>l>>r>>value;l--;r--;
            segment_tree.update(l,r,value);
        }
    }

    return 0;
}
