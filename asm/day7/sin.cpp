#include <cmath>
#include <iostream>

extern "C" double sinius(double a);

int main()
{
  std::cout << "\n--------------------------------------------------------------";
  std::cout << "\nSin of 1: \nAssembly:" << sinius(1) << "\nC++: " << std::sin(1);
  std::cout << "\n--------------------------------------------------------------";
  std::cout << "\nSin of 2: \nAssembly:" << sinius(2) << "\nC++: " << std::sin(2);
  std::cout << "\n--------------------------------------------------------------";
  std::cout << "\nSin of 1.57: \nAssembly:" << sinius(1.57) << "\nC++: " << std::sin(1.57);
  std::cout << "\n--------------------------------------------------------------";
  std::cout << "\nSin of 3: \nAssembly:" << sinius(3) << "\nC++: " << std::sin(3);
  double input;
  std::cout << "\n--------------------------------------------------------------\n";
  std::cin >> input;
  std::cout << "--------------------------------------------------------------";
  std::cout << "\nSin of input: \nAssembly:" << sinius(input) << "\nC++: " << std::sin(input);
  return 0;
}
