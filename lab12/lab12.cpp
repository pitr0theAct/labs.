

#include <iostream>
#include <fstream>
#include<sstream>
#include <queue>
#include<algorithm>
using namespace std;





class Compare
{
public:
    // Перегрузка оператора () для сравнения пары чисел
    bool operator() (pair<int, int> pair1, pair<int, int> pair2)
    {
        return pair1.first > pair2.first;
       
    }
};

// Функция для преобразования числа в строку
string ToString(int val) 
{
    stringstream stream;
    stream << val;
    return stream.str();
}

// Функция для объединения файлов
string mergeFiles(int counter) 
{

    
    string fileA, fileB;

    // Создание приоритетной очереди с минимальным элементом в вершине
    std::priority_queue<pair<int, int>, std::vector<pair<int, int> >, Compare> minHeap;
    
    
    ifstream* handles = new ifstream[counter];

    // Открытие и считывание файлов, добавление первого значения в очередь 
    for (int i = 1; i <= counter; i++) {
        
        string sortedInputFileName = "output" + ToString(i) + ".txt";
        
        handles[i - 1].open(sortedInputFileName.c_str());
        int firstValue;
        
        handles[i - 1] >> firstValue;
        minHeap.push(pair<int, int>(firstValue, i - 1));
    }

    string outputFileName = "output.txt";
    ofstream outputFile(outputFileName.c_str());


    // Выборка минимальных элементов из очереди и запись в выходной файл
    while (minHeap.size() > 0) {
        pair<int, int> minPair = minHeap.top();
        minHeap.pop();
        outputFile << minPair.first << '\n'; 
        int nextValue;
        flush(outputFile);
        
        // Если есть следующее значение в файле, добавляем его в очередь
        if (handles[minPair.second] >> nextValue) 
        {
            minHeap.push(pair <int, int>(nextValue, minPair.second));
        }
    }

    // Закрытие файлов
    for (int i = 1; i <= counter; i++) {
        handles[i - 1].close();
    }
    outputFile.close();
    
    delete[] handles;

    return outputFileName;
}

// Функция для сортировки и записи значений в файл
void sortAndWrite(int* values, int size, int numberOfChunks) 
{
    sort(values, values + size);
    string outputFileName = "output" + ToString(numberOfChunks) + ".txt";
    ofstream outputFile(outputFileName.c_str());
    for (int i = 0; i < size; i++) {
        outputFile << values[i] << '\n';
    }
    outputFile.close();
}

int main() {

    int numberOfChunks = 1;
    int maxSizeofMemory = 32;
    int chunkSize = maxSizeofMemory / sizeof(int);
    int* inputValues = new int[chunkSize];
    int readValue = 0;
    int currentCount = 0;
    bool unprocessedData = true;
    ifstream inputFile("input.txt");

    // Считывание значений из входного файла
    while (inputFile >> readValue) {
        unprocessedData = true;
        inputValues[currentCount++] = readValue; 
        
        // Если размер блока равен максимальному размеру памяти,
    // выполняем сортировку и запись в файл
        if (currentCount == chunkSize) {
            sortAndWrite(inputValues, currentCount, numberOfChunks); 
            
            numberOfChunks++;
            
            
            currentCount = 0;
            unprocessedData = false;
        }
    }

    // Если остались необработанные данные, выполняем сортировку и запись в файл
    if (unprocessedData) {
        sortAndWrite(inputValues, currentCount, numberOfChunks);
        
    }
    else {
        numberOfChunks--;
    }

    inputFile.close();
    delete[] inputValues;
    if (numberOfChunks != 0) {
        // Создаем очередь с минимальным элементом в вершине и выполняем слияние файлов
        std::priority_queue<pair<int, int>, std::vector<pair<int, int> >, Compare> minHeap;
        
   
        cout << "output is in file : " << mergeFiles(numberOfChunks)  << std::endl;
    
    }

    return 0;
}