#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <math.h>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include<random>

using namespace std;

struct Node;
struct Edge {
	int weight_;
	Node* from_;
	Node* to_;

	Edge(int weight, Node* from, Node* to)
		: weight_(weight), from_(from), to_(to) {
	};
};

struct Node {
	int val_;

	// һ��ļ������
	int in_;  // ��� �ж��ٸ��㣬ָ������
	int out_; // ���� �õ�ָ����ٸ���

	list<Node*> nexts_; // ָ��ĵ�
	list<Edge*> edges_; // ����ָ��ĵ�͸õ�ı�

	Node(int val) {
		this->val_ = val;
		this->in_ = 0;
		this->out_ = 0;
	}
};

struct Graph {
	map<int, Node*> nodes_;
	set<Edge*> edges_;
	Graph() = default;
};

// �ṹ from to weight
Graph create_graph(vector<vector<int>> matrix) {
	Graph graph;
	for (int i = 0; i < matrix.size(); i++) {
		int from = matrix[i][0];
		int to = matrix[i][1];
		int weight = matrix[i][2];

		if (graph.nodes_.find(from) == graph.nodes_.end()) // ���û�иõ㣬�����
		{
			graph.nodes_.insert({ from, new Node(from) });
		}
		if (graph.nodes_.find(to) == graph.nodes_.end()) //)//���û�иõ㣬�����
		{
			graph.nodes_.insert({ to, new Node(to) });
		}

		Node* from_node = graph.nodes_.find(from)->second;
		Node* to_node = graph.nodes_.find(to)->second;
		Edge* new_edge = new Edge(weight, from_node, to_node);

		from_node->nexts_.push_back(to_node); //
		from_node->out_++;                    // ����+1
		to_node->in_++;                       // ���+1

		from_node->edges_.push_back(new_edge); // ��ӱ�
		graph.edges_.insert(new_edge);         // ��ӱߵ�ͼ
	}
	return graph;
}

// ͼ�Ŀ�����ȱ�������Ҫ����
void BFS(Node* node) {
	if (node == nullptr) {
		return;
	}

	// ��������
	queue<Node*> node_queue;
	// setΪ���з���ֻҪĳ�������������ˣ���һ����ע�����
	set<Node*> visited_set;

	// �����������queue �� set��
	node_queue.push(node);
	visited_set.insert(node);

	// �����зǿ�
	while (!node_queue.empty()) {
		Node* cur = node_queue.front(); // ��¼cur
		node_queue.pop();               // ��������Ԫ��

		cout << cur->val_ << " "; // ��ӡ��Ҳ�����滻Ϊ������Ϊ��ϸ�ڶ���

		for (auto& next : cur->nexts_) // ��cur�е�next_��Ա
		{
			if (visited_set.find(next) == visited_set.end()) // ���û����set��ע���
			{
				node_queue.push(next);    // �������
				visited_set.insert(next); // ����setע��
			}
		}
	}
}

// ͼ��������ȱ���,��Ҫջ
void DFS(Node* node) {
	if (node == nullptr) {
		return;
	}

	stack<Node*> nodes_stack;
	set<Node*> nodes_set; // ȥ�� ע��

	nodes_stack.push(node); // �ѵ�ǰ�ķŽ�ȥ
	nodes_set.insert(node); // ע��һ��

	cout << node->val_ << " "; // �����Զ��壬��һ����Ҫ��ӡ

	while (!nodes_stack.empty()) // ֻҪstack���滹��
	{
		Node* cur = nodes_stack.top(); // ��ȡ����Ԫ�� A
		nodes_stack.pop();             // pop A

		for (auto& next : cur->nexts_) {
			if (nodes_set.find(next) == nodes_set.end()) // ������
			{
				nodes_stack.push(cur);  // �Ȱ�A ����Ѻ��ȥ
				nodes_stack.push(next); // ��ѹ��B
				nodes_set.insert(next); // ��ע��B

				cout << next->val_ << " "; // �����ھ� B������������Ϊ

				break; // ���ٿ�������ھ��ˣ���while��ʼ
			}
		}
	}
}

// ��������---�����˳��
list<Node*> sorted_topology(Graph graph) {
	// key ĳ��node*
	// value ʣ������
	map<Node*, int> in_map;

	// ���Ϊ0�ĵ���ܽ���ö���
	queue<Node*> zero_in_queue;

	// ����һ�µ�һ�����Ϊ0�ĵ�ֱ�ӽ������
	for (auto& node_pair : graph.nodes_) {
		in_map.insert({ node_pair.second, node_pair.second->in_ });
		if (node_pair.second->in_ == 0) {
			zero_in_queue.push(node_pair.second);
		}
	}

	list<Node*> result;

	while (!zero_in_queue.empty()) {
		Node* cur = zero_in_queue.front();
		zero_in_queue.pop();

		result.push_back(cur);

		// ȥ��cur ��Ӱ��
		// ����cur�ĺ���������in map�е���Ⱦ���Ҫ����һ����
		for (Node*& next : cur->nexts_) {
			in_map[next]--; // ��ȼ���һ��
			// �����ȼ��ٵ�0�� ֱ������У�
			if (in_map[next] == 0) {
				zero_in_queue.push(next);
			}
		}
	}

	return result;
}

// kruskal �㷨  �������ͼ
//  ��С��������
// ��֤���е���ͨ�ԣ���������ߵ�Ȩֵ��ͣ�
// �������ʹ�ò��鼯�����������ǡ� �����ʽ ���㶨��
// thinking��1.�����б����� 2.���ж��Ƿ��γ��˻�

struct MySets {
	unordered_map<Node*, list<Node*>> set_map;

	// constructor
	MySets(list<Node*> nodes) {
		for (auto& node : nodes) {
			list<Node*> set;
			set.push_back(node); // ʹ��ÿ���㶼��������һ������
			set_map[node] = set;
		}
	}

	bool is_same_set(Node* from, Node* to) {
		auto it_from = set_map.find(from);
		auto it_to = set_map.find(to);

		if (it_from == set_map.end() || it_to == set_map.end()) {
			return false; // �ڵ㲻���κμ�����
		}
		return it_from->second == it_to->second;
	}

	void union_set(Node* from, Node* to) {
		auto it_from = set_map.find(from);
		auto it_to = set_map.find(to);
		if (it_from == set_map.end() || it_to == set_map.end()) {
			return; // �ڵ㲻���κμ�����
		}

		// �����Ϻϲ�
		it_from->second.splice(it_from->second.end(), it_to->second);

		// ��from���to�����ڵļ��ϸ���
		for (auto node : it_from->second) {
			set_map[node] = it_from->second;
		}
	};
};

struct EdgeCompartor {
	bool operator()(Edge* lhs, Edge* rhs) const {
		return lhs->weight_ > rhs->weight_;
	}
};

// kruskal �㷨
// ���沢�鼯���ٽ�--�о�����д��һ��ʺ
unordered_set<Edge*> kruskalMST(Graph graph) {

	// ������ʼ��mysets
	list<Node*> init_list;
	for (auto c : graph.nodes_) {
		init_list.emplace_back(c.second);
	}
	MySets mysets(init_list);

	priority_queue<Edge*, vector<Edge*>, EdgeCompartor> priority_queue_;

	for (auto edge : graph.edges_) {
		priority_queue_.push(edge);
	}

	unordered_set<Edge*> result;

	while (!priority_queue_.empty()) {
		Edge* edge = priority_queue_.top();
		priority_queue_.pop();

		if (!mysets.is_same_set(edge->from_, edge->to_)) {
			result.insert(edge);
			mysets.union_set(edge->from_, edge->to_);
		}
	}
	return result;
}

// prim�㷨 �������ͼ
// ��ѡĳ������Ϊ��ʼ�㣬�Ըõ㣬����Ȩ����͵ıߣ���ĳ������룬�Ըõ㿪ʼ�������Խ����ıߣ����ܽ����Ѿ��������ıߡ�

unordered_set<Edge*> primMST(Graph graph) {
	// �����ıߣ�����С����
	// ��Ȼ��˭��С������˭
	priority_queue<Edge*, vector<Edge*>, EdgeCompartor>
		priority_queue; // nmd ����������

	unordered_set<Node*> node_set; // ����ע��

	unordered_set<Edge*> result; // �洢���

	// ���κ�һ���㿪ʼ,��Ҫ��Բ���ͨ��ͼ
	for (auto& node : graph.nodes_) {
		// û���ҵ����ͼ���set
		if (node_set.find(node.second) == node_set.end()) {
		}
		node_set.insert(node.second);
		for (auto& edge : node.second->edges_) { // ��ĳ���㣬���������ɸõ㷢���ı�
			priority_queue.push(edge);
		}

		while (!priority_queue.empty()) {
			Edge* edge = priority_queue.top(); // ��С�ı�
			priority_queue.pop();              // ������С�ı�

			Node* to_node = edge->to_; // ���ܵ��µĵ�

			if (node_set.find(to_node) ==
				node_set.end()) { // �����У������µĿ��õĵ�
				node_set.insert(to_node);
				result.insert(edge);

				for (auto& next_edge : to_node->edges_) {
					priority_queue.push(next_edge);
				}
			}
		}

		return result;
	};
}

// Djkstra�㷨
// ������û�и���Ȩ�ص������
// һ��Ҫ�涨������
//

Node*
get_min_distance_and_unselected_node(unordered_map<Node*, int> mp, unordered_set<Node*> touched_nodes);

unordered_map<Node*, int> Dijkstra1(Node* head) {
	// ��head�����������е����С����
	// key ��head������key
	// value ��head������key����̾���
	// ����ڱ��У�û��T�ļ�¼�������Ǵ�head�����������ľ���Ϊ������
	unordered_map<Node*, int> distance_map;

	distance_map.insert({ head, 0 });//��ʼ�ڵ㵽�Լ��ľ���

	//�Ѿ��������ĵ㣬��selectedndes�У��Ժ���Ҳ����
	unordered_set<Node*> selected_nodes;

	//distancemap���ҵ���С�ļ�¼�����Ҹü�¼�����Ѿ���ѡ����ˣ�
	Node* min_node =
		get_min_distance_and_unselected_node(distance_map, selected_nodes);

	//ֻҪmin_node����
	while (min_node != nullptr) {
		
		int distance = distance_map[min_node];

		//��min_node�����е�edge
		for (auto& edge : min_node->edges_) {
		
			Node* to_node = edge->to_;//min_node�����ĵ���ڵ�
			
			//���distancemap�л�û����ʼ�㵽�õ�ļ�¼
			if (distance_map.find(to_node)==distance_map.end()) {
			
				distance_map.insert({ to_node,distance + edge->weight_ });//�����ʼ�㾭��min_node����õ�ļ�¼
			}
			
			//����min_node��edge��ָ���
			distance_map.insert({ edge->to_, std::min(distance_map[to_node], distance + edge->weight_) });
		}
		
		selected_nodes.insert(node);
		
		min_node = get_min_distance_and_unselected_node(distance_map, 
		selected_nodes);
	}
	
	return distance_map;
}

Node*
get_min_distance_and_unselected_node(unordered_map<Node*, int> distance_map, unordered_set<Node*> touched_nodes) {
	
	Node* min_node = nullptr;

	int min_distance = INT_MAX;

	for (auto& entry : distance_map) {
		Node* node = entry.first;//�ڵ�
		int distance = entry.second;//��ʼ�㵽�ýڵ�ľ���

		if (
			touched_nodes.find(node)==touched_nodes.end()//����õ�û�б���
			&&
			distance<min_distance//������ʼ�ڵ㵽�õ�ľ���С�ڵ�ǰ��Сֵ
			) {
			min_node = node;//��node����Ϊmin_node
			min_distance = distance;//����distance
		}
	}

	return min_node;
}

// ������������
vector<vector<int>> generateSamples(int numSamples, int numVertices, int maxWeight) {
	vector<vector<int>> samples;

	// ���������������
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> vertDist(0, numVertices - 1);
	uniform_int_distribution<> weightDist(1, maxWeight);

	// ��������
	for (int i = 0; i < numSamples; ++i) {
		int startVertex = vertDist(gen);
		int endVertex = vertDist(gen);
		while (endVertex == startVertex) {
			endVertex = vertDist(gen);
		}
		int weight = weightDist(gen);
		samples.push_back({ startVertex, endVertex, weight });
	}

	return samples;
}

int main() {
	int numSamples = 50;     // ��������
	int numVertices = 70;     // ͼ�Ķ�����
	int maxWeight = 100;      // ���Ȩ��

	vector<vector<int>> samples = generateSamples(numSamples, numVertices, maxWeight);

	// ��ӡ���ɵ�����
	cout << "Generated samples:" << endl;
	for (const auto& sample : samples) {
		cout << "{";
		for (int i = 0; i < sample.size(); ++i) {
			cout << sample[i];
			if (i < sample.size() - 1) {
				cout << ", ";
			}
		}
		cout << "}" << endl;
	}


	// Create a graph,
	Graph myGraph = create_graph(samples);
	cout << "Dijkstra" << endl;
	auto res=Dijkstra1(myGraph.nodes_[0]);
	for (auto& r : res) {
		cout << r.first->val_ << " " << r.second << endl;;
	}


	//auto res = primMST(myGraph);
	//for (auto c : res) {
	//	cout << "(" << c->from_->val_ << "," << c->to_->val_ << "," << c->weight_
	//		<< ") , ";
	//}
	//cout << endl;
	//res = kruskalMST(myGraph);
	//for (auto c : res) {
	//	cout << "(" << c->from_->val_ << "," << c->to_->val_ << "," << c->weight_
	//		<< ") , ";
	//}

	// Perform operations on the graph (if needed)
	//  BFS(myGraph.nodes_.begin()->second);
	//  cout << endl;
	//  DFS(myGraph.nodes_.begin()->second);
	return 0;
}
