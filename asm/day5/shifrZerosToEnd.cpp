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
    "xor %%rcx, %%rcx\n\t"
    "xor %%rdx, %%rdx\n\t"
    "xor %%rbx, %%rbx\n\t"
    "xor %%rdi, %%rdi\n\t"

    "rows:\n\t"
    "cmp %0, %%rcx\n\t"
    "jge end\n\t"

      "columns:\n\t"
      "cmp %1, %%rdx\n\t"
      "jge rows_next\n\t"

      "lea (%2, %%rbx), %%rsi\n\t"
      "movslq (%%rsi, %%rdx, 4), %%rax\n\t"

      "test %%rax, %%rax\n\t"
      "jnz columns_next\n\t"

      "inc %%rdi\n\t"
      "push %%rcx\n\t"
      "movq %1, %%rcx\n\t"
      "dec %%rcx\n\t"

        "do_stuff:\n\t"
        "cmp %%rdx, %%rcx\n\t"
        "jl pre_next\n\t"
        "movslq (%%rsi, %%rcx, 4), %%rax\n\t"
        "movl %%eax, -4(%%rsi, %%rcx, 4)\n\t"
      
      "pre_next:\n\t"
      "pop %%rcx\n\t"
      
        "pop %%rsi\n\t"
        "filling_zero:\n\t"
        "movq "

      "columns_next:\n\t"
      "inc %%rdx\n\t"
      "jmp columns\n\t"

    "rows_next:\n\t"
    "inc %%rcx\n\t"
    "movq %1, %%rax\n\t"
    "mul %%rcx\n\t"
    "shl $2, %%rax\n\t"
    "movq %%rax, %%rbx\n\t"
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
