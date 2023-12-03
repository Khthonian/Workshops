// Copyright 2023 Stewart Charles Fisher II

// Import libraries
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>

int main() {
  // Create a UDP socket
  int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
  if (serverSocket == -1) {
    std::cerr << "Error: Socket could not be created!" << std::endl;
    return -1;
  }

  // Confirm server launch to user
  std::cout << "Server started. Waiting for messages..." << std::endl;

  // Bind the socket to a specific port
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

  // Receive a UDP message from the client
  char buffer[1024];
  sockaddr_in clientAddr{};
  socklen_t clientAddrLen = sizeof(clientAddr);

  ssize_t bytesReceived =
      recvfrom(serverSocket, buffer, sizeof(buffer), 0,
               (struct sockaddr*)&clientAddr, &clientAddrLen);
  if (bytesReceived == -1) {
    std::cerr << "Error: Message could not be received!" << std::endl;
    close(serverSocket);
    return -1;
  }

  // Print the received message
  buffer[bytesReceived] = '\0';  // Null-terminate the received data
  std::cout << "Received message from client: " << buffer << std::endl;

  // Close the socket
  close(serverSocket);

  return 0;
}
