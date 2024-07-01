/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line
/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
#include <iostream>

int heightcalc(SymNode* n) {
    if (n->left == NULL && n->right == NULL) {
        return 0;
    }
    else if (n->left == NULL) {
        return 1 + heightcalc(n->right);
    }
    else if (n->right == NULL) {
        return 1 + heightcalc(n->left);
    }
    else {
        int a = heightcalc(n->left);
        int b = heightcalc(n->right);
        if (a >= b) {
            return 1 + a;
        }
        else {
            return 1 + b;
        }
    }
}
int balanceFactor(SymNode* n) {
    if (heightcalc(n) == 0) {
        return 0;
    }
    else if (n->left == NULL) {
        return -1 * heightcalc(n);
    }
    else if (n->right == NULL) {
        return heightcalc(n);
    }
    else {
        int lheight = 1 + heightcalc(n->left);
        int rheight = 1 + heightcalc(n->right);
        return lheight - rheight;
    }
}
SymbolTable::SymbolTable(){
    root = NULL;
}

void SymbolTable::insert(string k){
    if (root == NULL) {
        SymNode* a = new SymNode(k);
        root = a;
        a->par = NULL;
        a->height = 0;
        size++;
    }
    else {
        SymNode* current = root;
        SymNode* a = new SymNode(k);
        a->height = 0;  
        bool done = false;
        while (current != NULL && !done) {
            a->height += 1;
            if (current->key < k)
            {
                if (current->right == NULL)
                {
                    current->right = a;
                    a->par = current;
                    SymNode* change = a;
                    change->height = heightcalc(change);
                    while (change->par != NULL) {
                        change = change->par;
                        change->height = heightcalc(change);
                    }
                    SymNode* rotate = a;
                    while (balanceFactor(rotate) <= 1 && balanceFactor(rotate) >= -1) {
                        if (rotate == root) {
                            break;
                        }
                        rotate = rotate->par;
                    }
                    if (balanceFactor(rotate) >= 2) {
                        SymNode* beta = rotate->left;
                        if (balanceFactor(beta) >= 0) {
                            root=rotate->LeftLeftRotation();
                        }
                        else {
                            root=rotate->LeftRightRotation();
                        }
                    }
                    else if (balanceFactor(rotate) <= -2) {
                        SymNode* beta = rotate->right;
                        if (balanceFactor(beta) <= 0) {
                            root=rotate->RightRightRotation();
                        }
                        else {
                            root=rotate->RightLeftRotation();
                        }
                    }
                    done = true;
                    size++;
                }
                else
                {
                    current = current->right;
                }
            }
            else if(current->key>k) 
            {
                if (current->left == NULL)
                {
                    current->left = a;
                    a->par = current;
                    SymNode* change = a;
                    change->height = heightcalc(change);
                    while (change->par != NULL) {
                        change = change->par;
                        change->height = heightcalc(change);
                    }
                    SymNode* rotate = a;
                    while (balanceFactor(rotate) <= 1 && balanceFactor(rotate) >= -1) {
                        if (rotate == root) {
                            break;
                        }
                        rotate = rotate->par;
                    }
                    if (balanceFactor(rotate) >= 2) {
                        SymNode* beta = rotate->left;
                        if (balanceFactor(beta) >= 0) {
                            root=rotate->LeftLeftRotation();
                        }
                        else {
                            root=rotate->LeftRightRotation();
                        }
                    }
                    else if (balanceFactor(rotate) <= -2) {
                        SymNode* beta = rotate->right;
                        if (balanceFactor(beta) <= 0) {
                            root=rotate->RightRightRotation();
                        }
                        else {
                            root=rotate->RightLeftRotation();
                        }
                    }
                    done = true;
                    size++;
                }
                else { current = current->left; }

            }
            else {
                break;
            }
        }
    }
}

void SymbolTable::remove(string k){
    if (k == root->key) {
        if (root->left == NULL && root->right == NULL) {
            root = NULL;
        }
        else if (root->left == NULL) {
            root->right->par = NULL;
            root = root->right;
        }
        else if (root->right == NULL) {
            root->par->left = NULL;
            root = root->left;
        }
        else {
            SymNode* node;
            node = root->right;
            while (node->left != NULL) {
                node = node->left;
            }
            string temps = node->key;
            int tempv = node->address;
            remove(node->key);
            root->key = temps;
            root->address = tempv;
        }
    }
    else {
        bool l;
        SymNode* current;
        if (k < root->key) {
            current = root->left;
            l = true;
        }
        else {
            current = root->right;
            l = false;
        }
        while (current->key != k) {
            if (current->key < k) {
                current = current->right;
                l = false;
            }
            else {
                current = current->left;
                l = true;
            }
        }
        if (current->left == NULL && current->right == NULL) {
            if (l) {
                current->par->left = NULL;
            }
            else current->par->right = NULL;
            SymNode* change = current->par;
            change->height = heightcalc(change);
            while (change->par != NULL) {
                change = change->par;
                change->height = heightcalc(change);
            }
            SymNode* rotate = current->par;
            while (balanceFactor(rotate) <= 1 && balanceFactor(rotate) >= -1) {
                if (rotate == root) {
                    break;
                }
                rotate = rotate->par;
            }
            if (balanceFactor(rotate) >= 2) {
                SymNode* beta = root->left;
                if (balanceFactor(beta) >= 0) {
                    root=root=rotate->LeftLeftRotation();
                }
                else {
                    root=rotate->LeftRightRotation();
                }
            }
            else if (balanceFactor(rotate) <= -2) {
                SymNode* beta = root->right;
                if (balanceFactor(beta) <= 0) {
                    root=rotate->RightRightRotation();
                }
                else {
                    root=rotate->RightLeftRotation();
                }
            }
            delete current;
        }
        else if (current->left == NULL) {
            SymNode* change;
            if (l) {
                current->par->left = current->right;
                current->right->par = current->par;
            }
            else {
                current->par->right = current->right;
                current->right->par = current->par;
            }
            change = current->par;
            change->height=heightcalc(change);
            while (change->par != NULL) {
                change = change->par;
                change->height = heightcalc(change);
            }
            SymNode* rotate = current->par;
            while (balanceFactor(rotate) <= 1 && balanceFactor(rotate) >= -1) {
                if (rotate == root) {
                    break;
                }
                rotate = rotate->par;
            }
            if (balanceFactor(rotate) >= 2) {
                SymNode* beta = root->left;
                if (balanceFactor(beta) >= 0) {
                    root=rotate->LeftLeftRotation();
                }
                else {
                    root=rotate->LeftRightRotation();
                }
            }
            else if (balanceFactor(rotate) <= -2) {
                SymNode* beta = root->right;
                if (balanceFactor(beta) <= 0) {
                    root=rotate->RightRightRotation();
                }
                else {
                    root=rotate->RightLeftRotation();
                }
            }
            delete current;
        }
        else if (current->right == NULL) {
            SymNode* change;
            if (l) {
                current->par->left = current->left;
                current->left->par = current->par;
            }
            else {
                current->par->right = current->left;
                current->left->par = current->par;
            }
            change = current->par;
            change->height = heightcalc(change);
            while (change->par != NULL) {
                change = change->par;
                change->height = heightcalc(change);
            }
            SymNode* rotate = current->par;
            while (balanceFactor(rotate) <= 1 && balanceFactor(rotate) >= -1) {
                if (rotate == root) {
                    break;
                }
                rotate = rotate->par;
            }
            if (balanceFactor(rotate) >= 2) {
                SymNode* beta = root->left;
                if (balanceFactor(beta) >= 0) {
                    root=rotate->LeftLeftRotation();
                }
                else {
                    root=rotate->LeftRightRotation();
                }
            }
            else if (balanceFactor(rotate) <= -2) {
                SymNode* beta = root->right;
                if (balanceFactor(beta) <= 0) {
                    root=rotate->RightRightRotation();
                }
                else {
                    root=rotate->RightLeftRotation();
                }
            }
            delete current;
        }
        else {
            SymNode* replace = current;
            current = current->right;
            while (current->left != nullptr) {
                current = current->left;
            }
            string temps = current->key;
            int tempv = current->address;
            remove(current->key);
            replace->key = temps;
            replace->address = tempv;
        }
    }
    size--;
}

int SymbolTable::search(string k){
    SymNode* current = root;
    while (current->key != k) {
        if (current->key < k) {
            current = current->right;
        }
        else {
            current = current->left;
        }
    }
    return current->address;
}

void SymbolTable::assign_address(string k,int idx){
    SymNode* current = root;
    while (current->key != k) {
        if (current->key > k) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    current->address = idx;
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

SymbolTable::~SymbolTable(){
    delete root;
}

// int main()
// {
//     SymbolTable a;
//     a.insert("a");
//     a.insert("b");
//     a.insert("c");
//     a.insert("e");
//     a.insert("d");
    

// }