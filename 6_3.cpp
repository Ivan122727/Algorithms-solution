/*
ID: 55369386
На вокзале есть некоторое количество тупиков, куда прибывают электрички. 
Этот вокзал является их конечной станцией. Дано расписание движения электричек, в котором для каждой электрички указано время ее прибытия, 
а также время отправления в следующий рейс. Электрички в расписании упорядочены по времени прибытия. Когда электричка прибывает, 
ее ставят в свободный тупик с минимальным номером. При этом если электричка из какого-то тупика отправилась в момент времени X, то электричку,
которая прибывает в момент времени X, в этот тупик ставить нельзя, а электричку, прибывающую в момент X+1 — можно.
В данный момент на вокзале достаточное количество тупиков для работы по расписанию. Напишите программу, которая по данному расписанию определяет,
какое минимальное количество тупиков требуется для работы вокзала.
Асимптотика: O(n)
Память: O(n)
*/
#include <iostream>
#include <vector>
#include <queue>

int Solve(std::priority_queue<int, std::vector<int>, std::greater<int>> deadEnds, int ans, int arr, int dep)
{       
    if (deadEnds.top() < arr)
    {
            deadEnds.pop();  // если есть свободный тупик
    }
    deadEnds.push(dep);
    if (deadEnds.size() > ans)
    {
        ans = deadEnds.size();
    }
    return ans;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    int n, arr, dep, ans = 1;;
    std::cin >> n;

    std::priority_queue<int, std::vector<int>, std::greater<int>> deadEnds;
    std::cin >> arr >> dep;
    deadEnds.push(dep);
    for (int i = 1; i < n; i++)
    {
        std::cin >> arr >> dep;
        ans = Solve(deadEnds, ans, arr, dep);
    }
    std::cout << ans << '\n';
    return 0;
}
