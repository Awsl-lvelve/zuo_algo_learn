#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<memory>

using namespace std;

/*一棵树如何变成字符串（序列化），又如何从字符串变成树（反序列化）*/

struct Node
{
	int val_;
	Node* left_;
	Node* right_;
	Node* parent_;

	Node(int val) :val_(val), left_(nullptr), right_(nullptr), parent_(nullptr) {};
};

/*先序遍历序列化*/

//序列化代码
string serialize_by_pre_order(Node* root) {
	if (root==nullptr)
	{
		return "#_";
	}
	string res = root->val_ + "_";
	res += serialize_by_pre_order(root->left_);
	res += serialize_by_pre_order(root->right_);

	return res;
}

//字符串分割
vector<string> split_by_char(string str, string charc) {
	if (str.empty())
	{
		return vector<string>();
	}
	vector<string>p;
	while(str.find(charc)!=string::npos)
	{
		int found = str.find(charc);
		p.push_back(str.substr(0,found));
		str = str.substr(found + 1);
	}
	p.push_back(str);

	return p;
}

//反序列化
Node* recon_by_pre_string(string pre_str) {
	vector<string>values = split_by_char(pre_str, "_");

	queue<string> str_queue;
	for (auto c : values) {
		str_queue.push(c);
	}
	return recon_pre_order_queue(str_queue);

}


Node* recon_pre_order_queue(queue<string>str_queue) {
	string val = str_queue.front();
	str_queue.pop();

	if (val=="#")
	{
		return nullptr;
	}

	Node* x = new Node(stoi(val));
	
	
	//下面的顺序不能乱！！！！
	x->left_ = recon_pre_order_queue(str_queue);
	x->right_ = recon_pre_order_queue(str_queue);
	return x;

}

int main() {
	





}