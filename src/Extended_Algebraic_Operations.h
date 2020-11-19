/* Copyright 2019 PIMath project contributors. All Rights Reserved.
 *
 * Licensed under the MIT license.
 *
 * Version: 1.1.1
 */

#ifndef EXTENDED_ALGEBRAIC_OPERATIONS_H
#define EXTENDED_ALGEBRAIC_OPERATIONS_H


#include "Algebraic_Operations.h"

template <class T>
class Extended_Algebraic_Operations : public Algebraic_Operations<T>
{
	public:
		Extended_Algebraic_Operations(T initNumber1, T initNumber2) : Algebraic_Operations<T>(initNumber1, initNumber2) {};
		string modular_exponentiation(T exp);
		string root();
		string greatest_common_divisor();
};


#endif

#include "Extended_Algebraic_Operations.tpp"
