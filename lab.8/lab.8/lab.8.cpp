//Дано целое число типа unsigned int, выведите на экран содержимое каждого из его байтов, используя знания по указателям.

#include <iostream>

int main()
{
	unsigned int n = UINT_MAX;
	int byte;
	char* pb;
	pb = (char*)&n;
	for (char* i = pb; i < pb + 4; i++)
	{
		byte = (int)*i;
		if (byte < 0)
		{
			std::cout << byte + 256 << " ";
		}
		else
		{
			std::cout << byte << " ";
		}
	}
}
