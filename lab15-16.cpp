

#include <iostream>
#include <string>
#include <stack>

//Структура для представления узла дерева
struct Node 
{
    int value;
    Node* left;
    Node* right;
};

//Создание нового узла дерева
Node* newNode(int value) 
{
    Node* node = new Node;//выделение памяти под новый узел
    node->value = value;//присвоение узлу переданных данных
    node->left = nullptr;//инициализация указателей на поддеревья
    node->right = nullptr;
    return node;//возврат созданного узла
}




//Рекурсивный прямой обход
/*Прямой обход (pre-order traversal) бинарного дерева происходит в следующем порядке: 
сначала посещаем текущий узел, затем обходим его 
левое поддерево и затем правое поддерево.*/
void preOrderRecursive(Node* node) 
{
    if (node == nullptr)
        return;

    std::cout << node->value << " ";
    preOrderRecursive(node->left);
    preOrderRecursive(node->right);
}



//Рекурсивный центральный обход
/*Центральный обход (in-order traversal) бинарного дерева происходит в следующем порядке: 
сначала обходим левое поддерево,
затем посещаем текущий узел и затем обходим правое поддерево.*/
void inOrderRecursive(Node* node) 
{
    if (node == nullptr)
        return;

    inOrderRecursive(node->left);
    std::cout << node->value << " ";
    inOrderRecursive(node->right);
}



//Рекурсивный концевой обход
/*Концевой обход (post-order traversal) бинарного дерева происходит в следующем порядке: 
сначала обходим левое поддерево, 
затем правое поддерево и затем посещаем текущий узел.*/
void postOrderRecursive(Node* node) 
{
    if (node == nullptr)
        return;

    postOrderRecursive(node->left);
    postOrderRecursive(node->right);
    std::cout << node->value << " ";
}



//Не рекурсивный прямой обход
void preOrderNonRecursive(Node* node) 
{
    if (node == nullptr)
        return;

    std::stack<Node*> stack;//создание стека для хранения узлов
    stack.push(node);//добавление корневого узла в стек

    while (!stack.empty())//пока стек не пуст
    {
        Node* current = stack.top();//получение текущего узла из стека
        stack.pop();//удаление текущего узла из стека

        std::cout << current->value << " ";//вывод данных текущего узла

        if (current->right)//если у текущего узла есть правое поддерево
            stack.push(current->right);//добавление правого поддерева в стек

        if (current->left)//если у текущего узла есть левое поддерево
            stack.push(current->left);//добавление левого поддерева в стек
    }
}



//Функция findIndex находит индекс последней закрывающей скобки в подстроке str с индексами от start до end
int findIndex(const std::string& str, int start, int end) 
{
    if (start > end)//Если начальный индекс больше конечного, то возвращаем -1
        return -1;

    std::stack<char> s;//Инициализируем стек для хранения открывающих скобок

    for (int i = start; i <= end; i++)//Итерируемся по символам в подстроке str с индексами от start до end
    {
        if (str[i] == '(')//Если символ является открывающей скобкой, то добавляем его в стек
            s.push(str[i]);
        else if (str[i] == ')')//Если символ является закрывающей скобкой
        {
            if (s.top() == '(')//Если верхний элемент стека - открывающая скобка
            {
                s.pop();//Удаляем открывающую скобку из стека
                if (s.empty())//Если стек пустой, значит найдена парная закрывающая скобка
                    return i;//Возвращаем индекс закрывающей скобки
            }
        }
    }

    return -1;//Если не найдена парная закрывающая скобка, возвращаем -1
}




//Функция treeFromString создает бинарное дерево из строки str с индексами от start до end
Node* treeFromString(const std::string& str, int start, int end) 
{
    if (start > end)//Если начальный индекс больше конечного, возвращаем nullptr
        return nullptr;

    int num = 0;//Инициализируем переменную для хранения числа
    while (start <= end && str[start] >= '0' && str[start] <= '9')//Итерируемся по символам в подстроке str с индексами от start до end
    {
        num *= 10;// Умножаем число на 10, чтобы сдвинуть разряд
        num += (str[start] - '0');// Добавляем текущую цифру к числу
        start++;//Увеличиваем индекс
    }

    Node* root = newNode(num);//Создаем новый узел дерева с числом num
    int index = -1;

    if (start <= end && str[start] == '(')//Если следующий символ после числа - открывающая скобка
        index = findIndex(str, start, end);//Находим индекс парной закрывающей скобки

    if (index != -1)//Если найдена парная закрывающая скобка
    {
        root->left = treeFromString(str, start + 1, index - 1);//Рекурсивно строим левое поддерево
        root->right = treeFromString(str, index + 2, end - 1);//Рекурсивно строим правое поддерево
    }

    return root;
}





int main() {
    std::string str = "8(3(1)(6(4)(7)))(10(14)(13))";
    Node* root = treeFromString(str, 0, str.length() - 1);

    
    setlocale(LC_ALL, "Russian");
    
    
    
    std::cout << "Рекурсивный прямой обход: ";
    preOrderRecursive(root);
    std::cout << std::endl << std::endl;;

    std::cout << "Рекурсивный центральный обход: ";
    inOrderRecursive(root);
    std::cout << std::endl << std::endl;

    std::cout << "Рекурсивный концевой обход: ";
    postOrderRecursive(root);
    std::cout << std::endl << std::endl;

    std::cout << "Не рекурсивный прямой обход: ";
    preOrderNonRecursive(root);
    std::cout << std::endl << std::endl;

    
}