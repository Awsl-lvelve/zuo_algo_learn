/*
找到二叉树的后继节点，一般是通过中序遍历即可。
不过代价很高，要求遍历，时间复杂度O(N)


1)X有



*/




#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<queue>

using namespace std;

struct Node
{
	int val_;
	Node* left_;
	Node* right_;
	Node* parent_;

	Node(int val) :val_(val), left_(nullptr), right_(nullptr), parent_(nullptr) {};
};

void in_order_traverse(Node *root) {
	if (root==nullptr)
	{
		return;
	}
	in_order_traverse(root->left_);
	cout << root->val_ << " ";
	in_order_traverse(root->right_);
}

Node* get_left_most_node(Node* node);
Node* get_successor_node(Node* node) {
	if (node==nullptr)
	{
		return nullptr;
	}
	if (node->right_!=nullptr)//某个节点有右边的树
	{
		return get_left_most_node(node->right_);//后继节点是最左的节点（中序遍历常识）
	}
	else//没有右树
	{
		Node* parent = node->parent_;//当前节点的父

		while (parent!=nullptr//父亲不是空，父亲是空，对应了树的最最右下方节点
			&&
			parent->left_!=node)//并且“node”不是node的父的左孩子（是右孩子）
		{
			node = parent;//node往上走
			parent = node->parent_;//parent也往上走
		}
		return	parent;
	}
}
Node* get_left_most_node(Node* node) {
	if (node==nullptr)
	{
		return node;
	}
	while (node->left_!=nullptr)
	{
		node = node->left_;
	}
	return node;

}


int main() {
	Node* root = new Node(1);
	root->left_ = new Node(2);
	root->right_ = new Node(3);

	root->left_->left_ = new Node(4);
	root->left_->left_->left_ = new Node(5);
	root->left_->left_->left_->right_ = new Node(6);

	root->right_->left_ = new Node(7);
	root->right_->left_->left_ = new Node(8);

	in_order_traverse(root);

	cout << get_successor_node(root->left_)->val_ << endl;

}