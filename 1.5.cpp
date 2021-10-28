/*
ID: 54672943
Вывести квадраты натуральных чисел от 1 до n, используя только O(n) операций сложения и вычитания (умножением пользоваться нельзя). n ≤ 1000.
*/
#include <iostream>

void Solve()
{
    int n, num = 0, d = 1;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        num += d;
        d += 2;
        std::cout << num << " ";
    }
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    Solve();
    return 0;
}
/*
Ассимптотика: O(n)
Память: T(1)
*/

