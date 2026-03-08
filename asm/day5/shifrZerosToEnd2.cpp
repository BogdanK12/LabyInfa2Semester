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

template <typename T, size_t size1, size_t size2>
void printMatrix(T matrix[size1][size2])
{
  for(size_t i{}; i < size1; i++)
  {
    print<T>(matrix[i], size2);
  }
}

int main()
{
  const size_t size1{4};
  const size_t size2{5};
  size_t size3 = size1;
  size_t size4 = size2;
  int matrix[size1][size2];
  for(size_t i{}; i < size1; i++)
  {
    for(size_t j{}; j < size2; j++)
    {
      if(i == j)
      {
        matrix[i][j] = 1;
      } else
      {
        matrix[i][j] = i*j;
      }
    }
  }
  // int tempMatrix[size1][size2];
  printMatrix<int, size1, size2>(matrix);
  /* shifting zeros to right end using assembly */
  asm volatile
  (
    "dec %0\n\t"
    "dec %1\n\t"
    "movq %0, %%rsi\n\t"
    "xor %%rcx, %%rcx\n\t"
    "xor %%rdx, %%rdx\n\t"
    "xor %%rbx, %%rbx\n\t"
    "xor %%rdi, %%rdi\n\t"

    "rows:\n\t"
    "cmp %0, %%rcx\n\t"
    "jg end\n\t"

      "columns:\n\t"
      "cmp %1, %%rdx\n\t"
      "jg rows_next\n\t"

      "movslq (%%rsi), %%rax\n\t"

      "test %%rax, %%rax\n\t"
      "jnz columns_next\n\t"

      "inc %%rdi\n\t"
      "push %%rcx\n\t"
      "movq %%rdx, %%rcx\n\t"

        "do_stuff:\n\t"
        "cmp %1, %%rcx\n\t"
        "jge pre_next\n\t"
        "movslq 4(%%rsi, %%rcx, 4), %%rax\n\t"
        "movl %%eax, (%%rsi, %%rcx, 4)\n\t"
        "inc %%rcx\n\t"
        "jmp do_stuff\n\t"
      
      "pre_next:\n\t"
      "pop %%rcx\n\t"
      
      "columns_next:\n\t"
      "inc %%rdx\n\t"
      "addq $4, %%rsi\n\t"
      "jmp columns\n\t"

    "rows_next:\n\t"
    "inc %%rcx\n\t"
    // "addq $4, %%rsi\n\t"
    "xor %%rdx, %%rdx\n\t"
    "jmp rows\n\t"

    "end:\n\t"
    : "+r"(size3), "+r"(size4)
    : "r"(matrix)
    : "rax", "rbx", "rcx", "rdx", "rsi", "rdi", "cc", "memory"
  );
  std::cout << '\n';
  printMatrix<int, size1, size2>(matrix);
  return 0;
}
