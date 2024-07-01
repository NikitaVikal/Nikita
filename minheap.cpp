/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"

// include <iostream>

//Write your code below this line

string giv_binary(int i){
	string s="";
	while(i>0){
		int rem=i%2;
		i=i/2;
		s=std::to_string(rem)+s;
	}
	return s;
}
void swapsimp(HeapNode* i1, HeapNode* i2) {
	int temp = i1->val;
	i1->val = i2->val;
	i2->val = temp;
}

MinHeap::MinHeap(){
	root = NULL;
	size = 0;
}

void MinHeap::push_heap(int num){
	if (size != 0) {
		string a = giv_binary(size + 1);
		HeapNode* create = new HeapNode(num);
		HeapNode* current  = root;
		if(size>1){
		for (int i = 1; i < a.length()-1; i++) {
			current = root;
			if (a[i]=='1') {
				current = current->right;
			}
			else if(a[i]=='0') {
				current = current->left;
			}
		}
		if(a[a.length()-1]=='0'){
			current->left=create;
			create->par=current;
			current=current->left;
		}
		else{
			current->right=create;
			create->par=current;
			current=current->right;
		}
		}
		else{
			root->left=create;
			create->par=root;
			current=current->left;
		}
		HeapNode* Heapify = current;
		while (Heapify->par != NULL) {
			if (Heapify->par->val < Heapify->val) {
				break;
			}
			else {
				swapsimp(Heapify->par, Heapify);
				Heapify = Heapify->par;
			}
		}
		size++;
	}
	else {
		HeapNode* create = new HeapNode(num);
		root = create;
		size++;
	}
}

int MinHeap::get_min(){
	return root->val;
}

void MinHeap::pop(){
	HeapNode* current = root;
	string a = giv_binary(size);
	if(size>1){
	for (int i = 1; i < a.length(); i++) {
		if (a[i]=='1') {
			current = current->right;
		}
		else if(a[i]=='0') {
			current = current->left;
		}
	}
	swapsimp(root, current);
	if (!(current->par == NULL)) {
		if (current == current->par->right) {
			current->par->right = NULL;
		}
		else {
			current->par->left = NULL;
		}
	}
	else{
		root = NULL;
	}
	current = root;
	while (!(current->left == NULL && current->right == NULL)) {
		if (current->right != NULL && current->left != NULL) {
			if (current->val < current->right->val && current->val < current->left->val) {
				break;
			}
			else if (current->right->val < current->left->val) {
				swapsimp(current, current->right);
				current = current->right;
			}
			else {
				swapsimp(current, current->left);
				current = current->left;
			}
		}
		else if (current->left != NULL) {
			if (current->val < current->left->val) {
				break;
			}
			swapsimp(current, current->left);
			current = current->left;
		}
		else if (current->right != NULL) {
			if (current->val < current->right->val){
				break;
			}
			swapsimp(current, current->right);
			current = current->right;
		}
	}
	}
	else{
		root=NULL;
	}
	size--;
}

MinHeap::~MinHeap(){

}

// int main(){
// 	MinHeap a;
// 	a.push_heap(1);
// 	a.push_heap(2);
// 	a.push_heap(3);
// 	a.push_heap(4);
// 	a.push_heap(5);
// 	cout<<a.get_min()<<endl;
// 	a.pop();
// 	cout<<a.get_min()<<endl;
// 	a.pop();
// 	cout<<a.get_min()<<endl;
// 	a.pop();
// 	cout<<a.get_min()<<endl;
// 	a.pop();
// 	cout<<a.get_min()<<endl;
// }
