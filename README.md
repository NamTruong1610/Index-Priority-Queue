# Index Priority Queue Library

This repository contains a template-based implementation of an **Index Priority Queue** in C++ along with a custom integer type `MyInteger` that tracks construction and copy operations. The project includes comprehensive tests written using the [Google Test framework](https://github.com/google/googletest).

## Project Structure

- **index_pq.hpp**  
  Implements the `IndexPriorityQueue` template class that maintains a priority queue indexed by element IDs. Key features include:
  - **Push, Pop, and Erase Operations:**  
    Insert elements with an associated key, remove the top element, or erase a specific index.
  - **Key Updates:**  
    Change the key associated with a specific index and maintain heap order using helper functions like `swim` and `sink`.
  - **Membership Query:**  
    Check whether an element is present in the priority queue.

- **my_integer.hpp**  
  Defines the `MyInteger` struct which:
  - Wraps an integer value.
  - Tracks the number of constructions, copies, assignments, and comparisons.
  - Provides helper functions to print and clear these counts.
  - Useful for performance testing and verifying that the priority queue minimizes unnecessary copies or assignments.

- **main.cpp**  
  Contains a series of unit tests using Google Test that verify:
  - Basic operations of the `IndexPriorityQueue` with different data types.
  - Behavior of key update operations (`changeKey`).
  - Correct handling of element erasure, including edge cases.
  - Efficiency tests using `MyInteger` to ensure that operations incur minimal overhead.

## Getting Started

### Prerequisites

- **C++ Compiler:**  
  A C++ compiler with C++17 support (e.g., `g++` or `clang++`).

- **Google Test:**  
  Ensure that [Google Test](https://github.com/google/googletest) is installed and accessible. You will need the include paths and library files for compilation.

### Compilation

Assuming you have Google Test installed, you can compile the project from the terminal. For example, using `g++`:

```bash
g++ -std=c++17 -I/path/to/googletest/include -L/path/to/googletest/lib main.cpp -lgtest -lgtest_main -pthread -o runTests
