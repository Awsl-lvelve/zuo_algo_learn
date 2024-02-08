#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<stack>
#include<map>
#include<set>

using namespace std;

struct Node
{
	int data_;
	Node* left_;
	Node* right_;

	Node(int data) :data_(data), left_(nullptr), right_(nullptr) {};
};

//n1 n2一定有公共祖先
//在该前提下，返回公共祖先

void traverse(Node* root, map<Node*, Node*>& father_map);
Node* locate_l_common_ancestor(Node* root, Node* n1, Node* n2) {
	map<Node*, Node*>father_map;

	father_map.insert(pair<Node*, Node*>(root, root));

	traverse(root, father_map);//遍历

	set<Node*>set01;

	set01.insert(n1);

	Node* cur = n1;


	while (cur != father_map.find(cur)->second)//只要不是头节点
	{
		set01.insert(cur);
		cur = father_map.find(cur)->second;
	}
	set01.insert(root);

	cur = n2;
	while (cur != father_map.find(cur)->second)
	{
		if (set01.find(cur) == set01.end())
		{
			cur = father_map.find(cur)->second;
		}
		else
		{
			break;
		}
	}
	return cur;
}

void traverse(Node* root, map<Node*, Node*>& father_map) {
	if (root == nullptr)
	{
		return;
	}

	father_map.insert({ root->left_,root });
	father_map.insert({ root->right_,root });



	traverse(root->left_, father_map);
	traverse(root->right_, father_map);

}

Node* lowest_ancestor(Node* head, Node* n1, Node* n2) {
	if (head == nullptr || head == n1 || head == n2)
	{//base case
		return head;
	}
	Node* left = lowest_ancestor(head->left_, n1, n2);
	Node* right = lowest_ancestor(head->right_, n1, n2);

	if (left != nullptr && right != nullptr)
	{
		return head;//返回自己了！
	}
	//左右两棵树，并不都有返回值,谁不为空返回谁？
	return left != nullptr ? left : right;
}

int main() {
	Node* tree = new Node(1024);
	tree->left_ = new Node(1);
	tree->right_ = new Node(2);
	tree->left_->left_ = new Node(3);
	tree->left_->left_->left_ = new Node(4);
	tree->left_->left_->right_ = new Node(5);

	tree->right_->left_ = new Node(6);
	auto p = tree->left_->left_->left_->right_ = new Node(7);

	auto q = tree->left_->left_;

	cout << lowest_ancestor(tree, p, q)->data_ << endl;
	cout << locate_l_common_ancestor(tree, p, q)->data_ << endl;

}