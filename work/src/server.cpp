#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

int main(){
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd == -1){
        std::cerr << "Socket creation failed" << std::endl;
        return -1;
    }
    std::cout << "Socket created successfully with fd: " << server_fd << std::endl;
    int opt = 1;
    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){
        std::cerr << "Set socket options failed" << std::endl;
        return -1;
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if(bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0){
        std::cerr << "Bind failed" << std::endl;
        return -1;
    }
    std::cout << "Bind successful on port 8080" << std::endl;

    if (listen(server_fd, 5) < 0) { // 5是等待队列的最大长度
        std::cerr << "Listen failed" << std::endl;
        close(server_fd);
        return 1;
    }
    std::cout << "Server is listening for connections..." << std::endl;

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_socket = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len);

    if (client_socket < 0) {
        std::cerr << "接受连接失败" << std::endl;
        close(server_fd);
        return 1;
    }
    std::cout << "Connection accepted, client socket fd: " << client_socket << std::endl;

    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
    std::cout << "Received connection from " << client_ip << ":" << ntohs(client_addr.sin_port) << std::endl;

    while(1){
        char buffer[1024] = {0};
        ssize_t bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
        if(bytes_read <= 0){
            std::cout << "Client disconnected or read error" << std::endl;
            break;
        }
        buffer[bytes_read] = '\0';
        std::cout << "Received: " << buffer << std::endl;

        const char* response = "Message received\n";
        send(client_socket, response, strlen(response), 0);
    };

    // 8. 关闭连接
    close(client_socket);
    close(server_fd);
    
    std::cout << "连接已关闭，服务器退出" << std::endl;

    return 0;
}