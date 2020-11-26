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
	cout << "Проверка что Q лежит на кривой \n";
	Point hessePoint = weirstrassPoint.getTwistedHessianPoint();
	hessePoint.isOnCurve();

	// Проверка что [q]P = E, q - порядок группы
	cout << "Проверка что [q]P = E, q - порядок группы \n";
	Point multPoint = hessePoint.genMultPoint(q);
	multPoint.isOnCurve();
	multPoint.printInAffine();

	// Проверить, что [q + 1]P = P и [q − 1]P = −P.
	cout << "Проверка что [q + 1]P = P и [q − 1]P = −P \n";
	multPoint = hessePoint.genMultPoint(q + 1);
	assert(multPoint == hessePoint);
	cout << "[q + 1]P = P : " << (multPoint == hessePoint) << '\n';

	multPoint = hessePoint.genMultPoint(q - 1);
	assert(multPoint == (-hessePoint));
	cout << "[q - 1]P = -P : " << (multPoint == (-hessePoint)) << '\n';

	// Случайные числа k1 k2
	ZZ k1 = RandomBnd(ZZ(1000000000));
	ZZ k2 = RandomBnd(ZZ(1000000000));

	//Для двух случайных k1, k2 проверить, что [k1]P + [k2]P = [k1 + k2]P
	assert((hessePoint.genMultPoint(k1) + hessePoint.genMultPoint(k2)) == hessePoint.genMultPoint((k1 + k2) % mod));
	cout << "[k1]P + [k2]P = [k1 + k2]P: " << ((hessePoint.genMultPoint(k1) + hessePoint.genMultPoint(k2)) == hessePoint.genMultPoint((k1 + k2) % mod)) << '\n';
	return 0;
}
