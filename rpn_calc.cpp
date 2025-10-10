#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <functional>

class RPNCalculator {
public:
    void push(double value) {
        stack.push(value);
    }

    double pop() {
        if (stack.empty()) {
            throw std::runtime_error("栈空");
        }
        double value = stack.top();
        stack.pop();
        return value;
    }

    void calculate(const std::string& operation) {
        if (operation == "+") {
            calc([](double a, double b) { return a + b; });
        }
        else if (operation == "-") {
            calc([](double a, double b) { return a - b; });
        }
        else if (operation == "*") {
            calc([](double a, double b) { return a * b; });
        }
        else if (operation == "/") {
            calc([](double a, double b) {
                if (b == 0) throw std::runtime_error("分母不能为零");
                return a / b;
                });
        }
        else if (operation == "%") {
            calc([](double a, double b) {
                if (b == 0) throw std::runtime_error("分母不能为零");
                return std::fmod(a, b);
                });
        }
        else if (operation == "^") {
            calc([](double a, double b) {
                return std::pow(a, b);
                });
        }
        else if (operation == "@") {
            if (stack.empty()) throw std::runtime_error("栈为空");
            double value = pop();
            if (value < 0)
            {
                 std::cout<<"负数无法计算平方根";
                 system("pause");
            }
            else

            {
                push(std::sqrt(value));
            }
        }
        else if (operation == "y") {
            int n = static_cast<int>(pop());
            yhsj(n);
        }
        else if (operation == "f") {
            int n = static_cast<int>(pop());
            push(fibonacci(n));
        }
        else if (operation == "c")
        {
            clear();
        }
        else {
            std::cout << "输入有误请重新输入" << std::endl;

        }
    }

    void clear() {
        while (!stack.empty()) {
            stack.pop();
        }
    }

    void computeRPN(const std::string& expression) {
        std::istringstream iss(expression);
        std::string token;

        while (iss >> token) {
            try {
                if (isNumber(token)) {
                    push(std::stod(token));
                }
                else {
                    calculate(token);
                }
            }
            catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
        }
        if (!stack.empty()) {
            std::cout << "结果: " << stack.top() << std::endl;
        }
        else {
            std::cout << "栈为空，没有结果。" << std::endl;
        }
    }

private:
    std::stack<double> stack;

    void calc(const std::function<double(double, double)>& operation) {
        if (stack.size() < 2) {
            std::cout << "表达式错误请重新输入" << std::endl;
            clear();
            return;
        }
        double b = pop();
        double a = pop();
        push(operation(a, b));
    }

    bool isNumber(const std::string& str) {
        std::istringstream iss(str);
        double temp;
        iss >> temp;
        return iss.eof() && !iss.fail();
    }

    void yhsj(int n) {
        std::vector<std::vector<int>> vc(n);
        int sum=0;
        for (int line = 0; line < n; line++) {
            vc[line].resize(line + 1);
            vc[line][0] = 1;  // 每行的第一个元素为 1
            vc[line][line] = 1;  // 每行的最后一个元素为 1

            for (int j = 1; j < line; j++) {
                vc[line][j] = vc[line - 1][j - 1] + vc[line - 1][j];
            }
        }

        std::cout << "杨辉三角的前 " << n << " 行:" << std::endl;
        for (const auto& row : vc) {
            for (int num : row) {
                std::cout << num << " ";
                sum += num;
            }
            std::cout << std::endl;
        }
        push(sum);
    }

    int fibonacci(int n) {
        int sum = 0;
        if (n <= 0) return 0;
        if (n == 1) return 1;
        int a = 0, b = 1, c;
        std::cout<<"斐波那契前"<<n<<"项：" << "1 ";
        for (int i = 2; i <= n; i++) {
            c = a + b;
            a = b;
            b = c;
            std::cout << b << " ";
            sum += b;
        }
        std::cout << std::endl;
        return sum+1;
    }
};

int main() {
    RPNCalculator rpnCalculator;
    std::string input;

    std::cout << "Welcome to RPN 计算机!" << std::endl;
    std::cout << "c:清空" << "y:杨辉三角" << "f:斐波那契" << "q:退出"<<std::endl;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "q") {
            break;
        }

        rpnCalculator.computeRPN(input);
    }

    return 0;
}

