/*
Дано N кубиков.
Требуется определить каким количеством способов можно выстроить из этих кубиков пирамиду.
Каждый вышележащий слой пирамиды должен быть строго меньше нижележащего.
Асимптотика: T(n) = O(n^2)
Память: M(n) = O(n)
ID: 65816905
*/
#include <iostream>
#include <vector>

long long GetPyramidsCount(int n)
{
    if (n <= 2)
    {
        return (n == 2) ? 1 : n;
    }
    std::vector<std::vector<long long>> dp(n);
    for (int i = 0; i < n; i++)
    {
        dp[i].resize(n, 0);
        dp[0][i] = 1;
    }
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            dp[i][j] = dp[i][j - 1];
            if (i >= j)
            {
                dp[i][j] += (i == j) ?  1 : dp[i - j - 1][j - 1];
            }
        }
    }
    return dp[n - 1][n - 1];
}

int main()
{
    int n;
    std::cin >> n;
    std::cout << GetPyramidsCount(n) << "\n";
    return 0;
}
