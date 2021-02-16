//https://leetcode.com/problems/implement-queue-using-stacks/
#include <stack>
#include <assert.h>
#include <iostream>

class MyQueue {
private:
    std::stack<int> stack_a{};
    std::stack<int> stack_b{};
public:
    MyQueue() {
        
    }
    
    void push(int x) {
       stack_a.push(x);
    }
    
    int pop() {
        int tmp = peek();
        stack_b.pop();
        return tmp;
    }
    
    int peek() {
        if (stack_b.empty()) {
            while(!stack_a.empty()) {
                stack_b.push(stack_a.top());
                stack_a.pop();
            }
        }
        assert(!stack_b.empty());
        int tmp = stack_b.top();
        return tmp;
    }
    
    bool empty() {
        return stack_a.empty() && stack_b.empty();
    }
};

int main(int argc, char* argv[]) {
    MyQueue* obj = new MyQueue();
    obj->push(1);
    int param_3 = obj->peek();
    int param_2 = obj->pop();
    bool param_4 = obj->empty();    
    std::cout << "param_3: " << param_3 << ", param_2: " << param_2 << ", param_4: " << param_4 << std::endl;
    delete obj;
}