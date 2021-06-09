/*
Implicit treaps are built over an array where keys are supposed to be the 
indices of elements in an array.
The subtree rooted at each node consists of nodes that form a contiguous subarray.
So it allows us to store a computed value of the contiguos subarray in that node which 
can thus be easily used to query a range.

The extra operation it provides is to slice a continuous part of an array and place it 
in the beginnnig,end or anywhere else and we can still get the answer of the segments.
[REMEMBER] : We don't store the keys as they are implicit and we are only concerned with the value
			 related to the segment which a node represents.

We can keep a value lazy at each node as we'll which can keep the value to be propogated down
that lazy value can be operation to reverse as well.
propogate reverse down and swap the left and the right child if reverse is equal to true. 
*/
#include<bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)

class Treap{

	struct Node{
		int priority;
		int val;	//this stores aggregate value of the subtree
		int original;	//this stores the original value of the index it corresponds to.
		int size;
		Node *left , *right;
		Node(int priority,int value) : priority(priority) ,original(value), val(value) ,size(1) , left(nullptr) , right(nullptr) {}
	};

	public :

	Node * root;

	Treap() : root(nullptr) {}

	//identity element (for sum it is 0 , for product it is 1 for max INT_MIN etc)
	int ID = 0;		

	int operate(int a,int b){	//How two elements are combined
		return a + b;
	}

	int size(Node * ptr){
		return ptr == nullptr ? 0 : ptr->size;
	}

	int combine(Node *l,Node *r,int v){
		int a = (l == nullptr ? ID : l->val);
		int b = (r == nullptr ? ID : r->val);
		return operate(operate(a,b),v);
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
			curr->val = combine(curr->left,curr->right,curr->original);
			curr->size = size(curr->left) + size(curr->right) + 1;
			return pair<Node*,Node*> {curr,p.second};
		} 
		else{
			pair<Node*,Node*> p = split(curr->left,sz);
			curr->left = p.second;
			curr->val = combine(curr->left,curr->right,curr->original);
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
			first->val = combine(first->left,first->right,first->original);
			first->size = size(first->left) + size(first->right) + 1;
			return first;
		}
		else {
			second->left = merge(first,second->left);
			second->val = combine(second->left,second->right,first->original);
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

	int query(int l,int r){
		int sz = r - l + 1;
		pair<Node *, Node *> p = split(root,l);
		pair<Node *,Node *> p2 = split(p.second,sz);
		int ans = p2.first->val;
		p.second = merge(p2.first,p2.second);
		root = merge(p.first,p.second);
		return ans;
	}

};

int main(){

	vector<int> v = {4,3,7,2,8,6,1,5};

	Treap T;
	T.build(v);

	cout<<T.query(0,2)<<endl;
	cout<<T.query(2,3)<<endl;
	cout<<T.query(4,5)<<endl;

	return 0;
}
