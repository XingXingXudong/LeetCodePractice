#include <iostream>
#include <vector>
#include <string>

int main(int argc, char* argv[]) {
    auto strs = std::vector<std::string>{"abc", "aaa", "bbb"};
    auto back = strs.back();
    back[2] = 'C';
    std::cout << "back: " << back << std::endl;
    for (const auto& x: strs) {
	    std::cout << x << ", ";
    }
    std::cout << std::endl;
}
