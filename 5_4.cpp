/*
ID: 59080308
Дан массив неотрицательных целых 64-разрядных чисел. 
Количество чисел не больше 1000000. Отсортировать 
массив методом MSD по битам (бинарный QuickSort).
Асимптотика: T(n) = O(n log n)
Память: M(n) = O(n)
*/
#include <iostream>

int Partition(unsigned long long* arr, int start, int finish, int bitPosition) 
{
	int bitNum, i = start;
	for (int j = start; j < finish; j++) 
	{
		bitNum = (arr[j] >> bitPosition) & 1ULL;
		if (bitNum == 0) 
		{
			std::swap(arr[i++], arr[j]);
		}
	}
	return i - start;
}

void BinaryQuickSort(unsigned long long* arr, int start, int finish, int bitPosition)
{
	if (bitPosition < 0 || (finish - start) <= 1) 
	{
		return;
	}
	int leftGroupAmount = Partition(arr, start, finish, bitPosition);
	BinaryQuickSort(arr, start, leftGroupAmount + start, bitPosition - 1);
	BinaryQuickSort(arr, start + leftGroupAmount, finish, bitPosition - 1);
}

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	int n;
	std::cin >> n;
	unsigned long long* arr = new unsigned long long[n];
	for (int i = 0; i < n; i++)
	{
		std::cin >> arr[i];
	}
	int maxBitNumber = 63;
	BinaryQuickSort(arr, 0, n, maxBitNumber);
	for (int i = 0; i < n; i++) 
	{
		std::cout << arr[i] << ' ';
	}
	std::cout << "\n";
	return 0;
}
