//Name: Anthony Le
//	Binary_Search_Tree class
//	create useful function for binary tree

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "Binary_Tree.h"


template<typename Item_Type>
class Binary_Search_Tree : public Binary_Tree<Item_Type>
{
public:
	// Constructor
	Binary_Search_Tree() : Binary_Tree<Item_Type>() {}

	// Public Member Functions
	virtual bool insert(const Item_Type& letter, const Item_Type& code, int index);

	virtual bool erase(const Item_Type& item);

	const Item_Type* min() const;

	const Item_Type* min(BTNode<Item_Type>* local_root) const;

	const Item_Type* max() const;

	const Item_Type* max(BTNode<Item_Type>* local_root) const;

	const Item_Type* find(const Item_Type& target) const;

	std::string decode(std::string target);
	std::string encode(std::string target);

//	Binary_Tree<Item_Type> searchNode(BTNode<Item_Type>*& local_root, std::string target);
private:

	// Private Member 
	virtual bool insert(BTNode<Item_Type>*& local_root,
		const Item_Type& letter, const Item_Type& code, int index);

	virtual bool erase(BTNode<Item_Type>*& local_root,
		const Item_Type& item);

	const Item_Type* find(BTNode<Item_Type>* local_root,
		const Item_Type& target) const;

	virtual void replace_parent(
		BTNode<Item_Type>*& old_root,
		BTNode<Item_Type>*& local_root);

}; // End binary search tree

template<typename Item_Type>
const Item_Type* Binary_Search_Tree<Item_Type>::min() const {
	return min(this->root);
		
}

template<typename Item_Type>
const Item_Type* Binary_Search_Tree<Item_Type>::min(BTNode<Item_Type>* local_root) const{
	if (local_root == NULL)
		return NULL;

		if (local_root->left == NULL)
			return &(local_root->data);
		 return min(local_root->left);
}

template<typename Item_Type>
const Item_Type* Binary_Search_Tree<Item_Type>::max() const {
	return max(this->root);

}

template<typename Item_Type>
const Item_Type* Binary_Search_Tree<Item_Type>::max(BTNode<Item_Type>* local_root) const{
	if (local_root == NULL)
		return NULL;

		if (local_root->right == NULL)
			return &(local_root->data);
		return max(local_root->right);
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Creator : Anthony Le																				    
//        Decode Function (public field)
//			put codes into a vector then pass each code to find() (public field) to find it in tree
//			return a combine string of each code
//////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Item_Type>
inline std::string Binary_Search_Tree<Item_Type>::decode(std::string target)
{	
	std::vector<std::string> sentence;
	std::string code;
	bool c = true;
	std::string q = "Not the right code";
	if (target == "") {
		c = false;
		std::cout << q << endl;
		return q;
	}
	for (int a = 0; a < target.size(); a++) {
		std::cout << target[a] << endl;
		if ((target[a] == '.' || target[a] == '_' || target[a] == ' ')) {
			if (target[a] == ' ') {
				sentence.push_back(code);
				code = "";
			}
			else {
				code += target[a];
			}
		}	
		else {			
			c = false;			
			return q;
		}		
	}
	if (code != "") {
		sentence.push_back(code);
		code = "";
	}
	if (c == true && !sentence.empty()) {
		for (int x = 0; x <= sentence.size()-1; x++) {
			code += *find(sentence[x]);
		}
	}
	return code;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Creator : Williams, Adrian																				    
//         Encoding function (public field)
//		   read each letter in a string 
//         then pass it to find function (public field) and get the return of code
//////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Item_Type>
inline std::string Binary_Search_Tree<Item_Type>::encode(std:: string target)
{
	
	std::string q = "Not the right code";
	for (int i = 0; i <= target.size()-1; i++) {
		if (isalpha(target[i])) {
			std::string a = "";
			a.push_back(target[i]);
			std::cout << *find(a);
		}
		else {
			return q;
		}
	}
	return "";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Creator : Hung Tran																				    
//         Wrapper of insert function (public field)
//////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Item_Type>
const Item_Type* Binary_Search_Tree<Item_Type>::find(
	const Item_Type& item) const {
	return find(this->root, item);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Creator : Hung Tran																				    
//         Find function (public field)
//		   travel all the tree and find target
//         
//         Don't pass code and letter to this function on the same string. Make it separate please
//         this function still have few errors.
//
//			case 1: If target is letter   //this case doesn't work ...
//                 return left sub_tree if target > tree data
//                 return left sub_tree if target < tree data
//                 return the sub tree code if it met the requirement
//          case 2:
//                 return left sub_tree if last char of target is dot and left sub tree is not null
//                 return left sub_tree if last char of target is dash and right sub tree is not null
//                 return the sub tree code if it met the requirement
//////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Item_Type>
const Item_Type* Binary_Search_Tree<Item_Type>::find(BTNode<Item_Type>* local_root, const Item_Type& target) const {
	
	if (isalpha(target[0])) {
		/*if (local_root == NULL) {
			std::string a = "";
			return &a;
		}*/
		if (target != local_root->data && target > local_root->data && local_root->left != NULL) {
			//std::cout << local_root->data; test string
			return find(local_root->left, target);
		}
			
		else if (target != local_root->data && target < local_root->data && local_root->right != NULL) {
			//std::cout << local_root->data; test string
			return find(local_root->right, target);
		}			
		else {
			//std::cout << local_root->data;
			return &local_root->code;		}
			
	}
	else {
		
		if (target != local_root->code && target[target.size()-1] == '.' && local_root->left != NULL)
			return find(local_root->left, target);
		else if (target != local_root->code && target[target.size()-1] == '_' && local_root->right != NULL)
			return find(local_root->right, target);
		else
			return &local_root->data;
	}		
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Creator : Hung Tran																				    
//         Wrapper of insert function (public field)
//////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Item_Type>
bool Binary_Search_Tree<Item_Type>::insert(const Item_Type& letter, const Item_Type& code, int index) {
	/*if (this->root == NULL) {
		return insert(this->root, item, index);
	}
	else {
		if (this->root->left == NULL) {
			return insert(this->root, item, index);
		}
		else if (this->root->right == NULL) {
			return insert(this->root, item, index);
		}
	
	}*/ //I tried to get the right root before pass it to recursive function, but It doesnt work like this :v 
	
	return insert(this->root, letter, code, index);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Creator : Hung Tran							
//  Recursive of insert function (private field)
//	Insert node to binary tree
//         Case 1: 
//		   case 2:
//               set node
//         case 3, case4: find next sub_tree and return it if case1,2 fail
//         else: return false
// Note: Still missing 13 nodes and I Don't know why ....
//////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Item_Type>
bool Binary_Search_Tree<Item_Type>::insert(BTNode<Item_Type>*& local_root,
	const Item_Type& letter, const Item_Type& code, int index){	

		if (local_root == NULL) {
			//test string
			//std::cout << local_root->data << local_root->code << "  : Z " << z << endl;
			//std::cout << letter << " vao node " << local_root->data << endl;


			local_root = new BTNode<Item_Type>(letter, code, NULL, NULL); //set node if root is null				
			return true;
		}
		else {
			//std::cout << local_root->data << local_root->code << "  :  " << z << endl;
			if (code.size() != 0) {
				std::string z(code.begin(), code.end() - 1); //get a string expect the last char for compare purpose

				//set new node to binary tree
				if (local_root->right == NULL &&
					code[code.size() - 1] == '_' 
					&& local_root->code == z) {					
					local_root->right = new BTNode<Item_Type>(letter, code, NULL, NULL);
				}
				else if (local_root->left == NULL && 
					code[code.size() - 1] == '.' &&
					local_root->code == z) {
					local_root->left = new BTNode<Item_Type>(letter, code, NULL, NULL);
				}				
				//If set new node fail this function will get next node by recursive
				else if (code[0] == '.' && local_root->left != NULL) {
					/*if (local_root->code == z && code[code.size() - 1] == '_') {
						return insert(local_root->right, letter, code, index);
					} *///this case doesnt work

					return insert(local_root->left, letter, code, index);

				}
				else if (code[0] == '_' && local_root->right != NULL) {
					/*if (code[code.size() - 1] == '.') {
						return insert(local_root->left, letter, code, index);
					} *///this case doesn't work
					return insert(local_root->right, letter, code, index);
				}
				/*if (code[0] == '.' && code[code.size() - 1] == '_' && local_root->right != NULL) {
					return insert(local_root->right, letter, code, index);
				}
				else if (code[0] == '_' && code[code.size() - 1] == '.' && local_root->right != NULL) {
					return insert(local_root->left, letter, code, index);
				}*/
				else {
					return false;								
				}					
			}			
		}		
	return true;
}


 template<typename Item_Type>
 bool Binary_Search_Tree<Item_Type>::erase(const Item_Type& item) {
	 return erase(this->root, item);
 }

template<typename Item_Type>
bool Binary_Search_Tree<Item_Type>::erase(BTNode<Item_Type>*& local_root, const Item_Type& item) {
	if (local_root == NULL) {
		return false;
	}
	else {
		if (item < local_root->data)
			return erase(local_root->left, item);
		else if (local_root->data < item)
			return erase(local_root->right, item);
		else {
			BTNode<Item_Type>* old_root = local_root;
			if (local_root->left == NULL) {
				local_root = local_root->right;
			}
			else if (local_root->right == NULL) {
				local_root = local_root->left;
			}
			else {
				replace_parent(old_root, old_root->left);
			}
			delete old_root;
			return true;
		}
	}
}

template<typename Item_Type>
void Binary_Search_Tree<Item_Type>::replace_parent(BTNode<Item_Type>*& old_root, BTNode<Item_Type>*& local_root) {
		if (local_root->right != NULL) {
			replace_parent(old_root, local_root->right);
		}
		else {
			old_root->data = local_root->data;
			old_root = local_root;
			local_root = local_root->left;
		}
}



#endif