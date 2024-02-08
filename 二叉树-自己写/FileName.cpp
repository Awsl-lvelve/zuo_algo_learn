#include<iostream>
#include<map>
#include<stack>
#include<queue>

using namespace std;


struct Node
{
	int val_;
	Node* left_;
	Node* right_;

	Node() :val_(0), left_(nullptr), right_(nullptr) {};
	Node(int value) :val_(value), left_(nullptr), right_(nullptr) {};
};

class Tree {
public:
	Node* root;

	Tree() :root(nullptr) {};
};

Node* insert_node(Node* root, int value) {
	if (root == nullptr)
	{
		return new Node(value);
	}
	else
	{
		if (root->val_ > value)
		{
			root->left_ = insert_node(root->left_, value);
		}
		else
		{
			root->right_ = insert_node(root->right_, value);
		}
	}
	return root;
}

void pre_order_traverse(Node* root);

void post_order_traverse(Node* root);

void in_order_traverse(Node* root);

void pre_order_non_recur(Node* root);

void in_order_non_recur(Node* root);

void post_order_non_recur(Node* root);

void get_tree_width(Node* root) {
	if (root == nullptr)
	{
		return;
	}
	queue<Node*>queue_node;
	queue_node.push(root);

	map<Node*, int>level_map;
	level_map.insert({ root,1 });

	int cur_level = 1;
	int cur_level_node_num = 0;

	int max_width = INT_MIN;

	while (!queue_node.empty())
	{
		Node* cur = queue_node.front();
		queue_node.pop();
		int cur_node_level = level_map.find(cur)->second;
		if (cur_level == cur_node_level)
		{
			cur_level_node_num++;
		}
		else
		{
			max_width = std::max(max_width, cur_level_node_num);
			cur_level++;
			cur_level_node_num = 1;
		}
		if (cur->left_ != nullptr) {
		}
		{
			level_map.insert({ cur->left_,cur_node_level + 1 });
			queue_node.push(cur->left_);
		}
		if (cur->right_ != nullptr)
		{
			level_map.insert({ cur->right_,cur_node_level + 1 });
			queue_node.push(cur->right_);
		}

	}
}

bool is_bst(Node* root, int& pre_val);

bool check_bst(Node* root);

bool check_bst_2(Node* root);

void process2(Node* head, vector<Node*>& in_order_list);

bool in_order_check_bst(Node* root);

bool judge_CBT(Node* root);

bool judge_FBT(Node* root);

bool judge_balence_tree(Node* root);

struct ReturnType
{
	bool is_balenced_;
	int height_;
	
	ReturnType(bool is_b,int hei):is_balenced_(is_b),height_(hei){}
};

ReturnType process(Node* x) {
	if (x==nullptr)
	{
		return ReturnType(true, 0);
	}

	ReturnType left_data = process(x->left_);
	ReturnType right_data = process(x->right_);

	int height = max(left_data.height_, right_data.height_) + 1;
	bool is_balenced = left_data.is_balenced_ && right_data.is_balenced_ && abs(left_data.height_ - right_data.height_) < 2;
	 
	return ReturnType(is_balenced, height);
}

struct ReturnTypeBST
{
	int max_;
	int min_;
	bool is_bst_;

	ReturnTypeBST(int max, int min, bool is_bst) :max_(max), min_(min), is_bst_(is_bst) {};
};

ReturnTypeBST* processBST(Node* x) {
	if (x==nullptr)
	{
		return nullptr;
	}
	ReturnTypeBST* left_data = processBST(x->left_);

	ReturnTypeBST* right_data = processBST(x->right_);


	int max=x->val_;
	int min=x->val_;

	if (left_data!=nullptr)
	{
		min =std::min(min, left_data->min_);
		max = std::max(max, left_data->max_);
	}

	if (right_data!=nullptr)
	{
		min = std::min(min, right_data->min_);
		max = std::max(max, right_data->max_);
	}
	
	//bool is_bst = true;
	//if ((left_data!=nullptr&&!left_data->is_bst_)||(left_data->max_>x->val_))
	//{
	//	is_bst = false;
	//}
	//if ((right_data!=nullptr&&!right_data->is_bst_)||(right_data->max_>x->val_))
	//{
	//	is_bst = false;
	//}


	bool is_bst = false;
	if (
		(left_data!=nullptr?(left_data->is_bst_&&left_data->max_<x->val_):true)
		&&
		(right_data!=nullptr?(right_data->is_bst_&&right_data->min_>x->val_):true)
		
		)
	{
		is_bst = true;
	}
	return new ReturnTypeBST(max,min,is_bst);

}

struct Info
{
	int height_;//树的高度
	int nodes_;//树的节点个数

	Info(int h, int n) :height_(h), nodes_(n) {};
};

bool is_F(Node* root) {
	if (root==nullptr)
	{
		return true;
	}
	Info data = f(root);

	return data.nodes_ == std::pow(2, data.height_) - 1;
}

Info f(Node* root) {
	if (root==nullptr)
	{
		return Info(0, 0);
	}

	Info left_data = f(root->left_);
	Info right_data = f(root->right_);
	int height=std::max(left_data.height_,right_data.height_)+1;
	int nodes = left_data.nodes_ + right_data.nodes_ + 1;
	return Info(height, nodes);

}

/*最低公共祖先*/
/**/

int main() {
	Tree tree;
	tree.root = new Node(1);
	tree.root->left_ = new Node(2);
	tree.root->right_ = new Node(3);

	tree.root->left_->left_ = new Node(4);
	tree.root->left_->right_ = new Node(5);

	tree.root->right_->left_ = new Node(6);
	tree.root->right_->left_->left_ = new Node(7);

	insert_node(tree.root, 8);
	insert_node(tree.root, -1);

	cout << "pre order" << endl;
	pre_order_traverse(tree.root);
	cout << endl;
	cout << "Non recursion pre order" << endl;
	pre_order_traverse(tree.root);
	cout << endl;
	cout << "Non recrsion in order" << endl;
	in_order_non_recur(tree.root);
	cout << "Non recrsion post order" << endl;

	post_order_non_recur(tree.root);
	cout << endl;

}




void pre_order_traverse(Node* root)
{
	if (root == nullptr)
	{
		return;
	}
	else
	{
		cout << root->val_ << " ";
		pre_order_traverse(root->left_);
		pre_order_traverse(root->right_);
	}
}

void  post_order_traverse(Node* root)
{
	if (root == nullptr)
	{
		return;
	}
	else
	{
		post_order_traverse(root->left_);
		post_order_traverse(root->right_);
		cout << root->val_ << " ";
	}

}

void in_order_traverse(Node* root)
{
	if (root == nullptr)
	{
		return;
	}
	in_order_traverse(root->left_);
	cout << root->val_ << " ";
	in_order_traverse(root->right_);
}

void pre_order_non_recur(Node* root)
{
	if (root != nullptr)
	{
		stack<Node*>st;
		st.push(root);

		while (!st.empty())
		{
			Node* node = st.top();
			cout << node->val_ << " ";

			st.pop();

			if (node->right_ != nullptr)
			{
				st.push(node->right_);
			}
			if (node->left_ != nullptr)
			{
				st.push(node->left_);
			}
		}

	}
}

void in_order_non_recur(Node* root)
{
	if (root != nullptr)
	{
		stack<Node*>st;
		while (!st.empty() || root != nullptr)
		{
			if (root != nullptr) {
				st.push(root);
				root = root->left_;
			}
			else
			{
				root = st.top();
				st.pop();
				cout << root->val_ << " ";
				root = root->right_;
			}
		}
	}
}

void post_order_non_recur(Node* root) {
	if (root != nullptr)
	{
		stack<Node*>s1;
		stack<Node*>s2;

		s1.push(root);

		while (!s1.empty())
		{
			root = s1.top();
			s1.pop();
			s2.push(root);

			if (root->left_ != nullptr)
			{
				s1.push(root->left_);
			}
			if (root->right_ != nullptr)
			{
				s1.push(root->right_);
			}
		}
		while (!s2.empty())
		{
			cout << s2.top()->val_ << " ";
			s2.pop();
		}
	}
}

bool check_bst(Node* root) {
	int pre_value = INT_MIN;
	is_bst(root, pre_value);
}

bool check_bst_2(Node* root)
{
	vector<Node*>in_order;
	process2(root, in_order);

	int pre_val = INT_MIN;
	for (auto c : in_order)
	{
		if (c->val_ < pre_val) {
			return false;
		}
		else
		{
			pre_val = c->val_;
		}
	}

}

void process2(Node* root, vector<Node*>& in_order_list)
{
	if (root == nullptr)
	{
		return;
	}
	process2(root->left_, in_order_list);
	in_order_list.push_back(root);
	process2(root->right_, in_order_list);
}

bool in_order_check_bst(Node* root)
{

	int pre_val = INT_MIN;

	if (root == nullptr)
	{
		return;
	}
	stack<Node*>stack;
	while (!stack.empty() || root != nullptr)
	{
		if (root != nullptr) {
			stack.push(root);
			root = root->left_;
		}
		else
		{
			root = stack.top();
			stack.pop();

			if (root->val_ < pre_val)
			{
				return false;
			}
			else
			{
				pre_val = root->val_;
			}

			root = root->right_;
		}
	}
	return	true;
}

//按照层来遍历
/*1.任意节点，有右孩子没有左孩子，则不是完全二叉树 return false
在1.不违规的条件下，首次遇到了左右不双全的情况，那么接下来所有的节点必须是叶子节点，否则不是完全二叉树
*/

bool judge_CBT(Node* root)
{
	if (root == nullptr)
	{
		return true;
	}

	queue<Node*>node_queue;//宽度优先遍历

	bool is_leaf = false;//一个开关（只有开，表示是否遇到过，左右两个节点不双全的事件）
	Node* l = nullptr;
	Node* r = nullptr;

	node_queue.push(root);//头节点进入队列

	while (!node_queue.empty())
	{
		root = node_queue.front();
		node_queue.pop();

		l = root->left_;
		r = root->right_;

		if (
			//如果遇到过孩子不双全的节点，并且，当前节点节点不是叶子节点，则为false
			(is_leaf && (l != nullptr || r != nullptr))
			||
			(l == nullptr && r != nullptr)//有右孩子无左孩子直接为false，条件1
			)
		{
			return false;
		}
	

		if (l != nullptr)node_queue.push(l);
		if (r != nullptr) node_queue.push(r);
		if (l == nullptr || r == nullptr) is_leaf = true;
	
	}
	return true;
}

//节点数目n、最大深度l,n=2^l-1
bool judge_FBT(Node* root)
{
	return false;
}

bool judge_balence_tree(Node* root)
{
	return false;
}

bool is_bst(Node* root, int& pre_value)
{
	if (root == nullptr)
	{
		return true;
	}
	bool is_left_bst = is_bst(root->left_, pre_value);
	if (!is_left_bst)
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

	return is_bst(root->right_, pre_value);
}

