

#include <iostream>
#include <vector>
#include <stack>
#include <cmath>

//Структура точки
struct Point 
{
	int x, y;
	Point(int _x, int _y) : x(_x), y(_y) {};
};

//Сортировка вставками
void sort_Insertion(std::vector<Point>& _arr)
{
	//Сортировка массива точек по возрастанию x-координаты
	for (int i = 0; i < _arr.size(); i++) 
	{
		for (int j = i; j > 0 && _arr[j - 1].x > _arr[j].x; j--) 
		{
			std::swap(_arr[j - 1], _arr[j]);
		}
	}
	//Если точки имеют одинаковую x-координату, сортируем по y-координате
	for (int i = 0; i < _arr.size() - 1; i++) 
	{
		if (_arr[i].x == _arr[i + 1].x && _arr[i].y > _arr[i + 1].y)
		{
			std::swap(_arr[i], _arr[i + 1]);
		}
	}
}

//Вычисление угла между точками в градусах(тремя точками a, b и c)
double calc_Angle(Point _a, Point _b, Point _c) 
{
	double angle_rad;

	// Вычисляются векторы u и v
	double ux = _b.x - _a.x;
	double uy = _b.y - _a.y;
	double vx = _c.x - _b.x;
	double vy = _c.y - _b.y;

	// Затем вычисляются их длины magnitudeU и magnitudeV
	double magnitudeU = sqrt(ux * ux + uy * uy);
	double magnitudeV = sqrt(vx * vx + vy * vy);

	// Если длины больше нуля, то вычисляется угол между векторами
	if (magnitudeU > 0 && magnitudeV > 0) 
	{
		double dotProduct = ux * vx + uy * vy;
		double cos_fi = dotProduct / (magnitudeU * magnitudeV);
		angle_rad = acos(cos_fi);
	}
	else
		angle_rad = 0.0;

	int angle_deg = 180 - angle_rad * 180.0 / 3.1415;

	// Возвращается угол в градусах
	return angle_deg;
};

// Функция определения направления поворота для трех точек
int orientation(Point p, Point q, Point r) 
{
	int pseudo_cross_product = (q.x - p.x) * (r.y - q.y) - (r.x - q.x) * (q.y - p.y);// Вычисляется псевдо-векторное произведение для трех точек

	// Если результат больше нуля - поворот направо, меньше нуля - поворот налево, иначе - прямая
	if (pseudo_cross_product > 0) 
	{
		return 1;
	}
	else if (pseudo_cross_product < 0) 
	{
		return -1;
	}
	else 
	{
		return 0;
	}
}

// Функция построения выпуклой оболочки
void chain(std::stack<Point>& Shell, std::vector<Point>& _arr, int _a, int _b) 
{
	int i = 0, angl = 0;
	// Находится точка с максимальным углом относительно текущего отрезка
	for (int j = 0; j < _arr.size(); j++) 
	{
		int _angl = calc_Angle(_arr[_a], _arr[_b], _arr[j]);// вычисление угла между точками
		if ((orientation(_arr[_a], _arr[_b], _arr[j]) > 0) && _angl > angl)// если точка j находится в нужной стороне от отрезка и ее угол больше текущего максимального угла
		{
			angl = _angl;
			i = j;
		}
	}
	// Если такая точка найдена, она добавляется в выпуклую оболочку и рекурсивно вызывается следующий шаг строения оболочки.
	if (i != 0) 
	{
		//std::cout << angl << '-' << _arr[i].x << ' ' << _arr[i].y << std::endl;
		Shell.push(_arr[i]);
		chain(Shell, _arr, _b, i);
	}
};

// Функция построения оболочки
std::stack<Point> build_Shell(std::vector<Point>& _arr)
{
	std::stack<Point> Shell;// создание стека для хранения точек выпуклой оболочки
	Shell.push(_arr[0]);// добавление первой точки массива в оболочку
	int pos_f = _arr.size() - 1;// определение индекса последней точки в массиве
	chain(Shell, _arr, pos_f, 0);// вызов функции для построения оболочки
	return Shell;// возврат построенной оболочки
};


int main() 
{
	// Инициализация массива точек и сортировка
	std::vector<Point> PointArray = { {0,0}, {0,100}, {100,0}, {50,50}, {8,0}, {4,0}, {7,0}, {0,13}, {12,25} };
	sort_Insertion(PointArray);

	// Построение оболочки
	std::stack<Point> Shell = build_Shell(PointArray);
	if (Shell.size() == 1) // если в оболочке только одна точка
	{
		Shell.push(PointArray[PointArray.size() - 1]);// добавление последней точки массива в оболочку
		chain(Shell, PointArray, 0, PointArray.size() - 1);// вызов функции для завершения построения оболочки
	}

	if (Shell.size() > 1) // если в оболочке больше одной точки
	{
		std::cout << "Shell created" << std::endl;// вывод сообщения об успешном построении оболочки
		while (!Shell.empty()) // цикл для вывода всех точек оболочки
		{
			std::cout << Shell.top().x << ' ' << Shell.top().y << std::endl; // вывод координат точки
			Shell.pop();// удаление точки из оболочки
		}
	}

	return 0;
}