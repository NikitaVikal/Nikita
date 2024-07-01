/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your code below this line
ExprTreeNode* maketree(vector<string> token) {
    if (token.size() == 1) {
        string a = token[0];
        if (a[0] <= 57) {
            int v = stoi(token[0]);
            ExprTreeNode* rot = new ExprTreeNode("VAL", v);
            return rot;
        }
        else {
            ExprTreeNode* rot = new ExprTreeNode();
            rot->type = "VAR";
            rot->id = a;
            return rot;
        }
    }
    else {
        int open = 0;
        bool done = false;
        for (int i = 0; i < token.size(); i++) {
            if (done) {
                break;
            }
            else if (token[i] == "(") {
                open++;
            }
            else if (token[i] == ")") {
                open--;
            }
            if (open == 1 && (token[i] == "+" || token[i] == "-" || token[i] == "*" || token[i] == "/")) {
                done = true;
                ExprTreeNode* rot = new ExprTreeNode();
                if (token[i] == "+") {
                    rot->type = "ADD";
                }
                else if (token[i] == "-") {
                    rot->type = "SUB";
                }
                else if (token[i] == "*") {
                    rot->type = "MUL";
                }
                else {
                    rot->type = "DIV";
                }
                vector<string> v = vector<string>(token.begin() + 1, token.begin() + i);
                vector<string> v2 = vector<string>(token.begin() + i + 1, token.end() - 1);
                rot->left = maketree(v);
                rot->right = maketree(v2);
                return rot;
            }
        }
    }
}

Parser::Parser(){
    symtable = new SymbolTable();
}

void Parser::parse(vector<string> code){
    string a = code[1];
    ExprTreeNode* root = new ExprTreeNode();
    root->type = "VAR";
    root->id = a;
    root->left = nullptr;
    root->right = nullptr;
    ExprTreeNode* l = new ExprTreeNode();
    if (code[0] == "del") {
        l->type = "DEL";
        l->id = "DEL";
        root->left=l;
        ExprTreeNode* r = new ExprTreeNode();
        r->type = "VAR";
        r->id = code[2];
        root->right=r;
    }
    else if (code[0] == "ret") {
        l->type = "RET";
        l->id = "RET";
        root->left=l;
        vector<string> treeable = vector <string>(code.begin() + 2, code.end());
        root->right = maketree(treeable);
    }
    else {
        l->type = "VAR";
        l->id = code[0];
        root->left = l;
        vector<string> treeable = vector <string>(code.begin() + 2, code.end());
        root->right = maketree(treeable);
    }
    expr_trees.push_back(root);
}

Parser::~Parser(){
    //delete symtable;
}