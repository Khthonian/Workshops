/*In this example, we use the select function to monitor multiple sockets for 
activity. When a new connection is made, it's added to the list of client 
sockets. The server continuously checks for data from clients and handles it 
when received. If a client disconnects or an error occurs, it is removed from 
the list of client sockets.
This approach can work for a small number of clients, but it has limitations in 
terms of scalability and may not be suitable for handling a large number of 
clients. Threading or non-blocking I/O can be more efficient in such cases.
*/
#define NOMINMAX
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
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

int main() 
{
    // Initialise the winsock - only windows
    #ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "Failed to initialize Winsock" << std::endl;
            return 1;
        }
    #endif


    SOCKET serverSocket;
    // use to store clients connected to the server
    std::vector<SOCKET> clientSockets(MAX_CLIENTS, 0);
    // Create the server socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error in socket creation" << std::endl;
        return 1;
    }

    sockaddr_in serverAddr, clientAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(12345);
    // bind the socket
    if (bind(serverSocket, reinterpret_cast<struct sockaddr*>(&serverAddr), sizeof(serverAddr)) == -1) {
        std::cerr << "Error in binding" << std::endl;
        return 1;
    }
    // listen
    if (listen(serverSocket, MAX_CLIENTS) == -1) {
        std::cerr << "Error in listen" << std::endl;
        return 1;
    }
     // Create a list of client sockets
    std::vector<SOCKET> activeClients;

    while (true) {
        fd_set readfds;
        FD_ZERO(&readfds);

        // Add the server socket to the set
        FD_SET(serverSocket, &readfds);

        SOCKET maxSocket = serverSocket;

        // Add all the client sockets to the set
        for (const auto& clientSocket : activeClients) {
            FD_SET(clientSocket, &readfds);
            maxSocket = std::max(maxSocket, clientSocket);
        }

        // Use select to monitor for activity on the sockets
        if (select(maxSocket + 1, &readfds, nullptr, nullptr, nullptr) == -1) {
            std::cerr << "Error in select" << std::endl;
            break;
        }

        // Check if there's a new connection on the server socket
        if (FD_ISSET(serverSocket, &readfds)) {
            SOCKET newClient = accept(serverSocket, reinterpret_cast<struct sockaddr*>(&clientAddr), nullptr);
            if (newClient != -1) {
                if (activeClients.size() < MAX_CLIENTS) {
                    activeClients.push_back(newClient);
                    std::cout << "New client connected" << std::endl;
                } else {
                    std::cerr << "Maximum number of clients reached" << std::endl;
                    closesocket(newClient);
                }
            }
        }

        // Check for data from clients
        for (auto it = activeClients.begin(); it != activeClients.end(); ) {
            SOCKET clientSocket = *it;
            if (FD_ISSET(clientSocket, &readfds)) {
                char buffer[1024];
                int valread = recv(clientSocket, buffer, sizeof(buffer), 0);
                if (valread <= 0) {
                    std::cout << "Client disconnected" << std::endl;
                    closesocket(clientSocket);
                    it = activeClients.erase(it);
                } else {
                    buffer[valread] = '\0';
                    std::cout << "Received: " << buffer << std::endl;
                    it++;
                }
            } else {
                it++;
            }
        }
    }

    #ifdef _WIN32
        WSACleanup();
    #endif

    return 0;
}
