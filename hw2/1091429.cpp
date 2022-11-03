/*
註解的另外一種output是也cout了array的內容
供檢查 / 除錯使用

simpleTest提供手動輸入測資的功能
*/

#include <iostream>
#include <time.h>
using std::cout;
using std::cin;
using std::endl; 

#include "heap.h"

void simpleTest();
void RandomTestPush();
void RandomTestArray();

int main() {
	srand(time(0));

	//simpleTest();
	RandomTestPush();
	RandomTestArray();
}

void simpleTest() {
	Heap<int> myData;
	vector<int> temp;
	int n, x;
	do {
		cout << "Input the number of the nodes: ";
		cin >> n;
	} while (isdigit(n));

	cout << "Input nodes: ";
	for (int i = 0; i < n; i++) {
		cin >> x;
		myData.push(x);
		temp.push_back(x);
	}
	Heap<int> myData2(temp.begin(), temp.end());

	cout << endl;
	cout << "每輸入一個值就進行一次heap sort：" << endl;
	myData.output();
	//myData.outputWithDetails();

	cout << endl;
	cout << "把整個array丟進heap sort處理：" << endl;
	myData2.output();
	//myData2.outputWithDetails();
}

void RandomTestPush() {
	Heap<int> myData;
	int size = rand() % 20 + 10;
	for (int i = 0; i < size; i++)
		myData.push(1 + rand() % 99);
	cout << "每輸入一個值就進行一次heap sort：" << endl;
	myData.output();
	//myData.outputWithDetails();
}

void RandomTestArray() {
	int size = rand() % 20 + 10;
	vector<int> temp(size);
	for (int i = 0; i < size; i++)
		temp[i] = 1 + rand() % 99;
	Heap<int> myData(temp.begin(), temp.end()); 
	cout << "把整個array丟進heap sort處理：" << endl;
	myData.output();
	//myData.outputWithDetails();
}