#include <cstddef>
#include <iostream>
#include <random>

void print(const int* arr, size_t size)
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
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> generator(-9000, 9000);
  const size_t size{10};
  size_t newSize;
  int *arr = new int[size];
  for(size_t i{}; i < size; i++)
  {
    arr[i] = generator(gen);
  }
  for(size_t i{}; i < size/2; i++)
  {
    arr[size - i - 1] = arr[i];
  }
  arr[0] = 0;
  /* count unique first */
  asm volatile
  (
    "movq %1, %%rsi\n\t" // rsi - array
    "movq %2, %%rdi\n\t" // rdi - size(10)
    "cmp $0, %%rdi\n\t"
    "je end1\n\t"
    "xor %%rax, %%rax\n\t" // rax = 0
    "xor %%rbx, %%rbx\n\t" // rbx = 0
    "xor %%rcx, %%rcx\n\t"
    "xor %%r9, %%r9\n\t"

    "external_loop1:\n\t"
    "cmp %%rdi, %%rcx\n\t"
    "jae end1\n\t"
    "xor %%rdx, %%rdx\n\t"
    "xor %%r8, %%r8\n\t"
    "movl (%%rsi, %%rcx, 4), %%eax\n\t"

      "inner_loop1:\n\t"
      "cmp %%rcx, %%rdx\n\t"
      "jae external_next1\n\t"

      "cmp %%rcx, %%rdx\n\t"
      "jz inner_next1\n\t"

      "movl (%%rsi, %%rdx, 4), %%ebx\n\t"
      "cmp %%ebx, %%eax\n\t"
      "jz equal1\n\t"
    
      "inner_next1:\n\t"
      "inc %%rdx\n\t"
      "jmp inner_loop1\n\t"

      "equal1:\n\t"
      "inc %%r8\n\t"
      "jmp inner_next1\n\t"
    
    "external_next1:\n\t"
    "inc %%rcx\n\t"
    "cmp $0, %%r8\n\t"
    "jz increase_r9\n\t"
    "jmp external_loop1\n\t"
  
    "increase_r9:\n\t"
    "inc %%r9\n\t"
    "jmp external_loop1\n\t"

    "end1:\n\t"
    "movq %%r9, %0\n\t"
    : "=r"(newSize)
    : "r"(arr), "r"(size)
    : "rax", "rbx", "rcx", "rdx", "rsi", "rdi", "r8", "r9", "cc"
  );
  print(arr, size);
  std::cout << newSize << '\n';
  int *newArray = new int[newSize];
  asm volatile
  (
    "movq %0, %%rsi\n\t" // rsi - array
    "mov %1, %%r10\n\t"
    "movq %2, %%rdi\n\t" // rdi - size(10)
    "cmp $0, %%rdi\n\t"
    "je end2\n\t"
    "xor %%rax, %%rax\n\t" // rax = 0
    "xor %%rbx, %%rbx\n\t" // rbx = 0
    "xor %%rcx, %%rcx\n\t"
    "xor %%r9, %%r9\n\t"

    "external_loop2:\n\t"
    "cmp %%r10, %%rcx\n\t"
    "jae end2\n\t"
    "xor %%rdx, %%rdx\n\t"
    "xor %%r8, %%r8\n\t"
    "movl (%%rsi, %%rcx, 4), %%eax\n\t"

      "inner_loop2:\n\t"
      "cmp %%rcx, %%rdx\n\t"
      "jae external_next2\n\t"

      "cmp %%rcx, %%rdx\n\t"
      "jz inner_next2\n\t"

      "movl (%%rsi, %%rdx, 4), %%ebx\n\t"
      "cmp %%ebx, %%eax\n\t"
      "jz equal2\n\t"
    
      "inner_next2:\n\t"
      "inc %%rdx\n\t"
      "jmp inner_loop2\n\t"

      "equal2:\n\t"
      "inc %%r8\n\t"
      "jmp inner_next2\n\t"
    
    "external_next2:\n\t"
    "inc %%rcx\n\t"
    "cmp $0, %%r8\n\t"
    "jz unique\n\t"
    "jmp external_loop2\n\t"
  
    "unique:\n\t"
    "movl %%eax, (%%rdi, %%r9, 4)\n\t"
    "inc %%r9\n\t"
    "jmp external_loop2\n\t"

    "end2:\n\t"
    : 
    : "r"(arr), "r"(size), "r"(newArray), "r"(newSize)
    : "rax", "rbx", "rcx", "rdx", "rsi", "rdi", "r8", "r9", "r10", "cc"
  );
  print(newArray, newSize);
  return 0;
}
