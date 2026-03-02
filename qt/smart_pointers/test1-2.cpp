#include <iostream>
#include <memory> // для std::unique_ptr
 class Fraction
{
private:
	int m_numerator = 0;
	int m_denominator = 1;
 public:
	Fraction(int numerator = 0, int denominator = 1) :
m_numerator(numerator), m_denominator(denominator)
	{
	}
 
	friend std::ostream& operator<<(std::ostream& out, const Fraction &f1)
	{out << f1.m_numerator << "/" << f1.m_denominator; 		return out;
	}
};
 
// Эта функция использует объект класса Fraction, поэтому //мы только его передаем.  Таким образом, мы можем не //беспокоиться о том, какой умный указатель использует //caller  
void printFraction(const Fraction* const ptr)
{
	if (ptr)		std::cout << *ptr;
}
 
int main()
{
	auto ptr = std::make_unique<Fraction>(7, 9);
 	printFraction(ptr.get());
 	return 0;
}

