/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"
#include <iostream>

//Write your code below this line
string gen(ExprTreeNode* n, Parser p) {
	if (n->type == "VAL") {
		return "PUSH " + std::to_string(n->num);
	}
	else if (n->type == "VAR") {
		int index = p.symtable->search(n->id);
		return "PUSH mem[" + std::to_string(index) + "]";
	}
	else if (n->type == "ADD" || n->type == "SUB" || n->type == "MUL" || n->type == "DIV") {
		return n->type;
	}
}

vector<string> generator(ExprTreeNode* n , Parser p) {
	if (n == NULL) {
		vector<string> ok = {};
		return ok;
	}
	else {
		vector<string> a, b, c;
		a = generator(n->right, p);
		b = generator(n->left, p);
		c = {};
		c.insert(c.end(), a.begin(), a.end());
		c.insert(c.end(), b.begin(), b.end());
		c.push_back(gen(n, p));
		return c;
	}
}

EPPCompiler::EPPCompiler(){
		
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
	memory_size = mem_limit;
	output_file = out_file;
	targ = Parser();
	least_mem_loc = MinHeap();
	for (int i = 0; i < memory_size; i++) {
		least_mem_loc.push_heap(i);
	}
}

void EPPCompiler::compile(vector<vector<string>> code){
	int n = code.size();
	
	for (int i = 0; i < n; i++) {

		 vector<string> aux;
        aux.push_back(code[i][0]);
        aux.push_back(code[i][1]);
        for (int j = 2; j < code[i].size(); j++)
        {
            if (code[i][j].length() > 1 and isdigit(code[i][j][0]) != 1)
            {
                for (int k = 0; k < code[i][j].length(); k++)
                {
                    aux.push_back(code[i][j].substr(k,1));
                }
                
            }

            else
			{
				if (isdigit(code[i][j][0]) == 1 and code[i][j][code[i][j].length()-1] == ')' )
				{
						aux.push_back(code[i][j].substr(0,code[i][j].length()-1));
						aux.push_back(code[i][j].substr(code[i][j].length()-1,1));
					
					
				}
				else{
				aux.push_back(code[i][j]);}
			}
            
        }
        
		vector<string> gene;
		vector<string> current = aux;
		targ.parse(current);
		if (current[0] == "del") {
			string var = current[2];
			int index = targ.symtable->search(var);
			least_mem_loc.push_heap(index);
			gene = generate_targ_commands();
		}
		else if (current[0] == "ret") {
			gene = generate_targ_commands();
		}
		else {
			string var = current[0];
			targ.symtable->insert(var);
			if (targ.symtable->search(var) == -1) {
				int index = least_mem_loc.get_min();
				least_mem_loc.pop();
				targ.symtable->assign_address(var, index);
			}
			gene = generate_targ_commands();
		}
		write_to_file(gene);
	}
}

vector<string> EPPCompiler::generate_targ_commands(){
	ExprTreeNode* current = targ.expr_trees.back();
	vector<string> command;
	if (current->left->type == "DEL") {
		//vector<string> command;
		string var = current->right->id;
		int index = targ.symtable->search(var);
		string ok = "DEL = mem[" + std::to_string(index) + "]";
		command.push_back(ok);
		targ.symtable->remove(var);
		return command;
	}
	else if (current->left->type == "RET") {
		command=generator(current->right,targ);
		command.push_back("RET = POP");
		return command;
	}
	else {
		command = generator(current->right, targ);
		string var = current->left->id;
		int index = targ.symtable->search(var);
		string ok = "mem[" + std::to_string(index) + "] = POP";
		command.push_back(ok);
		return command;
	}
}

void EPPCompiler::write_to_file(vector<string> commands){
	 ofstream outfile(output_file, ios::app);
	for (const auto& command : commands) {
		outfile << command << endl;
	}
	outfile << "\n";
}

EPPCompiler::~EPPCompiler(){
			
}
