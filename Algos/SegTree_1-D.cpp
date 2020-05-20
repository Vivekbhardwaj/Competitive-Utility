#include<bits/stdc++.h>
using namespace std;

template<class T> struct Seg {
    const T ID = 0; // comb(ID,b) must equal b
    T comb(T a, T b) { return a+b; }        //Change comb as per need
    int n; vector<T> seg;
    Seg(int _n) { n = _n; seg.resize(2*n); }
    void pull(int p) { seg[p] = comb(seg[2*p],seg[2*p+1]); }
    void upd(int p, T value) { // set value at position p
        seg[p += n] = value;
        for (p /= 2; p; p /= 2) pull(p);
    }
    T query(int l, int r) { // sum on interval [l, r]
        T ra = ID, rb = ID;
        for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
        if (l&1) ra = comb(ra,seg[l++]);
        if (r&1) rb = comb(seg[--r],rb);
        }
        return comb(ra,rb);
    }
};

int main(){
    int n;cin>>n;
    vector<int> v(n);
    Seg<int> seg_tree(n);
    for(int i=0;i<n;i++){
        cin>>v[i];
        seg_tree.upd(i,v[i]);
    }
    int query;cin>>query;
    while(query--){
        int l,r;
        cin>>l>>r;
        cout<<seg_tree.query(l,r)<<"\n";
    }
}