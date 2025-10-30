#include <iostream>
#include <unistd.h>


int main() {
    std::cout << "This is normal output." ;
    sleep(5);
    std::cout << std::endl;

    std::cerr << "This is an error message.";
    sleep(5);
    std::cout << std::endl;

    return 0;
}
