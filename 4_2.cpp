/*
ID: 59087595
Условие:
Дана последовательность целых чисел a1...an и натуральное число k, такое что для любых i, j: если j >= i + k, то a[i] <= a[j]. 
Требуется отсортировать последовательность. Последовательность может быть очень длинной. 
Время работы O(n * log(k)).
Доп. память O(k). Использовать слияние.
Асимптотика: T(n, k) = O(n * log(k))
Память: M(k) = O(k)
*/
#include <iostream>

template<class T>
void Merger(int lenFirst, T* firstArr, int lenSecond, T* secondArr)
{
	T* tempArr = new T[lenSecond];
	for (int i = 0; i < lenSecond; i++)
	{
		tempArr[i] = secondArr[i];
	}
	int i = lenFirst - 1;
	int j = lenSecond - 1;
	int end = lenFirst + lenSecond - 1;
	while (j > -1)
	{
		if (i > -1 && tempArr[j] < firstArr[i])
		{
			firstArr[end--] = firstArr[i--];
		}
		else
		{
			firstArr[end--] = tempArr[j--];
		}
	}
	delete[] tempArr;
}

template<class T>
void MergeSort(int right, T* arr) 
{
	if (right != 1) 
	{
		int mid = right / 2;
		MergeSort(mid, arr);
		MergeSort(right - mid, arr + mid);
		Merger(mid, arr, right - mid, arr + mid);
	}
}

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	int n, k;
	std::cin >> n >> k;
	int* firstArr = new int[2 * k];
	for (int i = 0; i < k; i++)
	{
		std::cin >> firstArr[i];
	}
	MergeSort(k, firstArr);
	int lenSecond = 0, pos = 0;
	for (int i = 0; i + k < n; i += k)
	{
		lenSecond = std::min(n - i - k, k);
		int* secondArr = new int[lenSecond];
		for (int j = 0; j < lenSecond; ++j)
		{
			std::cin >> secondArr[j];
		}
		MergeSort(lenSecond, secondArr);
		Merger(k, firstArr, lenSecond, secondArr);
		delete[] secondArr;
		for (int j = 0; j < k; ++j)
		{
			std::cout << firstArr[j] << " ";
		}
		for (int j = 0; j < lenSecond; j++)
		{
			firstArr[j] = firstArr[k + j];
		}
	}
	for (int i = 0; i < lenSecond; i++)
	{
		std::cout << firstArr[i] << " ";
	}
	delete[] firstArr;
	std::cout << "\n";
	return 0;
}
