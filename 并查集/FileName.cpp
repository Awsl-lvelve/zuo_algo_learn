#include<iostream>
#include<string>
#include<map>
#include<set>
#include<queue>
#include<unordered_map>
#include<unordered_set>

using namespace std;

template<class T>
struct Element {
  T value_;
  Element *parent_;
};

template<class T>
struct UnionFind {
  unordered_map<T, Element<T> *> element_map_;

  unordered_map<Element<T> *, int> father_map_;

  unordered_map<Element<T> *, int> size_map_;

  UnionFind(list<T> list) {
    for (auto val:list) {
        
    }
  }

};

template<class T>
bool is_same_set(Element<T> *a,Element<T>*b) {


}

template<class T>
void union_set(Element<T>* a, Element<T>* b) {

}

//�����ҵĹ��̻��е��Ż�
//�Ѵ���ڵ�֮����;�����нڵ�ȫ��ָ�����ڵ㣬����ṹƿ������
void flatize() {

}

int main() {

}
