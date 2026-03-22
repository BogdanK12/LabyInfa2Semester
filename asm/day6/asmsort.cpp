#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <random>

extern "C" void sort(int* array, size_t size) __attribute__((sysv_abi));

extern "C" void findClosestToAverage(int* array, size_t length, int** result) __attribute__((sysv_abi));

extern "C" size_t compare(int* array1, int* array2, size_t length);

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

size_t findPerfectShift(int* arr1, int* arr2, size_t size)
{
  size_t shift{compare(arr1, arr2, size)};
  size_t numberOfShifts{};
  for(size_t i{1}; i < size; i++)
  {
    size_t count{};
    for(size_t j{}; j < size; j++)   
    {
      if(arr1[j] == 1 && arr1[j] == arr2[(j + i) % size]){
        count++;
      }
    }
    if(count > shift)
    {
      shift = count;
      numberOfShifts = i;
    }
  }
  return numberOfShifts;
}

void fillArray(int* array, size_t len)
{
  std::random_device rd;
  std::mt19937 gener(rd());
  std::uniform_int_distribution<int> elem(-100, 100);
  for(int i = 0; i < len; i++)
  {
    array[i] = elem(gener);
  }
}

void binarizeArray(int* array, size_t len)
{
  for(size_t i{}; i < len; i++)
  {
    array[i] = abs(array[i] % 2);
  }
}

int main()
{
  const size_t size{10};

  int *g = new int[size];
  fillArray(g, size);
  int *cpp = copy(g, size);

  int* binaryArray1 = new int[size];
  int* binaryArray2 = new int[size];
  fillArray(binaryArray1, size);
  fillArray(binaryArray2, size);
  binarizeArray(binaryArray1, size);
  binarizeArray(binaryArray2, size);

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
  std::cout << '\n';
  std::cout << "Binary arrays: \n";
  print(binaryArray1, size);
  print(binaryArray2, size);
  std::cout << "\nEqual 1s: " << compare(binaryArray1, binaryArray2, size);
  std::cout << "\n(C++)Perfect shift equals: " << findPerfectShift(binaryArray1, binaryArray2, size);
  return 0;
}
