/*
ID: 
Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. 
Для каждого элемента массива B[i] найдите минимальный индекс k минимального элемента массива A, равного или превосходящего B[i]: A[k] >= B[i]. Если такого элемента нет, выведите n.
n, m ≤ 10000
Асимтотика: O(n * logn)
Память: T(n + m)
*/
#include <iostream>

int BinarySearch(const int* arr, int n, int element)
{
	int mid, first = 0, last = n;
	while (first < last)
	{
		mid = (first + last) / 2;
		if (arr[mid] < element)
		{
			first = mid + 1;
		}
		else
		{
			last = mid;
		}
	}
	return (first == n || arr[first] < element) ? n : first;
}

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	int n, m;
	std::cin >> n >> m;
	int* A = new int[n];
	int* B = new int[m];
	for (int i = 0; i < n; i++)
	{
		std::cin >> A[i];
	}
	for (int i = 0; i < m; i++)
	{
		std::cin >> B[i];
	}
	for (int i = 0; i < m; i++)
	{
		std::cout << BinarySearch(A, n, B[i]) << ' ';
	}
	delete[] A;
	delete[] B;
	std::cout << '\n';
	return 0;
}
