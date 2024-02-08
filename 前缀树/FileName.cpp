//介绍前缀树
//何为前缀树 ? 如何生成前缀树 ?
//例子 :
//	一个字符串类型的数组arr1，另一个字符串类型的数组arr2。
// arr2中有哪些字符，是arr1中出现的 ? 请打印。
// arr2中有哪些字符，是作为arr1中某个字符串前缀出现的 ? 请打印。
// arr2中有哪些字符，是作为arr1中某个字符串前缀出现的 ? 请打印 。
// arr2中出现次数最大的前缀。

#include<string>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<unordered_map>
#include<unordered_set>
#include<queue>
#include<stack>

using namespace std;

struct TrieNode {
	int pass_;
	int end_;
	int* nexts_;

	TrieNode() :pass_(0), end_(0), nexts_(new int[26]) {
		for (int i = 0; i < 26; i++) {
			nexts_[i] = INT_MIN;
		}

	};

	~TrieNode() {
		delete[] nexts_;
 	}
};

class Trie {
private:
	TrieNode* root_;
public:
	Trie() :root_(new TrieNode) {
	};

	void insert(string word) {
		if (word=="") {
			return;
		}

		const char* chs = word.c_str();

		TrieNode* node = root_;
		node->pass_++;

		int index = 0;

		for (int i = 0; chs[i] != '\0'; ++i) {
			index = chs[i] - 'a';//由字符对应该走那条路

			if (node->nexts_[index]==INT_MIN) {

			}

		}

	}
};



