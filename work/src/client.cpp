#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

int main(int argc, char* argv[]){
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(client_fd == -1){
        std::cerr << "Socket creation failed" << std::endl;
        return -1;
    }
    std::cout << "Socket created successfully with fd: " << client_fd << std::endl;

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
        std::cerr << "无效的服务器地址" << std::endl;
        close(client_fd);
        return 1;
    }

    if(connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        std::cerr << "连接服务器失败" << std::endl;
        close(client_fd);
        return -1;
    }
    std::cout << "Connected to server successfully" << std::endl;   
    // 发送数据
    while(1){
        std::string message;
        std::cout << "Enter message to send: ";
        std::getline(std::cin, message);
        if(message.empty()) break;

        ssize_t bytes_sent = send(client_fd, message.c_str(), message.size(), 0);
        if(bytes_sent == -1){
            std::cerr << "发送数据失败" << std::endl;
            break;
        }
        std::cout << "Sent " << bytes_sent << " bytes to server" << std::endl;

        char buffer[1024] = {0};
        ssize_t bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
        if(bytes_received == -1){
            std::cerr << "接收数据失败" << std::endl;
            break;
        } else if(bytes_received == 0){
            std::cout << "服务器关闭了连接" << std::endl;
            break;
        }
        buffer[bytes_received] = '\0';
        std::cout << "Received from server: " << buffer << std::endl;


        // 可选：等待服务器回复
        buffer[0] = 0;
        ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            std::cout << "服务器的回复: " << buffer << std::endl;
        } else {
            std::cerr << "接收回复失败或连接已关闭" << std::endl;
            close(client_fd);
            return 1;
        }
    }
    close(client_fd);
    std::cout << "连接已关闭，客户端退出" << std::endl;
    return 0;
}