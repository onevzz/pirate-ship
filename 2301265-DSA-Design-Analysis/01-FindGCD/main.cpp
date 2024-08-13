#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Find Common Factors
vector<int> common(const vector<int>& mFactors, vector<int> nFactors, int& count)
{
    vector<int> commonFactors;
    count++; // vector

    for (int i : mFactors)
    {
        auto it = find(nFactors.begin(), nFactors.end(), i);
        if (it != nFactors.end())
        {
            commonFactors.push_back(i);
            nFactors.erase(it);
            count += 2; // push, erase
        }
        count += 3; // for, auto, if
    }
    count++; // for

    return commonFactors;
}

// Compute the Product
int compute(const vector<int>& commonFactors, int& count)
{
    int gcd = 1;
    count++; // int

    for (int i : commonFactors)
    {
        gcd *= i;
        count += 2; // for, gcd
    }
    count++; // for

    return gcd;
}

// Naive Prime Factorization
vector<int> naive(int n, int& count)
{
    vector<int> factors;
    count++; // vector

    for (int i = 2; i <= n; i++)
    {
        while (n % i == 0)
        {
            factors.push_back(i);
            n /= i;
            count += 3; // while, push, divide
        }
        count += 2; // for, while
    }
    count++; // for

    return factors;
}

// Prime Listing using Sieve of Eratosthenes
vector<int> eratosthenes(int max, int& count)
{
    vector<bool> isPrime(max + 1, true);
    vector<int> primes;
    count += 2; // vector, vector

    for (int i = 2; i <= max; i++)
    {
        if (isPrime[i])
        {
            primes.push_back(i);
            for (int f = i * i; f <= max; f += i)
            {
                isPrime[f] = false;
                count += 2; // for, isPrime
            }
            count += 2; // push, for
        }
        count += 2; // for, if
    }
    count++; // for

    return primes;
}

// Prime Factorization using Sieve of Eratosthenes
vector<int> eratosthenesFactor(int n, const vector<int>& primes, int& count)
{
    vector<int> factors;
    count++; // vector

    for (int i : primes)
    {
        count++; // for

        while (n % i == 0)
        {
            factors.push_back(i);
            n /= i;
            count += 3; // while, push, divide
        }
        count++; // while

        if (n == 1)
        {
            break;
        }
        count++; // if
    }
    count++; // if || for

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

    count += 4; // vector, vector, vector, int

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

    count += 6; // int, vector, vector, vector, vector, int

    // MISSION ACCOMPLISHED
    return gcd;
}

// FindGCD3(m,n) [Recursive Euclidean Algorithm]
int FindGCD3(int m, int n, int& count)
{
    // Check for Invalid Values
    count++; // if
    if (m == 0)
        return n;
    count++; // if
    if (n == 0)
        return m;

    // Recursive Case
    count++; // if
    if (m > n)
    {
        count++; // modulo
        return FindGCD3(m % n, n, count);
    }
    else
    {
        count++; // modulo
        return FindGCD3(m, n % m, count);
    }
}

void standard()
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
}

void graph()
{

    int c = 0;
    int gcd = 1;
    int maxValue = 1;
    vector<int> c1;
    vector<int> c2;
    vector<int> c3;

    cout << "Please specify the max value that you would like to compute." << endl;
    cout << "The results will be in (m,n,gcd,operations)" << endl;
    cout << "MAX: ";
    cin >> maxValue;

    cout << "\nFindGCD1 =================================================" << endl;
    for (int i = 1; i <= maxValue; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            c = 0;
            gcd = FindGCD1(i, j, c);
            cout << i << "," << j << "," << gcd << "," << c << endl;
            c1.push_back(c);
        }
    }

    cout << "\nFindGCD2 =================================================" << endl;
    for (int i = 1; i <= maxValue; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            c = 0;
            gcd = FindGCD2(i, j, c);
            cout << i << "," << j << "," << gcd << "," << c << endl;
            c2.push_back(c);
        }
    }

    cout << "\nFindGCD3 =================================================" << endl;
    for (int i = 1; i <= maxValue; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            c = 0;
            gcd = FindGCD3(i, j, c);
            cout << i << "," << j << "," << gcd << "," << c << endl;
            c3.push_back(c);
        }
    }

    cout << "\n\nFindGCD1:";
    for (int i : c1)
        cout << " " << i;
    cout << "\n\nFindGCD2:";
    for (int i : c2)
        cout << " " << i;
    cout << "\n\nFindGCD3:";
    for (int i : c3)
        cout << " " << i;

    cout << endl;
}

int main()
{
    standard();

    return 0;
}
