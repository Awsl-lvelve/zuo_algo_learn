/*
�ҵ��������ĺ�̽ڵ㣬һ����ͨ������������ɡ�
�������ۺܸߣ�Ҫ�������ʱ�临�Ӷ�O(N)


1)X��



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
	if (node->right_!=nullptr)//ĳ���ڵ����ұߵ���
	{
		return get_left_most_node(node->right_);//��̽ڵ�������Ľڵ㣨���������ʶ��
	}
	else//û������
	{
		Node* parent = node->parent_;//��ǰ�ڵ�ĸ�

		while (parent!=nullptr//���ײ��ǿգ������ǿգ���Ӧ�������������·��ڵ�
			&&
			parent->left_!=node)//���ҡ�node������node�ĸ������ӣ����Һ��ӣ�
		{
			node = parent;//node������
			parent = node->parent_;//parentҲ������
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