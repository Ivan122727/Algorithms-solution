# Algorithms-solution: Module 1
___
# Задача 1
## В первой задачи у меня вариант 5.
### ID: 54672943
## Условие:
Вывести квадраты натуральных чисел от 1 до n, используя только O(n) операций сложения и вычитания (умножением пользоваться нельзя). n ≤ 1000.
#### Здесь я использую свойство:
###  расстояние между квадратами чисел - четные числа.
### 1 -> 3 = 4 -> 5 = 9 -> 7 = 16 -> 9 = 25 ... (n - 1)² -> 2 * n - 1 = n²  
# Вот код:
```C++
#include <iostream>
using namespace std;

void Solve()
{
    int n, num = 0, d = 1;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        num += d;
        d += 2;
        cout << num << " ";
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    Solve();
}

```
## Ассимптотика: O(n) 
## Память: 3 переменных типа int + 3 указателя.
## Итого: 24 байта.
___
# Задача 2
## Во второй задаче у меня вариант 2.
### ID: 54673214
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
	Point(): x(0), y(0){};
	
	Point(int& x, int& y)
	{
		this->x = x;
		this->y = y;
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
	int x, y;
};

double GetSquareTriangles(Point& a, Point& b, Point& c) // нахожу площадь через определитель матрицы 
{
    return abs(0.5 * ((a.GetX() - c.GetX()) * (b.GetY() - c.GetY()) - (b.GetX() - c.GetX()) * (a.GetY() - c.GetY())));
}

double Solve()
{
    int n, x, y;
	cin >> n;
	Point* points = new Point[n];
	double answer = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> x >> y;
		Point a(x, y);
		points[i] = a;
	}
	for (int i = 0; i < n - 1; i++)
	{
		answer += GetSquareTriangles(points[0], points[i], points[i + 1]);
	}
	delete[] points;
	return answer;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout << Solve();
}
```
## Ассимптотика: O(n) 
## Память: 2 * n переменных типа int + указатель массива + 2 переменных типа int + переменная типа double + 3 указателя + 3 указателя для функции.
## Итого: 8 * n + 48 (байт).
___
# Задача 3
## В третий задаче у меня вариант 1.
### ID: 54673301
## Условия:
Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. Для каждого элемента массива B[i] найдите минимальный индекс k минимального элемента массива A, равного или превосходящего B[i]: A[k] >= B[i]. Если такого элемента нет, выведите n. n, m ≤ 10000.
#### Здесь я пробигаюсь по каждому элементу массива B, нахожу, используя бинарный поиск, индекс элемента массива A, большего или равного элементу массива B. Если не нахожу искомый элемент, возращаю значение n.
# Вот код:
```C++
#include <iostream>
using namespace std;

int BinarySearch(const int* arr, int& n, int& element)
{
	int mid, first = 0, last = n;
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

void Solve()
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

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	Solve();
	
}
```
## Ассимптотика: O(n * log n)
## Память: 2 указателя для массива + (n + m + 2) переменных типа int + 5 указателей для функции + 3 перемменых типа int внутри функции.
## Итого: (n + m) * 4 + 48 (байт)
___
# Задача 4
## В четвертой задаче у меня вариант 1.
### ID: 55366866
## Условия:
Реализовать очередь с динамическим зацикленным буфером. Обрабатывать команды push back и pop front.  
Каждая команда задаётся как 2 целых числа: a b.  
a = 2 - pop front  
a = 3 - push back  
Если дана команда pop front, то число b - ожидаемое значение.  
Если команда pop front вызвана для пустой структуры данных, то ожидается “-1”.
# Вот код:
```C++
#include <iostream>
using namespace std;

class Queue {
public:
    
    Queue() : bufferSize(1), head(0), tail(0), countElem(0)
    {
        buffer = new int[bufferSize];
    }

    Queue(int& size) : bufferSize(size << 1), head(size), tail(size), countElem(0)
    {
        buffer = new int[bufferSize];
    }
    
    ~Queue()
    {
        delete[] buffer;
    }

    bool empty()
    {
        return head == tail;
    }

    void IncreaseBuffer()
    {
        bufferSize <<= 1;
        int* temp = new int[bufferSize];
        for (int i = 0; i < countElem; i++)
        {
            temp[i] = buffer[head + i];
        }
        delete[] buffer;
        buffer = temp;
        head = 0;
        tail = countElem + 1;
    }

    void ReduceBuffer()
    {
        bufferSize >>= 1;
        int* temp = new int[bufferSize];
        for (int i = 0; i < countElem; i++)
        {
            temp[i] = buffer[head + i];
        }
        delete[] buffer;
        buffer = temp;
        head = 0;
        tail = countElem + 1;
    }
    void push_back(int& a)
    {
        countElem++;
        if (countElem == bufferSize)
        {
            IncreaseBuffer();
        }
        buffer[tail] = a;
        tail = (tail + 1) % bufferSize;

    }

    int pop_front()
    {
        if (countElem << 2 == bufferSize)
        {
            ReduceBuffer();
        }
        int result = buffer[head];
        head = (head + 1) % bufferSize;
        return result;
    }

private:
    int* buffer;
    int bufferSize;
    int head;
    int tail;
    int countElem;
};

string Solve()
{
    int countOper, oper, num;
    cin >> countOper;
    Queue arr(countOper);
    for (int i = 0; i < countOper; i++)
    {
        cin >> oper >> num;
        switch (oper)
        {
        case 3:
            arr.push_back(num);
            break;
        default:
            if ((arr.empty() && num != -1) || (!arr.empty() && arr.pop_front() != num))
            {
                return "NO";
            }
            break;
        }
    }
    return "YES";
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout << Solve();
}


```
## Ассимптотика: O(n) 
## Память:  n + 3 переменных типа int + указатель класса + 3 переменных типа int.
## Итого: n + 28 (байт).
___
# Задача 5
## В пятой задаче у меня вариант 3.
### ID: 54883135
## Условия:
Дана последовательность N прямоугольников различной ширины и высоты (wi, hi). Прямоугольники расположены, начиная с точки (0, 0), на оси ОХ вплотную друг за другом (вправо).
Требуется найти M - площадь максимального прямоугольника (параллельного осям координат), который можно вырезать из этой фигуры  
В первой строке задано число N (1 ≤ N ≤ 10000).  
Далее идет N строк. В каждой строке содержится два числа width и height: ширина и высота i-го прямоугольника.  
(0 < width ≤ 10000, 0 ≤ height ≤ 10000)
#### Здесь я для каждого элемента нахожу участок где он ниже других.
# Вот код:
```C++
#include <iostream>
#include <vector>
using namespace std;

int Solve(vector <int>& temp, vector <pair<int, int>>& rectangles, vector <pair<int, int>>& lens, int& n)
{
	int k, ans = 0;
	for (int i = 0; i < n; i++)
	{
		k = 0;
		while (i != k && rectangles[i - k - 1].second >= rectangles[i].second)
		{
			k++;
		}
		lens[i].first = temp[i - k] - rectangles[i - k].first;
	}
	for (int i = n - 1; i >= 0; i--)
	{
		k = 0;
		while (i + k != n - 1 && rectangles[i + k + 1].second >= rectangles[i].second)
		{
			k++;
		}
		lens[i].second = temp[i + k];
	}
	for (int i = 0; i < n; i++)
	{
		ans = max(ans, rectangles[i].second * (lens[i].second - lens[i].first));
	}
	return ans;
}





int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector <int> temp(n); // доп массив, чтобы можно было за 1 операцию найти сумму на определенном участке.
	vector <pair<int, int>> rectangles(n);
	vector <pair<int, int>> lens(n); // Координаты участка где i - прямоугольник ниже остальных pair<начало, конец>
	cin >> rectangles[0].first >> rectangles[0].second;
	temp[0] = rectangles[0].first;
	for (int i = 1; i < n; i++)
	{
		cin >> rectangles[i].first >> rectangles[i].second;
		temp[i] = temp[i - 1] + rectangles[i].first;
	}
	cout << Solve(temp, rectangles, lens, n);
	temp.clear();
	temp.shrink_to_fit();
	rectangles.clear();
	rectangles.shrink_to_fit();
	lens.clear();
	lens.shrink_to_fit();
}
```
## Ассимптотика: O(n) 
#### Память:  переменная типа int + указатель + 3 указателя на векторы + 5 * n переменных int + 6 указателей для функций + 2 переменных типа int внутри функции.
## Итого: 20 * n + 52 (байт).
___
