#include <cstddef>
#include <cstdlib>
#include <iostream>

void print(short* arr, size_t size)
{
  std::cout << "| ";
  for(size_t i{}; i < size; i++)
  {
    std::cout << i << " | ";
  }
  std::cout << '\n';
}

int main()
{
  long size;
  if(!(std::cin >> size))
  {
    std::exit(52);
  }
  if(size <= 0)
  {
    std::exit(67);
  }
  short max, min;
  short maxIndex = 0;
  short minIndex = 0;
  short *g = (short *)malloc(size * sizeof(short));
  print(g, size);
  asm volatile (
    "mov (%4), %%bx\n\t"
    "mov %%bx, %%cx\n\t"
    "xor %%rdx, %%rdx\n\t"
    "xor %%esi, %%esi\n\t"
    "xor %%edi, %%edi\n\t"
    "inc %%rdx\n"
    "j1:\n\t"
    "cmp %5, %%rdx\n\t"
    "jge end\n\t"
    "mov (%4, %%rdx, 2), %%ax\n\t"
    "cmp %%bx, %%ax\n\t"
    "jg greater\n\t"
    "cmp %%cx, %%ax\n\t"
    "jl less\n\t "
    "jmp next\n"
    "greater:\n\t"
    "mov %%ax, %%bx\n\t"
    "mov %%dx, %%si\n\t"
    "jmp next\n"
    "less:\n\t"
    "mov %%ax, %%cx\n\t"
    "mov %%dx, %%di\n\t"
    "jmp next\n"
    "next:\n\t"
    "inc %%rdx\n\t"
    "jmp j1\n"
    "end:\n\t"
    "mov %%bx, %0\n\t"
    "mov %%cx, %2\n\t"
    "mov %%si, %1\n\t"
    "mov %%di, %3\n\t"
    : "=r"(max), "=r"(maxIndex), "=r"(min), "=r"(minIndex)
    : "r"(g), "r"(size)
    : "eax", "ebx", "edx", "ecx", "edi", "esi", "cc", "memory"
  );
  std::cout << min << " : " << minIndex << " | " << max << " : " <<  maxIndex;
  return 0;
}
