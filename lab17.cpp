
#include <iostream>
#include <string>

//Определение структуры узла дерева
struct Node 
{
    int data;// Значение узла
    Node* left;// Левый потомок
    Node* right;// Правый потомок

    Node(int value) : data(value), left(nullptr), right(nullptr) {}// Конструктор узла

};

//Класс двоичного дерева поиска
class BinarySearchTree 
{
private:  
    Node* root;

    //Рекурсивная вставка значения в дерево
    Node* insertRecursive(Node* node, int value) 
    {
        if (node == nullptr) 
        {
            return new Node(value);
        }

        if (value < node->data) 
        {
            node->left = insertRecursive(node->left, value);
        }
        else if (value > node->data) 
        {
            node->right = insertRecursive(node->right, value);
        }

        return node;
    }

    //Поиск минимального значения в дереве
    Node* findMin(Node* node) 
    {
        while (node->left != nullptr) 
        {
            node = node->left;
        }
        return node;
    }

    //Рекурсивное удаление значения из дерева
    Node* removeRecursive(Node* node, int value) {
        if (node == nullptr) 
        {
            return node;
        }

        if (value < node->data) 
        {
            node->left = removeRecursive(node->left, value);
        }
        else if (value > node->data) 
        {
            node->right = removeRecursive(node->right, value);
        }
        else {
            if (node->left == nullptr) 
            {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) 
            {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = removeRecursive(node->right, temp->data);
        }

        return node;
    }

    //Рекурсивный поиск значения в дереве
    bool searchRecursive(Node* node, int value) {
        if (node == nullptr) {
            return false;
        }

        if (value == node->data) {
            return true;
        }
        else if (value < node->data) {
            return searchRecursive(node->left, value);
        }
        else {
            return searchRecursive(node->right, value);
        }
    }

    //Генерация линейно-скобочной записи дерева
    std::string generateLinearBracketNotation(Node* node) {
        if (node == nullptr) {
            return "";
        }

        std::string result = std::to_string(node->data);

        if (node->left != nullptr || node->right != nullptr) {
            result += "(" + generateLinearBracketNotation(node->left) + ")";
            if (node->right != nullptr) {
                result += "(" + generateLinearBracketNotation(node->right) + ")";
            }
        }

        return result;
    }



public:
    //Конструктор
    BinarySearchTree() : root(nullptr) {}

    //Метод для вставки значения в дерево
    void insert(int value)
    {
        root = insertRecursive(root, value);
    }

    //Метод для удаления значения из дерева
    void remove(int value)
    {
        root = removeRecursive(root, value);
    }

    
    //Метод для поиска значения в дереве
    bool search(int value)
    {
        return searchRecursive(root, value);
    }

    
    
    //Метод для получение линейно-скобочной записи дерева
    std::string getLinearBracketNotation()
    {
        return generateLinearBracketNotation(root);
    }

    
    
    //Метод печати линейно-скобочной записи дерева
    void printLinearBracketNotation()
    {
        std::cout << "Бинарное дерево в линейно-скобочной записи: " << getLinearBracketNotation() << std::endl;
    }

};

int main() 
{
    
    setlocale(LC_ALL, "Russian");
    
    BinarySearchTree tree;// Создание объекта двоичного дерева

    std::string input;//8(3(1(0))(6(4)(7)))
    std::cout << "Введите бинарное дерево в линейно-скобочной записи: ";
    std::getline(std::cin, input);//Ввод линейно-скобочной записи дерева

    //Заполняем дерево 
    for (char c : input) 
    {
        if (isdigit(c)) 
        {
            int value = c - '0';
            tree.insert(value);
        }
    }

    while (true) 
    {
        std::cout << "\n1. Добавить узел\n2. Удалить узел\n3. Найти узел\n4. Вывести линейно-скобочную запись\n5. Выход\n";
        std::cout << "Ввидите число: ";

        int choice;
        std::cin >> choice;

        switch (choice) 
        {
        case 1: 
        {
            std::cout << "Введите значение для добавления: ";
            int value;
            std::cin >> value;
            tree.insert(value);
            break;
        }
        case 2: 
        {
            std::cout << "Введите значение для удаления: ";
            int value;
            std::cin >> value;
            tree.remove(value);
            break;
        }
        case 3: 
        {
            std::cout << "Введите значение для поиска: ";
            int value;
            std::cin >> value;
            std::cout << (tree.search(value) ? "Узел найден" : "Узел не найден") << std::endl;
            break;
        }
        case 4:
        {
            tree.printLinearBracketNotation();
            break;
        }
        case 5:
        {
            std::cout << "Бинарное дерево в линейно-скобочной записи: " << tree.getLinearBracketNotation() << std::endl;
            return 0;
        }
        default:
        {
            std::cout << "Неверный выбор." << std::endl;
        }
        }
    }

    return 0;
}


