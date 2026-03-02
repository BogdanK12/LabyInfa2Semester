#include <iostream>

int main()
{
  int a = 5;
  asm volatile (
    "mov %0, %%eax\n\t"
    "jj:\n\t"
    "sub $1, %%eax\n\t"
    "cmp $1, %%eax\n\t"
    "je jj"
    "mov %%eax, %0\n\t"
    : "+r"(a)
    :
    : "eax", "edx"
  );
  std::cout << a;
}
