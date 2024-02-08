#include<iostream>
#include<string>

using namespace std;

struct Node
{
	int data_;
	Node* nexts_;

	Node() = default;
	Node(int val) {
		this->data_ = val;
		this->nexts_ = nullptr;
	}
};

class LinkList
{
public:
	LinkList(int node_num);
	void clear_list();

	void insert_node(int val, int pos);
	void delete_node(int pos);
	void modi_node(int pos, int val);

	void print_list();
	
	void make_a_circle(int pos);

	Node* get_meet_point();

	Node* head;
	int node_num;

};

void LinkList::clear_list()
{
	Node* p = this->head;
	Node* q = p->nexts_;
	
	while (p->nexts_!=nullptr)
	{
		delete p;
		p = q;
		q = q->nexts_;
		node_num--;
	}
	
}

LinkList::LinkList(int node_num)
{
	this->head = new Node;
	this->node_num = node_num;
	Node* cur = head;

	for (int i = 0; i < node_num; i++)
	{
		Node* node = new Node(i);
		
		cur->nexts_ = node;
		
		cur = node;
	}

	cur->nexts_ = nullptr;
}

void LinkList::insert_node(int val, int pos)
{
	if (pos<0)
	{
		return;
	}
	if (pos>node_num+1)
	{
		return;
	}

	Node* p = this->head;

	Node* node = new Node(val);

	for (int i = 0; i < pos; i++)
	{
		p = p->nexts_;
	}
	node->nexts_ = p->nexts_;
	p->nexts_ = node;
	node_num++;
}

void LinkList::delete_node(int pos)
{
	if (pos<0)
	{
		return;
	}
	if (pos>node_num-1)
	{
		return;
	}

	Node* pre = this->head;
	Node* p=this->head->nexts_;
	
	for (int i = 0; i < pos; i++)
	{
		pre = pre->nexts_;
		p = p->nexts_;
	}

	pre->nexts_ = p->nexts_;
	
	delete p;
	node_num--;
}

void LinkList::modi_node(int pos, int val)
{
	if (pos<0)
	{
		return;
	}
	if (pos>node_num-1)
	{
		return;
	}

	Node* p = this->head->nexts_;
	for (int i = 0; i <=pos; i++)
	{
		p = p->nexts_;
	}
	p->data_ = val;

}

void LinkList::print_list()
{
	Node* p = this->head->nexts_;
	int i = 0;
	while (i<node_num)
	{
		cout << p->data_ << " ";
		p = p->nexts_;
		i++;
	}
	cout << endl;
}

void LinkList::make_a_circle(int pos)
{
	if (pos < 0)
	{
		return;
	}
	if (pos > node_num - 1)
	{
		return;
	}
	Node* p=this->head->nexts_;

	int i = 0;
	while(i<pos)
	{
		p = p->nexts_;
		i++;
	}

	Node* rear = this->head->nexts_;
	while (rear->nexts_!=nullptr)
	{
		rear = rear->nexts_;
	}

	rear->nexts_ = p;

}

Node* LinkList::get_meet_point()
{
	if (head==nullptr||head->nexts_==nullptr||head->nexts_->nexts_==nullptr)
	{
		return nullptr;
	}
	cout << "Herer" << endl;

	if (head == nullptr ||//不存在表
		head->nexts_==nullptr||//空表
		head->nexts_->nexts_==nullptr//只有一个元素
		)
	{
		return nullptr;
	}

	Node *slow = head->nexts_;
	Node *fast= head->nexts_->nexts_;

	while (slow!=fast||fast->nexts_!=nullptr||fast->nexts_->nexts_!=nullptr)//如果相遇
	{
		fast = fast->nexts_->nexts_;//fast移动两个
		slow = slow->nexts_;//slow移动一个
	}
	if (fast!=slow)
	{
		return nullptr;
	}

	fast = head->nexts_; //则fast回到head->next
	while (fast!=slow)
	{
		fast = fast->nexts_;
		slow = slow->nexts_;

		cout << "fast: " << fast->data_ << " next: " << slow->data_ << endl;

	}
	return fast;
}


int main() {
	LinkList list(7);
	list.print_list();

	//list.delete_node(7);
	//list.print_list();

	//list.insert_node(114, 0);
	//list.print_list();

	//list.clear_list();
	//list.print_list();

	list.make_a_circle(4);
	list.print_list();

	Node* ptr = list.get_meet_point();
	cout << ptr->data_ << endl;

	return 0;
}