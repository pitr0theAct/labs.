

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

//Класс вещи 
class Thing
{
    std::string name;//Название
    int weight;//Вес
    int cost;//Цена
public:
    //Конструктор
    Thing(std::string _name, int _weight, int _cost) : name(_name), weight(_weight), cost(_cost) {}

    //Метод который возвращает вес 
    int getWeight() const
    {
        return weight;
    }

    //Метод который возвращает цену 
    int getCost() const
    {
        return cost;
    }

    //Метод который возвращает имя
    std::string getName() const
    {
        return name;
    }
};

//Класс рюкзака 
class Backpack
{
    std::vector<std::vector<int>> dp; // Динамическое программирование для хранения результатов
    std::vector<Thing> things; // Все возможные предметы
    int capacity; // Вместимость рюкзака

public:
    //Конструктор 
    Backpack(int _capacity) : capacity(_capacity) {}//Передаем вместимость

    // Выбор предметов для помещения в рюкзак
    void selectedThings(const std::vector<Thing>& allThings)
    {
        things = allThings; //Присваиваем вектору things все предметы из allThings.

        // Инициализируем двумерный вектор dp размером (количество предметов + 1) x (вместимость рюкзака + 1) и заполняем нулями.
        dp.assign(things.size() + 1, std::vector<int>(capacity + 1, 0));


        for (int i = 1; i <= things.size(); ++i)// Начинаем итерацию по всем предметам, начиная с первого.
        {
            for (int w = 0; w <= capacity; ++w)// Во внутреннем цикле идем по всем возможным вместимостям рюкзака от 0 до capacity.
            {
                if (things[i - 1].getWeight() <= w)// Проверяем, помещается ли текущий предмет в текущую вместимость рюкзака. 
                {
                    // Если помещается, то вычисляем максимальную ценность, которую можно получить при взятии или не взятии текущего предмета.
                    dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - things[i - 1].getWeight()] + things[i - 1].getCost());
                }
                else
                {
                    dp[i][w] = dp[i - 1][w];// Если не помещается, то оставляем значение таким же, как для предыдущего предмета.
                }
            }
        }
    }

    // Печать выбранных предметов и общей стоимости
    void print()
    {
        int w = capacity;// Инициализируем w весом рюкзака
        std::cout << "Selected items:\n";//Выводим заголовок, объявляющий о начале вывода выбранных вещей
        for (int i = things.size(); i > 0 && w >= 0; --i)//Цикл, проходящий в обратном порядке по списку вещей, пока w не станет отрицательным.
        {
            if (dp[i][w] != dp[i - 1][w])//Проверяем, была ли выбрана текущая вещь.
            {
                //Выводим информацию о выбранной вещи (название, вес, стоимость)
                std::cout << "Name: " << things[i - 1].getName() << ", Weight: " << things[i - 1].getWeight() << ", Value: " << things[i - 1].getCost() << "\n";
                w -= things[i - 1].getWeight();//Вычитаем вес выбранной вещи из w, имитируя заполнение рюкзака
            }
        }
        std::cout << "Total cost: " << dp[things.size()][capacity] << "\n";//Выводим общую стоимость выбранных вещей
    }
};

int main()
{
    //Создаем вектор вещей
    std::vector<Thing> things{
        {"thing_1", 10, 5 },
        {"thing_2", 20, 8 },
        {"thing_3", 30, 10},
        {"thing_4", 40, 7 },
        {"thing_5", 50, 40},
        {"thing_6", 60,200},
        {"thing_7", 7, 530},
        {"thing_8", 8,  1 },
        {"thing_9", 9,  43}
    };

    Backpack backpack(120);//Вместимость рюкзака 
    backpack.selectedThings(things);//Выбор вещей 
    backpack.print();//Вывод
    return 0;
}

