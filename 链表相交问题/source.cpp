//�����������ཻ��һϵ������
//����Ŀ���������������л�Ҳ�����޻��ĵ�����ͷ�ڵ�head1��head2����ʵ��һ��������������������ཻ���뷵���ཻ�� ��һ���ڵ㡣������ཻ������null
//��Ҫ���������������֮��ΪN��ʱ�临�Ӷ���ﵽ0(N)������ռ临�Ӷ���ﵽ0(1)��

#include<iostream>
#include<string>
#include<vector> 

using namespace std;


struct Node {

	Node* nexts_;
	int data_;

	Node(int data) :data_(data), nexts_(nullptr) {};
	Node() :data_(0), nexts_(nullptr) {};

};

class List {
private:
	Node* head_;
	int node_count_;

private:

public:
	List() :head_(nullptr),node_count_(0){};

	List(int n) {
		head_=new Node;
		Node* p = head_;
		node_count_ = 0;

		for (int i = 0; i < n; i++)
		{
			Node* node = new Node(i);
			p->nexts_ = node;
			p = p->nexts_;
			node_count_++;
		}
	}

	void print_list()
	{
		Node* p = head_->nexts_;
		while (p)
		{
			cout << p->data_ << " ";
			p = p->nexts_;
		}
	}

	void make_loop(int pos) {
		Node* p = this->head_;

		Node* in_point = nullptr;
		int index = 0;

		while (p)
		{
			if (index == pos)
			{
				in_point = p;
			}
			index++;

			if (p->nexts_ == nullptr)
			{
				p->nexts_ = in_point;
				return;
			}
			p = p->nexts_;
		}

	}

	Node* get_loop_in_node() {
		if (head_->nexts_==nullptr||head_->nexts_->nexts_==nullptr)
		{
			return nullptr;
		}
		Node*slow = head_->nexts_;
		Node* fast = head_->nexts_->nexts_;
		while (slow!=fast)
		{
			if (fast->nexts_ == nullptr || fast->nexts_->nexts_ ==nullptr) { return nullptr; }
			fast = fast->nexts_->nexts_;
			slow = slow->nexts_;
		}
		fast = head_;
		while (fast!=slow)
		{
			fast = fast->nexts_;
			slow = slow->nexts_;
		}
		return slow;
	}

	Node* get_last_node() {
		Node* p = head_;

		while (p)
		{
			if (p->nexts_==nullptr)
			{
				return p;
			}
			else
			{
				p = p->nexts_;
			}
		}
	}

	//�����޻�����
	Node* get_first_knot(List lst) {

		Node* last_node = get_last_node();
		Node* lst_last_node = lst.get_last_node();

		if (last_node!=lst_last_node)
		{
			return nullptr;//�����ڽ���
		}
		 
		int length = this->node_count_;
		int lst_length = lst.node_count_;

		List longer_list = length > lst_length ? length : lst_length;
		List shorter_list = length > lst_length ? lst_length : length;

		int longer = max(length, lst_length);
		int shorter = min(length, lst_length);
		int sub=longer-shorter;

		Node* shorter_ptr = shorter_list.head_->nexts_;
		Node* longer_ptr = head_->nexts_;
		for (int i = 0; i < sub; i++)
		{
			longer_ptr = longer_ptr->nexts_;
		}

		for (int i = 0; i < shorter; i++)
		{
			if (longer_ptr == shorter_ptr) {
				return longer_ptr;
			}
			else
			{
				longer_ptr = longer_ptr->nexts_;
				shorter_ptr = shorter_ptr->nexts_;
			}
		}

		


	}

	//����������
	Node* both_loop(List lst ) {
		Node* cur1 = nullptr;
		Node* cur2 = nullptr;



	}



};



int main() {
	List lst(10);
	lst.print_list();
	lst.make_loop(5);
	//lst.print_list();
	cout << endl; 
	cout << lst.get_loop_in_node()->data_ << endl;

	

}

