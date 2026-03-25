#include <iostream>

extern "C" double sinius(double a);

int main()
{
  std::cout << sinius(1);
  return 0;
}
