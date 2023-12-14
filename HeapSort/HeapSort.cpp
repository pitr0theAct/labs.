

#include <iostream>

//Функция для построения max-heap
void heapify(int arr[], int N, int i)
{

    //Инициализируем наибольший элемент как корень
    int largest = i;

    //Левый потомок в позиции 2*i + 1
    int left = 2 * i + 1;

    //Правый потомок в позиции 2*i + 2
    int right = 2 * i + 2;

    //Если левый потомок больше наибольшего элемента на данный момент 
    if (left < N && arr[left] > arr[largest])
    {
        largest = left;
    }

    //Если правый потомок больше наибольшего элемнта на данный момент 
    if (right < N && arr[right] > arr[largest])
    {
        largest = right;
    }

    //Если самый большой элемент не корень
    if (largest != i) 
    {
        //то меняем местами наибольший элемент и корень 
        std::swap(arr[i], arr[largest]);

        //Преобразуем поддерево
        heapify(arr, N, largest);
    }
}

//Основная функция сортировки на основе max-heap
void heapSort(int arr[], int N)
{

    //Построение max-heap
    for (int i = N / 2 - 1; i >= 0; i--)
    {
        heapify(arr, N, i);
    }

    //Извлечение элементов из max-heap по одному
    for (int i = N - 1; i > 0; i--)
    {

        //Перемещаем текущий корень в конец
        std::swap(arr[0], arr[i]);

        //Преобразуем оставшееся поддерево в max-heap
        heapify(arr, i, 0);
    }
}




int main()
{
    int const N = 6;
    int arr[N] = { 12, 11, 13, 5, 6, 7 };

    
    std::cout << "Array before sorting:  ";
    for (int i = 0; i < N; i++)
    {
        std::cout << arr[i] << " ";
    }

    
    heapSort(arr, N);


    std::cout << std::endl << std::endl;
    std::cout << "Array afer sorting:  ";
    for (int i = 0; i < N; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

