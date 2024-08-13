#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Find Common Factors
vector<int> common(const vector<int>& mFactors, vector<int> nFactors, int& count)
{
    vector<int> commonFactors;
    for (int i : mFactors)
    {
        auto it = find(nFactors.begin(), nFactors.end(), i);
        if (it != nFactors.end())
        {
            commonFactors.push_back(i);
            nFactors.erase(it);
        }
    }

    return commonFactors;
}

// Compute the Product
int compute(const vector<int>& commonFactors, int& count)
{
    int gcd = 1;
    for (int i : commonFactors)
    {
        gcd *= i;
    }

    return gcd;
}

// Naive Prime Factorization
vector<int> naive(int n, int& count)
{
    vector<int> factors;
    for (int i = 2; i <= n; i++)
    {
        while (n % i == 0)
        {
            factors.push_back(i);
            n /= i;
        }
    }

    return factors;
}

// Prime Listing using Sieve of Eratosthenes
vector<int> eratosthenes(int max, int& count)
{
    vector<bool> isPrime(max + 1, true);
    vector<int> primes;

    for (int i = 2; i <= max; i++)
    {
        if (isPrime[i])
        {
            primes.push_back(i);
            for (int f = i * i; f <= max; f += i)
            {
                isPrime[f] = false;
            }
        }
    }

    return primes;
}

// Prime Factorization using Sieve of Eratosthenes
vector<int> eratosthenesFactor(int n, const vector<int>& primes, int& count)
{
    vector<int> factors;
    for (int i : primes)
    {
        while (n % i == 0)
        {
            factors.push_back(i);
            n /= i;
        }
        if (n == 1)
        {
            break;
        }
    }

    return factors;
}

// FindGCD1(m,n) [Naive]
int FindGCD1(int m, int n, int& count)
{
    // STEP1 & STEP2: Find the prime factorization of m & n
    vector<int> mFactors = naive(m, count);
    vector<int> nFactors = naive(n, count);

    //STEP3: Find all the common prime factors
    vector<int> commonFactors = common(mFactors, nFactors, count);

    // STEP4: Compute the product of all the common prime factors
    int gcd = compute(commonFactors, count);

    // MISSION ACCOMPLISHED
    return gcd;
}

// FindGCD2(m,n) [Sieve of Eratosthenes]
int FindGCD2(int m, int n, int& count)
{
    int max = std::max(m, n);
    vector<int> primes = eratosthenes(max, count);

    // STEP1 & STEP2: Find the prime factorization of m & n
    vector<int> mFactors = eratosthenesFactor(m, primes, count);
    vector<int> nFactors = eratosthenesFactor(n, primes, count);

    //STEP3: Find all the common prime factors
    vector<int> commonFactors = common(mFactors, nFactors, count);

    // STEP4: Compute the product of all the common prime factors
    int gcd = compute(commonFactors, count);

    // MISSION ACCOMPLISHED
    return gcd;
}

// FindGCD3(m,n) [Recursive Euclidean Algorithm]
int FindGCD3(int m, int n, int& count)
{
    // Check for Invalid Values
    if (m == 0)
        return n;
    if (n == 0)
        return m;

    // Recursive Case
    if (m > n)
        return FindGCD3(m % n, n, count);
    else
        return FindGCD3(m, n % m, count);
}

int main()
{
    int m, n;
    int c1 = 0, c2 = 0, c3 = 0;

    cout << "Please specify integers m and n that you would like to find the greatest common divisor of." << endl;
    cout << "m: ";
    cin >> m;
    cout << "n: ";
    cin >> n;

    int gcd1 = FindGCD1(m, n, c1);
    int gcd2 = FindGCD2(m, n, c2);
    int gcd3 = FindGCD3(m, n, c3);

    cout << "FindGCD1: " << gcd1 << ", Operations Executed: " << c1 << endl;
    cout << "FindGCD2: " << gcd2 << ", Operations Executed: " << c2 << endl;
    cout << "FindGCD3: " << gcd3 << ", Operations Executed: " << c3 << endl;

    return 0;
}
