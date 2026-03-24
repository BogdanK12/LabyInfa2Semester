#include <iostream>

extern "C" double sinius(double a);

int main()
{
  std::cout << sinius(2);
  return 0;
}
