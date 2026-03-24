#include <iostream>

extern "C" double discriminant(double a, double b, double c) __attribute__((cdecl));

int main()
{
  double result(discriminant(1, 2, 1));
  std::cout << "Result: " << result;
  return 0;
}
