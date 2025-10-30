#include <iostream>

int main() {
    int x=0;
    std::cin >> x;
    std::cin.sync();

    std::cout << "Hello, Stream! You entered: " << x << std::endl;
    
    return 0;
}
