#include<iostream>
#include<string>
#include<vector>


using namespace std;

//暴力递归 2^N
int64_t fib(int n) {
	if (n<=0) {
		return 0;
	}
	if (n<=2&&n>0) {
		return 1;
	}
	return fib(n - 1) + fib(n - 2);
}

//依次求值O N
int64_t fib2(int n) {
	if (n<1) {
		return 0;
	}
	if (n==1||n==2) {
		return 1;
	}
	int64_t res = 1;
	int64_t pre = 1;
	int64_t tmp = 0;
	for (int i = 3; i <=n ; i++) {
		tmp = res;
		res = res + pre;
		pre = tmp;
	}
	return res;
}

vector<vector<int64_t>> matrix_power(vector<vector<int64_t>>m, int p) {
	vector<vector<int64_t>>res;
	res.resize(m.size(), vector<int64_t>(m[0].size(), 1));

	vector<vector<int64_t>>tmp = m;


}


int64_t fib3(int n) {
	if (n<1) {
		return 0;
	}
	if (n==1||n==2) {
		return 1;
	}
	vector<vector<int64_t>>base { {1,1},{0,1} };
	vector<vector<int64_t>>res=

}


int main() {
	cout << "请输入项编号：" << " ";
	string n;
	cin >> n;//100
	//cout << fib(stoi(n)) << endl;//shit
	cout << fib2(stoi(n)) << endl;//better


}