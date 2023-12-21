#include <iostream>

using namespace std;

//Описание структуры Node, представляющей узел дерева
struct Node
{
	int value;// Значение ключа
	struct Node* left, * right;//Указатели на левое и правое поддерево
};

//Функция создания нового узла дерева
struct Node* newNode(int item)
{
	struct Node* temp = new Node;// Выделение памяти для нового узла
	temp->value = item;// Присваивание значения 
	temp->left = temp->right = NULL;// Инициализация указателей на левое и правое поддерево
	return temp;// Возврат указателя на новый узел
}

// Функция для сохранения отсортированных значений в массиве
void storeSorted(Node* root, int arr[], int& i)
{
	if (root != NULL)// Если узел не равен NULL
	{
		storeSorted(root->left, arr, i);// Рекурсивный вызов для сохранения отсортированных значений в левом поддереве
		arr[i++] = root->value;// Сохранение значения в массиве и увеличение счетчика i
		storeSorted(root->right, arr, i);// Рекурсивный вызов для сохранения отсортированных значений в правом поддереве
	}
}

// Функция для вставки нового узла в дерево
Node* insert(Node* node, int key)
{
	if (node == NULL) return newNode(key);// Если узел равен NULL, создаем новый узел

	if (key < node->value)// Если значение меньше значения текущего узла, рекурсивно вставляем узел в левое поддерево
	{
		node->left = insert(node->left, key);
	}
	else if (key > node->value)// Если значение больше значения текущего узла, рекурсивно вставляем узел в правое поддерево
	{
		node->right = insert(node->right, key);
	}
	return node;
}

// Функция для сортировки массива с помощью двоичного дерева поиска
void treeSort(int arr[], int n)
{
	struct Node* root = NULL;// Создание корневого узла дерева
	root = insert(root, arr[0]);
	
	// Вставка остальных элементов массива в дерево
	for (int i = 1; i < n; i++)
	{
		root = insert(root, arr[i]);
	}

	int i = 0;
	storeSorted(root, arr, i);// Сохранение отсортированных значений в массиве
}

int main()
{
	int arr[] = { 9, 10, 8, 5, 4 };// Инициализация исходного массива
	int n = sizeof(arr) / sizeof(arr[0]);// Вычисление размера массива


	treeSort(arr, n);// Вызов функции сортировки массива с помощью двоичного дерева

	
	// Вывод отсортированного массива
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
	std::cout << std::endl;
	
}
