/*
ID: 54672943
Вывести квадраты натуральных чисел от 1 до n, используя только O(n) операций сложения и вычитания (умножением пользоваться нельзя). n ≤ 1000.
Ассимптотика: O(n)
Память: T(1)
*/
#include <iostream>

void Solve(int& num, int& d)
{
    num += d;
    d += 2;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    int n, num = 0, d = 1;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        Solve(num, d);
        std::cout << num << " ";
    }   
    std::cout << "\n";
    return 0;
}

