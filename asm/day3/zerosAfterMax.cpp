#include <climits>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <random>

template <class T>
void print(const T* array, size_t size)
{
  std::cout << '\n' << "| ";
  for(size_t i{}; i < size; i++)
  {
    std::cout << array[i] << " | ";
  }
  std::cout << '\n';
}

int main()
{
  std::random_device rd;
  std::mt19937 gener(rd());
  std::uniform_int_distribution<short> elem(SHRT_MIN, SHRT_MAX);
  short max, min;
  short maxIndex = 0;
  short minIndex = 0;
  short *g = new short[10];
  for(int i = 0; i < 10; i++)
  {
    g[i] = elem(gener);
  }
  print<short>(g, 10);
  asm volatile (
    "movq %1, %%rsi\n\t"
    "movw (%%rsi), %%ax\n\t"
    "xor %%rcx, %%rcx\n\t"
    "inc %%rcx\n\t"
    "loop:\n\t"
    "cmp $10, %%rcx\n\t"
    "jae end\n\t"
    "movw (%%rsi, %%rcx, 2), %%bx\n\t"
    "cmp %%ax, %%bx\n\t"
    "jg greater\n\t"
    "next:\n\t"
    "inc %%rcx\n\t"
    "jmp loop\n\t"
    "greater:\n\t"
    "mov %%bx, %%ax\n\t"
    "mov %%rcx, %%rdx\n\t"
    "jmp next\n\t"
    "end:\n\t"
    "inc %%rdx\n\t"
    "loop2:\n\t"
    "cmp $10, %%rdx\n\t"
    "jge final\n\t"
    "movw $0, (%%rsi, %%rdx, 2)\n\t"
    "inc %%rdx\n\t"
    "jmp loop2\n\t"
    "final:\n\t"
    "movw %%ax, %0"
    : "=r"(max)
    : "r"(g)
    : "rax", "rbx", "rdx", "rcx", "rdi", "rsi", "cc"
  );
  std::cout << max << '\n';
  print<short>(g, 10);
  return 0;
}
