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

int main()
{
    int n;
    std::cin >> n;
    int dp[101][2];
    std::vector<int> pos(n + 1);
    for (int i = 1; i <= n; i++)
    {
        std::cin >> pos[i];
    }
    std::sort(pos.begin(), pos.end());
    dp[1][0] = 1e9;
    dp[1][1] = 0;
    for (int i = 2; i <= n; i++)
    {
        dp[i][0] = std::min(dp[i - 1][0], dp[i - 1][1]) + (pos[i] - pos[i - 1]);
        dp[i][1] = dp[i - 1][0];
    }
    std::cout << dp[n][0];
    return 0;
}
