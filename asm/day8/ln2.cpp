#include <iomanip>
#include <ios>
#include <iostream>

extern "C" double ln2();

int main()
{
  std::cout << "----------------------------------------\n";
  std::cout << "Ln2 = " << std::fixed << std::setprecision(10) << ln2();
  std::cout << "\n----------------------------------------\n";
  return 0;
}
