/*ÿһ��������߶����ұ�С*/
#include<iostream>


struct Node 
{
	int val_;
	Node* left_;
	Node* right_;

	Node() :val_(0), left_(nullptr), right_(nullptr) {};
	Node(int val) :val_(val), left_(nullptr), right_(nullptr) {};
};

class BST {
public:
	Node* root_;


	BST() :root_(nullptr) {};
};


int pre_value = INT16_MIN;
bool isBST(Node* root) {
	if (root==nullptr)
	{
		return true;
	}
	//�������
	bool isLeftBST = isBST(root->left_);
	if (!isLeftBST)
	{
		return false;
	}

	if (root->val_ <= pre_value)
	{
		return false;
	}
	else
	{
		pre_value = root->val_;
	}

	return isBST(root->right_);

}

//Ҳ��Ҳ���������Ȼ����


void inorder_un_recur(Node* root) {

}