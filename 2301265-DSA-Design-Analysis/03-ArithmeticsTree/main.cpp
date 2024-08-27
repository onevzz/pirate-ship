#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <sstream>
#include <cmath>
#include <map>
#include <algorithm>
#include <fstream>

using namespace std;

struct Node {
    string value;
    Node* left;
    Node* right;
    Node(string val) : value(val), left(nullptr), right(nullptr) {}
};

class ExpressionTree {
public:
    Node* root;

    ExpressionTree(const string& expr) {
        string modifiedExpr = modifyExpression(expr);
        root = buildTree(modifiedExpr);
    }

    ~ExpressionTree() {
        destroyTree(root);
    }

    double evaluate() {
        return evaluateNode(root);
    }

private:
    unsigned long long factorial(int n) {
        if (n == 0 || n == 1) return 1;
        unsigned long long result = 1;
        for (int i = 2; i <= n; ++i) {
            result *= i;
        }
        return result;
    }

    string replaceFactorials(string expr) {
        stringstream result;
        for (size_t i = 0; i < expr.size(); ++i) {
            if (isdigit(expr[i])) {
                size_t j = i;
                while (j < expr.size() && isdigit(expr[j])) ++j;
                if (j < expr.size() && expr[j] == '!') {
                    int num = stoi(expr.substr(i, j - i));
                    result << factorial(num);
                    i = j; // Skip the '!' character
                } else {
                    result << expr.substr(i, j - i);
                    i = j - 1;
                }
            } else {
                result << expr[i];
            }
        }
        return result.str();
    }

    string modifyExpression(const string& expr) {
        string modifiedExpr;
        for (size_t i = 0; i < expr.length(); ++i) {
            if (expr[i] == '-' && (i == 0 || expr[i - 1] == '(')) {
                modifiedExpr += "0";
            }
            if (i > 0 && expr[i] == '(' && isdigit(expr[i - 1])) {
                modifiedExpr += '*';
            }
            modifiedExpr += expr[i];
        }
        return replaceFactorials(modifiedExpr);
    }

    Node* buildTree(const string& expr) {
        stack<Node*> nodes;
        stack<char> ops;

        for (size_t i = 0; i < expr.length(); ++i) {
            if (expr[i] == ' ') continue;

            if (isdigit(expr[i])) {
                string num;
                while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.')) {
                    num += expr[i++];
                }
                --i;
                nodes.push(new Node(num));
            } else if (expr[i] == '(') {
                ops.push(expr[i]);
            } else if (expr[i] == ')') {
                while (!ops.empty() && ops.top() != '(') {
                    processOperator(nodes, ops);
                }
                ops.pop();
            } else if (isOperator(expr[i])) {
                while (!ops.empty() && precedence(ops.top()) >= precedence(expr[i])) {
                    processOperator(nodes, ops);
                }
                ops.push(expr[i]);
            }
        }

        while (!ops.empty()) {
            processOperator(nodes, ops);
        }

        return nodes.top();
    }

    void processOperator(stack<Node*>& nodes, stack<char>& ops) {
        Node* right = nodes.top(); nodes.pop();
        Node* left = nodes.top(); nodes.pop();
        char op = ops.top(); ops.pop();
        Node* newNode = new Node(string(1, op));
        newNode->left = left;
        newNode->right = right;
        nodes.push(newNode);
    }

    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
    }

    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        if (op == '^') return 3;
        return 0;
    }

    double evaluateNode(Node* node) {
        if (!node->left && !node->right) {
            return stod(node->value);
        }

        double leftValue = evaluateNode(node->left);
        double rightValue = evaluateNode(node->right);

        if (node->value == "+") return leftValue + rightValue;
        if (node->value == "-") return leftValue - rightValue;
        if (node->value == "*") return leftValue * rightValue;
        if (node->value == "/") return leftValue / rightValue;
        if (node->value == "^") return pow(leftValue, rightValue);

        return 0;
    }

    void destroyTree(Node* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
};

string removeWhitespaces(const string& str){
    string result;
    result.reserve(str.size());

    for (char chr : str){
        if (!isspace(static_cast<unsigned char>(chr))){
            result += chr;
        }
    }
    return result;
}

string fixParentheses(const string& expr) {
    stack<char> parenthesesStack;
    string result = expr;

    // Traverse the expression
    for (char ch : expr) {
        if (ch == '(') {
            parenthesesStack.push(ch);
        } else if (ch == ')') {
            if (!parenthesesStack.empty() && parenthesesStack.top() == '(') {
                parenthesesStack.pop();
            } else {
                // If unmatched closing parenthesis, ignore it
                result += ch;
            }
        }
    }

    // Add the missing closing parentheses
    while (!parenthesesStack.empty()) {
        result += ')';
        parenthesesStack.pop();
    }

    return result;
}

string replaceExponentiation(const string& expr) {
    string result;
    bool inExponentiation = false;
    int base = 0;
    int exponent = 0;
    for (char ch : expr) {
        if (isdigit(ch)) {
            if (inExponentiation) {
                exponent = exponent * 10 + (ch - '0');
            } else {
                base = base * 10 + (ch - '0');
            }
        } else if (ch == '^') {
            inExponentiation = true;
        } else {
            if (inExponentiation) {
                result += '(';
                for (int i = 0; i < exponent; ++i) {
                    if (i > 0) result += '*';
                    result += to_string(base);
                }
                result += ')';
                inExponentiation = false;
            }
            result += ch;
        }
    }

    // Handle case if expression ends with an exponentiation
    if (inExponentiation) {
        result += '(';
        for (int i = 0; i < exponent; ++i) {
            if (i > 0) result += '*';
            result += to_string(base);
        }
        result += ')';
    }

    return result;
}

string insertMultiplicationSign(const string& expr) {
    string result;
    bool lastWasDigit = false;

    for (char ch : expr) {
        if (isdigit(ch)) {
            lastWasDigit = true;
            result += ch;
        } else if (ch == '(') {
            if (lastWasDigit) {
                result += '*';
            }
            result += ch;
            lastWasDigit = false;
        } else {
            result += ch;
            lastWasDigit = false;
        }
    }

    return result;
}

int main() {
    string testfile = "./customTestcase.txt";
    string inf;

    cout << "1: Load custom test file." << endl;
    cout << "2: Load lab test file." << endl;
    cout << "3: Load assign test file." << endl;
    cout << "---------------------------------" << endl;
    cin >> inf;
    if(3-stoi(inf) < 0 || 3-stoi(inf) > 2){
        return 0;
    }

    if(stoi(inf) == 2){
        testfile = "./labTestcase.txt";
    }else if(stoi(inf) == 3){
        testfile = "./testcaseGiven1.txt";
    }

    ifstream MyFile(testfile);

    string myText;

    while (getline (MyFile, myText)) {
        string expr = removeWhitespaces(myText.substr(1, myText.length() - 2));
        if(expr == ""){
            cout << "Expression " << expr << ": 0" << endl;
            continue;
        }
        // cout << replaceExponentiation(expr) << endl;

        ExpressionTree allYouCanTree(insertMultiplicationSign(fixParentheses(expr)));
        cout << "Expression " << expr << ": " << allYouCanTree.evaluate() << endl;
    }
    return 0;
}
