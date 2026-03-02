#include <iostream>
#include <memory> // для std::shared_ptr
 
class Item
{
public:
	Item() { std::cout << "Item acquired\n"; }
	~Item() { std::cout << "Item destroyed\n"; }
};
 
int main()
{
	auto ptr1 = std::make_shared<Item>();
	std::shared_ptr<Item> ptr2(ptr1);
 
	return 0;
}

