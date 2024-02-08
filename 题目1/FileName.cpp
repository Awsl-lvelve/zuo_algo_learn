/*	1.数组中有一种数字，它出现了基数次，其他的数字都出现了偶数次
*	2. 数组中有两种数字，它出现了奇数次，其他数字都出现了偶数次
* 
*	要求：请分别找出该种特殊数字，要求时间复杂度O(N)~一个循环
			空间复杂度O(1)~~~~~只能用有限几个变量
*/

#include<iostream>
using namespace std;

void tst1() {
	// 第一题的求解
	//选0，开始异或
	int arr[] = { 1,1,1,1,3,4,3,4,4,5,5,5,5 };
	int XOR = 0;//0异或别的等于别的
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		XOR = XOR ^ arr[i];
	}
	cout << XOR << endl;
}

void tst2() {
	int arr[] = { 1,0,0,0,4,4,4,4,2,2 };
	int XOR = 0;

	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		XOR = XOR ^ arr[i];//是a^b的结果
	}

	int XOR2=

}



int main() {
	
}

