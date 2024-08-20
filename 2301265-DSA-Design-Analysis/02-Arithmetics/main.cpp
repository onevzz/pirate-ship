#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <stack>
#include <queue>

using namespace std;

string removeWhitespaces(const string& str)
{
    string result;
    result.reserve(str.size());

    for (char chr : str)
    {
        if (!isspace(static_cast<unsigned char>(chr)))
        {
            result += chr;
        }
    }

    return result;
}

bool isBalanced(const string& str)
{
    // I'm hungry for Pizzas at 4AM right now.
    stack<char> dominos;

    for (char chr : str)
    {
        if (chr == '(' || chr == '{' || chr == '[')
        {
            dominos.push(chr);
        }

        else if (chr == ')' || chr == '}' || chr == ']')
        {
            if (dominos.empty())
                return false;

            char topping = dominos.top();
            dominos.pop();

            if ((chr == ')' && topping != '(') || (chr == '}' && topping != '{') || (chr == ']' && topping != '['))
                return false;
        }
    }

    return dominos.empty();
}

int precedence(const char& op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;

    return 0;
}

double apply(const double& a, const double& b, const char& op)
{
    switch (op)
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: throw invalid_argument("Invalid Operator");
    }

    return 0;
}

double evaluate(const string& expression)
{
    stack<double> ops;
    stack<double> values;

    auto it = expression.begin();
    while (it != expression.end())
    {
        if (isspace(*it))
        {
            it++;
            continue;
        }

        if (isdigit(*it) || *it == '.')
        {
            string no;

            while ((isdigit(*it) || *it == '.') && it != expression.end())
            {
                no += *it;
                it++;
            }

            values.push(stod(no));
        }

        else if (*it == '(')
        {
            ops.push(*it);
            it++;
        }

        else if (*it == ')')
        {
            while (!ops.empty() && ops.top() != '(') {
                double val2 = values.top(); values.pop();
                double val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(apply(val1, val2, op));
            }
            ops.pop(); // Pop the opening '('
            it++;
        }

        else if (*it == '+' || *it == '-' || *it == '*' || *it == '/')
        {
            while (!ops.empty() && precedence(ops.top()) >= precedence(*it)) {
                double val2 = values.top(); values.pop();
                double val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(apply(val1, val2, op));
            }
            ops.push(*it); // Push the operator
            it++;
        }

        else
        {
            throw invalid_argument("Invalid character in the expression");
        }
    }

    while (!ops.empty())
    {
        double val2 = values.top(); values.pop();
        double val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(apply(val1, val2, op));
    }

    return values.top();
}

void generateSubsets(const vector<int>& T) {
    stack<vector<int>> S;
    queue<vector<int>> Q;
    Q.push({});

    // Process each subset in the queue
    while (!Q.empty())
    {
        vector<int> subset = Q.front();
        Q.pop();

        // Push the current subset onto the stack
        S.push(subset);

        // Generate new subsets by adding each element to the current subset
        for (int i = 0; i < T.size(); ++i)
        {
            // Check if the element is already in the subset
            if (subset.empty() || T[i] > subset.back())
            {
                vector<int> newSubset = subset;
                newSubset.push_back(T[i]);
                Q.push(newSubset);
            }
        }
    }

    // Output all subsets
    while (!S.empty())
    {
        vector<int> subset = S.top();
        S.pop();
        cout << "{ ";
        for (int num : subset)
        {
            cout << num << " ";
        }
        cout << "}" << endl;
    }
}

void program1()
{
    string str;
    cout << "String: ";
    getline(cin, str);
    str = removeWhitespaces(str);

    if (isBalanced(str))
        cout << "Balanced. As all things should be." << endl;
    else
        cout << "Not Balanced. THANOS IS VERY ANGRY!" << endl;
}

void program2()
{
    string expression;
    cout << "Expression: ";
    getline(cin, expression);
    expression = removeWhitespaces(expression);

    double result = evaluate(expression);
    cout << "Result: " << result << endl;
}

void program3()
{
    string str;
    cout << "Enter the elements of the set separated by commas: ";
    getline(cin, str);
    str = removeWhitespaces(str);

    string item;
    vector<int> T;
    istringstream ss(str);

    while (getline(ss, item, ','))
    {
        item = removeWhitespaces(item);
        if (!item.empty())
        {
            T.push_back(stoi(item));
        }
    }

    cout << "All possible subsets are: " << endl;
    generateSubsets(T);
}

int main()
{
    program1(); cout << endl;
    program2(); cout << endl;
    program3();
    return 0;
}
