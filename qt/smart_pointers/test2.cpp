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
	Item *item = new Item;
	std::shared_ptr<Item> ptr1(item);
	{
		std::shared_ptr<Item> ptr2(item); // создаем ptr2 напрямую из item (вместо ptr1)
 
		std::cout << "Killing one shared pointer\n";
	} // ptr2 выходит из области видимости здесь, и выделенный Item уничтожается также здесь
 
	std::cout << "Killing another shared pointer\n";
 
	return 0;
}
