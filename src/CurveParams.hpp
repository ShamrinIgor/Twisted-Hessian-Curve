//
//  CurveParams.hpp
//  NestekenoCpp
//
//  Created by Игорь Шамрин on 24.11.2020.
//  Copyright © 2020 Игорь. All rights reserved.
//

#ifndef CurveParams_hpp
#define CurveParams_hpp

#include <stdio.h>
#include <NTL/ZZ.h>

using namespace NTL;

/// Структура, хранящая параметры кривой
struct CurveParams {

	/// Параметры кривой
	ZZ a, d, mod;

	CurveParams() {}

	/// Конструктор `CurveParams`
	/// @param aString параметр а в виде строки
	/// @param dString переметр d в виде строки
	/// @param modString модуль в виде строки
	CurveParams(const char* aString, const char* dString, const char* modString) {
		a = conv<ZZ>(aString);
		d = conv<ZZ>(dString);
		mod = conv<ZZ>(modString);
	}
};

#endif /* CurveParams_hpp */
