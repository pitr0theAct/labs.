


#include <iostream>

//Объединяет два отсортированных подмассива в один
void merge(int array[], int const left, int const mid,int const right)
{
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;

    //Создаем временные подмассивы
    auto* leftArray = new int[subArrayOne],
    * rightArray = new int[subArrayTwo];

    //Копируем данные во временные подмассивы
    for (auto i = 0; i < subArrayOne; i++)
    {
        leftArray[i] = array[left + i];
    }
    for (auto j = 0; j < subArrayTwo; j++)
    {
        rightArray[j] = array[mid + 1 + j];
    }

    
    //Слияние временных подмассивов обратно в основной массив
    
    auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) 
    {
        if (leftArray[indexOfSubArrayOne]<= rightArray[indexOfSubArrayTwo]) 
        {
            array[indexOfMergedArray]
                = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else 
        {
            array[indexOfMergedArray]= rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    //Копирование оставшихся элементов из LeftArray[], если они есть
    while (indexOfSubArrayOne < subArrayOne) 
    {
        array[indexOfMergedArray]= leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    //Копирование оставшихся элементов из RightArray[], если они есть
    while (indexOfSubArrayTwo < subArrayTwo) 
    {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}

//Основная функция, реализующая сортировку слиянием
void mergeSort(int array[], int const begin, int const end)
{
    if (begin >= end)
    {
        int mid = begin + (end - begin) / 2;
        
        //Рекурсивно сортируем два подмассива
        mergeSort(array, begin, mid);
        mergeSort(array, mid + 1, end);
        
        //Объединяем сортированные подмассивы
        merge(array, begin, mid, end);
    }
}

//Функция для вывода массива 
void printArray(int A[], int size)
{
    for (int i = 0; i < size; i++)
        std::cout << A[i] << " ";
    std::cout << std::endl;
}


int main()
{
    int arr[] = { 12, 11, 13, 5, 6, 7 };
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Given array is \n";
    printArray(arr, arr_size);

    mergeSort(arr, 0, arr_size - 1);

    std::cout << "\nSorted array is \n";
    printArray(arr, arr_size);
    
}



