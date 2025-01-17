#include "head/server.h"
#include <iostream>
#include <fstream>

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif


#define PORT 8080 // port    
#define LOCAL INADDR_LOOPBACK //localhost

using namespace std;



// Функция для чтения HTML-файла
string readHTMLFile(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return "";
    }

    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return content;
}

// Функция для отправки HTML-страницы
void sendHTMLPage(int client_socket, const string& htmlContent) {
    // Формируем HTTP-ответ
    string response = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: " + to_string(htmlContent.size()) + "\r\n"
        "Connection: close\r\n\r\n" +
        htmlContent;

        if (send(client_socket, response.c_str(), response.size(), 0) < 0) {
        perror("Failed to send data");
    }
    // Отправляем клиенту HTTP-ответ
}


Server::Server() {

    int server_fd; 
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    cout << "Server initialized" << endl;
    
    while (true)
    {
        int addrlen = sizeof(address);
        int client_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        char client_ip[INET_ADDRSTRLEN]; // INET_ADDRSTRLEN - максимальная длина IP-адреса
        inet_ntop(AF_INET, &address.sin_addr, client_ip, INET_ADDRSTRLEN); // Преобразуем IP-адрес клиента в строку
        cout << "Client connected from IP: " << client_ip << ", Port: " << ntohs(address.sin_port) << endl; // ntohs - преобразует порт в сетевой порядок байт

        // Читаем HTML-файл
        string htmlContent = readHTMLFile("index.html");
        if (!htmlContent.empty()) {
            // Отправляем HTML-страницу клиенту
            sendHTMLPage(client_socket, htmlContent);
        } else {
            cerr << "Failed to send HTML content" << endl;
        }


        // Закрываем соединение
        #ifdef _WIN32
                closesocket(client_socket);
        #else
                close(client_socket);
        #endif
                cout << "Client disconnected" << endl;
            }

        #ifdef _WIN32
            WSACleanup();
        #endif
        
}

Server::~Server(){
    cout << "Server destructor" << endl;
}

void Server::start(){
   
}


void Server::restart(){
    cout << "Server restarted" << endl;
}