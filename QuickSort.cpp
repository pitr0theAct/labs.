

#include <iostream>

//Основаная функция для сортировки
void QuickSort(int mas[], int left, int right)
{
    //Если оказалось что левая граница больше правой то все уже отсортировано
    if (left > right)
    {
        return;
    }
    
    //Задаем опорный элемент как середину массива
    int p = mas[(left + right) / 2];
    //Задаем индексы
    int i = left;
    int j = right;
    
    while (i <= j)
    {
        //Пока i элемент < опроного элемента двигаем i вперед
        while (mas[i] < p) i++;
        //Пока j  элемент > опроного элемента двигаем j назад
        while (mas[j] > p) j--;
        
        //Меняем элементы местами
        if (i <= j)
        {
            int tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;
            i++;
            j--;
        }
        
    
    
    }
    //Рекурсивно сортируем элементы до и после опорного элемента
    QuickSort(mas, left, j);
    QuickSort(mas, i, right);




}


//Функция для вывода массива на экран
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}



int main()
{
    
    setlocale(LC_ALL, "Russian");
    
    
    int const n = 6;
    int arr[] = { 10, 7, 8, 9, 1, 5 };
    

    std::cout << "Исходный массив:" << std::endl;
    printArray(arr, n);

    QuickSort(arr, 0, n - 1);

    std::cout << "Отсортированный массив:" << std::endl;
    printArray(arr, n);

    
}


