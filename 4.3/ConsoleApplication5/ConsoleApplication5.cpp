

#include <iostream>
/*Дана целочисленная матрица{Aij}i = 1..n, j = 1..m(n, m <= 100).Найти строку с наибольшим произведением элементов и заменить все
элементы этой строки этим произведением.*/




//Заменяет строку массива с наибольшим произведением элементов этим произведением 
void swapLine(int m[100][100], int maxi, int b)
{
	int n = 0;
	int k = 0;
	for (int j = 0; j <= b - 2; j++)
	{
		k = m[maxi][j] * m[maxi][j + 1];
	}
	for (int j = 0; j < b; j++)
	{
		m[maxi][j] = k;
	}
}

//Находит наибольшее произвидение элеменов 
void Summ(int arr[100][100], int a, int b)
{
	int max = 0;
	int maxi = 0;
	int k = 1;
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
		{
			k *= arr[i][j];
			if (k > max)
			{
				max = k;
				maxi = i;
			}
		}
	}
	swapLine(arr, maxi, b);
}


int main()
{
	int N;
	int n;
	int matrix[100][100];
	std::cin >> N;
	std::cin >> n;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cin >> matrix[i][j];
		}
	}
	std::cout << std::endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	Summ(matrix, N, n);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

