#include <iostream>
#include <sstream>

void buffer_independence_test() {
    // 获取各自的流缓冲区
    auto* cout_buffer = std::cout.rdbuf();
    auto* clog_buffer = std::clog.rdbuf();
    
    // 正确输出指针地址
    std::cout << "cout 缓冲区地址: " << static_cast<const void*>(cout_buffer) << std::endl;
    std::cout << "clog 缓冲区地址: " << static_cast<const void*>(clog_buffer) << std::endl;
    
    // 它们有各自独立的流缓冲区对象
    if (cout_buffer == clog_buffer) {
        std::cout << "cout和clog共享同一个缓冲区" << std::endl;
    } else {
        std::cout << "cout和clog使用不同的缓冲区" << std::endl;
    }
}

int main() {
    buffer_independence_test();
    return 0;
}