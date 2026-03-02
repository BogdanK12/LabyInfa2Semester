#include <climits>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <random>

template <class T>
void print(const T* array, size_t size)
{
  std::cout << "| ";
  for(size_t i{}; i < size; i++)
  {
    std::cout << array[i] << " | ";
  }
  std::cout << '\n';
}

void bubble_sort(short *arr, size_t size)
{
  for(size_t i{}; i < size - 1; i++)
  {
    for(size_t j{}; j < size - i - 1; j++)
    {
      if(arr[j] > arr[j + 1])
      {
        std::swap(arr[j], arr[j + 1]);
      }
    }
  }
}

short* copy(short *arr, size_t size)
{
  short *retval = new short[size];
  for(size_t i{}; i < size; i++)
  {
    retval[i] = arr[i];
  }
  return retval;
}

int main()
{
  const size_t size{10};
  std::random_device rd;
  std::mt19937 gener(rd());
  std::uniform_int_distribution<short> elem(SHRT_MIN, SHRT_MAX);
  short max, min;
  short maxIndex = 0;
  short minIndex = 0;
  short *g = new short[size];
  for(int i = 0; i < size; i++)
  {
    g[i] = elem(gener);
  }
  // for(size_t i{}; i < size; i++)
  // {
  //   g[i] = 52 - 2 * i;
  // }
  // g[0] = 50;
  short *cpp = copy(g, size);
  print<short>(g, size);
  /*  rsi - for adress
      rax(ax), rbx(bx) - for comparison
      rcx, rdx - for cycles
      rdi - for size
       */
  asm volatile (
    "movq %0, %%rsi\n\t"
    "xor %%rax, %%rax\n\t"
    "xor %%rbx, %%rbx\n\t"
    "xor %%rcx, %%rcx\n\t"
    "xor %%rdx, %%rdx\n\t"

    "movq %1, %%rdi\n\t"
    "dec %%rdi\n\t"
    "movq %%rdi, %%r8\n\t"

    "external_loop:\n\t"
    "cmp %%rdi, %%rcx\n\t"
    "jae end\n\t"

      "inner_loop:\n\t"
      "cmp %%r8, %%rdx\n\t"
      "jae external_next\n\t"

      "movw (%%rsi, %%rdx, 2), %%bx\n\t"
      // "inc %%rdx\n\t"
      "movw 2(%%rsi, %%rdx, 2), %%ax\n\t"
      // "dec %%rdx\n\t"
      "cmp %%bx, %%ax\n\t"
      "jl greater\n\t"
      
      "inner_next:\n\t"
      "inc %%rdx\n\t"
      "jmp inner_loop\n\t"

      "greater:\n\t"
      "movw %%ax, (%%rsi, %%rdx, 2)\n\t"
      "movw %%bx, 2(%%rsi, %%rdx, 2)\n\t"
      "jmp inner_next\n\t"

    "external_next:\n\t"
    "inc %%rcx\n\t"
    "dec %%r8\n\t"
    "xor %%rdx, %%rdx\n\t"
    "jmp external_loop\n\t"

    "end:\n\t"
    : 
    : "r"(g), "r"(size)
    : "rax", "rbx", "rdx", "rcx", "rdi", "rsi", "r8", "cc"
  );
  std::cout << "Sorted using Assembly: \n";
  print<short>(g, size);
  bubble_sort(cpp, size);
  std::cout << "Sorted using C++: \n";
  print<short>(cpp, size);
  return 0;
}
