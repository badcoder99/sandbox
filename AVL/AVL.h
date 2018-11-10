#pragma once
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stack>
using namespace std;

class AVL {
private:
	struct Node { int data; Node *left, *right; } *root;

	static Node *insert(Node *ptr, int data);
	static Node *remove(Node *ptr, int data);
	static Node *rotateRight(Node *ptr);
	static Node *rotateLeft(Node *ptr);
	static Node *rebalance(Node *ptr);	
	static int height(Node *ptr);
	static int balance(Node *ptr);
	static void print(Node *ptr, int level);

public:
	AVL();
	~AVL();
	void insert(int data);
	void remove(int data);
	void print();
};

	
