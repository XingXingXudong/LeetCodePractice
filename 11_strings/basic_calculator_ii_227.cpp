// https://leetcode.com/problems/basic-calculator-ii/
#include <gtest/gtest.h>
#include <string>
#include <stack>

long parseNum(const std::string& s, int& i) {
    long n = 0;
    while (i < (int)s.length() && std::isdigit(s[i])) {
        n = 10 * n + (s[i] - '0');
        ++i;
    }
    return n;
}

int calculate(const std::string& s_) {
    std::string s{s_};
    size_t idx = 0;
    while((idx = s.find(' ', idx)) != std::string::npos) {
        s.erase(idx, 1);
    }
    auto num_stack = std::stack<int>{};
    int i = 0;
    long n = parseNum(s, i);
    num_stack.push(n);
    char op;

    while (i < (int)s.length()) {
        // while(s[i] == ' ') {
        //     ++i;
        // }
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
            op = s[i];
            ++i;
        }
        // while(s[i] == ' ') {
        //     ++i;
        // }
        n = parseNum(s, i);
        if (op == '+') {
            num_stack.push(n);
        } else if (op == '-') {
            num_stack.push(-n);
        } else if (op == '*') {
            int f1 = num_stack.top() * n;
            num_stack.pop();
            num_stack.push(f1);
        } else {
            int f2 = num_stack.top() / n;
            num_stack.pop();
            num_stack.push(f2);
        }
    }
    int ans = 0;
    while (!num_stack.empty()) {
        ans += num_stack.top();
        num_stack.pop();
    }
    return ans;
}

TEST(calculate, a) {
    std::string s = "3+2*2";
    int output = 7;
    EXPECT_EQ(calculate(s), output);
}

TEST(calculate, b) {
    std::string s = "32/2";
    int output = 16;
    EXPECT_EQ(calculate(s), output);
}

TEST(calculate, c) {
    std::string s = "3+5 / 2";
    int output = 5;
    EXPECT_EQ(calculate(s), output);
}

TEST(calculate, d) {
    std::string s = " 3/5 ";
    int output = 0;
    EXPECT_EQ(calculate(s), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}