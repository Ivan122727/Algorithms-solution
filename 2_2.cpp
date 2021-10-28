/*
ID: 55601055
Вычислить площадь выпуклого n-угольника, заданного координатами своих вершин. Вначале вводится количество вершин,
затем последовательно целочисленные координаты всех вершин в порядке обхода по часовой стрелке. n < 1000, координаты < 10000.
*/
#include <iostream>
#include <vector>

void GetSquareTriangles(std::pair<int, int>& a, std::pair<int, int>& b, std::pair<int, int>& c, double& square)
{
    square = abs(((b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first))) * 0.5;
    return;
}

double Solve()
{
    int n;
    double answer = 0, square = 0;
    std::cin >> n;
    std::vector <std::pair<int, int>> points(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> points[i].first >> points[i].second;
    }

    for (int i = 1; i < n - 1; i++)
    {
        GetSquareTriangles(points[0], points[i], points[i + 1], square);
        answer += square;
    }
    return answer;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cout << Solve();
    return 0;
}
/*
Ассимптотика: O(n)
Память: T(n)
*/