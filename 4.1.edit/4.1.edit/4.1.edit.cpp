#include <iostream>
//Дана последовательность натуральных чисел {aj}j=1...n (n<=10000). Если в последовательности нет ни одного простого числа, упорядочить последовательность по неубыванию.

//проверка на простые числа 
int notPrime(int x, int size)
{
	bool flag = false;
	for (int d = 2; d <= sqrt(x); d++)
	{
		if ((x % d) == 0)
		{
			flag = true;
		}
	}
	return flag;
}
int main()
{
	int size;
	bool flag = false;
	int mas[10000];
	std::cin >> size;
	std::cout << " " << std::endl;
	int simple = 0;
	int tmp;
	//Ввод массива 
	for (int i = 0; i < size; i++)
	{
		std::cin >> mas[i];
	}
	for (int i = 0; i < size; i++)
	{
		if (notPrime(mas[i], size))
		{
			for (int i = 0; i < size - 1; i++)
			{
				for (int j = 0; j < size; j++)
				{
					//сортировка
					if (mas[i] > mas[j])
					{
						std::swap(mas[i], mas[j]);
					}
				}
			}
		}
	}
	//Выыод массива 
	for (int i = 0; i < size; i++)
	{
		std::cout << mas[i] << " ";
	}
}
