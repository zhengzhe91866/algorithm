/*
main function���ǬO��D���x���r��j�p�A�r�Ӥj�|�v�T�ƪ�

simpleTest���Ѥ�ʿ�J���ꪺ�\��
RandomTestPush�MRandomTestArray���G�ۦP�A�u�t�b���k
*/
#include <cwchar>
#include <Windows.h>
#include <iostream>
#include <time.h>
using std::cout;
using std::cin;
using std::endl; 

#include "heap.h"

//random���d��
#define MIN_NUMBER 1
#define MAX_NUMBER 99

void simpleTest();
void RandomTestPush();
void RandomTestArray();

void outputWithDetails(const vector<int>& );
void space(int n);
int length(int n);

int main() {
	//windows
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 10;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");    // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	system("mode 650");

	srand(time(0));

	//simpleTest();
	//RandomTestPush();
	RandomTestArray();

	system("pause");
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
	cout << "�C��J�@�ӭȴN�i��@��heap sort�G" << endl;
	myData.outputWithDetails();
	//myData.outputWithArray();

	cout << endl;
	cout << "����array��iheap sort�B�z�G" << endl;
	myData2.outputWithDetails();
	//myData.outputWithArray();
}

void RandomTestPush() {
	Heap<int> myData;
	int size = rand() % MAX_NUMBER + MIN_NUMBER;
	for (int i = 0; i < size; i++)
		myData.push(1 + rand() % 99);
	cout << "�C��J�@�ӭȴN�i��@��heap sort�G" << endl;
	myData.outputWithDetails();
	//myData.outputWithArray();
}

void RandomTestArray() {
	int size = rand() % MAX_NUMBER + MIN_NUMBER;
	vector<int> temp(size);
	for (int i = 0; i < size; i++)
		temp[i] = 1 + rand() % 99;
	outputWithDetails(temp);
	Heap<int> myData(temp.begin(), temp.end()); 
	cout << "����array��iheap sort�B�z�G" << endl;
	myData.outputWithDetails();
	//myData.outputWithArray();
}

int length(int n) {
	int len = n ? 0 : 1;
	while (n) { len++, n /= 10; }
	return len;
}

void space(int n) {
	for (int i = 0; i < n; i++)
		cout << " ";
}

void outputWithDetails(const vector<int>& temp) {
	cout << "Origin tree(unsorted): " << endl;
	if (temp.size() == 0) return;

	int s = temp.size(); //�`�@���X�Ӽ�
	int pos = 0;         //�{�b������m
	int sp = 0;          //�Ʀr�������Z��
	const int maxLevel = log2(s) + 1; //tree���h��
	int n = pow(2, maxLevel) - 2;     //�Ĥ@�ӼƸ���ت��Z��

	for (int i = 0; i < maxLevel; i++) {
		int num = pow(2, i); //�o��n��X�X�ӼƦr
		space(n);
		for (int k = 0; k < num; k++) {
			int len = length(temp[pos]);
			space(length(MAX_NUMBER) - len); //�ƪ�
			cout << temp[pos];

			if (k != num - 1) space(sp); //�Ʀr�������ť�

			pos++;
			if (pos == s) break; //�Ʀr���]���F
		}
		//��W��
		sp = n;
		n /= 2;
		n--;
		cout << endl;
	}
	cout << endl;
}