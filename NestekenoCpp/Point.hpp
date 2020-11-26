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

struct Point {
public:
	ZZ x, y, z;
	CurveParams params;

	Point(ZZ x, ZZ y, ZZ z, CurveParams params): x(x), y(y), z(z), params(params) {}

	Point(const char* xString, const char* yString, const char* zString, CurveParams curveParams = CurveParams()) {
		x = conv<ZZ>(xString);
		y = conv<ZZ>(yString);
		z = conv<ZZ>(zString);
		params = curveParams;
	}

	Point() {}

	Point operator +(Point);

	bool operator ==(Point);

	Point operator -(); 

	void print();

	void printInAffine();

	long isOnCurve();

	Point getTwistedHessianPoint();

	Point genMultPoint(ZZ k);

	Point doublePoint(); 
private:
	ZZ getNu();
	Point rotatedSum(Point b);
};

#endif /* Point_hpp */
