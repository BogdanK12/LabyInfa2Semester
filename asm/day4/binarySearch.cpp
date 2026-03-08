#include <cstddef>
#include <iostream>

template <typename T>
void print(const T* arr, size_t size)
{
  std::cout << "| ";
  for(size_t i{}; i < size; i++)
  {
    std::cout << arr[i] << " | ";
  }
  std::cout << '\n';
}

int main()
{
  const size_t size{10};
  int *array = new int[size]{1, 2, 7, 13, 34, 45, 52, 71, 90, 101};
  int element;
  if (!(std::cin >> element))
  {
    std::exit(52);
  }
  size_t length, index;
  /*
      rsi - array pointer
      rdi - array size - 1
      rax, rbx - for comparing
      r8, r9 - lower/upper bound
  */
  int exists{1};
  print<int>(array, size);
  asm volatile
  (
    "movq %2, %%rsi\n\t"
    "movq %3, %%rdi\n\t"
    "dec %%rdi\n\t"
    "movslq %4, %%rcx\n\t"
    "movq %%rdi, %%rax\n\t"
    "xor %%rbx, %%rbx\n\t"
    "xor %%rdx, %%rdx\n\t"
    "xor %%r8, %%r8\n\t"
    "movq %%rdi, %%r9\n\t"
    "shr $1, %%rax\n\t"
    
    "loop:\n\t"
    "cmp %%r9, %%r8\n\t"
    "jg no_element\n\t"
    "movslq (%%rsi, %%rax, 4), %%rbx\n\t"
    "cmp %%rcx, %%rbx\n\t"
    "je end\n\t"
    "jl greater\n\t"
    "jg less\n\t"

    "greater:\n\t"
    "movq %%rax, %%r8\n\t"
    "inc %%r8\n\t"
    "jmp next\n\t"

    "less:\n\t"
    "movq %%rax, %%r9\n\t"
    "dec %%r9\n\t"
    "jmp next\n\t"

    "next:\n\t"
    "movq %%r9, %%rax\n\t"
    "addq %%r8, %%rax\n\t"
    "shr $1, %%rax\n\t"
    "jmp loop\n\t"

    "no_element:\n\t"
    "movl $0, %1\n\t"
    "movq $-1, %0\n\t"
    "jmp very_end\n\t"
    
    "end:\n\t"
    "movl $1, %1\n\t"
    "movq %%rax, %0\n\t"
    "very_end:\n\t"
    : "=r"(index), "=r"(exists)
    : "r"(array), "r"(size), "r"(element)
    : "rax", "rbx", "rcx", "rdx", "rsi", "rdi", "r8", "r9", "cc", "memory"
  );
  if (exists)
  {
    std::cout << "Index: " << index;
  } else
  {
    std::cout << "There is no such element.\n";
  }
  return 0;  
}

