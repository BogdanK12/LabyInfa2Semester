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
  const size_t size2{7};
  int *array = new int[size]{1, 2, 7, 13, 34, 45, 52, 71, 90, 101};
  int *array2 = new int[size2]{4, 22, 44, 52, 56, 77, 101};
  /*
      rsi, rbx - source array pointers
      rdi - destination array
      rax, rdx - for comparing
      rcx - counter
  */
  print<int>(array, size);
  print<int>(array2, size2);
  int *array3 = new int[size + size2];
  asm volatile
  (
    "movq %1, %%r10\n\t"
    "movq %3, %%r11\n\t"
    "xor %%r8,  %%r8\n\t"
    "xor %%r9,  %%r9\n\t"
    "xor %%rdx, %%rdx\n\t"
    "movslq (%0, %%r8, 4), %%rax\n\t"
    "movslq (%2, %%r9, 4), %%rbx\n\t"

    "loop:\n\t"
    "addq %%r8, %%r9\n\t"
    "addq %%r10, %%r11\n\t"
    "cmp %%r9, %%r11\n\t"
    "jge end\n\t"
    "subq %%r8, %%r9\n\t"
    "subq %%r10, %%r11\n\t"
    "cmp %%r8, %%r10\n\t"
    "jge end_of_1_array\n\t"
    "cmp %%rax, %%rdx\n\t"
    "jle rax_is_less\n\t"

    "rax_is_less:\n\t"
    "addq %%r8, %%r9\n\t"
    "movl %%eax, (%4, %%r9, 4)\n\t"
    "subq %%r8, %%r9\n\t"
    "inc %%r8\n\t"
    "movslq (%0, %%r8, 4), %%rax\n\t"
    "jmp loop\n\t"

    "rbx_is_less:\n\t"
    "addq %%r8, %%r9\n\t"
    "movl %%ebx, (%4, %%r9, 4)\n\t"
    "subq %%r8, %%r9\n\t"
    "inc %%r9\n\t"
    "movslq (%2, %%r9, 4), %%rbx\n\t"
    "jmp loop\n\t"

    "end_of_1_array:\n\t"
    "cmp %%r9, %%r11\n\t"
    "jge end\n\t"

    "end_of_2_array:\n\t"
    "cmp %%r8, %%r10\n\t"
    "jge end\n\t"
    
    "end:\n\t"
    : 
    : "r"(array), "r"(size), "r"(array2), "r"(size2), "r"(array3)
    : "rax", "rbx", "rcx", "rdx", "r8", "r9", "r10", "r11", "cc", "memory"
  );
  print <int> (array3, size + size2);
  return 0;  
}


