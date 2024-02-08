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

	// 一般的兼顾有向
	int in_;  // 入度 有多少个点，指向这里
	int out_; // 出度 该点指向多少个点

	list<Node*> nexts_; // 指向的点
	list<Edge*> edges_; // 链接指向的点和该点的边

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

// 结构 from to weight
Graph create_graph(vector<vector<int>> matrix) {
	Graph graph;
	for (int i = 0; i < matrix.size(); i++) {
		int from = matrix[i][0];
		int to = matrix[i][1];
		int weight = matrix[i][2];

		if (graph.nodes_.find(from) == graph.nodes_.end()) // 如果没有该点，则插入
		{
			graph.nodes_.insert({ from, new Node(from) });
		}
		if (graph.nodes_.find(to) == graph.nodes_.end()) //)//如果没有该点，则插入
		{
			graph.nodes_.insert({ to, new Node(to) });
		}

		Node* from_node = graph.nodes_.find(from)->second;
		Node* to_node = graph.nodes_.find(to)->second;
		Edge* new_edge = new Edge(weight, from_node, to_node);

		from_node->nexts_.push_back(to_node); //
		from_node->out_++;                    // 出度+1
		to_node->in_++;                       // 入度+1

		from_node->edges_.push_back(new_edge); // 添加边
		graph.edges_.insert(new_edge);         // 添加边到图
	}
	return graph;
}

// 图的宽度优先遍历，需要队列
void BFS(Node* node) {
	if (node == nullptr) {
		return;
	}

	// 依赖队列
	queue<Node*> node_queue;
	// set为队列服务，只要某个点进入过队列了，其一定被注册过了
	set<Node*> visited_set;

	// 将出发点放入queue 和 set中
	node_queue.push(node);
	visited_set.insert(node);

	// 当队列非空
	while (!node_queue.empty()) {
		Node* cur = node_queue.front(); // 记录cur
		node_queue.pop();               // 弹出顶端元素

		cout << cur->val_ << " "; // 打印，也阔以替换为处理行为，细节定制

		for (auto& next : cur->nexts_) // 对cur中的next_成员
		{
			if (visited_set.find(next) == visited_set.end()) // 如果没有在set中注册过
			{
				node_queue.push(next);    // 进入队列
				visited_set.insert(next); // 进入set注册
			}
		}
	}
}

// 图的深度优先遍历,需要栈
void DFS(Node* node) {
	if (node == nullptr) {
		return;
	}

	stack<Node*> nodes_stack;
	set<Node*> nodes_set; // 去重 注册

	nodes_stack.push(node); // 把当前的放进去
	nodes_set.insert(node); // 注册一下

	cout << node->val_ << " "; // 阔以自定义，不一定需要打印

	while (!nodes_stack.empty()) // 只要stack里面还有
	{
		Node* cur = nodes_stack.top(); // 获取顶端元素 A
		nodes_stack.pop();             // pop A

		for (auto& next : cur->nexts_) {
			if (nodes_set.find(next) == nodes_set.end()) // 不含有
			{
				nodes_stack.push(cur);  // 先把A 重新押回去
				nodes_stack.push(next); // 再压入B
				nodes_set.insert(next); // 再注册B

				cout << next->val_ << " "; // 处理邻居 B，或者其他行为

				break; // 不再看下面的邻居了，从while开始
			}
		}
	}
}

// 拓扑排序---编译的顺序！
list<Node*> sorted_topology(Graph graph) {
	// key 某个node*
	// value 剩余的入度
	map<Node*, int> in_map;

	// 入度为0的点才能进入该队列
	queue<Node*> zero_in_queue;

	// 先找一下第一批入度为0的点直接进入队列
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

		// 去掉cur 的影响
		// 所有cur的后续，其再in map中的入度均需要减少一个！
		for (Node*& next : cur->nexts_) {
			in_map[next]--; // 入度减少一个
			// 如果入度减少到0了 直接入队列！
			if (in_map[next] == 0) {
				zero_in_queue.push(next);
			}
		}
	}

	return result;
}

// kruskal 算法  针对无向图
//  最小生成树：
// 保证所有点联通性，并且整体边的权值最低！
// 这里最好使用并查集，但是这里是“ 替代方式 ”搞定的
// thinking：1.将所有边排序 2.再判断是否形成了环

struct MySets {
	unordered_map<Node*, list<Node*>> set_map;

	// constructor
	MySets(list<Node*> nodes) {
		for (auto& node : nodes) {
			list<Node*> set;
			set.push_back(node); // 使得每个点都各自属于一个集合
			set_map[node] = set;
		}
	}

	bool is_same_set(Node* from, Node* to) {
		auto it_from = set_map.find(from);
		auto it_to = set_map.find(to);

		if (it_from == set_map.end() || it_to == set_map.end()) {
			return false; // 节点不在任何集合中
		}
		return it_from->second == it_to->second;
	}

	void union_set(Node* from, Node* to) {
		auto it_from = set_map.find(from);
		auto it_to = set_map.find(to);
		if (it_from == set_map.end() || it_to == set_map.end()) {
			return; // 节点不在任何集合中
		}

		// 将集合合并
		it_from->second.splice(it_from->second.end(), it_to->second);

		// 把from点和to点所在的集合更新
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

// kruskal 算法
// 后面并查集会再讲--感觉下面写的一坨屎
unordered_set<Edge*> kruskalMST(Graph graph) {

	// 用来初始化mysets
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

// prim算法 针对无向图
// 挑选某个点作为开始点，以该点，解锁权重最低的边，把某个点带入，以该点开始解锁可以解锁的边，不能解锁已经被解锁的边。

unordered_set<Edge*> primMST(Graph graph) {
	// 解锁的边，进入小根堆
	// 当然，谁最小，考虑谁
	priority_queue<Edge*, vector<Edge*>, EdgeCompartor>
		priority_queue; // nmd 不会命名了

	unordered_set<Node*> node_set; // 用于注册

	unordered_set<Edge*> result; // 存储结果

	// 从任何一个点开始,主要针对不连通的图
	for (auto& node : graph.nodes_) {
		// 没有找到，就加入set
		if (node_set.find(node.second) == node_set.end()) {
		}
		node_set.insert(node.second);
		for (auto& edge : node.second->edges_) { // 由某个点，解锁所有由该点发出的边
			priority_queue.push(edge);
		}

		while (!priority_queue.empty()) {
			Edge* edge = priority_queue.top(); // 最小的边
			priority_queue.pop();              // 弹出最小的边

			Node* to_node = edge->to_; // 可能的新的点

			if (node_set.find(to_node) ==
				node_set.end()) { // 不含有！则是新的可用的点
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

// Djkstra算法
// 适用于没有负数权重的情况！
// 一定要规定出发点
//

Node*
get_min_distance_and_unselected_node(unordered_map<Node*, int> mp, unordered_set<Node*> touched_nodes);

unordered_map<Node*, int> Dijkstra1(Node* head) {
	// 从head出发，到所有点的最小距离
	// key 从head出发到key
	// value 从head出发到key的最短距离
	// 如果在表中，没有T的记录，含义是从head出发到这个点的距离为正无穷
	unordered_map<Node*, int> distance_map;

	distance_map.insert({ head, 0 });//起始节点到自己的距离

	//已经求过距离的点，在selectedndes中，以后再也不碰
	unordered_set<Node*> selected_nodes;

	//distancemap中找到最小的记录，并且该记录不能已经被选择过了！
	Node* min_node =
		get_min_distance_and_unselected_node(distance_map, selected_nodes);

	//只要min_node还有
	while (min_node != nullptr) {
		
		int distance = distance_map[min_node];

		//对min_node的所有的edge
		for (auto& edge : min_node->edges_) {
		
			Node* to_node = edge->to_;//min_node出发的到达节点
			
			//如果distancemap中还没有起始点到该点的记录
			if (distance_map.find(to_node)==distance_map.end()) {
			
				distance_map.insert({ to_node,distance + edge->weight_ });//添加起始点经由min_node到达该点的记录
			}
			
			//插入min_node的edge所指向的
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
		Node* node = entry.first;//节点
		int distance = entry.second;//起始点到该节点的距离

		if (
			touched_nodes.find(node)==touched_nodes.end()//如果该点没有被锁
			&&
			distance<min_distance//并且起始节点到该点的距离小于当前最小值
			) {
			min_node = node;//将node更新为min_node
			min_distance = distance;//更新distance
		}
	}

	return min_node;
}

// 生成样本函数
vector<vector<int>> generateSamples(int numSamples, int numVertices, int maxWeight) {
	vector<vector<int>> samples;

	// 设置随机数生成器
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> vertDist(0, numVertices - 1);
	uniform_int_distribution<> weightDist(1, maxWeight);

	// 生成样本
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
	int numSamples = 50;     // 样本数量
	int numVertices = 70;     // 图的顶点数
	int maxWeight = 100;      // 最大权重

	vector<vector<int>> samples = generateSamples(numSamples, numVertices, maxWeight);

	// 打印生成的样本
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
