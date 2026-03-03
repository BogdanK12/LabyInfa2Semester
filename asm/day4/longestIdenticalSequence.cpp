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
  int *array = new int[size]{1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
  size_t length, index;
  /*
      rsi - array pointer
      rdi - array size - 1
      rax, rbx - for comparing
      rcx - counter
      rdx - counter of current sequence(?)
      r8  - counter for longest sequence
      r9  - counter for longest sequence start index 
  */
  asm volatile
  (
    "movq %2, %%rsi\n\t"
    "movq %3, %%rdi\n\t"
    "cmp $0, %%rdi\n\t"
    "je end\n\t"
    "dec %%rdi\n\t"
    "xor %%rax, %%rax\n\t"
    "xor %%rcx, %%rcx\n\t"
    "xor %%rdx, %%rdx\n\t"
    "xor %%r8,  %%r8\n\t"
    "xor %%r9,  %%r9\n\t"
    "movl (%%rsi, %%rcx, 4), %%ebx\n\t"

    "loop:\n\t"
    "cmp %%rdi, %%rcx\n\t"
    "ja end\n\t"

    "movl (%%rsi, %%rcx, 4), %%eax\n\t"
    "cmp %%eax, %%ebx\n\t"
    "je equal\n\t"

    "not_equal:\n\t"
    "mov %%eax, %%ebx\n\t"
    "cmp %%r8, %%rdx\n\t"
    "jbe change_current\n\t"

    "replace_sequence:\n\t"
    "movq %%rdx, %%r8\n\t"
    "movq %%rcx, %%r9\n\t"
    "sub %%rdx, %%r9\n\t"

    "change_current:\n\t"
    "xor %%rdx, %%rdx\n\t"
    "inc %%rdx\n\t"
    
    "next:\n\t"
    "inc %%rcx\n\t"
    "jmp loop\n\t"

    "equal:\n\t"
    "inc %%rdx\n\t"
    "jmp next\n\t"
    
    "end:\n\t"
    "cmp %%r8, %%rdx\n\t"
    "jbe end2\n\t"
    "movq %%rdx, %%r8\n\t"
    "movq %%rcx, %%r9\n\t"
    "sub %%rdx, %%r9\n\t"

    "end2:\n\t"
    "movq %%r8, %0\n\t"
    "movq %%r9, %1\n\t"
    : "=r"(length), "=r"(index)
    : "r"(array), "r"(size)
    : "rcx", "rsi", "rdi", "cc"
  );
  print<int>(array, size);
  std::cout << "Index: " << index << ", length: " << length << '\n';
  return 0;  
}
