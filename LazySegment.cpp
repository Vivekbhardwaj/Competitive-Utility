//For sum query while adding the value of lazy[] to the node we add it after multiplting 
//it with the interval length of that node of tree

#include<bits/stdc++.h>
using namespace std;
#define int long long 

const int MAXN=4e5+5;
int seg_tree_min_range_query[4*MAXN];
int lazy_min_range_query[4*MAXN];
int n;

void propogate_to_child_min_query(int curr,int value){
    seg_tree_min_range_query[curr]+=value;
    lazy_min_range_query[2*curr]+=value;
    lazy_min_range_query[2*curr+1]+=value;
    lazy_min_range_query[curr]=0;
}

void update_min(int ul,int ur,int value,int curr=1,int l=0,int r=n-1){

    if(r<l) return ;
    if(ul>r||ur<l) return ;

    if(lazy_min_range_query[curr]){
        propogate_to_child_min_query(curr,lazy_min_range_query[curr]);
    }

    if(l>=ul&&r<=ur){
        seg_tree_min_range_query[curr]+=value;
        lazy_min_range_query[2*curr]+=value;
        lazy_min_range_query[2*curr+1]+=value;
        return;
    }

    int mid=(l+r)/2;
    update_min(ul,ur,value,2*curr,l,mid);
    update_min(ul,ur,value,2*curr+1,mid+1,r);

    seg_tree_min_range_query[curr]=min(seg_tree_min_range_query[2*curr],seg_tree_min_range_query[2*curr+1]);
}


int query_min(int ql,int qr,int curr=1,int l=0,int r=n-1){
    if(r<l) return INT_MAX;
    if(ql>r||qr<l) return INT_MAX;

    if(lazy_min_range_query[curr]){
        propogate_to_child_min_query(curr,lazy_min_range_query[curr]);
    }

    if(ql<=l&&qr>=r) {
        return seg_tree_min_range_query[curr];
    }
    return min(query_min(ql,qr,2*curr,l,(l+r)/2),query_min(ql,qr,2*curr+1,(l+r)/2+1,r));
}





int seg_tree_max_range_query[4*MAXN];
int lazy_max_range_query[4*MAXN];


void propogate_to_child_max_query(int curr,int value){
    seg_tree_max_range_query[curr]+=value;
    lazy_max_range_query[2*curr]+=value;
    lazy_max_range_query[2*curr+1]+=value;
    lazy_max_range_query[curr]=0;
}

void update_max(int ul,int ur,int value,int curr=1,int l=0,int r=n-1){

    if(r<l) return ;
    if(ul>r||ur<l) return ;

    if(lazy_max_range_query[curr]){
        propogate_to_child_max_query(curr,lazy_max_range_query[curr]);
    }

    if(l>=ul&&r<=ur){
        seg_tree_max_range_query[curr]+=value;
        lazy_max_range_query[2*curr]+=value;
        lazy_max_range_query[2*curr+1]+=value;
        return;
    }

    int mid=(l+r)/2;
    update_max(ul,ur,value,2*curr,l,mid);
    update_max(ul,ur,value,2*curr+1,mid+1,r);

    seg_tree_max_range_query[curr]=max(seg_tree_max_range_query[2*curr],seg_tree_max_range_query[2*curr+1]);
}


int query_max(int ql,int qr,int curr=1,int l=0,int r=n-1){
    if(r<l) return INT_MIN;
    if(ql>r||qr<l) return INT_MIN;

    if(lazy_max_range_query[curr]){
        propogate_to_child_max_query(curr,lazy_max_range_query[curr]);
    }

    if(ql<=l&&qr>=r) {
        return seg_tree_max_range_query[curr];
    }
    return max(query_max(ql,qr,2*curr,l,(l+r)/2),query_max(ql,qr,2*curr+1,(l+r)/2+1,r));
}





int32_t main(){
    int n,m;cin>>n>>m;
    vector<int> v(n);
    for(auto &i : v) cin>>i;
    for(int i=1;i<n;i++) v[i]+=v[i-1];
    for(int i=0;i<n;i++){
        update_max(i,i,v[i]);
        update_min(i,i,v[i]);
    }
    while(1){
        int x,y;
        cin>>x>>y;
        cout<<query_max(x,y)<<"\n";
        cout<<query_min(x,y)<<"\n";
    }
    return 0;
}
