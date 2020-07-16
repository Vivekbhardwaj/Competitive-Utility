#include<bits/stdc++.h>
using namespace std;
#define int long long
#define FAST ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);

struct Node{
    Node * arr[2];
    Node(){
        arr[0]=nullptr;
        arr[1]=nullptr;
    }
    bool isEndOfWord=false;
};
 
void insert(Node * Root,int to_insert){
    Node * curr=Root;
    for(int i=31;i>=0;i--){
        if(to_insert&(1<<i)){
            if(curr->arr[1]==nullptr)curr->arr[1]=new Node();
            curr=curr->arr[1];
        }
        else{
            if(curr->arr[0]==nullptr)curr->arr[0]=new Node();
            curr=curr->arr[0];
        }
    }
    curr->isEndOfWord=true;
    return;
}
 
unsigned int mx(Node * Root,unsigned int complementary_to){
    Node * curr=Root;
    unsigned int ans=0;
    for(int i=31;i>=0;i--){
        if(complementary_to&(1<<i)){
            if(curr->arr[0]==nullptr) curr=curr->arr[1];
            else{ans|=(1<<i);curr=curr->arr[0];}
        }
        else{
            if(curr->arr[1]==nullptr) {curr=curr->arr[0];}
            else{ans|=(1<<i);curr=curr->arr[1];}
        }
    }
    return ans;
}

bool isEmpty(Node* root) 
{ 
    for (int i = 0; i < 2; i++) 
        if (root->arr[i]!=nullptr) 
            return false; 
    return true; 
} 


Node* remove(Node* root, int key, int depth = 31) 
{ 
    if (!root) 
        return nullptr; 
  
    if (depth == -1) { 
  
        if (root->isEndOfWord) 
            root->isEndOfWord = false; 
  
        if (isEmpty(root)) { 
            //cout<<"deleting";
            delete (root); 
            root = nullptr; 
        } 
  
        return root; 
    } 
  
    int index = ((1ll<<depth)&key)?1:0;
    // cout<<index<<"\n"; 
    root->arr[index] = remove(root->arr[index], key, depth - 1); 


    if (isEmpty(root) && root->isEndOfWord == false) { 
        delete (root); 
        root = nullptr; 
    } 
  
    return root; 
} 

int32_t main(){
    FAST

    int q;cin>>q;
    map<int,int> mp;
    Node *root=new Node();
    mp[0]++;insert(root,0);
    while(q--){
        char type;
        cin>>type;
        if(type=='+'){
            int to_insert;cin>>to_insert;
            mp[to_insert]++;
            if(mp[to_insert]==1)
                insert(root,to_insert);
        }
        else if(type=='-'){
            int to_delete;cin>>to_delete;
            mp[to_delete]--;
            if(mp[to_delete]==0){
                cout<<"calling delete for "<<to_delete<<"\n";
                root= remove(root,to_delete);
            }
        }
        else{
            int mx_to;
            cin>>mx_to;
            cout<<mx(root,mx_to)<<"\n";
        }
    }
    

    return 0;
}
