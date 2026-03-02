#include <climits>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <random>

template <class T>
void print(const T* array, size_t size)
{
  for(size_t i{}; i < size; i++)
  {
    std::cout << array[i] << " | ";
  }
  std::cout << '\n';
}

double averageOfPositive(const short* arr, size_t size)
{
  long sum{};
  long ind{};
  for(size_t i{}; i < size; i++)
  {
    if(i[arr] > 0)
    {
      sum += arr[i];
      ind++;
    }
  }
  return static_cast<double>(sum) / ind;
}

int main()
{
  std::random_device rd;
  std::mt19937 gener(rd());
  std::uniform_int_distribution<short> elem(SHRT_MIN, SHRT_MAX);
  short max, min;
  short maxIndex = 0;
  short minIndex = 0;
  short *g = new short[10];
  for(int i = 0; i < 10; i++)
  {
    g[i] = elem(gener);
  }
  print<short>(g, 10);
  long averageOfPositives;
  asm volatile
  (
  "movq %1, %%rsi\n\t"
  "xor %%rax, %%rax\n\t"
  "xor %%rbx, %%rbx\n\t"
  "xor %%rcx, %%rcx\n\t"
  "xor %%rdi, %%rdi\n"
  "loop:\n\t"
  "cmp $10, %%rcx\n\t"
  "jae end1\n\t"
  "movswq (%%rsi, %%rcx, 2), %%rbx\n\t"
  "cmp $0, %%rbx\n\t"
  "jg positive\n\t"
  "next:\n\t"
  "inc %%rcx\n\t"
  "jmp loop\n\t"
  "positive:\n\t"
  "addq %%rbx, %%rax\n\t"
  "inc %%rdi\n\t"
  "jmp next\n\t"
  "end1:\n\t"
  "xor %%rdx, %%rdx\n\t" 
  "cmp $0, %%rdi\n\t"
  "je end2\n\t"
  "idivq %%rdi\n\t"
  "end2:\n\t"
  "movq %%rax, %0\n\t"
  : "=r"(averageOfPositives)
  : "r"(g)
  : "rax", "rbx", "rcx", "rdx", "rdi", "rsi", "cc"
  );
  std::cout << averageOfPositives << " - from assembly, " << averageOfPositive(g, 10) << " - from C++;\n";
  delete [] g;
  return 0;
}
