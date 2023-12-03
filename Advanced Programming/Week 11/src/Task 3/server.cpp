// Copyright 2023 Stewart Charles Fisher II

// Import libraries
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <thread>
#include <vector>

// Define the max amount of clients
const int MAX_CLIENTS = 100;

// Define a function to handle communication with a specific client
void handleClient(int clientSocket, const sockaddr_in& clientAddr) {
  char clientIP[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &(clientAddr.sin_addr), clientIP, INET_ADDRSTRLEN);

  // Receive a message from the client
  char buffer[1024];
  ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
  if (bytesReceived > 0) {
    buffer[bytesReceived] = '\0';  // Null-terminate the received data
    std::cout << "Received message from " << clientIP << ": " << buffer
              << std::endl;

    // Send a response to the client
    const char* response = "Message broadcasted successfully.";
    ssize_t bytesSent = send(clientSocket, response, strlen(response), 0);
    if (bytesSent == -1) {
      std::cerr << "Error: Response could not be sent!" << std::endl;
    } else {
      std::cout << "Response sent to client " << clientIP << ": " << response
                << std::endl;
    }
  }

  // Close the client socket after handling the communication
  close(clientSocket);
}

int main() {
  // Create a TCP socket
  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket == -1) {
    std::cerr << "Error: Socket could not be created!" << std::endl;
    return -1;
  }

  // Confirm server launch to user
  std::cout << "Server started. Waiting for connections..." << std::endl;

  // Bind the server socket to a specific port
  sockaddr_in serverAddr{};
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(12345);
  serverAddr.sin_addr.s_addr = INADDR_ANY;

  if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) ==
      -1) {
    std::cerr << "Error: Socket could not be bound!" << std::endl;
    close(serverSocket);
    return -1;
  }

  // Listen for incoming connections
  if (listen(serverSocket, 5) == -1) {
    std::cerr << "Error: Connections could not be listened for!" << std::endl;
    close(serverSocket);
    return -1;
  }

  std::vector<int> clientSockets;  // To keep track of connected clients

  while (true) {
    // Accept incoming client connections
    sockaddr_in clientAddr{};
    socklen_t clientAddrLen = sizeof(clientAddr);
    int clientSocket =
        accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSocket != -1) {
      if (clientSockets.size() < MAX_CLIENTS) {
        clientSockets.push_back(clientSocket);

        char* clientIP = inet_ntoa(clientAddr.sin_addr);
        std::cout << "Client connected: " << clientIP << std::endl;

        // Create a thread for the new client
        std::thread clientThread(handleClient, clientSocket, clientAddr);
        clientThread.detach();
      } else {
        std::cerr << "Error: Client connection could not be established!"
                  << std::endl;
        close(clientSocket);
      }
    }
  }

  return 0;
}
