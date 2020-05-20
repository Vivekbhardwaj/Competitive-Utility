#include<bits/stdc++.h>
using namespace std;
#define int long long




template<typename T>
class Seg{
    public : 
        T ID=0;             
        vector<T> tree;
        int n;
        T combine(T x,T y){
            return x+y;        
        }
        Seg(int _n){
            n=_n;
            tree.resize(2*n,ID);
        }

        void update(int pos,int value){
            pos+=n;tree[pos]=value;pos/=2;
            while(pos){
                tree[pos]=combine(tree[2*pos],tree[2*pos+1]);
                pos/=2;
            }
        }
        T query(int l,int r){
            T left_answer=ID;T right_answer=ID;
            l+=n,r+=n;
            while(l<=r){
                if(l&1) {left_answer=combine(left_answer,tree[l]);l++;}
                if(r%2==0){right_answer=combine(right_answer,tree[r]);r--;}
                l>>=1;r>>=1;
            }
            return combine(left_answer,right_answer);
        }
};


template<typename T>
class Seg2{
    private :   
        vector<T> tree;
        int n;
        int m;
    public : 
        Seg2(int _n,int _m){
            n=_n;
            m=_m;
            for(int i=0;i<2*n;i++){
                tree.push_back(Seg<int>(m));
            }
        }

        void update(int pos_row,int pos_col,int value){
            pos_row+=n;tree[pos_row].update(pos_col,value);pos_row/=2;
            while(pos_row){
                tree[pos_row].update(pos_col,tree[2*pos_row].query(pos_col,pos_col)+tree[2*pos_row+1].query(pos_col,pos_col));
                pos_row/=2;
            }
        }
        int query(int rl,int rr,int cl,int cr){
            int left_answer=0,right_answer=0;
            rl+=n,rr+=n;
            while(rl<=rr){
                if(rl&1) {left_answer=left_answer+tree[rl].query(cl,cr);rl++;}
                if(rr%2==0){right_answer=right_answer+tree[rr].query(cl,cr);rr--;}
                rl>>=1;rr>>=1;
            }
            return left_answer+right_answer;
        }
};





int32_t main(){
    int n,q;cin>>n>>q;
    vector<string>s(n);

    for(auto &i : s) cin>>i;

    Seg2<Seg<int>> s_tree(n,n);

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(s[i][j]=='*') s_tree.update(i,j,1);
        }
    }

    while(q--){
        int rl,cl,rr,cr;cin>>rl>>cl>>rr>>cr;rr--;rl--;cl--;cr--;
        cout<<s_tree.query(rl,rr,cl,cr)<<"\n";
    }

    return 0;
}
