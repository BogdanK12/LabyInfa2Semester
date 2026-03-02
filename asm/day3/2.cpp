#include <iostream>

int main()
{
  int a, b;
  short g[10];
  for(int i = 0; i < 10; i++)
  {
    g[i] = 52 - i;
  }
  asm volatile (
    "section .data\n"
    ""
    "movzwl (%1), %%ebx\n\t"
    "mov $0, %%rdx\n"
    "j1:\n\t"
    "cmp $10, %%rdx\n\t"
    "je end\n\t"
    "movzwl (%1, %%rdx, 2), %%eax\n\t"
    "inc %%edx\n\t"
    "cmp %%ebx, %%eax\n\t"
    "jl less\n\t"
    "jg greater\n\t"
    "jmp j1\n"
    "less:\n\t"
    "mov %%eax, %%edx\n\t"
    "mov %%dx, %%cx\n\t"
    "jmp j1\n"
    "greater:\n\t"
    "mov %%eax, \n\t"
    "mov %%edx, %%\n\t"
    "jmp j1\n\t"
    "end:\n\t"
    "mov %%ebx, %0\n\t"
    "mov %%ecx, %1\n\t"
    : "=r"(a), "=r"(b)
    : "r"(g)
    : "eax", "ebx", "edx", "ecx"
  );
  std::cout << a << b;
  return 0;
}
