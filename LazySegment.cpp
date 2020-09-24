#include<bits/stdc++.h>
using namespace std;
#define int long long

const int inf = 1e18;
const int MOD = 1e9+7;

class SegTree{

    private : 
    vector<pair<int,int>> seg;
    vector<int> lazy;
    int n;

    public : 

    SegTree(int n,vector<int> &v){
        this->n = n;
        this->seg.resize(8*n);
        this->lazy.resize(8*n);
        build(0,n-1,1,v);

    }

    inline pair<int,int> combine(pair<int,int> l,pair<int,int> r){
        return l.first < r.first ?  l : r;
    }

    void build(int l,int r,int curr,vector<int> &v){
        if(r<l) return;
        if(l == r){
            seg[curr].first = v[l];
            seg[curr].second = l;
            return;
        }
        int mid = (l+r)/2;
        build(l,mid,2*curr,v);
        build(mid+1,r,2*curr+1,v);
        seg[curr] = combine(seg[2*curr],seg[2*curr + 1]);
    }

    void propogate_down(int curr){
        seg[curr].first+=lazy[curr];
        lazy[2*curr]+=lazy[curr];
        lazy[2*curr + 1]+= lazy[curr];
        lazy[curr] = 0;
        return;
    }

    void update(int ul,int ur,int val,int l,int r,int curr=1){
        if(r<l) return;

        if(lazy[curr]!=0) propogate_down(curr);

        if(r<ul || l>ur) return;

        if(l>=ul && r<=ur){
            seg[curr].first+=val;
            lazy[2*curr]+=val; lazy[2*curr+1]+=val;
            return;
        }

        int mid = (l+r)/2;
        update(ul,ur,val,l,mid,2*curr);
        update(ul,ur,val,mid+1,r,2*curr+1);
        seg[curr] = combine(seg[2*curr],seg[2*curr +1]);
        return;
    }

    pair<int,int> query(int ql,int qr,int l,int r,int curr=1){

        if(r<l) return {2*inf,2*inf};

        if(lazy[curr]) propogate_down(curr);

        if(r<ql || l>qr) return {2*inf,2*inf};

        if(l>=ql&&r<=qr){
            return seg[curr];
        }
        int mid = (l+r)/2;
        return combine(query(ql,qr,l,mid,2*curr),query(ql,qr,mid+1,r,2*curr+1));

    }

};
