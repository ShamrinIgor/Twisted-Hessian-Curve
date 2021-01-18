//
//  Point.hpp
//  NestekenoCpp
//
//  Created by Игорь Шамрин on 24.11.2020.
//  Copyright © 2020 Игорь. All rights reserved.
//

#ifndef Point_hpp
#define Point_hpp

#include <stdio.h>
#include <NTL/ZZ.h>
#include "CurveParams.hpp"

using namespace NTL;
using namespace std;

/// Структура, хранящая координаты точки и параметры кривой
struct Point {
public:
	/// Проективные координаты точки
	ZZ x, y, z;
	/// Параметры кривой
	CurveParams params;

	/// Конструктор `Point`
	/// @param x координата x
	/// @param y координата y
	/// @param z координата z
	/// @param params параметры кривой
	Point(ZZ x, ZZ y, ZZ z, CurveParams params): x(x), y(y), z(z), params(params) {}


	/// Конструктор `Point`
	/// @param xString координата x в виде строки
	/// @param yString координата y в виде строки
	/// @param zString координата z в виде строки
	/// @param curveParams параметры кривой
	Point(const char* xString, const char* yString, const char* zString, CurveParams curveParams = CurveParams()) {
		x = conv<ZZ>(xString);
		y = conv<ZZ>(yString);
		z = conv<ZZ>(zString);
		params = curveParams;
	}

	Point() {}

	/// Операция сложения Standard Addition Law
	Point operator +(Point);

	/// Сравнение точек на равенство
	bool operator ==(Point);

	/// Операция вычитания точек
	Point operator -();

	/// Вывести точку
	void print();

	/// Вывести точку в аффинных координатах
	void printInAffine();

	/// Получить аффинные координаты точки
	void getInAffine(ZZ &affineX, ZZ &affineY);

	/// Проверка, что точка лежит на кривой
	long isOnCurve();

	/// Возвращает точку на искревленной форме Гессе, если в Point указа точка на кривой Вейерштрасса
	Point getTwistedHessianPoint();

	/// Вычисление кратной точки
	/// @param k порядок
	Point genMultPoint(ZZ k);

	/// Операция удвоения точки с помощью Rotated Addition Law
	Point doublePoint();
	
private:
	ZZ getNu();
};

#endif /* Point_hpp */
