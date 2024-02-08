#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<memory>

using namespace std;

namespace paper_folding {

	//i �㼶
	//N �ܲ㼶

	void print_process(int i, int N, bool down) {
		if (i>N)
		{
			return;
		}
		print_process(i + 1, N, true);
		cout << (down ? "��" : "͹");
		print_process(i + 1, N, false);
	}

	void print_all_folds( int N) {
		print_process(1, N, true);
	}
}

using namespace paper_folding;
int main() {
	print_all_folds(15);
}
