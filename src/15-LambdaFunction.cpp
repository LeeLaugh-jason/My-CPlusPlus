#include <iostream>
#include <vector>

struct Adder {
    auto operator()(int a, int b) const {
        return a + b;
    }
};

int main() {
    Adder add;
    std::cout << add(3, 4) << std::endl;  // Outputs: 7
    return 0;
}

