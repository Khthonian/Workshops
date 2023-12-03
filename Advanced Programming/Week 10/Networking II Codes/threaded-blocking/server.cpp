#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <cstring>

#ifdef _WIN32
    #include <winsock2.h>
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #define SOCKET int
    #define closesocket close
#endif

const int MAX_CLIENTS = 5;

// reading cllients buffer needs to be thread
// that is the resource contention part of the application
/*
The HandleClient function is responsible for managing the 
communication with an individual client in a dedicated thread.

Isolation: The HandleClient function isolates the logic for interacting with a client. 
This isolation makes it easier to develop and maintain the server code. 
It also prevents issues with data and resources shared between clients.

Non-Blocking: Since the HandleClient function runs in a separate thread, 
it can perform socket operations without blocking the main server thread. 
This ensures that the server remains responsive to new client connections 
and other activities while handling client-specific operations.


*/
void ReadClientBuffer(SOCKET clientSocket) {
    char buffer[1024];
    int valread;

    while (true) {
        valread = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (valread <= 0) {
            std::cout << "Client disconnected" << std::endl;
            break;
        } else {
            buffer[valread] = '\0';
            std::cout << "Received: " << buffer << std::endl;
        }
    }
    closesocket(clientSocket);
}

int main() 
{
    #ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "Failed to initialize Winsock" << std::endl;
            return 1;
        }
    #endif

    SOCKET serverSocket;
    std::vector<SOCKET> clientSockets;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error in socket creation" << std::endl;
        return 1;
    }

    sockaddr_in serverAddr, clientAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(12345);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error in binding" << std::endl;
        return 1;
    }

    if (listen(serverSocket, MAX_CLIENTS) == -1) {
        std::cerr << "Error in listen" << std::endl;
        return 1;
    }

    while (true) {
        SOCKET newClient = accept(serverSocket, (struct sockaddr*)&clientAddr, nullptr);
        if (newClient != -1) {
            if (clientSockets.size() < MAX_CLIENTS) {
                clientSockets.push_back(newClient);
                std::cout << "New client connected" << std::endl;
                std::thread clientThread(ReadClientBuffer, newClient);
                clientThread.detach(); // Detach the thread to run independently
            } else {
                std::cerr << "Maximum number of clients reached" << std::endl;
                closesocket(newClient);
            }
        }
    }   

    #ifdef _WIN32
        WSACleanup();
    #endif

    return 0;
}
