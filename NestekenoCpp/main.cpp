//
//  main.cpp
//  NestekenoCpp
//
//  Created by Игорь Шамрин on 29.10.2020.
//  Copyright © 2020 Игорь. All rights reserved.
//
#include <NTL/ZZ.h>
using namespace std;
using namespace NTL;
#define par_q "115792089237316195423570985008687907852907080286716537199505774922796921406320"
#define par_mod "115792089237316195423570985008687907853269984665640564039457584007913111864739"


void getD(ZZ& x, ZZ mod) {
	add(x, x, 8);
	x = x%mod;
	InvMod(x, x, mod);
	mul(x, x, 105);
	x = x%mod;
}

void getNu(ZZ& rop, ZZ& d, ZZ& mod, ZZ& u, ZZ& v) {
	ZZ temp1, temp2, temp3, d2, d3;
	temp1 = ZZ(0);
	temp2 = ZZ(0);
	temp3 = ZZ(0);
	d2 = ZZ(0);
	d3 = ZZ(0);

    PowerMod(d2, d, ZZ(2), mod);
	PowerMod(d3, d, ZZ(3), mod);

	MulMod(temp1, d, 3, mod);
	MulMod(temp1, temp1, u, mod);
	NegateMod(temp1, temp1, mod);

	NegateMod(temp2, ZZ(36), mod);

	AddMod(temp1, temp1, temp2, mod);

	MulMod(temp2, d3, 9, mod);

	AddMod(temp1, temp1, temp2, mod);
	AddMod(temp1, temp1, v, mod);

	NegateMod(temp2, ZZ(1), mod);

	AddMod(temp2, temp2, d3, mod); // D^3 - 1

    MulMod(temp1, temp1, temp2, mod);
    MulMod(temp1, temp1, 6, mod); // 6(D^3 - 1)(v + 9D^3 - 3Du - 36)

    MulMod(temp2, d3, 3, mod); // 3D^3

    MulMod(temp3, d, u, mod);
    NegateMod(temp3, temp3, mod); // -Du

    AddMod(temp2, temp2, temp3, mod); // 3D^3 - Du

    NegateMod(temp3, ZZ(12), mod);
    AddMod(temp2, temp2, temp3, mod); // 3D^3 - Du - 12
    PowerMod(temp2, temp2, 3, mod); // (3D^3 - Du - 12)^3

    MulMod(temp3, d2, 9, mod); // 9D^2
    AddMod(temp3, temp3, u, mod); // u + 9D^2
    PowerMod(temp3, temp3, 3, mod); // (u + 9D^2)^3

    AddMod(temp2, temp2, temp3, mod); // (u + 9D^2)^3 + (3D^3 - Du - 12)^3

    InvMod(temp2, temp2, mod); // 1/((u + 9D^2)^3 + (3D^3 - Du - 12)^3)

    MulMod(rop, temp1, temp2, mod);

}

struct point{
	ZZ x, y, z;
	point(ZZ x, ZZ y, ZZ z): x(x), y(y), z(z) {}
	point() {}
};

struct curveParams{
	ZZ a, d, mod;
};

point sumPoints(point a, point b, curveParams c){
	point res;
	ZZ temp1 = ZZ(), temp2 = ZZ(), temp_A = ZZ(), temp_B = ZZ(), temp_C = ZZ(), temp_D = ZZ(), temp_E = ZZ(), temp_F = ZZ();


	MulMod(temp_A, a.x, b.z, c.mod);
	cout << "temp_A " << temp_A << '\n';
	MulMod(temp_B, a.z, b.z, c.mod);
	cout << "temp_B " << temp_B << '\n';
	MulMod(temp_C, a.y, b.x, c.mod);
	cout << "temp_C " << temp_C << '\n';
	MulMod(temp_D, a.y, b.y, c.mod);
	cout << "temp_D " << temp_D << '\n';
	MulMod(temp_E, a.z, b.y, c.mod);
	cout << "temp_E " << temp_E << '\n';
	MulMod(temp_F, a.x, b.x, c.mod);
	cout << "temp_F " << temp_F << '\n';
	MulMod(temp_F, temp_F, c.a, c.mod);
	cout << "temp_F " << temp_F << '\n';

	MulMod(temp1, temp_A, temp_B, c.mod);
	MulMod(temp2, temp_C, temp_D, c.mod);
	NegateMod(temp2, temp2, c.mod);
	AddMod(res.x, temp1, temp2, c.mod); //X3 = AB - CD

	MulMod(temp1, temp_D, temp_E, c.mod);
	MulMod(temp2, temp_F, temp_A, c.mod);
	NegateMod(temp2, temp2, c.mod);
	AddMod(res.y, temp1, temp2, c.mod); //Y3 = DE - FA

	MulMod(temp1, temp_F, temp_C, c.mod);
	MulMod(temp2, temp_B, temp_E, c.mod);
	NegateMod(temp2, temp2, c.mod);
	AddMod(res.z, temp1, temp2, c.mod);

	return res;
}

point doublePoint(point a, curveParams b){
	struct point res;
	ZZ temp1 = ZZ(), temp2 = ZZ(), temp_P = ZZ(), temp_2P = ZZ(), temp_S = ZZ(), temp_A = ZZ(), temp_C = ZZ(), temp_D = ZZ(), temp_E = ZZ(), temp_minustwo = ZZ();

	AddMod(temp_P, a.y, a.z, b.mod); //P = Y*Z

	MulMod(temp_2P, temp_P, 2, b.mod); //2*P

	AddMod(temp_S, a.y, a.z, b.mod); // S = Y*Z

	PowerMod(temp1, temp_S, 2, b.mod);
	NegateMod(temp2, temp_P, b.mod);
	AddMod(temp_A, temp1, temp2, b.mod); // A = S^2 - P

	NegateMod(temp1, temp_2P, b.mod);
	AddMod(temp1, temp_A, temp1, b.mod);
	MulMod(temp_C, temp1, temp_S, b.mod); // C = (A - 2*P)*S

	NegateMod(temp1, a.y, b.mod);
	AddMod(temp1, temp1, a.z, b.mod);
	MulMod(temp_D, temp1, temp_A, b.mod); // D = A*(Z - Y)

	MulMod(temp1, a.x, temp_2P, b.mod);
	MulMod(temp1, temp1, b.d, b.mod);
	NegateMod(temp1, temp1, b.mod);
	MulMod(temp2, temp_C, 3, b.mod);
	AddMod(temp_E, temp1, temp2, b.mod); // E = 3C - d*X*2P

	NegateMod(temp_minustwo, ZZ(2), b.mod); // minustwo = -2 (???)

	MulMod(temp1, a.x, b.d, b.mod);
	MulMod(res.x, temp_minustwo, temp1, b.mod); // X3 = minustwo*X*D

	NegateMod(temp1, temp_E, b.mod);
	AddMod(temp1, temp_D, temp_E, b.mod);
	MulMod(res.y, temp1, a.z, b.mod); // Y3 = (D - E)*Z1

	AddMod(temp1, temp_D, temp_E, b.mod);
	MulMod(res.z, temp1, a.y, b.mod); // Z3 = (D + E)*Y1

	return res;
}

point genMultPoint(point a, curveParams b, ZZ k){
	point q = point();
	q.x = 0;
	q.y = 1;
	q.z = 0;

	for(long i = NumBits(k) - 1; i >= 0; i--){
		q = doublePoint(q, b);
		if(bit(k, i) == 1){
			q = sumPoints(q, a, b);
		}
	}

	return q;
}

void getXY(ZZ& x, ZZ& y, ZZ& u, ZZ& v, ZZ& d, ZZ& mod) {
	ZZ temp1 = ZZ(), temp2 = ZZ(), temp3 = ZZ(), d2 = ZZ(), d3 = ZZ(), nu = ZZ();

	getNu(nu, d, mod, u, v);

	PowerMod(d2, d, 2, mod);
	PowerMod(d3, d, 3, mod);

	//X
	MulMod(temp1, d2, 9, mod); // 9D^2
	AddMod(temp1, temp1, u, mod); // 9D^2 + u
	MulMod(x, temp1, nu, mod); // nu*(9D^2 + u)


	//Y
	MulMod(temp2, d, u, mod); // D*x

	NegateMod(temp2, temp2, mod); // -D*x
	NegateMod(temp3, ZZ(12), mod); // -12
	AddMod(temp2, temp2, temp3, mod); // -D*x - 12

	MulMod(temp3, d3, 3, mod); // 3D^3
	AddMod(temp1, temp2, temp3, mod); // 3*D^3 -D*x - 12
	MulMod(temp2, temp1, nu, mod); // nu*(3*D^3 -D*x - 12)

	NegateMod(temp3, ZZ(1), mod); // -1
	AddMod(y, temp2, temp3, mod); // - 1 + nu*(3*D^3 -D*x - 12)
}


void testQ(point a, curveParams b){
	ZZ q;
	point res;
	conv(q, par_q);

	res = genMultPoint(a, b, q);

	cout << res.x << res.y << res.z << '\n';
}

long isOnCurve(point a, curveParams b){
	ZZ temp1 = ZZ(), temp2 = ZZ();

	PowerMod(temp1, a.x, 3, b.mod);
	MulMod(temp1, temp1, b.a, b.mod);// a*X^3

	PowerMod(temp2, a.y, 3, b.mod);
	AddMod(temp1, temp1, temp2, b.mod);// a*X^3 + Y^3

	PowerMod(temp2, a.z, 3, b.mod);
	AddMod(temp1, temp1, temp2, b.mod);// a*X^3 + Y^3 + z^3

	MulMod(temp2, a.x, a.y, b.mod);
	MulMod(temp2, temp2, a.z, b.mod);
	MulMod(temp2, temp2, b.d, b.mod); // d*X*Y*Z

	long res = temp1 == temp2;

	if(res == 0){
		cout << "Point is on the curve\n";

	}
	else{
		cout << "Point is NOT on the curve\n";
	}
	return res;
}

int main() {
	point my_point = point(), new_point = point(), Epoint = point();
	curveParams my_params = curveParams();
	conv(my_point.x, "8119021769418921565894388378008753471190077835025535568042996557746564092404");
	conv(my_point.y, "28771053522948763457620123068270166170894398578116419877580784537256379313025");
	my_point.z = ZZ(1);
	new_point.z = ZZ(1);
	my_params.a = 1;
	my_params.d = 3;
	conv(my_params.mod, par_mod);

	getXY(new_point.x, new_point.y, my_point.x, my_point.y, my_params.d, my_params.mod);
	cout << "X   :" << new_point.x << '\n';
	cout << "Y   :" << new_point.y << '\n';

	isOnCurve(new_point, my_params);
	return 0;
}
