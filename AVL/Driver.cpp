#include "AVL.h"
#include <iostream>
using namespace std;

int main() {
	AVL tree;
	char cmd;
	int val;
	while (cin >> cmd) {
		switch (cmd) {
		case 'i':
			cin >> val;
			tree.insert(val);
			break;
		case 'p':
			cout << endl;
			tree.print();
			cout << endl;
			break;
		case 'r':
			cin >> val;
			tree.remove(val);
			break;
		case 'c':
			tree = AVL();
			break;
		case 'q':
			return 0;
		}
	}
}

