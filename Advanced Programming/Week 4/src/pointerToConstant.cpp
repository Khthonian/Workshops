#include <iostream>

int main() {
  // Declare a const integer variable
  const int constVar = 50;

  // Declare a point to constVar
  const int *constPtr = &constVar;

  // Attempt to modify constVar
  *constPtr = 100;

  return 0;
}
