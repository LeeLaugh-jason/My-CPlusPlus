#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    for (volatile int i = 0; i < 1000000; ++i){
        std::cout << "Hello, Stream!" ;
    }
    
    return 0;
}
