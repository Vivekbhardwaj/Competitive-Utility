#include<bits/stdc++.h>
using namespace std;

struct Node{
    Node * arr[2];
    vector<int> indices;        //store all the indices that will be encountered while goint to leaf through this node
    Node(){
        arr[0] = arr[1] = nullptr;
    }
};

//type 0 : add an element to the end
void insert(Node * root,int num,int idx){
    Node * curr = root;
    for(int i = 23 ; i>=0 ; i--){
        if(curr -> arr[(num>>i)&1] == nullptr) curr -> arr[(num>>i)&1] = new Node();
        curr = curr -> arr[(num>>i)&1];
        (curr ->indices).push_back(idx);
    }
    return;
};

//type 2 : Delete last element
Node * del(Node * root,int idx,int curr_bit = 23){
    if(curr_bit == -1) return nullptr;

    if(root -> arr[0] != nullptr && (root->arr[0]->indices).back() == idx){
        (root ->arr[0]-> indices).pop_back();
        root -> arr[0] = del(root -> arr[0],idx,curr_bit-1);
    }
    else {
        (root ->arr[1]-> indices).pop_back();
        root -> arr[1] = del(root -> arr[1],idx,curr_bit-1);
    }

    if(root -> arr[0] == nullptr && root -> arr[1] == nullptr){
        if((root -> indices).size()==0){
            delete root;
            return nullptr;
        }
        else{
            return root;
        }
    }
    else{
        return root;
    }

    return root;
}

//type 1 : Maximize xor with num on interval l to r
int findMax(Node * root,int num,int l,int r){
    int ans = 0;
    for(int i = 23 ; i>=0 ; i--){
        int curr_bit = (num>>i)&1;
        
        if(root -> arr[curr_bit^1] == nullptr)  root = root ->arr[curr_bit];
        else{
            bool ok = (upper_bound((root -> arr[curr_bit^1] -> indices).begin() , (root ->arr[curr_bit^1] ->indices).end(), r)
                        -lower_bound((root -> arr[curr_bit^1] -> indices).begin() , (root ->arr[curr_bit^1] ->indices).end(), l)
                        > 0) ;
            
            if(ok) ans|=(1<<i) , root = root -> arr[curr_bit^1];
            else root = root -> arr[curr_bit];

        }
        
    }

    return ans;
}

//type 3 :  On the interval L..R, count the number of integers less than or equal to x.
int findLessThan(Node * root,int num , int l, int r){
    int count = 0;
    for(int i = 23 ; i>=0 ; i--){
        if((num >> i)&1){
            if(root -> arr[1] == nullptr) {
                count += upper_bound((root -> arr[0] -> indices).begin() , (root ->arr[0] ->indices).end(), r)
                      -lower_bound((root -> arr[0] -> indices).begin() , (root ->arr[0] ->indices).end(), l);
                return count;
            }
            else if(root -> arr[0] == nullptr){
                root = root -> arr[1];
            }
            else{
                count += upper_bound((root -> arr[0] -> indices).begin() , (root ->arr[0] ->indices).end(), r)
                    -lower_bound((root -> arr[0] -> indices).begin() , (root ->arr[0] ->indices).end(), l);

                root = root -> arr[1];
            }
        }
        else{
            if(root ->arr[0] == nullptr) return count;
            else root = root -> arr[0];
        }
    }

    count+=upper_bound((root -> indices).begin() , (root ->indices).end(), r)
           -lower_bound((root -> indices).begin() , (root ->indices).end(), l);

    return count;
}


//type 4 : On the interval L..R, find the kth smallest integer (kth order statistic).
int kthOrderStastics(Node * root,int l,int r,int k){
    int ans = 0;
    for(int i=23 ; i>=0 ; i--){
        int cnt_0 = 0,cnt_1 = 0;
        if(root -> arr[0] != nullptr) 
                    cnt_0 = upper_bound((root -> arr[0] -> indices).begin() , (root ->arr[0] ->indices).end(), r)
                    -lower_bound((root -> arr[0] -> indices).begin() , (root ->arr[0] ->indices).end(), l);

        if(root -> arr[1] != nullptr)
                    cnt_1 = upper_bound((root -> arr[1] -> indices).begin() , (root ->arr[1] ->indices).end(), r)
                    -lower_bound((root -> arr[1] -> indices).begin() , (root ->arr[1] ->indices).end(), l);

        if(cnt_0 >= k) root = root -> arr[0];
        else {
            k-=cnt_0;
            ans|=(1<<i);
            root = root -> arr[1];
        }
    }
    return ans;
}




int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int q;cin>>q;
    Node * root = new Node();
    int elements = 0;
    while(q--){
        int type;
        cin>>type;
        if(type == 0){
            int x;cin>>x;
            if(root == nullptr) root = new Node();
            elements++;
            insert(root,x,elements);
        }
        else if(type == 1){
            int l , r , x;
            cin>>l>>r>>x;
            cout<<(x^findMax(root,x,l,r))<<"\n";
        }
        else if(type == 2){
            int k;cin>>k;
            while(k--){
                root = del(root,elements);
                elements--;
            }
        }
        else if(type == 3){
            int l, r, x;
            cin>>l>>r>>x;
            if(elements == 0) cout<<0<<"\n";
            else cout<<findLessThan(root,x,l,r)<<"\n";
        }
        else{
            int l,r,k;
            cin>>l>>r>>k;
            cout<<kthOrderStastics(root,l,r,k)<<"\n";
        }
    }


    return 0;
}
