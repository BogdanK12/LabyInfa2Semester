#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <random>

extern "C" void sort(int* array, size_t size) __attribute__((sysv_abi));

extern "C" void findClosestToAverage(int* array, size_t length, int** result) __attribute__((sysv_abi));

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

void bubble_sort(int *arr, size_t size)
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

int* copy(int *arr, size_t size)
{
  int *retval = new int[size];
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
  std::uniform_int_distribution<int> elem(-100, 100);

  int *g = new int[size];

  for(int i = 0; i < size; i++)
  {
    g[i] = elem(gener);
  }

  int *cpp = copy(g, size);

  print<int>(g, size);
  std::cout << "Sorted using Assembly: \n";
  sort(g, size);
  print<int>(g, size);

  bubble_sort(cpp, size);
  std::cout << "Sorted using C++: \n";
  print<int>(cpp, size);
  int* closestToAverage;
  findClosestToAverage(g, size, &closestToAverage);
  std::cout << "\nClosest to average: " << *closestToAverage;
  return 0;
}
