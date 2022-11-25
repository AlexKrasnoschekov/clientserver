#include "clientserver.h"
#pragma once


void Stream() {
    std::thread Server(server);
    std::thread Client(client);
    Server.join();
    Client.join();
    
}


int main(int argc, char** argv)
{
    if (argc && argv) {
        getport(argc, argv);
    }
    else {
        parameters::port = 1111;
    }
    Stream();
    return 0;
}

