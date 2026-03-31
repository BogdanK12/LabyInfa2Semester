#include <iostream>

extern "C" double integral(double limit);

int main()
{
  double input;
  std::cin >> input;
  std::cout << "-------------------------------------\n";
  std::cout << integral(input);
  std::cout << "\n------------------------------------\n";
  return 0;
}
