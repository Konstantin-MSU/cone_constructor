//212-Сущев-Визуализация пирамидv - Гауссовов распределение

#include <iostream>     // библиотека вывода в консоль
#include <fstream>      // библиотека работы с файлами
#include <list>         // двусвязный список STL
#include <string>       // строки
#include <random>		// генератор сл. чисел
#include <vector>		// вектор
#include <cmath>		// математика

#define Dens 1000		// количество точек в 1 конусе

class centre { // класс точки центра окружности
private:
	float x;
	float y; // координаты центра
public:
	centre(float a, float b) : x(a), y(b) {}

	// геттеры и сеттеры

	float getX() const { return x; }
	float getY() const { return y; }

	void setX(float newX) { x = newX; }
	void setY(float newY) { y = newY; }
};

class circle: public centre { // класс окружности
private:
	float R; // радиус
public:
	circle(float x, float y, float r) : centre(x, y), R(r) {}
	
	// геттеры и сеттеры

	float getR() const { return R; }
	float getS() const { return R*R*3.141593; }

	void setR(float newR) { R = newR; }
};

class pyramid : public circle { // класс пирамид
private:
	float H;
public:
	pyramid(float x, float y, float r, float h) : circle(x, y, r), H(h) {}

	// геттеры и сеттеры

	float getH() const { return H; }
	float getV() const { return H * getS() /3.0; }

	void setH(float newH) { H = newH; }
};



std::list<pyramid> readP(const std::string& name) {
	// 212-Сущев - функция чтения пирамид

	std::list<pyramid> cones; // создаем список
	float x, y, r, h; 
	std::ifstream fin(name); // открываем файл

	while (fin >> x >> y >> r >> h) { // пока из файла извлекается квартет параметров конуса
		cones.emplace_back(x, y, r, h); // выделяем место под новую пирамиду и даем ей параметры
	}
	return cones;
}

bool A(float x) {
	if ((x < 0.002) && (x > -0.002)) {
		return true;
	}
	return false;
}

double Ga(double sr, double otkl) {
	// 212-Сущев-Константин - функция генерации Гауссово распределенного вектора
	double x = 0;

	static std::random_device rd;
	static std::mt19937 seed(rd()); // создаем генератор с равномерным распределением
	std::normal_distribution<double> dist(sr, otkl); // превращаем в ормальное	
	x = dist(seed);

	return (x);

}



int main() {
	// Читаем пирамиды из файла
	std::list<pyramid> cones = readP("data.txt");
	//std::ofstream output("cones-eq.txt");
	std::ofstream points("cone-points.txt");

	float x, y, z, w;
	int i = 0;


	//if (!output.is_open()) {
	//	std::cerr << "Error: cannot creat a file" << std::endl;
	//	return 1;
	//}

	if (cones.empty()) {// ошибка, если файл не открывается, либо пуст
		std::cerr << "Error: no data was found" << std::endl;
		return 1;
	}

	
	for (const pyramid& p : cones) {
		x = p.getX();
		y = p.getY();
		z = p.getR() / 3;
		i = 0;
		//std::cout << x << y << z << "\n";
		while (i < Dens) {
			i++;
			
			points << Ga(x,z) << " " << Ga(y, z) << std::endl;
		}
	}

	/*for (const pyramid& p : cones) {
		output << "(x - " << p.getX() << ")^2 + (y - " <<
			p.getY() << ")^2 = (" << p.getR() / p.getH() <<
			"*z - " << p.getR() << ")^2" << std::endl;
	
		//x = -1*p.getR()- p.getX();
		x = -10.0;
		//while (x < p.getR()+0.1+ p.getX()) {
		while (x < 10.0) {
			//y = -1*p.getR()-p.getY();
			y = -10.0;
			//while (y < p.getR()+0.1+ p.getY()) {
			while (y < 10.0) {
				z = 0.0;
				while (z < p.getH()+0.1) {
				//while (z < 8.0) {
					if (A((x - p.getX()) * (x - p.getX()) + (y - p.getY()) * (y - p.getY()) - (z * p.getR() / p.getH() - p.getR()) * (z * p.getR() / p.getH() - p.getR()))) {
						points << x << " " << y << " " << z << std::endl;
					}
					z += 0.03;
				}
				y += 0.03;
			}
			x += 0.03;
		}
		std::cout << "done" << std::endl;
	}*/
	return 0;
}