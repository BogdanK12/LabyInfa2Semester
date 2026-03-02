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
  short *g = (short *)malloc(10 * sizeof(short));
  for(int i = 0; i < 10; i++)
  {
    g[i] = elem(gener);
  }
  print<short>(g, 10);
  asm volatile (
    "mov (%4), %%bx\n\t"
    "mov %%bx, %%cx\n\t"
    "xor %%rdx, %%rdx\n\t"
    "xor %%esi, %%esi\n\t"
    "xor %%edi, %%edi\n\t"
    "inc %%rdx\n"
    "j1:\n\t"
    "cmp $10, %%rdx\n\t"
    "je end\n\t"
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
    : "r"(g)
    : "eax", "ebx", "edx", "ecx", "edi", "esi", "cc"
  );
  std::cout << min << " : " << minIndex << " | " << max << " : " <<  maxIndex << '\n';
  // long averageOfPositives;
  // asm volatile
  // (
  // "movq %1, %%rsi\n\t"
  // "xor %%rax, %%rax\n\t"
  // "xor %%rbx, %%rbx\n\t"
  // "xor %%rcx, %%rcx\n\t"
  // "xor %%rdi, %%rdi\n"
  // "loop:\n\t"
  // "cmp $10, %%rcx\n\t"
  // "jbe end1\n\t"
  // "movw (%%rsi, %%rcx, 2), %%bx\n\t"
  // "cmp $0, %%rbx\n\t"
  // "inc %%rcx\n\t"
  // "jl loop\n\t"
  // "addq %%rbx, %%rax\n\t"
  // "inc %%rdi\n\t"
  // "jmp loop\n\t"
  // "end1:\n\t"
  // "xor %%rdx, %%rdx\n\t" 
  // "cmp $0, %%rdi\n\t"
  // "jle end2\n\t"
  // "div %%rdi\n\t"
  // "end2:\n\t"
  // "movq %%rax, %0\n\t"
  // : "=r"(averageOfPositives)
  // : "r"(g), "r"(minIndex)
  // : "rax", "rbx", "rcx", "rdx", "rdi"
  // );
  // std::cout << averageOfPositives;
  return 0;
}
