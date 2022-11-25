#include <winsock2.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include "constants.h"
#pragma comment(lib, "Ws2_32.lib")
#include <string>
#pragma once
#pragma warning(disable: 4996)
inline void server() {
    WSAData wsaData;
    WORD Version = MAKEWORD(2, 1);
    if (WSAStartup(Version, &wsaData)) {
        std::cout << "Cannot upload library!" << std::endl;
        exit(1);
    }
    SOCKADDR_IN ad;
    ad.sin_addr.s_addr = inet_addr(parameters::ip);
    ad.sin_port = htons(parameters::port);
    ad.sin_family = AF_INET;
    SOCKET sListen = socket(AF_INET, SOCK_STREAM, 0);
    bind(sListen, (SOCKADDR*)&ad, sizeof(ad));
    listen(sListen, SOMAXCONN);
    int sizead = sizeof(ad);
    SOCKET newConnection;
    newConnection = accept(sListen, (SOCKADDR*)&ad, &sizead);
    closesocket(sListen);
    char message[1000];
    int counter = 0;
    while (true) {
        std::memset(message, 0, sizeof(message));
        int got = recv(newConnection, message, sizeof(message), 0);
        if (got != SOCKET_ERROR) {
            if (counter == 0) {
                if (strcmp(message, "START") != 0) {
                    std::cerr << "Wrong start" << std::endl;
                    break;
                }
                counter++;
                send(newConnection, message, got, 0);
            }
            else {
                if (strcmp(message, "STOP") == 0) {
                    std::memset(message, 0, sizeof(message));
                    closesocket(newConnection);
                    break;
                }
                counter++;
                send(newConnection, message, got, 0);
            }
        }
        else {
            std::cerr << "Error in recv(). Quitting" << std::endl;
            std::memset(message, 0, sizeof(message));
            break;
        }
        if (got == 0) {
            std::cout << "client disconnected" << std::endl;
            std::memset(message, 0, sizeof(message));
            break;
        }
    }
    closesocket(newConnection);
    std::memset(message, 0, sizeof(message));
    std::cout << "server returned\n";
    return;
}