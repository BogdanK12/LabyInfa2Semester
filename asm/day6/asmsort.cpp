#include <climits>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <random>

extern "C" void sort(short* array, size_t size) __attribute__((sysv_abi));

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

  short *g = new short[size];

  for(int i = 0; i < size; i++)
  {
    g[i] = elem(gener);
  }

  short *cpp = copy(g, size);

  print<short>(g, size);
  std::cout << "Sorted using Assembly: \n";
  sort(g, size);
  print<short>(g, size);

  bubble_sort(cpp, size);
  std::cout << "Sorted using C++: \n";
  print<short>(cpp, size);
  return 0;
}
