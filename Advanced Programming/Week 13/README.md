# Concurrent Input Processing System

## Problem Statement

"Implement a program to process a large dataset concurrently using multiple threads and a shared resource, and then merge the results."

## `std::jthread`

Using `std::jthread` in place of `std::thread` in the program provides multiple benefits for memory management and safety.

### Automatic Joining

`std::jthread` automatically joins once it goes out of scope, unlike `std::thread` which requires the explicit usage of `join()` or `detach()`. If a `std::thread` fails to join or detach prior to destruction, the program will terminate with an error. `std::jthread` automatically handles the cleanup process, preventing program failures.

### Modern Standard Compliance

`std::jthread` was introduced with C++20, meaning that the program features a more modern practice.

### Simpler Code

Using `std::jthread` allows for simpler and more maintainable code, due to the lesser requirements for explicit calls.

## Race Conditions

> "A race condition occurs in a parallel program execution when two or more threads access a common resource, e.g. a variable in shared memory, and the order of the accesses depends on the timing, i.e., the progress of individual threads." - Christoph von Praun, Encyclopedia of Parallel Computing

To prevent race conditions in the program, the `_dataset_` vector is used in a read-only fashion. Each thread writes only to its allocated portion of the `_processedData_` vector.

## Result Merging

As the results are written directly to the `_processedData_` vector, the results are effectively being merged automatically. As soon as all threads have finished execution, the results are already merged.
