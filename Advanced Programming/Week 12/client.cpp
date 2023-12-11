// Copyright 2023 Stewart Charles Fisher II

// Include libraries
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>

int main() {
  // Create a TCP socket
  int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (clientSocket == -1) {
    std::cerr << "Error creating socket." << std::endl;
    return 1;
  }

  // Prepare the server address structure
  struct sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(12345);
  serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

  // Connect to the server
  if (connect(clientSocket, (struct sockaddr*)&serverAddress,
              sizeof(serverAddress)) == -1) {
    std::cerr << "Error connecting to server." << std::endl;
    close(clientSocket);
    return 1;
  }

  // Prompt the user to enter a list of numbers
  std::cout << "Enter a list of numbers separated by spaces: ";
  std::string input;
  std::getline(std::cin, input);

  // Prepare the list of numbers
  std::stringstream ss(input);
  int num;
  std::vector<int> numbers;
  while (ss >> num) {
    numbers.push_back(num);
  }

  // Send data to the server
  send(clientSocket, numbers.data(), numbers.size() * sizeof(int), 0);

  // Receive computed statistics from the server
  int stats[4];  // Assuming the server sends average, min, max, and median
  recv(clientSocket, stats, sizeof(stats), 0);

  // Display computed statistics to the user
  std::cout << "Received statistics from server:\n";
  std::cout << "Average: " << stats[0] << "\n";
  std::cout << "Minimum: " << stats[1] << "\n";
  std::cout << "Maximum: " << stats[2] << "\n";
  std::cout << "Median: " << stats[3] << "\n";

  // Close the socket
  close(clientSocket);

  return 0;
}
