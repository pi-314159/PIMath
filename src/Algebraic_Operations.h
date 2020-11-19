/* Copyright 2019 PIMath project contributors. All Rights Reserved.
 *
 * Licensed under the MIT license.
 *
 * Version: 1.1.1
 */

#ifndef ALGEBRAIC_OPERATIONS_H
#define ALGEBRAIC_OPERATIONS_H


#include <string>
#include <vector>
#include <tuple>

using namespace std;

template <class T>
class Algebraic_Operations
{
	protected:
		string * number1 = new string, * number2 = new string, answer;
		void split_str_to_vec(vector <long long int> & strVec, string * initStr);
		inline void add_leading_zero(long long int & n, int len, string & result);
	public:
		Algebraic_Operations(T initNumber1, T initNumber2);
		void new_number(T tempNumber1, T tempNumber2);
		string current_result();
		string addition();
		string subtraction();
		string multiplication(bool pow = false, unsigned long long int exp = 1);
		tuple<string, string> division(long long int round_to = 10, bool mod = false);
		~Algebraic_Operations();
};


#endif

#include "Algebraic_Operations.tpp"
