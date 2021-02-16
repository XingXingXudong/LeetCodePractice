// https://leetcode.com/problems/min-stack/

#include <stack>
#include <iostream>

class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
        
    }
    
    void push(int x) {
        stack_.push(x);
        if (min_stack_.empty()) {
            min_stack_.push(x);
        } else {
            min_stack_.push(x < min_stack_.top() ? x : min_stack_.top());
        }
    }
    
    void pop() {
        stack_.pop();
        min_stack_.pop();
    }
    
    int top() {
        return stack_.top();
    }
    
    int getMin() {
        return min_stack_.top();
    }

private:
    std::stack<int> min_stack_{};
    std::stack<int> stack_{};
};

int main(int argc, char* argv[]) {
    //Your MinStack object will be instantiated and called as such:
    MinStack* obj = new MinStack();
    obj->push(3);
    obj->push(2);
    obj->push(4);
    obj->push(3);
    obj->push(1);
    int param_2 = obj->getMin();
    std::cout << "param_2: " << param_2 << std::endl;
    int param_3 = obj->top();
    obj->pop();
    int param_4 = obj->getMin();
    std::cout << "param_3: " << param_3 << ", param_4: " << param_4 << std::endl;
}