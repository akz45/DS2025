#include <iostream>
#include <string>
#include <cctype>
using namespace std;
template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };
    Node* topNode;

public:
    Stack() : topNode(nullptr) {}
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
    void push(T data) {
        Node* newNode = new Node(data);
        newNode->next = topNode;
        topNode = newNode;
    }
    T pop() {
        if (isEmpty()) {
            throw "Stack is empty!";
        }
        Node* temp = topNode;
        T data = temp->data;
        topNode = topNode->next;
        delete temp;
        return data;
    }
    T top() const {
        if (isEmpty()) {
            throw "Stack is empty!";
        }
        return topNode->data;
    }
    bool isEmpty() const {
        return topNode == nullptr;
    }
};
double calculate(double num1, double num2, char op) {
    switch (op) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': 
            if (num2 == 0) {
                throw "Division by zero!";
            }
            return num1 / num2;
        default: throw "Invalid operator!";
    }
}
int getPriority(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    } else {
        return 0;
    }
}
double stringCalculator(const string& expr) {
    Stack<double> numStack;
    Stack<char> opStack; 

    for (int i = 0; i < expr.size(); ++i) {
        char c = expr[i];
        if (isspace(c)) {
            continue;
        }
        if (isdigit(c) || c == '.') {
            string numStr;
            while (i < expr.size() && (isdigit(expr[i]) || expr[i] == '.')) {
                numStr += expr[i++];
            }
            i--;
            numStack.push(stod(numStr));
        }
        else if (c == '(') {
            opStack.push(c);
        }
        else if (c == ')') {
            while (!opStack.isEmpty() && opStack.top() != '(') {
                char op = opStack.pop();
                double num2 = numStack.pop();
                double num1 = numStack.pop();
                numStack.push(calculate(num1, num2, op));
            }
            if (opStack.isEmpty() || opStack.top() != '(') {
                throw "Mismatched parentheses!";
            }
            opStack.pop();
        }

        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!opStack.isEmpty() && opStack.top() != '(' && 
                   getPriority(opStack.top()) >= getPriority(c)) {
                char op = opStack.pop();
                double num2 = numStack.pop();
                double num1 = numStack.pop();
                numStack.push(calculate(num1, num2, op));
            }
            opStack.push(c);
        }
        else {
            throw "Invalid character in expression!";
        }
    }
    while (!opStack.isEmpty()) {
        char op = opStack.pop();
        if (op == '(') {
            throw "Mismatched parentheses!";
        }
        double num2 = numStack.pop();
        double num1 = numStack.pop();
        numStack.push(calculate(num1, num2, op));
    }

    if (numStack.isEmpty() || !opStack.isEmpty()) {
        throw "Invalid expression!";
    }
    return numStack.pop();
}
int main() {
    try {
        string expr;
        cout << "请输入表达式：";
        getline(cin, expr);
        double result = stringCalculator(expr);
        cout << "计算结果：" << result << endl;
    } catch (const char* msg) {
        cout << "错误：" << msg << endl;
    }
    return 0;
}
