// Copyright 2023 Stewart Charles Fisher II

// Include libraries
#include <sys/types.h>

#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#ifndef DATAPROCESSING_H_
#define DATAPROCESSING_H_

class DataProcessor {
 private:
  std::vector<std::string> _dataset_;
  std::vector<std::string> _processedData_;
  std::mutex _mutex_;

 public:
  bool loadData(const std::string& filename);

  void processInParallel(int numThreads);

  void processChunk(int startIndex, int chunkSize);

  bool saveData(const std::string& filename);
};

#endif  // DATAPROCESSING_H_
