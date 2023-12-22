

#include <iostream>
#include <cmath>

//Структура для представления точки в двумерном пространстве
struct Point 
{
    double x;
    double y;
};


//Структура для представления прямой
struct Line 
{
    double A;//коэффициент при x
    double B;//коэффициент при y
    double C;//свободный член
};

// Функция для нахождения расстояния между двумя точками
double findDistance(const Point& point1, const Point& point2) 
{
    double dx = point2.x - point1.x;
    double dy = point2.y - point1.y;
    return std::sqrt(dx * dx + dy * dy);
}

//Функция для нахождения точек пересечения двух прямых
void findIntersectionPoints(Line line1, Line line2, Point& intersectionPoint) 
{
    double determinant = line1.A * line2.B - line2.A * line1.B;//Опредлеитель второго порядка 

    if (determinant == 0)//Если определитель равен нулю 
    {
        std::cout << "Lines are parallel, no intersection points." << std::endl;
        return;
    }

    intersectionPoint.x = (line2.B * line1.C - line1.B * line2.C) / determinant;
    intersectionPoint.y = (line1.A * line2.C - line2.A * line1.C) / determinant;
}

//Функция для нахождения точек пересечения прямой и отрезка
void findIntersectionPoints(Line line, Point linePoint, Point point1, Point point2, Point& intersectionPoint) 
{
    //Находим разность координат x и y между точками отрезка
    double deltaX = point2.x - point1.x;
    double deltaY = point2.y - point1.y;

    //Создаем прямую, параллельную отрезку
    Line segmentLine;
    segmentLine.A = -deltaY;//Коэффициент A
    segmentLine.B = deltaX;//Коэффициент B
    segmentLine.C = -segmentLine.A * point1.x - segmentLine.B * point1.y;//Коэффициент C для уравнения прямой

    findIntersectionPoints(line, segmentLine, intersectionPoint);//Находим точки пересечения прямой и отрезка
}

//Функция для нахождения точек пересечения прямой и окружности
void findIntersectionPoints(Point center, double radius, Line line, Point& intersectionPoint1, Point& intersectionPoint2) 
{
    //Получаем коэффициенты A, B и C для уравнения прямой
    double A = line.A;
    double B = line.B;
    double C = line.C;
    //Получаем радиус окружности
    double r = radius;

    //Вычисляем расстояние от центра окружности до прямой
    double distance = A * center.x + B * center.y + C;

    //Если расстояние больше радиуса, то нет точек пересечения
    if (std::abs(distance) > r) 
    {
        std::cout << "No intersection points." << std::endl;
        return;
    }

    //Вычисляем квадратный корень из части формулы для нахождения точек пересечения
    double sqrtPart = std::sqrt(std::pow(r, 2) - std::pow(distance, 2));
    //Вычисляем множитель для получения точек пересечения
    double mult = 1 / std::sqrt(std::pow(A, 2) + std::pow(B, 2));

    //Находим первую точку пересечения
    intersectionPoint1.x = center.x - B * mult * distance + A * mult * sqrtPart;
    intersectionPoint1.y = center.y + A * mult * distance + B * mult * sqrtPart;

    //Находим вторую точку пересечения
    intersectionPoint2.x = center.x - B * mult * distance - A * mult * sqrtPart;
    intersectionPoint2.y = center.y + A * mult * distance - B * mult * sqrtPart;
}

//Функция для нахождения точек пересечения отрезка и окружности
void findIntersectionPoints(Point center, double radius, Point point1, Point point2, Point& intersectionPoint1, Point& intersectionPoint2) 
{
    Line line;
    line.A = point1.y - point2.y;//Коэффициент A
    line.B = point2.x - point1.x;//Коэффициент B
    line.C = point1.x * point2.y - point2.x * point1.y;//Коэффициент C для уравнения прямой

    findIntersectionPoints(center, radius, line, intersectionPoint1, intersectionPoint2);//Находим точки пересечения отрезка и прямой
}

Point* findIntersectionPoints(Point* points, int numPoints) 
{
    // Заданные точки
    Point A = points[0];  
    Point B = points[1];  
    Point C = points[2];  
    Point D = points[3];  
    Point E = points[4];  
    Point G = points[5];
    Point F = points[6];
    Point O = points[7];


    // Радиусы окружностей
    double Radius = findDistance(A, C);
    

    // Находим 10 точек пересечения
    Point* intersectionPoints = new Point[10];

    // Первая точка - центр "малой" окружности
    intersectionPoints[0] = C;

    //Четырехугольник - ABCD
    Line line1;
    line1.A = A.y - B.y;
    line1.B = B.x - A.x;
    line1.C = A.x * B.y - B.x * A.y;
    findIntersectionPoints(line1, C, A, B, intersectionPoints[1]);

    Line line2;
    line2.A = C.y - D.y;
    line2.B = D.x - C.x;
    line2.C = C.x * D.y - D.x * C.y;
    findIntersectionPoints(line2, B, C, D, intersectionPoints[2]);

    Line line3;
    line3.A = A.y - D.y;
    line3.B = D.x - A.x;
    line3.C = A.x * D.y - D.x * A.y;
    findIntersectionPoints(line3, C, A, D, intersectionPoints[3]);

    Line line4;
    line4.A = A.y - D.y;
    line4.B = D.x - A.x;
    line4.C = A.x * D.y - D.x * A.y;
    findIntersectionPoints(line4, A, C, D, intersectionPoints[4]);

    

    //Треугольник EGF
    Line line5;
    line5.A = A.y - D.y;
    line5.B = D.x - A.x;
    line5.C = A.x * D.y - D.x * A.y;
    findIntersectionPoints(line5, G, E, F, intersectionPoints[5]);

    Line line6;
    line6.A = A.y - D.y;
    line6.B = D.x - A.x;
    line6.C = A.x * D.y - D.x * A.y;
    findIntersectionPoints(line6, E, F, G, intersectionPoints[6]);

    Line line7;
    line7.A = A.y - D.y;
    line7.B = D.x - A.x;
    line7.C = A.x * D.y - D.x * A.y;
    findIntersectionPoints(line7, G, F, E, intersectionPoints[7]);


    //Центр  окружности
    intersectionPoints[8] = O;

    return intersectionPoints;
}

int main() {
    setlocale(LC_ALL, "Russian");
    Point* points = new Point[8];
    points[0] = { 0.0, 0.0 };
    points[1] = { 1.0, 0.0 };
    points[2] = { 0.5, 0.5 };
    points[3] = { 0.25, 0.25 };
    points[4] = { 2, 0.25 };
    points[5] = { 2, 0 };
    points[6] = { 0, 2 };
    points[7] = { 0.75, 0.25 };
    

    Point* intersectionPoints = findIntersectionPoints(points, 8);

    std::cout << "Точки пересечения:" << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << "Точка " << i + 1 << ": (" << intersectionPoints[i].x << ", " << intersectionPoints[i].y << ")" << std::endl;
    }

    delete[] points;
    delete[] intersectionPoints;

    return 0;
}


