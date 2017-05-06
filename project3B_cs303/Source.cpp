//Name: Hung Tran
//Main Function 
// -Read file and create everything

#include <iostream>
#include <fstream>
#include <string>
#include "Binary_Search_Tree.h"
#include <map>

using namespace std;

int main() {

	//File I/O
	


	ifstream fin("morse.txt");
	ofstream fout("output.txt");

	//Throw error if can't open input file
	if (!fin) {
		cerr << "Error opening input file!";
		system("pause");
		return 1;
	}

	/*map<char, vector<char>> mp;*/

	string line;
	//fin >> line;
	Binary_Search_Tree<string> tree; //this tree use insert function but fail
	Binary_Search_Tree<string> tree2; //this tree use vector and read_tree function to create binary tree
	vector<string> test;
	vector<string> test2{ "","e.", "i..", "s...", "h....", "NULL", "NULL", "v..._", "NULL", "NULL",
		"u.._", "f.._.",  "NULL", "NULL",  "NULL", "a._", "r._.", "l._..", "NULL", "NULL","NULL", "w.__", "p.__.",
		"NULL", "NULL", "j.___", "NULL", "NULL", "t_", "n_.", "d_..",  "b_...", "NULL","NULL",
		"x_.._", "NULL", "NULL", "k_._", "c_._.","NULL", "NULL", "y_.__", "NULL", "NULL", "m__","g__.", "z__..",
		"NULL", "NULL", "q__._", "o___", "NULL", "NULL", }; //ordered vector :v

	string txt = "";
	string txtcode = "";	
	
	while (fin >> line) {
		test.push_back(line);
		//tree.insert(txt, txtcode);	
	}
	fin.close();
	
	/*while (fin.good()) {

		test.push_back(line);
		fin >> line;
	}
	test.push_back(line);*/
	bool f;
	int n = 0;
	tree.insert(txt, txtcode, n);
	while (!test.empty()) {
		for (vector<string>::iterator it = test.begin(); it < test.end();) {
			txt = "";
			txt.push_back(*it->begin());
			string tx(it->begin() + 1, it->end());
			txtcode = tx;
			if (n == (it->size()-1) ) {
				
				f = tree.insert(txt, txtcode, n);
				/*cout << *it << endl;*/
				it = test.erase(it);
				//cout << *it << endl;
				//if (f == true) {
				//	
				//}
				//else {
				//	++it;
				//	continue;
				//}
				//
				////it = test.begin();
				//
				
			}
			else {
				++it;
			}
			
		}
		n++;
	}
	cout << tree.number_of_nodes() << "  " << endl; //keep track how many node in tree
	
	tree2.read_tree(test2);
	tree2.encode("ab");
	tree.decode("ab");
	

	system("pause");
	return 0;
}