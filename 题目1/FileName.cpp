/*	1.��������һ�����֣��������˻����Σ����������ֶ�������ż����
*	2. ���������������֣��������������Σ��������ֶ�������ż����
* 
*	Ҫ����ֱ��ҳ������������֣�Ҫ��ʱ�临�Ӷ�O(N)~һ��ѭ��
			�ռ临�Ӷ�O(1)~~~~~ֻ�������޼�������
*/

#include<iostream>
using namespace std;

void tst1() {
	// ��һ������
	//ѡ0����ʼ���
	int arr[] = { 1,1,1,1,3,4,3,4,4,5,5,5,5 };
	int XOR = 0;//0����ĵ��ڱ��
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
		XOR = XOR ^ arr[i];//��a^b�Ľ��
	}

	int XOR2=

}



int main() {
	
}

