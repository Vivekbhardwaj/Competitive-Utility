//This involves slicing the end of the array and adding it to the front of the array
#include<bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)

class Treap{

	struct Node{
		int priority;
		int original;	//this stores the original value of the index it corresponds to.
		int size;
		Node *left , *right;
		Node(int priority,int value) : priority(priority) ,original(value),size(1) , left(nullptr) , right(nullptr) {}
	};

	public :

	Node * root;

	Treap() : root(nullptr) {}

	int size(Node * ptr){
		return ptr == nullptr ? 0 : ptr->size;
	}

	/*
	Splits the tree/subtree rooted at curr into two subtrees with left one has sz no. of elements
	and all the other elements belong to the second tree.
	*/
	pair<Node*,Node*> split(Node * curr,int sz){
		if(sz == 0)	//all the elements go to the right part
			return pair<Node*,Node*> {nullptr,curr};
		
		if(curr == nullptr)
			return pair<Node*,Node*> {nullptr,nullptr};

		//this means we need some elements from the curr->right subtree
		if(size(curr->left) + 1 <= sz){	
			pair<Node*,Node*> p = split(curr->right,sz-(size(curr->left) + 1));
			curr->right = p.first;
			curr->size = size(curr->left) + size(curr->right) + 1;
			return pair<Node*,Node*> {curr,p.second};
		} 
		else{
			pair<Node*,Node*> p = split(curr->left,sz);
			curr->left = p.second;
			curr->size = size(curr->left) + size(curr->right) + 1;
			return pair<Node*,Node*> {p.first,curr};
		}
	}

	/*
	Concatenates two segments for example [0,1,2] is concatenated with [5,3,5]
	results in the tree corresponding to segment [0,1,2,5,3,5]
	*/

	Node * merge(Node * first,Node * second){
		if(first == nullptr) return second;
		if(second == nullptr) return first;

		//first will stay at top so combine the first->right with second
		if(first->priority > second->priority){
			first->right = merge(first->right,second);
			first->size = size(first->left) + size(first->right) + 1;
			return first;
		}
		else {
			second->left = merge(first,second->left);
			second->size = size(second->left) + size(second->right) + 1;
			return second;
		}
	}

	void build(vector<int> &v){
		//adding all the elements to the treap
		for(int i=0;i<(int)v.size();i++){
			int priority = uid(0,1000000000);
			Node * new_node = new Node(priority,v[i]);
			root = merge(root,new_node);
		}
	}

	void query(int l,int r,int n){

		int sz1 = r - l;
		int sz2 = n - r;

		//take the segment [l....l+sz1) and [r...r + sz2) and swap these segments
		if(sz1 <= sz2){
			int sz = sz1;

			//first => [0..l) and second => [l...n)
			pair<Node *,Node *> P = split(root,l);

			//first => [l...l+sz) and second => [l+sz....n)
			pair<Node *,Node *> a = split(P.second,sz);

			//first => [l+sz i.e. r ....l+2*sz) second [l+2*sz..n)
			pair<Node *,Node *> b = split(a.second,sz);

			root = merge(merge(P.first,b.first),merge(a.first,b.second));

		}
		else{
			int sz = sz2;

			//first => [0..l) and second => [l...n)
			pair<Node *,Node *> P = split(root,l);

			//first => [l...l+sz) and second => [l+sz....n)
			pair<Node *,Node *> a = split(P.second,sz);

			pair<Node *,Node *> b = split(a.second,sz1-sz2);

			root = merge(merge(P.first,b.second),merge(b.first,a.first));
		}

		return;
	}

	void inorder(Node *root){
		if(root == nullptr)
			return;
		inorder(root->left);
		cout<<root->original<<" ";
		inorder(root->right);
		return;
	}

};

int main(){

	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);

	int n;
	cin>>n;
	vector<int> v(n);
	iota(v.begin(),v.end(),1);
	Treap T;
	T.build(v);
	int t = n;
	while(t--){
		int a,b;
		cin>>a>>b;
		a--;b--;
		if(b<=a)
			continue;
		T.query(a,b,n);
	}
	T.inorder(T.root);
	cout<<endl;


	return 0;
}
