#pragma once

#ifndef SERVER_H
#define SERVER_H

#include <string>
class Server {
public:
    Server();
    ~Server();
    std::string readHTMLFile(const std::string& filename); // Функция для чтения HTML-файла
    void sendHTMLPage(int client_socket, const std::string& htmlContent); // Функция для отправки HTML-страницы
private:
    void start();
    void restart();
};

#endif