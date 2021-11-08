/*
ID: 55601055
Вычислить площадь выпуклого n-угольника, заданного координатами своих вершин. Вначале вводится количество вершин,
затем последовательно целочисленные координаты всех вершин в порядке обхода по часовой стрелке. n < 1000, координаты < 10000.
Асимптотика: O(n)
Память: T(n)
*/
#include <iostream>
#include <vector>

double GetSquareTriangles(std::pair<int, int>& a, std::pair<int, int>& b, std::pair<int, int>& c)
{
    return abs(((b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first))) * 0.5;
}

double Solve(std::vector<std::pair<int, int>>& points, int n)
{
    double answer = 0;
    for (int i = 1; i < n - 1; i++)
    {
        answer += GetSquareTriangles(points[0], points[i], points[i + 1]);
    }
    return answer;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> points(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> points[i].first >> points[i].second;
    }
    std::cout << Solve(points, n) << "\n";
    return 0;
}
