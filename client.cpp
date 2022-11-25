#include <winsock2.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "constants.h"
#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable : 4996)
#pragma once

inline void client() {
    WSAData wsaData;
    WORD Version = MAKEWORD(2, 1);
    if (WSAStartup(Version, &wsaData)) {
        std::cout << "Cannot upload library" << std::endl;
        exit(1);
    }
    SOCKADDR_IN ad;
    ad.sin_addr.s_addr = inet_addr(parameters::ip);
    ad.sin_port = htons(parameters::port);
    ad.sin_family = AF_INET;
    char buf[1000];
    std::string message = std::string("");
    SOCKET Connect = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(Connect, (SOCKADDR*)&ad, sizeof(ad))) {
        std::cout << "Cannot connect" << std::endl;
        return;
    }
    else {
        while (true) {
            std::cout << ">";
            std::getline(std::cin, message);
            int sendcheck = send(Connect, message.c_str(), sizeof(message), 0);
            if (sendcheck != SOCKET_ERROR) {
                std::memset(buf, 0, 1000);
                int got = recv(Connect, buf, sizeof(buf), 0);
                if (got > 0)
                {
                    std::cout << "SERVER> " << std::string(buf, 0, got) << std::endl;
                }
            }
            if (strcmp(message.c_str(), "STOP") == 0) {
                std::memset(buf, 0, 1000);
                message.clear();
                closesocket(Connect);
                break;
            }
        }
    }
    ZeroMemory(buf, 1000);
    message.clear();
    closesocket(Connect);
    std::cout << "client returned\n";
    return;
}