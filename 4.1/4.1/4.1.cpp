#include <iostream>
//Дана последовательность натуральных чисел {aj}j=1...n (n<=10000). Если в последовательности нет ни одного простого числа, упорядочить последовательность по неубыванию.


//Пузырьковая сортировка
void bubbleSort(int list[], int listLength)
{
	while (listLength--)
	{
		bool swapped = false;

		for (int i = 0; i < listLength; i++)
		{
			if (list[i] > list[i + 1])
			{
				std::swap(list[i], list[i + 1]);
				swapped = true;
			}
		}

		if (swapped == false)
			break;
	}
}
int main()
{
	int size;//Размер
	int mas[100000];
	std::cout << " " << std::endl;
	std::cin >> size;
	int simple=0;
	//Ввод массива 
	for (int i = 0; i < size; i++)
	{
		std::cin >> mas[i];
		//Проверка на простые числа
		for (int d = 2; d < i; d++)
		{
			if ((mas[i] % d) == 0)
			{
				simple += 1;
			}
		}
	}

	//Если не простых чисел сортируем 
	if (simple != 0)
	{
		bubbleSort(mas, size);
	}

	//Выыод массива 
	for (int i = 0; i < size; i++)
	{
		std::cout << mas[i] << " ";
	}
}