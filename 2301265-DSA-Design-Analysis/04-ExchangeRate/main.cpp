#include <iostream>
#include <vector>
#include <limits>
#include <sstream>

using namespace std;

struct Result {
    int buyDate;
    int sellDate;
    double profit;
};

Result maxCrossingProfit(const vector<double> &exchangeRates, int low, int mid, int high) {
    double leftMin = exchangeRates[mid];
    int minIndex = mid;
    for (int i = mid - 1; i >= low; i--) {
        if (exchangeRates[i] < leftMin) {
            leftMin = exchangeRates[i];
            minIndex = i;
        }
    }

    double rightMax = exchangeRates[mid + 1];
    int maxIndex = mid + 1;
    for (int j = mid + 2; j <= high; j++) {
        if (exchangeRates[j] > rightMax) {
            rightMax = exchangeRates[j];
            maxIndex = j;
        }
    }

    return {minIndex + 1, maxIndex + 1, rightMax - leftMin};
}

Result maxProfitDivideAndConquer(const vector<double> &exchangeRates, int low, int high) {
    if (low == high) {
        return {low + 1, high + 1, 0};  // No profit with one day
    }

    int mid = (low + high) / 2;

    Result leftResult = maxProfitDivideAndConquer(exchangeRates, low, mid);
    Result rightResult = maxProfitDivideAndConquer(exchangeRates, mid + 1, high);
    Result crossResult = maxCrossingProfit(exchangeRates, low, mid, high);

    if (leftResult.profit >= rightResult.profit && leftResult.profit >= crossResult.profit) {
        return leftResult;
    } else if (rightResult.profit >= leftResult.profit && rightResult.profit >= crossResult.profit) {
        return rightResult;
    } else {
        return crossResult;
    }
}

// Time Complexity: O(N^2)
void bruteForce(vector<double> &exchangeRates) {
    int n = exchangeRates.size();
    int buyDate = 0, sellDate = 0;
    double maxProfit = numeric_limits<double>::min();

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            double profit = exchangeRates[j] - exchangeRates[i];
            if (profit > maxProfit) {
                maxProfit = profit;
                buyDate = i + 1;   // 1-based index
                sellDate = j + 1;  // 1-based index
            }
        }
    }

    cout << buyDate << endl;
    cout << exchangeRates[buyDate - 1] << endl;
    cout << sellDate << endl;
    cout << exchangeRates[sellDate - 1] << endl;
    cout << maxProfit << endl;
    cout << (sellDate - buyDate) << endl;
}

// Time Complexity: O(N log N)
void divideAndConquer(vector<double> &exchangeRates) {
    int n = exchangeRates.size();
    Result result = maxProfitDivideAndConquer(exchangeRates, 0, n - 1);

    cout << result.buyDate << endl;
    cout << exchangeRates[result.buyDate - 1] << endl;
    cout << result.sellDate << endl;
    cout << exchangeRates[result.sellDate - 1] << endl;
    cout << result.profit << endl;
    cout << (result.sellDate - result.buyDate) << endl;
}

int main() {
    int n;
    cin >> n;
    cin.ignore();

    string ratesLine;
    getline(cin, ratesLine);

    double rate;
    stringstream ss(ratesLine);
    vector<double> exchangeRates;

    while (ss >> rate) {
        exchangeRates.push_back(rate);
    }

    // Brute Force Method
    cout << "/***** Brute Force Method ********************/" << endl;
    bruteForce(exchangeRates);

    // Divide and Conquer Method
    cout << "/***** Divide and Conquer Method *************/" << endl;
    divideAndConquer(exchangeRates);

    return 0;
}
