/*Balanced Binary Search Tree - Treap
Operations - O(LOG N)
(1) Insert 
(2) Delete 
(3) Find
This implementation allows storing of only single instance of each key
*/

#include<bits/stdc++.h>
using namespace std;

struct Node{
	int priority;
	int key;
	Node *left , *right;
	Node(int priority,int key) : priority(priority) , key(key) , left(nullptr) , right(nullptr) {}
};

/*
Split the subtree rooted at node pointed by current into two subtree's such that 
left subtree contains keys less than equal to split_point
and right subtree contains nodes greater than equal to split_point
*/
pair<Node*,Node*> split(Node* curr,int split_point){
	//split a null tree into two null trees
	if(curr == nullptr)
		return pair<Node*,Node*> {nullptr,nullptr};

	/*
	if key of current node is greater than split point then it will lie in the right subtree after split
	so split the subtree curr->left recursively and out of those two subtree's which it'll return
	the right one will be left child of current
	*/
	if(curr->key > split_point){
		pair<Node*,Node*> splitted_left = split(curr->left,split_point);
		curr->left = splitted_left.second;
		pair<Node*,Node*> ans = {splitted_left.first,curr};
		return ans;
	}
	/*
	in this case the curr node will lie in the left subtree after splitting
	so split the curr->right recursively and out ot the returned two make the first one the
	right child of current
	*/
	else{
		pair<Node*,Node*> splitted_right = split(curr->right,split_point);
		curr->right = splitted_right.first;
		pair<Node*,Node*> ans = {curr,splitted_right.second};
		return ans;
	}
}


/*
Merging two BST's can only be done if all the elements in the first subtree are less than
all the elements than the right subtree and ,the concept of merging is based on the priority 
of the root nodes of the trees being merged.
[REMEMBER] : All elements of first will stay left compared to all elements of second
*/
Node * merge(Node* first,Node *second){
	if(first == nullptr) return second;
	if(second == nullptr) return first;

	/*
	In this case since the priority is maintained by the max-heap property the node pointed by first
	must stay at the top and the second is supposed to be merged with right subtree of first
	ans then make the merged subtree the right child of first and return first.
	*/
	if(first->priority > second->priority){
		first -> right = merge(first->right,second);
		return first;
	}
	/*
	In this case second must stay at the top so merge the first with left child of second and make
	the result as the left child of second
	*/
	else{
		second->left = merge(first,second->left);
		return second;
	}
}

/*
Find is basic binary search tree property
*/
bool find(Node *curr,int key){
	if(curr == nullptr)
		return false;
	if(curr->key == key)
		return true;
	else if(curr->key < key)
		return find(curr->right,key);
	else
		return find(curr->left,key);
}

/*
To insert split the tree such that 
first tree has all keys less than x and, second has all keys greater than x.
Then create a tree with single node with key x.
merge this single tree with the second tree
*/
Node * insert(Node * root,int x){
	//Don't insert if already present
	if(find(root,x))
		return root;
	pair<Node*,Node*> p = split(root,x);
	int priority = rand()%100000000;
	Node * new_node = new Node(priority,x);
	p.first = merge(p.first,new_node);
	root = merge(p.first,p.second);
	return root;
}

/*
To delete split the tree into three parts such that the middle part has only the node to be deleted
Then delete the middle part
and merge the first and third part
*/
Node * remove(Node * root,int x){
	pair<Node *,Node *> p = split(root,x);
	pair<Node *,Node *> p2 = split(p.first,x-1);
	if(p2.second != nullptr) //there would be only one instance of key -> x so delete it
		delete p2.second;
	root = merge(p2.first,p.second);
	return root;
}

//sorted array
void print_inorder(Node *curr){
	if(curr == nullptr) return;
	print_inorder(curr->left);
	cout<<curr->key<<" ";
	print_inorder(curr->right);
	return;
}


int main(){

	//Testing
	Node * root = nullptr;
	cout<<"1. to add , 2. to delete , 3. to find\n";

	while(true){
		int type;
		cin>>type;
		int key;
		cin>>key;
		if(type == 1){
			root = insert(root,key);
		}
		else if(type == 2){
			root = remove(root,key);
		}
		else{
			cout<<(find(root,key)?"found":"not found")<<endl;
		}
		print_inorder(root);
		cout<<endl;

	}

	return 0;
}