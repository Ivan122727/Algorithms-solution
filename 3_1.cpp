/*
ID: 59077080	
Условие:
Даны неотрицательные целые числа n, k и массив целых чисел из диапазона [0..109] размера n.
Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k ∈[0..n-1] в отсортированном массиве.
Напишите нерекурсивный алгоритм.
Требования к дополнительной памяти: O(n).
Требуемое среднее время работы: O(n).
Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
Описание для случая прохода от начала массива к концу:
Выбирается опорный элемент.
Опорный элемент меняется с последним элементом массива.
Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного. Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы. Последним элементом лежит опорный.
Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j. Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.
Асимптотика: T(n) = O(n)
Память: M(n) = O(n)
*/
#include <iostream>

template<class T>
void SelectPivot(T* arr, int left, int right)
{
    if (arr[left] > arr[(left + right) / 2])
    {
        if(arr[left] < arr[right - 1])
        {
            std::swap(arr[left], arr[right - 1]);
        }
        else if(arr[(left + right) / 2] > arr[right - 1])
        {
            std::swap(arr[(left + right) / 2], arr[right - 1]);
        }
    }
    else
    {
        if (arr[left] > arr[right - 1])
        {
            std::swap(arr[left], arr[right - 1]);
        }
        else if(arr[(left + right) / 2] < arr[right - 1])
        {
            std::swap(arr[(left + right) / 2], arr[right - 1]);
        }
    }
}

template<class T>
int Partition(T* arr, int left, int right) 
{
    if (right - left <= 1)
    {
        return left;
    }
    SelectPivot(arr, left, right);
    T pivot = arr[right - 1];
    int i = left, j = left;
    while (j < right - 1) 
    {
        if (!(pivot < arr[j]))
        { 
            std::swap(arr[i++], arr[j++]);
        }
        else
        {
            j++;
        }
    }
    std::swap(arr[i], arr[j]);
    return i;
}

template<class T>
T OrdinalStatistics(T* arr, int len, int k) 
{
    int part, left = 0, right = len;
    while (true) 
    {
        part = Partition(arr, left, right);
        if(part == k) 
        {
            return arr[part];
        }
        else if(part > k)
        {
            right = part;
        }
        else
        {
            left = part + 1;
        }
    }
}

int main() 
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    unsigned int n, k;
    std::cin >> n >> k;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) 
    {
        std::cin >> arr[i];
    }
    std::cout << OrdinalStatistics(arr, n, k) << "\n";
    delete[] arr;
    return 0;
}
