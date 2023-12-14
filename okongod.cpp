#include <iostream>
#include<vector>
#include<algorithm>



//Функция для проверки скобок 
bool Check(std::string s)
{
    //Создаем переменную i со значаением -1
    int i = -1;

    //Проходим по все строке
    for (auto c : s) 
    {
        //Если находим открытую скобку то увеличиваем счетчик на 1 и заменяем i символ строки открытой скобкой
        if (c == '(' || c == '{' || c == '[')
        {

            s[++i] = c;
        }

        else 
        {
            //Если это закрывающая скобка той же соответствующей открывающей скобки то уменьшаем i на -1
            if (i >= 0 && ((s[i] == '(' && c == ')') || (s[i] == '{' && c == '}') || (s[i] == '[' && c == ']')))
            {

                i--;
            }
            //В противном случае false 
            else
            {
                return false;
            }
        }

    }
    if (i == -1)
    {
        return true;
    }

}


//Функция для проверки деления на 0
bool isValid(const std::string & expression) 
{
    for (auto i = 0; i < expression.length(); ++i) 
    {
        if (expression[i] == '/') 
        {
            // Проверяем, что все числа, после знака "/" являются ненулевыми
            if (expression[i + 1] == '0') 
            {
                return false;
            }
        }
    }
    return true;
}


//Функция для проверки, является ли символ оператором
bool isOperator(char op) 
{
    return op == '+' || op == '-' || op == '*' || op == '/';
}

// Функция, которая вычисляет операцию над двумя числами
double performOperation(double num1, double num2, char op) 
{
    if (op == '+') 
    {
        return num1 + num2;
    }
    else if (op == '-') 
    {
        return num1 - num2;
    }
    else if (op == '*') 
    {
        return num1 * num2;
    }
    else if (op == '/') 
    {
        return num1 / num2;
    }
    
}

// Функция для вычисления значения выражения
double evaluateExpression(std::string expression) 
{
    std::vector<double> numbers;
    std::vector<char> operators;

    for (int i = 0; i < expression.length(); i++) 
    {
        // Если текущий символ - число, преобразуем его в число и добавляем в вектор чисел
        if (isdigit(expression[i])) 
        {
            double num = 0;
            while (i < expression.length() && isdigit(expression[i])) 
            {
                // Считываем все цифры числа
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            numbers.push_back(num);
            i--;
        }
        // Если текущий символ - оператор, добавляем в вектор операторов
        else if (isOperator(expression[i])) 
        {
            while (!operators.empty() && isOperator(operators.back())) 
            {
                // Если приоритет текущего оператора меньше или равен приоритету оператора на вершине,
                // выполним операцию с двумя последними числами и оператором на вершине
                if ((expression[i] == '*' || expression[i] == '/') &&
                    (operators.back() == '+' || operators.back() == '-')) 
                {
                    break;
                }
                double num2 = numbers.back();
                numbers.pop_back();

                double num1 = numbers.back();
                numbers.pop_back();

                char op = operators.back();
                operators.pop_back();

                numbers.push_back(performOperation(num1, num2, op));
            }
            operators.push_back(expression[i]);
        }
        // Если текущий символ - открывающая скобка, добавляем в вектор операторов
        else if ((expression[i] == '(') || (expression[i] == '{') || (expression[i] == '['))
        {
            operators.push_back(expression[i]);
        }
        // Если текущий символ - закрывающая скобка, выполняем операции до открывающей скобки
        else if (expression[i] == ')' || (expression[i] == '}') || (expression[i] == ']'))
        {
            while ((!operators.empty()) && (operators.back() != '(') && (operators.back() != '{') && (operators.back() != '['))
            {
                double num2 = numbers.back();
                numbers.pop_back();

                double num1 = numbers.back();
                numbers.pop_back();

                char op = operators.back();
                operators.pop_back();

                numbers.push_back(performOperation(num1, num2, op));
            }
            if (!operators.empty()) 
            {
                operators.pop_back();
            }
        }
    }

    //Выполняем оставшиеся операции
    while (!operators.empty()) 
    {
        double num2 = numbers.back();
        numbers.pop_back();

        double num1 = numbers.back();
        numbers.pop_back();

        char op = operators.back();
        operators.pop_back();

        numbers.push_back(performOperation(num1, num2, op));
    }

   
    return numbers.back();
    
}




int main() 
{
    
    setlocale(LC_ALL, "Russian");
    
    std::string expression;
    std::cout << "Введите математическое выражение: ";
    std::cin >> expression;

    if (!(Check(expression)) && isValid(expression))
    {
        double result = evaluateExpression(expression);
        std::cout << "Результат: " << result << std::endl;
    }
    else
    {
        std::cout << "Ошибка" << std::endl;
    }

    
    
    
    
}





	




