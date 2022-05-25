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

int main() 
{
    int n;
    std::cin >> n;
    std::vector<std::vector<long long>> dp(n);
    if (n == 1 || n == 2 || n == 0) 
    {
        if (n == 2) 
        {
            std::cout << 1;
            return 0;
        }
        std::cout << n;
        return 0;
    }
    for (int i = 0; i < n; i++) 
    {
        dp[i].resize(n, 0);
    }
    for (int i = 0; i < n; i++) 
    {
        dp[i][0] = 0;
        dp[0][i] = 1;
    }
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n; j++) 
        {
            if (i == j)
            {
                dp[i][j] = dp[i][j - 1] + 1; 
            }
            else if (i > j) 
            {
                dp[i][j] = dp[i][j - 1] + dp[i - j - 1][j - 1];
            }
            else 
            {
                dp[i][j] = dp[i][j - 1];
            }
        }
    }
    std::cout << dp[n - 1][n - 1];
    return 0;
}
