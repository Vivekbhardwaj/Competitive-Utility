#include<bits/stdc++.h>
using namespace std;

typedef struct trieNode{
    trieNode * Data[26];
    bool end;
};


trieNode *root;

void insert_string(string &s){
    trieNode *curr=root;
    for(auto i : s){
        if(curr->Data[i-'A']==nullptr){
            curr->Data[i-'A']=new trieNode;
        }
        curr=curr->Data[i-'A'];
    }
    curr->end=true;
}

bool find(string &s){
    trieNode * curr=root;
    for(auto i : s){
        if(curr->Data[i-'A']!=nullptr) curr=curr->Data[i-'A'];
        else return false;
    }
    if(curr->end==true) return true;
    return false;
}

int main(){
    int t;cin>>t;
    while(t--){
        root=new trieNode;
        int n;cin>>n;
        for(int i=0;i<n;i++){
            string s;cin>>s;
            insert_string(s);
        }
        int q;cin>>q;
        while(q--){
            string s;cin>>s;
            cout<<(find(s)?"Found\n":"Not found\n");
        }
    }
}