/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"
#include <iostream>
//Write your code below this line

int heightcal(SymNode* n) {
    if (n->left == NULL && n->right == NULL) {
        return 0;
    }
    else if (n->left == NULL) {
        return 1 + heightcal(n->right);
    }
    else if (n->right == NULL) {
        return 1 + heightcal(n->left);
    }
    else {
        int a = heightcal(n->left);
        int b = heightcal(n->right);
        if (a >= b) {
            return 1 + a;
        }
        else {
            return 1 + b;
        }
    }
}
void set_height(SymNode* n){
	SymNode* change = n;
    change->height = heightcal(change);
    while (change->par != NULL) {
        change = change->par;
        change->height = heightcal(change);
    }
}

SymNode::SymNode(){
	left = NULL;
	right = NULL;
}

SymNode::SymNode(string k){
	key = k;
	left = NULL;
	right = NULL;
}

SymNode* SymNode::LeftLeftRotation(){
	SymNode* curr = this->left;
	if (this->par!=NULL && this->par->left == this) {
		this->par->left = curr;
	}
	else if (this->par!=NULL && this->par->right==this) {
		this->par->right = curr;
	}
	SymNode* r = curr->right;
	curr->right = this;
	curr->par = this->par;
	this->par = curr;
	this->left = r;
	if(r!=NULL){
		r->par = this;
	}
	set_height(this);
	set_height(curr);
	SymNode* root = this;
	while (root->par != NULL) {
		root = root->par;
	}
	return root;
}

SymNode* SymNode::RightRightRotation(){
	SymNode* curr = this->right;
	if (this->par!=NULL && this->par->left==this) {
		this->par->left = curr;
	}
	else if(this->par!=NULL && this->par->right==this) {
		this->par->right = curr;
	}
	SymNode* l = curr->left;
	curr->left = this;
	curr->par = this->par;
	this->par = curr;
	this->right = l;
	if(l!=NULL){
		l->par = this;
	}
	set_height(this);
	set_height(curr);
	SymNode* root = this;
	while (root->par != NULL) {
		root = root->par;
	}
	return root;
}

SymNode* SymNode::LeftRightRotation(){
	SymNode* currl = this->left;
	SymNode* curr = currl->right;
	if (this->par!=NULL && this->par->left == this) {
		this->par->left = curr;
	}
	else if(this->par!=NULL && this->par->right==this) {
		this->par->right = curr;
	}
	SymNode* l = curr->left;
	SymNode* r = curr->right;
	curr->par = this->par;
	curr->left = currl;
	curr->right = this;
	currl->par = curr;
	this->par = curr;
	currl->right = l;
	this->left = r;
	if(r!=NULL){
		r->par = this;
	}
	if(l!=NULL){
		l->par = currl;
	}
	set_height(this);
	set_height(currl);
	set_height(curr);
	SymNode* root = this;
	while (root->par != NULL) {
		root = root->par;
	}
	return root;
}

SymNode* SymNode::RightLeftRotation(){
	SymNode* currr = this->right;
	SymNode* curr = currr->left;
	if (this->par!=NULL && this->par->left == this) {
		this->par->left = curr;
	}
	else if(this->par!=NULL && this->par->right==this) {
		this->par->right = curr;
	}		
	SymNode* l = curr->left;
	SymNode* r = curr->right;
	curr->par = this->par;
	curr->right = currr;
	curr->left = this;
	currr->par = curr;
	this->par = curr;
	currr->left = r;
	this->right = l;
	if(r!=NULL){
		r->par = currr;
	}
	if(l!=NULL){
		l->par = this;
	}
	set_height(this);
	set_height(currr);
	set_height(curr);
	SymNode* root = this;
	while (root->par != NULL) {
		root = root->par;
	}
	return root;
}

SymNode::~SymNode(){
	// left = NULL;
	// right = NULL;
	// par = NULL;
}
