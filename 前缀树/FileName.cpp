//����ǰ׺��
//��Ϊǰ׺�� ? �������ǰ׺�� ?
//���� :
//	һ���ַ������͵�����arr1����һ���ַ������͵�����arr2��
// arr2������Щ�ַ�����arr1�г��ֵ� ? ���ӡ��
// arr2������Щ�ַ�������Ϊarr1��ĳ���ַ���ǰ׺���ֵ� ? ���ӡ��
// arr2������Щ�ַ�������Ϊarr1��ĳ���ַ���ǰ׺���ֵ� ? ���ӡ ��
// arr2�г��ִ�������ǰ׺��

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
			index = chs[i] - 'a';//���ַ���Ӧ��������·

			if (node->nexts_[index]==INT_MIN) {

			}

		}

	}
};



