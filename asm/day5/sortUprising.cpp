#include <cstddef>
#include <iomanip>
#include <iostream>
#include <random>

template <typename T>
void print(const T* arr, size_t size)
{
  std::cout << "| ";
  for(size_t i{}; i < size; i++)
  {
    std::cout << std::setw(3) << arr[i] << " | ";
  }
}

template <typename T, size_t size1, size_t size2>
void printMatrix(T matrix[size1][size2])
{
  for(size_t i{}; i < size1; i++)
  {
    print<T>(matrix[i], size2);
    std::cout << '\n';
  }
}

int main()
{
  const size_t size1{4};
  const size_t size2{5};
  const size_t size5{size2 + 1};
  size_t size3 = size1;
  size_t size4 = size2;
  std::random_device rd;
  std::mt19937 gg(rd());
  std::uniform_int_distribution<int> gen(-2, 2);
  int matrix[size1][size2];
  for(size_t i{}; i < size1; i++)
  {
    for(size_t j{}; j < size2; j++)
    {
      if(i == j)
      {
        matrix[i][j] = 0;
      } else
      {
        matrix[i][j] = gen(gg);
      }
    }
  }
  std::cout << "Before shifting 0 to end: \n";
  printMatrix<int, size1, size2>(matrix);
  asm volatile
  (
    "dec %0\n\t"
    "dec %1\n\t"
    "movq %2, %%rsi\n\t"
    "xor %%rcx, %%rcx\n\t"
    "xor %%rdx, %%rdx\n\t"
    "xor %%rbx, %%rbx\n\t"
    "xor %%rdi, %%rdi\n\t"

    "rows:\n\t"
    "cmp %0, %%rcx\n\t"
    "jg end1\n\t"

      "columns:\n\t"
      "cmp %1, %%rdx\n\t"
      "jg fill_zeros\n\t"

      "movl (%%rsi, %%rdx, 4), %%eax\n\t"

      "test %%eax, %%eax\n\t"
      "jz skip_filling\n\t"

      "movl %%eax, (%%rsi, %%rdi, 4)\n\t"
      "inc %%rdi\n\t"

      "skip_filling:\n\t"
      "inc %%rdx\n\t"
      "jmp columns\n\t"

      "fill_zeros:\n\t"
      "cmp %1, %%rdi\n\t"
      "jg next_row\n\t"
      "movl $0, (%%rsi, %%rdi, 4)\n\t"
      "inc %%rdi\n\t"
      "jmp fill_zeros\n\t"
    "next_row:\n\t"
    "inc %%rcx\n\t"
    "lea (%%rsi, %%rdx, 4), %%rsi\n\t"
    "xor %%rdx, %%rdx\n\t"
    "xor %%rdi, %%rdi\n\t"
    "jmp rows\n\t"

    "end1:\n\t"
    : "+r"(size3), "+r"(size4)
    : "r"(matrix)
    : "rax", "rbx", "rcx", "rdx", "rsi", "rdi", "cc", "memory"
  );
  std::cout << "\nAfter shifting 0 to end: \n";
  printMatrix<int, size1, size2>(matrix);
  int tempMatrix[size1][size2 + 1];
  asm volatile
  (
    "lea (%0), %%rsi\n\t"
    "lea (%1), %%rdi\n\t"
    "xor %%rbx, %%rbx\n\t"
    "xor %%rcx, %%rcx\n\t"
    "xor %%rdx, %%rdx\n\t"

    "copying_row:\n\t"
      "cmp %2, %%rcx\n\t"
      "jge end2\n\t"

      "copying_column:\n\t"
        "cmp %3, %%rdx\n\t"
        "jge next_row2\n\t"

        "movl (%%rsi, %%rdx, 4), %%eax\n\t"
        "movl %%eax, (%%rdi, %%rdx, 4)\n\t"
        "test %%eax, %%eax\n\t"
        "jnz next_column\n\t"
        "inc %%ebx\n\t"
        
      "next_column:\n\t"
        "inc %%rdx\n\t"
        "jmp copying_column\n\t"

    "next_row2:\n\t"
      "lea (%%rsi, %%rdx, 4), %%rsi\n\t"
      "movl %%ebx, (%%rdi, %%rdx, 4)\n\t"
      "inc %%rdx\n\t"
      "inc %%rcx\n\t"
      "lea (%%rdi, %%rdx, 4), %%rdi\n\t"
      "xor %%rbx, %%rbx\n\t"
      "xor %%rdx, %%rdx\n\t"
      "jmp copying_row\n\t"

    "end2:\n\t"
    : 
    : "r"(matrix), "r"(tempMatrix), "r"(size1), "r"(size2)
    : "rax", "rbx", "rcx", "rdx", "rsi", "rdi", "cc", "memory"
  );
  std::cout << "\nAfter adding column for zeros:\n";
  printMatrix<int, size1, size5>(tempMatrix);
  asm volatile
  (
    "movq %1, %%rdi\n\t"
    // "movl -4(%0, %2, 4), %%ebx\n\t"
    "xor %%rcx, %%rcx\n\t"
    "xor %%rdx, %%rdx\n\t"

    "sort_cycle:\n\t"
      "cmp $0, %%rdi\n\t"
      "jle end3\n\t"
      "lea (%0), %%rsi\n\t"
      "movl -4(%0, %2, 4), %%ebx\n\t"


      "go_through_zeros:\n\t"
        "cmp %%rdi, %%rcx\n\t"
        "jge swap_rows\n\t"
        "movl -4(%%rsi, %2, 4), %%eax\n\t"
        "cmp %%eax, %%ebx\n\t"
        "jl swap_index\n\t"

        "next_zero:\n\t"
        "inc %%rcx\n\t"
        "lea (%%rsi, %2, 4), %%rsi\n\t"
        "jmp go_through_zeros\n\t"
        
        "swap_index:\n\t"
        "movl %%eax, %%ebx\n\t"
        "movq %%rcx, %%rdx\n\t"
        "jmp next_zero\n\t"

      "swap_rows:\n\t"
        "movq %%rdx, %%rax\n\t"
        "imul %2, %%rax\n\t"
        "lea (%0, %%rax, 4), %%rsi\n\t"

        "movq %%rdi, %%rax\n\t"
        "dec %%rax\n\t"
        "imul %2, %%rax\n\t"
        "lea (%0, %%rax, 4), %%rbx\n\t"
        "xor %%rcx, %%rcx\n\t"

        "swapping:\n\t"
        "cmp %2, %%rcx\n\t"
        "jge sort_next\n\t"
        "movl (%%rsi, %%rcx, 4), %%eax\n\t"
        "movl (%%rbx, %%rcx, 4), %%edx\n\t"
        "movl %%eax, (%%rbx, %%rcx, 4)\n\t"
        "movl %%edx, (%%rsi, %%rcx, 4)\n\t"
        "inc %%rcx\n\t"
        "jmp swapping\n\t"
        
    "sort_next:\n\t"
    "dec %%rdi\n\t"
    "xor %%rcx, %%rcx\n\t"
    "xor %%rdx, %%rdx\n\t"
    "jmp sort_cycle\n\t"
    
    "end3:\n\t"
    : 
    : "r"(tempMatrix), "r"(size1), "r"(size5)
    : "rax", "rbx", "rcx", "rdx", "rsi", "rdi", "cc", "memory"
  );
  std::cout << "\nAfter sorting:\n";
  printMatrix<int, size1, size5>(tempMatrix);
  return 0;
}
