// Copyright 2023 Stewart Charles Fisher II

// Include libraries
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
  // Create a TCP socket
  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket == -1) {
    std::cerr << "Error creating socket." << std::endl;
    return 1;
  }

  // Prepare the server address structure
  struct sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(12345);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  // Bind the socket to the server address
  if (bind(serverSocket, (struct sockaddr*)&serverAddress,
           sizeof(serverAddress)) == -1) {
    std::cerr << "Error binding socket." << std::endl;
    close(serverSocket);
    return 1;
  }

  // Listen for incoming connections
  if (listen(serverSocket, SOMAXCONN) == -1) {
    std::cerr << "Error listening for connections." << std::endl;
    close(serverSocket);
    return 1;
  }

  while (true) {
    // Accept incoming connection
    struct sockaddr_in clientAddress;
    socklen_t clientAddressSize = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress,
                              &clientAddressSize);
    if (clientSocket == -1) {
      std::cerr << "Error accepting connection." << std::endl;
      close(serverSocket);
      return 1;
    }

    // Receive data from the client
    double receivedData[100];  // Assuming a maximum of 100 numbers
    ssize_t bytesReceived =
        recv(clientSocket, receivedData, sizeof(receivedData), 0);

    if (bytesReceived == -1) {
      std::cerr << "Error receiving data from client." << std::endl;
      close(clientSocket);
      continue;
    }

    // Process the received data
    std::vector<double> numbers(receivedData,
                                receivedData + bytesReceived / sizeof(double));

    // Print received numbers and their count
    std::cout << "Received " << numbers.size() << " numbers from the client: ";
    for (double num : numbers) {
      std::cout << num << " ";
    }
    std::cout << std::endl;

    // Calculate statistics
    double average =
        std::accumulate(numbers.begin(), numbers.end(), 0.0) / numbers.size();
    double minimum = *std::min_element(numbers.begin(), numbers.end());
    double maximum = *std::max_element(numbers.begin(), numbers.end());

    std::sort(numbers.begin(), numbers.end());
    double median;
    if (numbers.size() % 2 == 0) {
      median =
          (numbers[numbers.size() / 2 - 1] + numbers[numbers.size() / 2]) / 2;
    } else {
      median = numbers[numbers.size() / 2];
    }

    // Print computed statistics
    std::cout << "Computed Statistics:\n";
    std::cout << "Average: " << average << "\n";
    std::cout << "Minimum: " << minimum << "\n";
    std::cout << "Maximum: " << maximum << "\n";
    std::cout << "Median: " << median << "\n";

    // Send computed statistics back to the client
    double stats[] = {static_cast<double>(average), minimum, maximum, median};
    send(clientSocket, stats, sizeof(stats), 0);

    // Close the client socket
    close(clientSocket);
  }

  // Close the server socket
  close(serverSocket);

  return 0;
}
