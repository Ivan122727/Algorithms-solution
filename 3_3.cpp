/*
В дощечке в один ряд вбиты гвоздики.
Любые два гвоздика можно соединить ниточкой.
Требуется соединить некоторые пары гвоздиков ниточками так, чтобы к каждому гвоздику была привязана хотя бы одна ниточка, а суммарная длина всех ниточек была минимальна.
Асимптотика: T(n) = O(n)
Память: M(n) = O(n)
ID: 65420291
*/
#include <algorithm>
#include <iostream>
#include <vector>

int GetMinLengthSum(std::vector<int>& pos, int n)
{
    std::sort(pos.begin(), pos.end());
    std::vector<std::pair<int, int>> dp(n + 1);
    dp[1].first = 1e9;
    dp[1].second = 0;
    for (int i = 2; i <= n; i++)
    {
        dp[i].first = std::min(dp[i - 1].first, dp[i - 1].second) + (pos[i] - pos[i - 1]);
        dp[i].second = dp[i - 1].first;
    }
    return dp[n].first;
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> pos(n + 1);
    for (int i = 1; i <= n; i++)
    {
        std::cin >> pos[i];
    }
    std::cout << GetMinLengthSum(pos, n) << "\n";
    return 0;
}
