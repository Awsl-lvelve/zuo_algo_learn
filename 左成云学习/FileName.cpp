#include<iostream>
#include<set>
#include<map>
#include<unordered_map>
#include<unordered_set>
#include<string>

using namespace std;

struct Node
{
	string _name;
	int _age;
	float _height;
};


void print_map(const unordered_map<string,string>& map) {
	for (auto c : map) {
		cout <<sizeof(c.first) << " " << sizeof(c.second )<< endl;
		cout << typeid(c.first).name() << endl;
		cout << typeid(c.second).name() << endl;
	}
	cout << endl;
}
void print_map(const unordered_map<int,double>& map) {
	for (auto c : map) {
		cout << sizeof(c.first) << " " << sizeof(c.second) << endl;
		cout << typeid(c.first).name() << endl;
		cout << typeid(c.second).name() << endl;
	}
	cout << endl;
}

void print_map(const unordered_map<Node, int>& map) {
	for (auto c : map) {
		cout << sizeof(c.first) << " " << sizeof(c.second) << endl;
		cout << typeid(c.first).name() << endl;
		cout << typeid(c.second).name() << endl;
	}
	cout << endl;
}





int main() {
	unordered_set<int>hash_set;
	hash_set.insert(3);

	string str1 = hash_set.find(3) == hash_set.end() ? "不存在" : "存在";
	cout <<str1  << endl;
	hash_set.erase(3);
	str1 = hash_set.find(3) == hash_set.end() ? "不存在" : "存在";
	cout << str1 << endl;

	unordered_map<int, string>hash_map;
	hash_map.insert(make_pair(1, string("侯东江")));
	hash_map.insert(make_pair(1, string("曾秋琳")));//map插入时候会做检查，这一条无法插入
	hash_map.insert(make_pair(2, string("2")));

	//print_map(hash_map);
	//hash_map.erase(1);
	//print_map(hash_map);


	unordered_map<string, string>map_test;
	pair<string, string>p1 = make_pair(string("shfiahgowhgireognwiogjowehgowhgfweog"), string("侯东江22222"));
	pair<string, string>p2 = make_pair(string("sfdisehfowefhowegwsfsfsdfsdfsdfsdfsdfsdfdsfsdfsdeogj"), string("曾秋琳"));
	map_test.insert(p1);
	map_test.insert(p2);

	unordered_map<int,double>map_test_2;
	map_test_2.insert(pair<int,double>(123, 123.5));
	map_test_2.insert(pair<int, double>(1234, 1234.5));

	print_map(map_test_2);

	unordered_map<Node, int>map_tst;
	Node node1;
	node1._name = string("侯东江");
	node1._age = 24;
	node1._height = 174;

	Node node2;
	node2._name = string("曾秋琳");
	node2._age = 24;
	node2._height = 150;

	map_tst.insert(pair<Node, int>(node1, 1));
	map_tst.insert(pair<Node, int>(node2, 2));

	print_map(map_tst);






}