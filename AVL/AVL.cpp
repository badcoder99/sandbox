#include "AVL.h"

AVL::Node *AVL::insert(Node *ptr, int data) {
	if (ptr) {
		if (data < ptr->data) {
			ptr->left = insert(ptr->left, data);
		}
		else if (data > ptr->data) {
			ptr->right = insert(ptr->right, data);
		}
		ptr = rebalance(ptr);
	}
	else {
		ptr = new Node{data, nullptr, nullptr};
	}
	return ptr;
}

AVL::Node *AVL::remove(Node *ptr, int data) { 
	if (ptr) {
		if (data < ptr->data) {
			ptr->left = remove(ptr->left, data);
		}
		else if (data > ptr->data) {
			ptr->right = remove(ptr->right, data);
		}
		else {
			if (!ptr->left && !ptr->right) {
				delete ptr;
				ptr = nullptr;
			}
			else if (ptr->left && !ptr->right) {
				Node *tmp = ptr;
				ptr = ptr->left;
				delete tmp;
			}
			else if (!ptr->left && ptr->right) {
				Node *tmp = ptr;
				ptr = ptr->right;
				delete tmp;
			}
			else {
				Node *tmp = ptr->right;
				while (tmp->left) {
					tmp = tmp->left;
				}
				ptr->data = tmp->data;
				ptr->right = remove(ptr->right, ptr->data);
			}
				
		}
		ptr = rebalance(ptr);
	}
	return ptr;
}

AVL::Node *AVL::rotateRight(Node *ptr) {
	Node *tmp = ptr;
	ptr = tmp->left;
	tmp->left = ptr->right;
	ptr->right = tmp;
	return ptr;
}

AVL::Node *AVL::rotateLeft(Node *ptr) {
	Node *tmp = ptr;
	ptr = tmp->right;
	tmp->right = ptr->left;
	ptr->left = tmp;
	return ptr;
}

AVL::Node *AVL::rebalance(Node *ptr) {
	if (ptr) {
		int bal = balance(ptr);
		if (bal == -2) {
			int rbal = balance(ptr->right);
			if (rbal > 0) {
				ptr->right = rotateRight(ptr->right);
			}
			ptr = rotateLeft(ptr);
		}
		else if (bal == 2) {
			int lbal = balance(ptr->left);
			if (lbal < 0) {
				ptr->left = rotateLeft(ptr->left);
			}
			ptr = rotateRight(ptr);
		}
	}	
	return ptr;
}

int AVL::height(Node *ptr) {
	return (ptr ? max(height(ptr->left), height(ptr->right)) + 1 : 0);
}

int AVL::balance(Node *ptr) {
	return height(ptr->left) - height(ptr->right);
}

void AVL::print(Node *ptr, int level) {
	if (ptr->left) {
		print(ptr->left, level + 1);
	}
	else if (ptr->right) {
		cout << endl;
	}
	for (int i = 0; i < level; ++i) {
		cout << "   ";
	}
	cout << setw(4) << ptr->data << endl;
	if (ptr->right) {
		print(ptr->right, level + 1); 
	}
	else if (ptr->left) {
		cout << endl;
	}
}

AVL::AVL() : root(nullptr) { }

AVL::~AVL() {
	stack<Node*> stk;
	if (root) {
		stk.push(root);
	}
	while (!stk.empty()) {
		Node *ptr = stk.top();
		stk.pop();
		if (ptr->left) {
			stk.push(ptr->left);
		}
		if (ptr->right) {
			stk.push(ptr->right);
		}
		delete ptr;
	}			
}

void AVL::insert(int data) {
	root = insert(root, data);
}

void AVL::remove(int data) {
	root = remove(root, data);
}

void AVL::print() {
	if (root) {
		print(root, 0);
	}
	else {
		cout << "--" << endl;
	}
}
