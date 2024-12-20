#include <iostream>
#include <sstream>
#include <climits>
#include <string>
#include <vector>

using namespace std;

// Function to find the number of ways to make change and list the combinations
// Recurrence Eq: dp[i] = dp[i] + dp[i−c] for i > 0 with dp[0] = 1
void coinChange(vector<int>& coins, int amount) {
    vector<vector<vector<int>>> dp(amount + 1);
    dp[0] = {{}};

    for (int coin : coins) {
        for (int i = coin; i <= amount; i++) {
            for (auto combination : dp[i - coin]) {
                combination.push_back(coin);
                dp[i].push_back(combination);
            }
        }
    }

    cout << "Ways to make change = " << dp[amount].size() << endl;
    for (const auto& combination : dp[amount]) {
        for (int coin : combination) {
            cout << coin << " ";
        }
        cout << endl;
    }
}

// Function to find the minimum number of coins to make change and the combination
// Recurrence Eq: dp[i] = min(dp[i], dp[i−c] + 1) for i > 0 with dp[0] = 0
void minCoinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX);
    vector<vector<int>> coinCombinations(amount + 1);
    dp[0] = 0;

    for (int coin : coins) {
        for (int i = coin; i <= amount; i++) {
            if (dp[i - coin] != INT_MAX && dp[i - coin] + 1 < dp[i]) {
                dp[i] = dp[i - coin] + 1;
                coinCombinations[i] = coinCombinations[i - coin];
                coinCombinations[i].push_back(coin);
            }
        }
    }

    if (dp[amount] == INT_MAX) {
        cout << "No solution for making change with the given coins." << endl;
    } else {
        cout << "Minimum number of coins to make change = " << dp[amount] << endl;
        for (int coin : coinCombinations[amount]) {
            cout << coin << " ";
        }
        cout << endl;
    }
}

int main() {
    int amount;
    vector<int> coins;

    string inputLine;

    // Part 0: Define the amount of money and the values of coins.
    cout << "Define the amount of money and the values of coins (separated by spaces)" << endl;
    cout << "Amount: ";
    cin >> amount;
    cin.ignore();

    cout << "Values: ";
    getline(cin, inputLine);

    int coin;
    stringstream ss(inputLine);
    while (ss >> coin) {
        coins.push_back(coin);
    }

    // Part 1: Number of ways to make change and the combinations.
    cout << "\nPart 1: Coin Change Problem" << endl;
    coinChange(coins, amount);

    // Part 2: Minimum number of coins to make change and the combination.
    cout << "\nPart 2: Minimum Coin Change Problem" << endl;
    minCoinChange(coins, amount);

    return 0;
}
