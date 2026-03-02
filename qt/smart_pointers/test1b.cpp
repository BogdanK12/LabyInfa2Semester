#include <iostream>
#include <memory> // для std::shared_ptr
 
class Something; // предположим, что Something - это класс, который может выбросить исключение
 
int main()
{
	doSomething(std::shared_ptr<Something>(new Something), std::shared_ptr<Something>(new Something));
 
	return 0;
}

