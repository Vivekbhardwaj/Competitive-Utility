//Solution to Z.Frog Jump 3 | AtCoder Educational DP Contest

#include<bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN=1e6+5;     //the max value of our x that is to be substituted in the line to get y

//index i of the segment tree stores the line which corresponds to the dominating line in atleast one half of that segment
//dominating line maybe the line giving max value or the min value for a particular x
//this tree gurantees that atleast one node on path from top to the leaf will give the best ans for x
pair<int,int> li_ciao_tree[4*MAXN];     //pair corresponds to {slope of line , y-intercept of line}

void init_tree(){
    // set all the nodes such that they yield inf if case you need to query for min afterwards 
    //otherwise set them to -inf
    const int INF=1e18+47;
    for(int i=0;i<4*MAXN;i++){
        li_ciao_tree[i]={0,INF};
    }
}

//y value for a given x
int f(int x,pair<int,int> line){
    return line.first*x+line.second;
}

inline bool intersection_occurs(int curr_f_l,int curr_f_mid,int new_f_l,int new_f_mid){
    
    if(curr_f_l<new_f_l&&curr_f_mid<new_f_mid) return false;
    else if(curr_f_l>new_f_l&&curr_f_mid>new_f_mid) return false;
    else return true;
    
}

pair<int,int> dominating_line(pair<int,int> line1,pair<int,int> line2,int dummy_x){

    //because we want the value of our linear function to be minimum , to make it maximum just reverse the condition
    if(line1.first*dummy_x+line1.second<line2.first*dummy_x+line2.second) return line1;
    else return line2;
}

void insert(pair<int,int> new_line,int l=0,int r=MAXN,int curr=1){

    if(l==r){
        li_ciao_tree[curr]=dominating_line(li_ciao_tree[curr],new_line,l);
        return;
    }

    int mid=(l+r)/2;
    int curr_f_l=f(l,li_ciao_tree[curr]);
    int curr_f_mid=f(mid,li_ciao_tree[curr]);

    int new_f_l=f(l,new_line);
    int new_f_mid=f(mid,new_line);

    //in the current segment we will store the line which is dominating in one of its complete part (maybe right or left)
    if(new_f_mid<=curr_f_mid) swap(li_ciao_tree[curr],new_line);

    //and take the other line and recusively call using it further, because part of this line will be lower and part of this line will be upper
    if(intersection_occurs(curr_f_l,curr_f_mid,new_f_l,new_f_mid)){
        //there is an intersection in the left part of current node range
        //i.e. there is change of dominance in the left range which in other words means that the right part 
        //of current range has a single dominating line (we set the curr index with it )
        //recurse on the left segment
        
        insert(new_line,l,mid,2*curr);
    }
    else{
        
        insert(new_line,mid+1,r,2*curr+1);
    }

    return;

}


int query(int x,int l=0,int r=MAXN,int curr=1){
    if(l==r) return f(x,li_ciao_tree[curr]);
    int mid=(l+r)/2;
    int ans=f(x,li_ciao_tree[curr]);
    //cout<<"("<<l<<","<<r<<") -->"<<ans<<"\n";
    if(x<=mid){
        return min(ans,query(x,l,mid,2*curr));
    }
    else {
        return min(ans,query(x,mid+1,r,2*curr+1));
    }
}
