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

struct CurveParams {

	ZZ a, d, mod;

	CurveParams() {}

	CurveParams(const char* aString, const char* dString, const char* modString) {
		a = conv<ZZ>(aString);
		d = conv<ZZ>(dString);
		mod = conv<ZZ>(modString);
	}
};

#endif /* CurveParams_hpp */
