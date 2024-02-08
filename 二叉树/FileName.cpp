#include<iostream>
#include<stack>
#include<queue>
#include <map>
using namespace std;

struct Node
{
	int value_;
	Node* left_;
	Node* right_;

	Node() = default;
	Node(int val) :value_(val), left_(nullptr), right_(nullptr) {};

};

class BiTree {
public:
	Node * root_;

private:
	Node* inorder_traverse_(Node *node);
	Node* post_order_traverse_(Node* node);
	Node* pre_order_traverse_(Node* node);
	Node* insert_node_(int val, Node* node);

public:
	void non_recursion_pre_order_traverse();
	void non_recursion_post_order_traverse();
	void non_recursion_in_order_traverse();
	BiTree() :root_(nullptr) {};
	void insert_node(int val);
	void create_tree(int node_num);
	void inorder_traverse();
	void post_order_traverse();
	void pre_order_traverse();
	void print_tree();
	
	int get_max_width();

	int get_max_width_no_hash();
};

Node* BiTree::inorder_traverse_(Node* node)
{
	if (node == nullptr)
	{
		return nullptr;
	}
	else
	{
		inorder_traverse_(node->left_);
		cout << node->value_ << " ";
		inorder_traverse_(node->right_);
	}
	return node;
}

Node* BiTree::post_order_traverse_(Node* node)
{
	if (node==nullptr)
	{
		return nullptr;
	}
	else
	{
		post_order_traverse_(node->left_);
		post_order_traverse_(node->right_);
		cout << node->value_ << " ";
	}
}

Node* BiTree::pre_order_traverse_(Node* node)
{
	if (node!=nullptr)
	{
		cout << node->value_ << " ";
		pre_order_traverse_(node->left_);
		pre_order_traverse_(node->right_);
	}
	return node;
}

Node* BiTree::insert_node_(int val, Node* node)
{
	if (node == nullptr)
	{
		return new Node(val);
	}
	else
	{
		if (val < node->value_)
		{
			node->left_ = insert_node_(val, node->left_);
		}
		else if (val > node->value_)
		{
			node->right_ = insert_node_(val, node->right_);
		}
	}
	return node;
}

void BiTree::non_recursion_pre_order_traverse()
{
	cout << "None recursion pre-order" << endl;
	Node* head = root_;

	if (root_!=nullptr)
	{
		stack<Node*>st;
		st.push(head);
		while (!st.empty())
		{
			head = st.top();
			cout << head->value_ << " ";
			st.pop();
			if (head->right_!=nullptr)
			{
				st.push(head->right_);
			}
			if (head->left_!=nullptr)
			{
				st.push(head->left_);
			}
		}
	}
	cout << endl;
}

void BiTree::non_recursion_post_order_traverse()
{
	cout << "None recursion post order" << endl;
	Node* head = root_;
	if (head)
	{
		stack<Node*> s1;
		stack<Node*>s2;

		s1.push(head);
		while (!s1.empty())
		{
			head = s1.top();
			s2.push(head);
			s1.pop();

			if (head->left_!=nullptr)
			{
				s1.push(head->left_);
			}
			if (head->right_!=nullptr)
			{
				s1.push(head->right_);
			}
		}
		while (!s2.empty())
		{
			cout << s2.top() ->value_<< " ";
			s2.pop();
		}
	}
	cout << endl;
}

void BiTree::non_recursion_in_order_traverse()
{
	cout << "non_recursion_in_order_traverse" << endl;
	Node* head = root_;
	
	if (head!=nullptr)
	{
		stack<Node*>st;
		while (!st.empty()||head!=nullptr)
		{
			if (head != nullptr) { 
				st.push(head);
				head = head->left_;
			}
			else
			{
				head = st.top();
				st.pop();
				cout << head->value_ << " ";
				head = head->right_;
			}
		}
	}
	cout << endl;
}

void BiTree::insert_node(int val)
{
	root_=this->insert_node_(val,root_);
}

void BiTree::create_tree(int node_num)
{
	this->root_ = new Node;
	
	for (int i = 0; i < node_num; i++)
	{
		
	}

}

void BiTree::inorder_traverse()
{
	cout << "In order traverse" << endl;
	if (this->root_ == nullptr)
	{
		return;
	}
	else
	{
		this->inorder_traverse_(root_);
	}
	cout << endl;
}

void BiTree::post_order_traverse()
{
	cout << "Post Order Traverse" << endl;
	if (root_!=nullptr)
	{
		post_order_traverse_(root_);
	}
	cout << endl;
}

void BiTree::pre_order_traverse()
{
	cout << "Pre Order Traverse" << endl;
	if (root_!=nullptr)
	{
		pre_order_traverse_(root_);
	}
	cout << endl;
}
//深度优先遍历：先序遍历
//宽度优先遍历：
//实际上也是宽度优先遍历
void BiTree::print_tree()
{
	if (root_==nullptr)
	{
		cout << "Tree is empty." << endl;
		return;
	}
	queue<Node*>node_queue;
	node_queue.push(root_);

	while (!node_queue.empty())
	{
		Node* cur = node_queue.front();
		cout << cur->value_ << " ";
		node_queue.pop();
		if (cur->left_)
		{
			node_queue.push(cur->left_);
		}
		if (cur->right_)
		{
			node_queue.push(cur->right_);
		}
	}
	cout << endl;
}

//最大宽度
int BiTree::get_max_width()
{
	if (root_==nullptr)
	{
		return 0;
	}
	queue<Node*>queue_node;
	queue_node.push(root_);

	map<Node*, int>level_map;//标识节点位于第几层
	level_map.insert({ root_,1 });//开始root在第一层

	int cur_level = 1;//当前层级
	int cur_level_nodes_num = 0;//当前层发现的节点
	int max = INT16_MIN;//初始化最大宽度

	while (!queue_node.empty())//队列里面还有元素，表示并非所有节点都遍历了阿
	{
		Node* cur = queue_node.front();//队列首端点元素
		int cur_node_level = level_map.find(cur)->second;//找到当前节点所在层级
		if (cur_level==cur_level)//想统计的层和当前层一致，表示仍在统计某一层的节点数量，还没有完成
		{
			cur_level_nodes_num++;//所以当前层级节点数目+1
		}
		else//如果不一致，则该层已经统计完了
		{
			max = std::max(max, cur_level_nodes_num);//更新最大宽度
			cur_level++;//层级加一
			cur_level_nodes_num = 1;//因为已经到另外一层了，而且能够到另外一层表示，这一层已经有节点了
		}

		if (cur->left_!=nullptr)
		{
			level_map.insert({ cur->left_,cur_node_level + 1 });//入栈更新levelmap
		}
		if (cur->right_!=nullptr)
		{
			level_map.insert({ cur->right_,cur_node_level + 1 });
		}
	}
	return max;
}

int BiTree::get_max_width_no_hash()
{

}



int main() {
	BiTree tree;
	tree.root_ = new Node(1);
	tree.root_->left_ = new Node(-22222222);
	tree.root_->right_ = new Node(3);
	tree.root_->left_->left_ = new Node(INT16_MIN);
	tree.root_->left_->right_ = new Node(7777);

	//tree.pre_order_traverse();

	//tree.inorder_traverse();

	//tree.post_order_traverse();

	//tree.non_recursion_pre_order_traverse();

	//tree.non_recursion_post_order_traverse();

	//tree.non_recursion_in_order_traverse();

	tree.print_tree();
}
