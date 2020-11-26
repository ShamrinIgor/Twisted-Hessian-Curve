//
//  Point.cpp
//  NestekenoCpp
//
//  Created by Игорь Шамрин on 24.11.2020.
//  Copyright © 2020 Игорь. All rights reserved.
//
#include "Point.hpp"

Point Point::operator+(Point bPoint) {
	ZZ mod = params.mod;
	ZZ x1 = x, x2 = bPoint.x, y1 = y, y2 = bPoint.y, z1 = z, z2 = bPoint.z;
	
	ZZ x3 = (x1*x1*y2*z2 - x2*x2*y1*z1) % mod;
	ZZ y3 = (z1*z1*x2*y2 - z2*z2*x1*y1) % mod;
	ZZ z3 = (y1*y1*x2*z2 - y2*y2*x1*z1) % mod;
	
	return Point(x3, y3, z3, params);
}

bool Point::operator ==(Point point) {
	ZZ affineX = (x*InvMod(z, params.mod)) % params.mod;
	ZZ affineY = (y*InvMod(z, params.mod)) % params.mod;

	ZZ affineXarg = (point.x*InvMod(point.z, point.params.mod)) % point.params.mod;
	ZZ affineYarg = (point.y*InvMod(point.z, point.params.mod)) % point.params.mod;
	return affineX == affineXarg && affineY == affineYarg;
}

Point Point::operator -() {
	return Point(x, z, y, params);
}

void Point::print() {
	std::cout << "X: " << x << '\n';
	std::cout << "Y: " << y << '\n';
	std::cout << "Z: " << z << '\n';
}

void Point::printInAffine() {
	ZZ affineX = (x*InvMod(z, params.mod)) % params.mod;
	ZZ affineY = (y*InvMod(z, params.mod)) % params.mod;

	std::cout << "Affine X: " << affineX << '\n';
	std::cout << "Affine Y: " << affineY << '\n';
}

long Point::isOnCurve(){

	ZZ left = (power(x, 3) + power(y, 3) + power(z, 3)) % params.mod;
	ZZ right = (3*params.d*x*y*z) % params.mod;

	long res = (left == right);

	if(res == 1){
		cout << "Point is on the curve\n";
	}
	else{
		cout << "Point is NOT on the curve\n";
	}
	return res;
}

ZZ Point::getNu() {
	ZZ numerator = (6*(power(params.d,3) - 1)*(y + 9*power(params.d,3) - 3*params.d*x - 36)) % params.mod;
	ZZ denominator = (power((x + 9*params.d*params.d),3) + power(3*power(params.d,3) - params.d*x - 12, 3)) % params.mod;

	return (numerator*InvMod(denominator, params.mod)) % params.mod;
}

Point Point::getTwistedHessianPoint() {
	ZZ nu = getNu();
	cout << nu << '\n';
	//X
	ZZ newX = (nu*(9*params.d*params.d + x)) % params.mod;
	//Y
	ZZ newY = (nu*(3*power(params.d,3) - params.d*x - 12) - 1) % params.mod;

	return Point(newX, newY, ZZ(1), params);
}

Point Point::genMultPoint(ZZ k) {
	Point q = Point("0",
					"115792089237316195423570985008687907853269984665640564039457584007913111864738",
					"1",
					params);


	for(long i = NumBits(k) - 1; i >= 0; i--) {
		q = q.doublePoint();
		if(bit(k, i) == 1){
			q = q + (*this);
		}
	}

	return q;
}

Point Point::doublePoint() {
	ZZ newX = (power(z, 3)*x - power(y, 3)*x) % params.mod;
	ZZ newY = (power(y, 3)*z - power(x, 3)*z) % params.mod;
	ZZ newZ = (params.a*power(x, 3)*y - power(z, 3)*y) % params.mod;

	return Point(newX, newY, newZ, params);
}
