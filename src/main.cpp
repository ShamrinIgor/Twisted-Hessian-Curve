//
//  main.cpp
//  NestekenoCpp
//
//  Created by Игорь Шамрин on 29.10.2020.
//  Copyright © 2020 Игорь. All rights reserved.
//
#include "Point.hpp"
#include "CurveParams.hpp"
#include <NTL/ZZ.h>
using namespace std;
using namespace NTL;

#define par_q "115792089237316195423570985008687907852907080286716537199505774922796921406320"
#define par_mod "115792089237316195423570985008687907853269984665640564039457584007913111864739"

const ZZ q = conv<ZZ>(par_q);
const ZZ mod = conv<ZZ>(par_mod);

int main() {
	CurveParams params = CurveParams("1", "3", par_mod);

	Point weirstrassPoint = Point("8119021769418921565894388378008753471190077835025535568042996557746564092404",
								  "28771053522948763457620123068270166170894398578116419877580784537256379313025",
								  "1",
								  params);

	// Проверка что Q лежит на кривой
	cout << "Тест 1 - Проверка что Q лежит на кривой: ";
	Point hessePoint = weirstrassPoint.getTwistedHessianPoint();
	long isOnCurve = hessePoint.isOnCurve();
	assert(isOnCurve == 1);
	if (isOnCurve == 1) {
		cout << "Успешно пройден \n";
	} else
	{
		cout << "Не пройден \n";
	}

	// Проверка что [q]P = E, q - порядок группы
	cout << "Тест 2 - Проверка что [q]P = E, q - порядок группы: ";
	Point multPoint = hessePoint.genMultPoint(q);
	isOnCurve = multPoint.isOnCurve();
	ZZ affineX;
	ZZ affineY;
	multPoint.getInAffine(affineX, affineY);
	assert((isOnCurve == 1) && (affineX == 0) && affineY == (mod - 1));
	if ((isOnCurve == 1) && (affineX == 0) && affineY == (mod - 1)) {
		cout << "Успешно пройден \n";
	} else
	{
		cout << "Не пройден \n";
	}

	// Проверить, что [q + 1]P = P и [q − 1]P = −P.
	cout << "Тест 3 - Проверка что [q + 1]P = P и [q − 1]P = −P: ";
	multPoint = hessePoint.genMultPoint(q + 1);
	assert(multPoint == hessePoint);
	if (multPoint == hessePoint) {
		cout << "Успешно пройден \n";
	} else
	{
		cout << "Не пройден \n";
	}

	cout << "Тест 4 - Проверка что [q + 1]P = P : ";
	assert(multPoint == hessePoint);
	if (multPoint == hessePoint) {
		cout << "Успешно пройден \n";
	} else
	{
		cout << "Не пройден \n";
	}


	multPoint = hessePoint.genMultPoint(q - 1);
	assert(multPoint == (-hessePoint));
	cout << "Тест 5 - Проверка, что [q - 1]P = -P : ";
	if (multPoint == (-hessePoint)) {
		cout << "Успешно пройден \n";
	} else
	{
		cout << "Не пройден \n";
	}

	// Случайные числа k1 k2
	ZZ k1 = RandomBnd(ZZ(1000000000));
	ZZ k2 = RandomBnd(ZZ(1000000000));

	//Для двух случайных k1, k2 проверить, что [k1]P + [k2]P = [k1 + k2]P
	assert((hessePoint.genMultPoint(k1) + hessePoint.genMultPoint(k2)) == hessePoint.genMultPoint((k1 + k2) % mod));
	cout << "Тест 6 - [k1]P + [k2]P = [k1 + k2]P: ";
	if ((hessePoint.genMultPoint(k1) + hessePoint.genMultPoint(k2)) == hessePoint.genMultPoint((k1 + k2) % mod)) {
		cout << "Успешно пройден \n";
	} else
	{
		cout << "Не пройден \n";
	}
	return 0;
}
