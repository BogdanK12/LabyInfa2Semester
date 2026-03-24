#include <cstddef>
#include <iostream>

extern "C" size_t factorial(size_t);

int main()
{
  std::cout << factorial(4) << " | " << factorial(10);
  return 0;
}
