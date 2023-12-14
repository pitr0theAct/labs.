#include <iostream>
#include <vector>

// Функция для нахождения максимального элемента
int findMax(int arr[], int n) 
{
    int maxElement = arr[0];
    for (int i = 1; i < n; i++) 
    {
        if (arr[i] > maxElement) 
        {
            maxElement = arr[i];
        }
    }
    return maxElement;
}



// Функция для сортировки массива по указанному разряду
void countSort(int arr[], int n, int exp) 
{
    const int RANGE = 10; // Диапазон чисел (0-9)
    int* output = new int[n];// Вспомогательный массив для сохранения отсортированного массива(Динамическое выделение памяти)
    int count[RANGE] = { 0 };// Массив для хранения количества элементов с определенными разрядами

    // Подсчитываем количество элементов с определенными разрядами
    for (int i = 0; i < n; i++) 
    {
        count[(arr[i] / exp) % 10]++;
    }

    // Преобразуем count[i] так, чтобы count[i] содержал фактическую позицию
    // данного разряда в отсортированном массиве output[]
    for (int i = 1; i < RANGE; i++) 
    {
        count[i] += count[i - 1];
        
    }

    // Строим отсортированный массив
    for (int i = n - 1; i >= 0; i--) 
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Копируем отсортированный массив output в исходный массив arr
    for (int i = 0; i < n; i++) 
    {
        arr[i] = output[i];
    }

    delete[] output;//Отчистка памяти 
}


// Функция для сортировки массива методом корневой сортировки
void radixSort(int arr[], int n) 
{
    // Находим максимальное число для определения количества разрядов
    int maxElement = findMax(arr, n);

    // Сортировка массива по каждому разряду
    for (int exp = 1; maxElement / exp > 0; exp *= 10) 
    {
        countSort(arr, n, exp);
    }
}









// Пример использования
int main() 
{
    setlocale(LC_ALL, "Russian");
    
     



    int const n = 8;
    int mas[n] = { 170, 45, 75, 90, 802, 24, 2, 66 };

    std::cout << "Исходный массив: ";
    for (int i = 0; i < n; i++)
    {
        std::cout << mas[i] << " ";
    }

    radixSort(mas, n);

    std::cout << std::endl << std::endl;;
    std::cout << "Отсортированный массив: ";
    for (int i = 0; i < n; i++)
    {
        std::cout << mas[i] << " ";
    }

    std::cout << std::endl;

    
}
