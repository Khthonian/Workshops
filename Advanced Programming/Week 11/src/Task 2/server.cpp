// Copyright 2023 Stewart Charles Fisher II

// Import libraries
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

int main() {
  // Create a TCP socket
  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket == -1) {
    std::cerr << "Error: Socket could not be created!" << std::endl;
    return -1;
  }

  // Confirm server launch to user
  std::cout << "Server started. Waiting for connections..." << std::endl;

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

  // Listen for incoming connections
  if (listen(serverSocket, 5) == -1) {
    std::cerr << "Error: Connections could not be listened for!" << std::endl;
    close(serverSocket);
    return -1;
  }

  // Accept a client connection and obtain a new socket descriptor
  sockaddr_in clientAddr{};
  socklen_t clientAddrLen = sizeof(clientAddr);
  int clientSocket =
      accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
  if (clientSocket == -1) {
    std::cerr << "Error: Connection could not be accepted!" << std::endl;
    close(serverSocket);
    return -1;
  }

  // Receive a TCP message from the client
  char buffer[1024];
  ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
  if (bytesReceived == -1) {
    std::cerr << "Error: Message could not be received!" << std::endl;
    close(serverSocket);
    close(clientSocket);
    return -1;
  }

  // Print the received message
  buffer[bytesReceived] = '\0';  // Null-terminate the received data
  std::cout << "Received message from client: " << buffer << std::endl;

  // Send a response message to the client
  const char* response = "Message received successfully.";
  ssize_t bytesSent = send(clientSocket, response, strlen(response), 0);
  if (bytesSent == -1) {
    std::cerr << "Error: Response could not be sent!" << std::endl;
  }

  // Confirm response delivery to user
  std::cout << "Response sent to client: " << response << std::endl;

  // Close the sockets
  close(serverSocket);
  close(clientSocket);

  return 0;
}
