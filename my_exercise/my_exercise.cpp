// my_exercise.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "pch.h"
#include "BinarySearchTree.h"
#include "AVLTree.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdint>
#include <cstdio>

int compareInt(const int a, const int b) {
	if (a > b) {
		return 1;
	}
	else if (a < b) {
		return -1;
	}
	return 0;
}

void merge(int *intArray, int *tempArray, const int n) {
	int *aStart = intArray;
	int *aEnd = intArray + n / 2;
	int *bStart = intArray + n / 2;
	int *bEnd = intArray + n;

	int i = 0;
	while ((aStart != aEnd) && (bStart != bEnd)) {
		if (1 == compareInt(*aStart, *bStart)) {
			tempArray[i++] = *(bStart++);
		}
		else {
			tempArray[i++] = *(aStart++);
		}
	}
	while (aStart != aEnd) {
		tempArray[i++] = *(aStart++);
	}
	while (bStart != bEnd) {
		tempArray[i++] = *(bStart++);
	}
	for (int i = 0; i != n; ++i) {
		intArray[i] = tempArray[i];
	}
}

void mergeSort(int *intArray, int *tempArray, const int n) {
	if (n > 1) {
		mergeSort(intArray, tempArray, n / 2);
		mergeSort(intArray + n / 2, tempArray + n / 2, (n + 1) / 2);
	}

	merge(intArray, tempArray, n);
}

void mergeSort(int *intArray, const int n) {
	int *tempArray = new int[n];

	mergeSort(intArray, tempArray, n);

	delete[] tempArray;
}




int main()
{
#if 0
	int16_t aaa[] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7};
	printf("%#x\n", *(aaa + 2));
	printf("%#x\n", ((int16_t *)((int32_t *)aaa + 1))[2]);
	printf("%#x\n", ((int32_t *)((int16_t *)aaa + 2))[1]);
#endif

#if 1
	const int n = 18;
	AVLTree tree;
	int value;

	srand(time(NULL));

	/*for (int i = 0; i != n; ++i) {
		value = rand() % 10 + 1;
		std::cout << value << " : " << tree.Insert(value) << std::endl;
	}*/

	int values[] = { 64, 32, 96, 112, 80, 48, 16, 40, 24, 56, 8, 20, 22, 18, 17, 23, 21, 19 };
	for (int i = 0; i != n; ++i) {
		std::cout << values[i] << " : " << tree.Insert(values[i]) << std::endl;
	}/**/

	std::cout << "-------------" << std::endl;
	//std::cout << "remove : " << tree.Remove(32) << std::endl;
	std::cout << "-------------" << std::endl;
	tree.Print();
	std::cout << "-------------" << std::endl;
	std::cout << tree.GetNodeNum() << std::endl;
	std::cout << "-------------" << std::endl;
	std::cout << tree.GetHeight() << std::endl;
#endif










	/*const int n = 18;
	int *intArray = new int[n];

	srand(time(NULL));

	for (int i = 0; i != n; ++i) {
		intArray[i] = rand() % 1000 + 1;
	}

	for (int i = 0; i != n; ++i) {
		std::cout << intArray[i] << std::endl;
	}
	std::cout << "-------------" << std::endl;

	mergeSort(intArray, n);
	for (int i = 0; i != n; ++i) {
		std::cout << intArray[i] << std::endl;
	}

	delete[] intArray;*/
	system("PAUSE");
	return 0;
}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的秘訣: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
