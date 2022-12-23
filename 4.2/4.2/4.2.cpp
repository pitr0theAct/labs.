

#include <iostream>
/*Ввести последовательность натуральных чисел{Aj}j = 1...n(n <= 1000).Упорядочить последовательность по неубыванию суммы цифр числа,
числа с одинаковыми суммами цифр дополнительно упорядочить по неубыванию произведения цифр числа, числа с одинаковыми суммами цифр и одинаковыми 
произведениями цифр дополнительно упорядочить по неубыванию самого числа.*/





//Функция возвращает Сумму чифр числа
int SumOfDigits(int x)
{
	int sum = 0;
	while (x > 0)
	{
		sum += x % 10;
		x /= 10;
	}
	return sum;
}

//Функция возвращает первую цифру числа 
int firstDigit(int x)
{
	while (x > 9)
		x /= 10;
	return x;
}

//Функция возвращает произведение цифр чила 
int CompOfDigits(int x)
{
	int comp = 1;
	while (x > 0)
	{
		comp *= x % 10;
		x /= 10;
	}
	return comp;
}

int main()
{
	int mas[1000];
	//N - Длинна маиссива
	int N;//Размер массива
	std::cout << "Enter size " << " " << std::endl;
	std::cin >> N;
	//Ввод массива
	for (int i = 0; i < N; i++)
	{
		std::cin >> mas[i];
	}
	for (int i = 0; i < N - 1; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			//сравнение суммы цифр числа
			if (SumOfDigits(mas[i]) > SumOfDigits(mas[j]))
			{
				std::swap(mas[i], mas[j]);
			}
			else if (SumOfDigits(mas[i]) == SumOfDigits(mas[j]))
			{
				//Сравнение произведения цифр чила
				if ((CompOfDigits(mas[i])) > (CompOfDigits(mas[j])))
				{
					std::swap(mas[i], mas[j]);
				}
				else if ((CompOfDigits(mas[i])) == (CompOfDigits(mas[j])))
				{
					//Сравнение самих чисел
					if (firstDigit(mas[i]) == firstDigit(mas[j]))
					{
						if (mas[i] > mas[j])
							std::swap(mas[i], mas[j]);
					}
					else if (firstDigit(mas[i]) > firstDigit(mas[j]))
					{
						std::swap(mas[i], mas[j]);
					}
				}
			}
		}
	}
	//Вывод массива
	for (int i = 0; i < N; i++)
	{
		std::cout << mas[i] << " ";
	}
}
