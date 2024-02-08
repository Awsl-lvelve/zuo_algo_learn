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

//往上找的过程会有的优化
//把代表节点之下沿途的所有节点全部指向代表节点，避免结构瓶颈现象
void flatize() {

}

int main() {

}
