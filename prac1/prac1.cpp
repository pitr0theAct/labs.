
#include <iostream>
#include <string>
#include <vector>

class Cipher
{
private:
	std::string m_text;//Исходный текст 
	std::string m_encode_text;//Закодированный текст 
	std::string m_decode_text;//Декодированный текст 

	std::vector<std::string> splitedText;

	//Первые 30 чисел последовательности Фибоначчи
	const int fibo_numbers[30] = { 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269 };


	//Метод разделяющий текст 
	void SplitText(const std::string& text) 
	{
		std::string temp;

		for (int i = 0; i < text.size(); i++)
		{

			if (text[i] == ' ') 
			{
				splitedText.push_back(temp);
				temp.clear();
				continue;
			}
			if (i == text.size() - 1)
			{
				temp += text[i];
				splitedText.push_back(temp);
			}
			temp += text[i];
		}
	}

	//Метод который возвращает индекс числа Фибоначчи
	int FindFibonachiIndex(int& num)
	{
		for (int i = 0; i < 30; i++) 
		{
			if (fibo_numbers[i] == num) 
			{
				return i;
			}
		}
	}

public:
	
	//Конструктор
	Cipher(const std::string& text)
	{
		m_text = text;
	}

	//Кодирование
	std::string Encode(std::vector<int>& key) 
	{
		SplitText(m_text);//Разделение текста 
		for (auto i : key)//Прохождение через каждое значение вектора
		{
			m_encode_text += splitedText[FindFibonachiIndex(i)] + ' ';//Записываем слова согласно key{ 2,8,5,1,3 }
		}
		return m_encode_text;
	}

	//Декодирование
	std::string Decode(std::vector<int>& key) 
	{
		splitedText.clear();
		SplitText(m_encode_text);//Разделение закодированного текста 

		std::vector<std::string> temp(splitedText);
		for (int i = 0; i < key.size(); i++) 
		{
			splitedText[FindFibonachiIndex(key[i])] = temp[i];//Возвращаемся к исходной кодировке 
		}

		for (auto word : splitedText)//Прохождение через каждое значение вектора
		{
			m_decode_text += word + ' ';//Записываем слова в исходном порядке
		}
		return m_decode_text;
	}

};



int main()
{
	std::string text = "Hello, my name is Ivan.";
	std::vector <int> key{ 2,8,5,1,3 };
	
	

	Cipher cipher(text);

	
	std::string str1 = cipher.Encode(key);
	std::cout << str1 << std::endl;
	std::cout << std::endl;

	
	std::string str2 = cipher.Decode(key);
	std::cout << str2 << std::endl;


}