// Copyright 2023 Stewart Charles Fisher II

// Import libraries
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <ostream>

int main() {
  // Create a UDP socket
  int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
  if (clientSocket == -1) {
    std::cerr << "Error: Socket could not be created!" << std::endl;
    return -1;
  }

  // Prepare the destination server address and port information
  sockaddr_in serverAddr{};
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(12345);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  // Get the message from the user
  std::cout << "Enter the message to send: ";
  std::string message;
  std::getline(std::cin, message);

  // Use the sendto() function to send the message to the server
  ssize_t bytesSent = sendto(clientSocket, message.c_str(), message.size(), 0,
                             (struct sockaddr*)&serverAddr, sizeof(serverAddr));
  if (bytesSent == -1) {
    std::cerr << "Error: Message could not be sent!" << std::endl;
    close(clientSocket);
    return -1;
  }

  // Confirm message delivery to user
  std::cout << "Message sent to server." << std::endl;

  // Close the socket
  close(clientSocket);

  return 0;
}
