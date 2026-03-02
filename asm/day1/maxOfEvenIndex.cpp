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

short maxOfEvenIndexes(const short* g, size_t size)
{
  short max = g[0];
  for(size_t i{}; i < size; i += 2)
  {
    if(g[i] > max)
    {
      max = g[i];
    }
  }
  return max;
}

int main()
{
  std::random_device rd;
  std::mt19937 gener(rd());
  std::uniform_int_distribution<short> elem(SHRT_MIN, SHRT_MAX);
  short max;
  short *g = new short[10];
  for(int i = 0; i < 10; i++)
  {
    g[i] = elem(gener);
  }
  print<short>(g, 10);
  asm volatile (
    "movq %1, %%rsi\n\t"
    "xor %%rax, %%rax\n\t"
    "xor %%rbx, %%rbx\n\t"
    "xor %%rcx, %%rcx\n\t"
    "movswq (%%rsi), %%rax\n\t"
    "inc %%rcx\n\t"
    "inc %%rcx\n\t"

    "loop:\n\t"
    "cmp $10, %%rcx\n\t"
    "jae end\n\t"
    "movswq (%%rsi, %%rcx, 2), %%rbx\n\t"
    "cmp %%rax, %%rbx\n\t"
    "jg greater\n\t"
    
    "next:\n\t"
    "inc %%rcx\n\t"
    "inc %%rcx\n\t"
    "jmp loop\n\t"

    "greater:\n\t"
    "movq %%rbx, %%rax\n\t"
    "jmp next\n\t"
    "end:\n\t"
    "movw %%ax, %0\n\t"
    : "=r"(max)
    : "r"(g)
    : "rax", "rbx", "rcx", "rsi", "cc"
  );
  std::cout << max << " - assembly : "<< maxOfEvenIndexes(g, 10) << " - C++" << '\n';
  return 0;
}
