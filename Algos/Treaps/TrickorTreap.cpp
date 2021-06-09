// This involves quering and use of parent pointers
#include<bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)

class Treap{

	struct Node{
		int priority;
		long long original;	//this stores the original value of the index it corresponds to.
		long long val;
		int size;
		Node *left , *right;
		Node *parent;
		Node(int priority,long long value) : priority(priority) ,original(value),size(1) ,val(value), left(nullptr) , right(nullptr),parent(nullptr) {}
	};

	public :

	map<int,Node*> mp;

	int nodes;

	Node * root;

	Treap() : root(nullptr) , nodes(1) {}

	//identity element (for sum it is 0 , for product it is 1 for max INT_MIN etc)
	long long ID = 0;		

	long long  operate(long long a,long long b){	//How two elements are combined
		return a + b;
	}

	int size(Node * ptr){
		return ptr == nullptr ? 0 : ptr->size;
	}

	long long combine(Node *l,Node *r,int v){
		long long a = (l == nullptr ? ID : l->val);
		long long b = (r == nullptr ? ID : r->val);
		return operate(operate(a,b),v);
	}

	/*
	Splits the tree/subtree rooted at curr into two subtrees with left one has sz no. of elements
	and all the other elements belong to the second tree.
	*/
	pair<Node*,Node*> split(Node * curr,int sz){
		if(sz == 0){
			//all the elements go to the right part
			if(curr != nullptr)
				curr->parent = nullptr;
			return pair<Node*,Node*> {nullptr,curr};
		}	
		
		if(curr == nullptr)
			return pair<Node*,Node*> {nullptr,nullptr};

		//this means we need some elements from the curr->right subtree
		if(size(curr->left) + 1 <= sz){	
			pair<Node*,Node*> p = split(curr->right,sz-(size(curr->left) + 1));
			curr->right = p.first;
			curr->size = size(curr->left) + size(curr->right) + 1;
			curr->val = combine(curr->left,curr->right,curr->original);
			if(curr->left != nullptr)
				curr->left->parent = curr;
			if(curr->right != nullptr)
				curr->right->parent = curr;
			curr->parent = nullptr;
			return pair<Node*,Node*> {curr,p.second};
		} 
		else{
			pair<Node*,Node*> p = split(curr->left,sz);
			curr->left = p.second;
			curr->size = size(curr->left) + size(curr->right) + 1;
			curr->val = combine(curr->left,curr->right,curr->original);
			if(curr->left != nullptr)
				curr->left->parent = curr;
			if(curr->right != nullptr)
				curr->right->parent = curr;
			curr->parent = nullptr;
			return pair<Node*,Node*> {p.first,curr};
		}
	}

	/*
	Concatenates two segments for example [0,1,2] is concatenated with [5,3,5]
	results in the tree corresponding to segment [0,1,2,5,3,5]
	*/

	Node * merge(Node * first,Node * second){
		if(first == nullptr) {if(second!=nullptr)second->parent = nullptr;return second;}
		if(second == nullptr) {if(first != nullptr)first->parent = nullptr;return first;}

		//first will stay at top so combine the first->right with second
		if(first->priority > second->priority){
			first->right = merge(first->right,second);
			if(first->right != nullptr)
				first->right->parent = first;
			if(first->left != nullptr)
				first->left->parent = first;
			first->size = size(first->left) + size(first->right) + 1;
			first->val = combine(first->left,first->right,first->original);
			return first;
		}
		else {
			second->left = merge(first,second->left);
			second->size = size(second->left) + size(second->right) + 1;
			second->val = combine(second->left,second->right,second->original);
			if(second->right != nullptr)
				second->right->parent = second;
			if(second->left != nullptr)
				second->left->parent = second;
			return second;
		}
	}

	void add(long long val){
		int priority = uid(0,1000000000);
		Node * new_node = new Node(priority,val);
		mp[nodes] = new_node;
		nodes++;
		return;
	}

	bool unite(int x,int y){
		Node *a = mp[x];
		Node *b = mp[y];
		while(a->parent != nullptr) a = a->parent;
		while(b->parent != nullptr) b = b->parent;
		if(a == b) return false;	//they are already in the same tree

		merge(a,b);
		return true;
	}

	bool seperate(int nd,int sz){
		Node *a = mp[nd];
		while(a->parent != nullptr) a = a->parent;
		if(a->size > sz){
			split(a,sz);
			return true;
		}
		else{
			return false;
		}
	}

	long long get_sum(int nd){
		Node *a = mp[nd];
		while(a->parent != nullptr) a = a->parent;
		return a->val;
	}

};

int main(){

	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);

	int q;
	cin>>q;

	Treap T;
	int nodes = 0;
	int id = 0;
	map<int,int> node_id;
	while(q--){
		id++;
		int type;
		cin>>type;
		if(type == 1){
			nodes++;
			node_id[id] = nodes;
			long long val;cin>>val;
			T.add(val);
		}
		else if(type == 2){
			int x,y;
			cin>>x>>y;
			x = node_id[x],y = node_id[y];
			T.unite(x,y);
		}
		else if(type == 3){
			int nd,sz;
			cin>>nd>>sz;
			nd = node_id[nd];
			T.seperate(nd,sz);
		}
		else{
			int nd;
			cin>>nd;
			nd = node_id[nd];
			cout<<T.get_sum(nd)<<"\n";
		}
	}

	return 0;
}
