# Algorithms-solution: UGATY ERMOLOV IVAN
___
# Задача 1
## В первой задачи у меня вариант 5.
### ID: 53326202
## Условие:
Вывести квадраты натуральных чисел от 1 до n, используя только O(n) операций сложения и вычитания (умножением пользоваться нельзя). n ≤ 1000.
#### Здесь я использую свойство:
### n² = ∑ арифметических прогрессий(1..i), i ∈ 1 до n, 
Могу легко доказать его по мат индукции или используя геометрию.
# Вот код:
```C++
#include <iostream>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, num = 0, d = 1;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        num += d;
        d += 2;
        cout << num << " ";
    }
}
```
## Ассимптотика: O(n) 
## Память: 4 переменных типа int + 4 указателя.
## Итого: 32 байта.
___
# Задача 2
## Во второй задаче у меня вариант 2.
### ID: 53661312
## Условие:
Вычислить площадь выпуклого n-угольника, заданного координатами своих вершин. Вначале вводится количество вершин, затем последовательно целочисленные координаты всех вершин в порядке обхода по часовой стрелке. n < 1000, координаты < 10000.
#### Здесь я разбиваю n-угольник на треугольники вот так:
<a href="https://ibb.co/ySjNRN9"><img src="https://i.ibb.co/Kwv5G5P/2.png" alt="2" border="0"></a>
# Вот код:
```C++
#include <iostream>
using namespace std;

class Point
{
public:
	Point()
	{
		x = y = 0;
	}
	Point(int x, int y)
	{
		this->x = (double)(x);
		this->y = (double)(y);
	}
	int GetX()
	{
		return x;
	}
	int GetY()
	{
		return y;
	}
private:
	double x, y;
};

double GetSquareTriangles(Point& a, Point& b, Point& c) // нахожу площадь через определитель матрицы 
{
    return abs(0.5 * ((a.GetX() - c.GetX()) * (b.GetY() - c.GetY()) - (b.GetX() - c.GetX()) * (a.GetY() - c.GetY())));
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	int fn = n - 1;
	Point* points = new Point[n];
	double answer = 0;
	for (int i = 0; i < n; i++)
	{
		int x, y;
		cin >> x >> y;
		Point a(x, y);
		points[i] = a;
	}

	for (int i = 0; i < fn; i++)
	{
		answer += GetSquareTriangles(points[0], points[i], points[i + 1]);
	}

	cout << answer;
	delete[] points;
}
```
## Ассимптотика: O(n) 
## Память: 2 * n переменных типа int + указатель массива + 3 указателя для функции.
## Итого: 8 * n + 16 (байт).
___
# Задача 3
## Во третий задаче у меня вариант 1.
### ID: 53661246
## Условия:
Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. Для каждого элемента массива B[i] найдите минимальный индекс k минимального элемента массива A, равного или превосходящего B[i]: A[k] >= B[i]. Если такого элемента нет, выведите n. n, m ≤ 10000.
#### Здесь я пробигаюсь по каждому элементу массива B, нахожу, используя бинарный поиск, индекс элемента массива A, большего или равного элемнту массива B. Если не нахожу искомый элемент, возращаю значение n.
# Вот код:
```C++
#include <iostream>
using namespace std;

int BinarySearch(const int* arr, int& n, int& element)
{
	int first = 0, last = n, mid;
	while (first < last) 
	{
		mid = (first + last) >> 1;
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
	int n, m;
	cin >> n >> m;
	int* A = new int[n];
	int* B = new int[m];
	for (int i = 0; i < n; i++)
	{
		cin >> A[i];
	}
	for (int i = 0; i < m; i++)
	{
		cin >> B[i];
	}
	for (int i = 0; i < m; i++)
	{
		cout << BinarySearch(A, n, B[i]) << ' ';
	}
	delete[] A;
	delete[] B;
}
```
