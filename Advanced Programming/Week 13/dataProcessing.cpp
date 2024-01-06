// Copyright 2023 Stewart Charles Fisher II

#include <sys/types.h>

#include "dataProcessing.h"

// Define a function to load data from file
bool DataProcessor::loadData(const std::string& filename) {
  std::ifstream file(filename);
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      _dataset_.push_back(line);
    }
    file.close();
    return true;
  }
  return false;
}

// Define a function to process data in parallel
void DataProcessor::processInParallel(int numThreads) {
  // Get the size for each chunk
  int chunkSize = _dataset_.size() / numThreads;
  // Account for uneven divisions
  int remainingElements = _dataset_.size() % numThreads;
  // Allocate space for processed data
  _processedData_.resize(_dataset_.size());

  // Create vector to store threads
  /* jthreads are used due to being able to automatically rejoin once out of
   * scope, allowing for superior memory safety to normal threads.
   */
  std::vector<std::jthread> threads;

  int startIndex = 0;
  for (int i = 0; i < numThreads; ++i) {
    // Adjust chunk size per thread
    int currentChunkSize = chunkSize + (i < remainingElements ? 1 : 0);
    // Create new thread to process chunk
    threads.emplace_back(&DataProcessor::processChunk, this, startIndex,
                         currentChunkSize);
    // Update start index
    startIndex += currentChunkSize;
  }
}

// Define a function to process a chunk of data and store the results
void DataProcessor::processChunk(int startIndex, int chunkSize) {
  for (int i = 0; i < chunkSize; ++i) {
    // Calculate dataset index
    int dataIndex = startIndex + i;
    // Check bounds
    if (dataIndex < _dataset_.size()) {
      // Convert string to integer
      int num = std::stoi(_dataset_[dataIndex]);
      // Double the number and store to the vector
      _processedData_[dataIndex] = std::to_string(num * 2);
    }
  }
}

// Define a function to save the processed data to file
bool DataProcessor::saveData(const std::string& filename) {
  std::ofstream file(filename);
  if (file.is_open()) {
    for (const std::string& line : _processedData_) {
      file << line << "\n";
    }
    file.close();
    return true;
  }
  return false;
}

int main(int argc, char** argv) {
  if (argc < 4) {
    std::cout << "Usage: ./data_processing_program <input_file> <output_file> "
                 "<num_threads>"
              << std::endl;
    return 0;
  }

  int maxThreads = std::thread::hardware_concurrency();
  std::cout << "Maximum number of available threads: " << maxThreads
            << std::endl;
  if (std::stoi(argv[3]) > maxThreads) {
    return 1;
  }

  std::string inputFilename = argv[1];
  std::string outputFilename = argv[2];
  int numThreads = std::stoi(argv[3]);

  DataProcessor dataProcessor;

  // Load data from file
  bool loadSuccess = dataProcessor.loadData(inputFilename);
  if (!loadSuccess) {
    std::cout << "Error: Failed to load data from file." << std::endl;
    return 0;
  }

  // Process data in parallel
  dataProcessor.processInParallel(numThreads);

  // Save processed data to file
  bool saveSuccess = dataProcessor.saveData(outputFilename);
  if (saveSuccess) {
    std::cout
        << "Data processing completed successfully. Processed data saved to "
        << outputFilename << "." << std::endl;
  } else {
    std::cout << "Error: Failed to save processed data to file." << std::endl;
  }

  return 0;
}
