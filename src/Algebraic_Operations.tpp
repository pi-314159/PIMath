/* Copyright 2019 PIMath project contributors. All Rights Reserved.
 *
 * Licensed under the MIT license.
 *
 * Version: 1.1.1
 */

#include <iostream>
#include <typeinfo>
#include <algorithm>

#define llint long long int
#define ullint unsigned long long int
typedef long long int * llint_ptr;
typedef unsigned long long int * ullint_ptr;

template <class T>
Algebraic_Operations<T>::Algebraic_Operations(T initNumber1, T initNumber2)
{
	new_number(initNumber1, initNumber2);
}

template <class T>
void Algebraic_Operations<T>::split_str_to_vec(vector <long long int> & strVec, string * initStr)
{
	initStr->erase(remove(initStr->begin(), initStr->end(), '.'), initStr->end());
	for (long long int strTempLen = initStr->size() - 18; strTempLen > -18; strTempLen -= 18)
	{
		if (strTempLen < 0)
		{
			strVec.insert(strVec.begin(), stoll(initStr->substr(0, 18 + strTempLen)));
		} else
		{
			strVec.insert(strVec.begin(), stoll(initStr->substr(strTempLen, 18)));
		}
	}
}

template <class T>
inline void Algebraic_Operations<T>::add_leading_zero(llint & n, int len, string & result)
{
	result = string(len--, '0');
	for (llint val=(n < 0) ? -n : n; len >= 0 && val != 0; --len, val /= 10) result[len] = '0' + val % 10;
	if (len >= 0 && n < 0) result[0] = '-';
}

template <class T>
void Algebraic_Operations<T>::new_number(T tempNumber1, T tempNumber2)
{
	auto format = [](string & lambdaString)
	{
		lambdaString.erase(0, min(lambdaString.find_first_not_of(" "), lambdaString.size() - 1));
		char * sign  = (char*)malloc(2);
		if (lambdaString.at(0) == '-' || lambdaString.at(0) == '+')
		{
			sign[0] = lambdaString.at(0);
			lambdaString = lambdaString.substr(1);
		} else
		{
			sign[0] = '+';
		}
		sign[1] = '\0';
		lambdaString.erase(0, min(lambdaString.find_first_not_of(" "), lambdaString.size() - 1));
		lambdaString.erase(0, min(lambdaString.find_first_not_of("0"), lambdaString.size() - 1));
		if (lambdaString.at(0) == '.') lambdaString.insert(0, 1, '0');
		if (lambdaString.find_first_not_of("0.") == string::npos)
		{
			lambdaString.insert(0, 1, '+');
		} else
		{
			lambdaString = sign + lambdaString;
		}
		free(sign);
	};

	*number1 = tempNumber1;
	*number2 = tempNumber2;
	format(*number1);
	format(*number2);

	llint_ptr tempFinalDigits = new long long int[2];
	tempFinalDigits[0] = 0;
	tempFinalDigits[1] = 0;
	if (number1->find(".") == string::npos) *number1 += ".";
	tempFinalDigits[0] = number1->substr(number1->find("."), number1->size()).size();
	if (number2->find(".") == string::npos) *number2 += ".";
	tempFinalDigits[1] = number2->substr(number2->find("."), number2->size()).size();
	if (tempFinalDigits[0] >= tempFinalDigits[1])
	{
		if (tempFinalDigits[1] == 0 && tempFinalDigits[1] != tempFinalDigits[0])
		{
			*number2 += '.';
			tempFinalDigits[1] = 1;
		}
		*number2 += string(tempFinalDigits[0] - tempFinalDigits[1], '0');
	} else
	{
		if (tempFinalDigits[0] == 0)
		{
			*number1 += '.';
			tempFinalDigits[0] = 1;
		}
		*number1 += string(tempFinalDigits[1] - tempFinalDigits[0], '0');
	}
	delete[] tempFinalDigits;

	return;
}

template <class T>
string Algebraic_Operations<T>::current_result()
{
	return answer;
}

template <class T>
string Algebraic_Operations<T>::addition()
{
	answer = "";

	auto zeroReturn = [](string & retStr, string & ogStr)
	{
		retStr = ogStr;
		if (ogStr.at(0) == '+') retStr.erase(0, 1);
	};

	if (number1->find_first_not_of("+-0.") == string::npos)
	{
		zeroReturn(answer, *number2);
	} else if (number2->find_first_not_of("+-0.") == string::npos)
	{
		zeroReturn(answer, *number1);
	}

	if (answer != "") return answer;

	// 1 means positive, -1 means negative.
	int * sign = new int(number1->at(0) == '+' ? 1 : -1);

	if (number1->at(0) == number2->at(0))
	{
		*number1 = number1->substr(1);
		*number2 = number2->substr(1);

		int * addOne = new int(0);
		llint_ptr tempNumberAdd1 = new long long int(0);
		llint_ptr tempNumberAdd2 = new long long int(0);

		llint_ptr number1Size = new long long int(number1->size());
		llint_ptr number2Size = new long long int(number2->size());

		vector <llint> longestNumber;
		vector <llint> shortestNumber;

		string * longestNumberTemp = new string(*number1Size >= *number2Size ? *number1 : *number2);
		string * shortestNumberTemp = new string(*number1Size < *number2Size ? *number1 : *number2);
		string * addTempAnswer = new string("");

		llint_ptr dotPosition = new long long int(*number1Size - number1->find(".") - 1);

		split_str_to_vec(longestNumber, longestNumberTemp);
		split_str_to_vec(shortestNumber, shortestNumberTemp);
		delete longestNumberTemp;
		delete shortestNumberTemp;

		*number1Size = longestNumber.size();
		*number2Size = shortestNumber.size();

		llint_ptr tempN2 = (*number1Size > *number2Size ? number2Size : number1Size);

		auto newOne = [](llint & firstParam, int & secondParam)
		{
			if (firstParam > 999999999999999999)
			{
				secondParam = 1;
				firstParam -= 1000000000000000000;
			} else
			{
				secondParam = 0;
			}
		};

		for (llint tempN1 = (*number1Size > *number2Size ? *number1Size : *number2Size) - 1; tempN1 >= 0; tempN1--)
		{
			if (*tempN2 > 0)
			{
				--*tempN2;
				*tempNumberAdd1 = longestNumber[tempN1];
				*tempNumberAdd2 = shortestNumber[*tempN2];
				*tempNumberAdd1 += *tempNumberAdd2 + *addOne;
			} else
			{
				*tempNumberAdd1 = longestNumber[tempN1];
				*tempNumberAdd1 += *addOne;
			}
			newOne(*tempNumberAdd1, *addOne);
			add_leading_zero(*tempNumberAdd1, 18, *addTempAnswer);
			answer = *addTempAnswer + answer;
		}
		if (*addOne != 0) answer = to_string(*addOne) + answer;

		answer.insert(answer.length() - *dotPosition, 1, '.');
		answer.erase(0, min(answer.find_first_not_of("0"), answer.size() - 1));
		if (answer.at(0) == '.') answer.insert(0, 1, '0');

		if (*sign != 1)
		{
			answer.insert (0, 1, '-');
			*number1 = "-" + *number1;
			*number2 = "-" + *number2;
		} else
		{
			*number1 = "+" + *number1;
			*number2 = "+" + *number2;
		}

		vector <llint> ().swap(longestNumber);
		vector <llint> ().swap(shortestNumber);

		delete addOne;
		delete dotPosition;
		delete tempNumberAdd1;
		delete tempNumberAdd2;
		delete addTempAnswer;
		delete number1Size;
		delete number2Size;

		answer.erase(answer.find_last_not_of("0") + 1, string::npos);
	} else
	{
		*number1 = "+" + number1->substr(1);
		*number2 = "+" + number2->substr(1);
		answer = subtraction();
		if (*sign != 1)
		{
			if (answer[0] == '-')
			{
				answer.erase(0, 1);
			} else if (answer != "0.")
			{
				answer.insert (0, 1, '-');
			}
			*number1 = "-" + number1->substr(1);
			*number2 = "+" + number2->substr(1);
		} else
		{
			*number1 = "+" + number1->substr(1);
			*number2 = "-" + number2->substr(1);
		}
	}

	delete sign;
	return answer;
}

template <class T>
string Algebraic_Operations<T>::subtraction()
{
	answer = "";

	auto zeroReturn = [](string & retStr, string & ogStr, bool flipSign = false)
	{
		retStr = ogStr;
		if (ogStr.at(0) == '+')
		{
			retStr.erase(0, 1);
			if (flipSign == true && retStr.at(0) != '0') retStr = "-" + retStr;
		} else
		{
			if (flipSign == true) retStr.erase(0, 1);
		}
	};

	if (number1->find_first_not_of("+-0.") == string::npos)
	{
		zeroReturn(answer, *number2, true);
	} else if (number2->find_first_not_of("+-0.") == string::npos)
	{
		zeroReturn(answer, *number1);
	}

	if (answer != "") return answer;

	if (*number1 == *number2) return "0.";

	int * sign = new int(number1->at(0) == '+' ? 1 : -1);

	if (number1->at(0) == number2->at(0))
	{
		int * ogSign = new int(*sign);
		*number1 = number1->substr(1);
		*number2 = number2->substr(1);

		int * borrowOne = new int(0);
		llint_ptr tempNumberMin1 = new long long int(0);
		llint_ptr tempNumberMin2 = new long long int(0);

		llint_ptr number1Size = new long long int(number1->size());
		llint_ptr number2Size = new long long int(number2->size());

		vector <llint> longestNumber;
		vector <llint> shortestNumber;

		string * longestNumberTemp, * shortestNumberTemp, * subTempAnswer = new string("");

		switch (*number1Size - *number2Size)
		{
			case 0 :
				longestNumberTemp = new string(number2->compare(*number1) >= 0 ? *number2 : *number1);
				shortestNumberTemp = new string(number2->compare(*number1) < 0 ? *number2 : *number1);
				break;
			default :
				longestNumberTemp = new string(*number1Size >= *number2Size ? *number1 : *number2);
				shortestNumberTemp = new string(*number1Size < *number2Size ? *number1 : *number2);
				break;
		}

		if (*longestNumberTemp == *number2 && *number2 != *number1) *sign *= -1;

		llint_ptr dotPosition = new long long int(*number1Size - number1->find(".") - 1);

		split_str_to_vec(longestNumber, longestNumberTemp);
		split_str_to_vec(shortestNumber, shortestNumberTemp);
		delete longestNumberTemp;
		delete shortestNumberTemp;

		*number1Size = longestNumber.size();
		*number2Size = shortestNumber.size();

		llint_ptr tempN2 = (*number1Size > *number2Size ? number2Size : number1Size);

		auto removeOne = [](llint & firstParam, llint & secondParam, int & thirdParam)
		{
			if (firstParam < secondParam)
			{
				thirdParam = 1;
				firstParam += 1000000000000000000;
			} else
			{
				thirdParam = 0;
			}
			firstParam -= secondParam;
		};

		for (llint tempN1 = (*number1Size > *number2Size ? *number1Size : *number2Size) - 1; tempN1 >= 0; tempN1--)
		{
			if (*tempN2 > 0)
			{
				--*tempN2;
				*tempNumberMin1 = longestNumber[tempN1];
				*tempNumberMin2 = shortestNumber[*tempN2];
			} else
			{
				*tempNumberMin1 = longestNumber[tempN1];
				*tempNumberMin2 = 0;
			}
			*tempNumberMin1 -= *borrowOne;
			removeOne(*tempNumberMin1, *tempNumberMin2, *borrowOne);
			add_leading_zero(*tempNumberMin1, 18, *subTempAnswer);
			answer = *subTempAnswer + answer;
		}

		answer.insert(answer.length() - *dotPosition, 1, '.');
		answer.erase(0, min(answer.find_first_not_of("0"), answer.size() - 1));
		if (answer.at(0) == '.') answer.insert(0, 1, '0');

		if (*sign != 1) answer.insert (0, 1, '-');
		if (*ogSign != 1)
		{
			*number1 = "-" + *number1;
			*number2 = "-" + *number2;
		} else
		{
			*number1 = "+" + *number1;
			*number2 = "+" + *number2;
		}

		vector <llint> ().swap(longestNumber);
		vector <llint> ().swap(shortestNumber);

		delete ogSign;
		delete borrowOne;
		delete subTempAnswer;
		delete tempNumberMin1;
		delete tempNumberMin2;
		delete number1Size;
		delete number2Size;

		answer.erase(answer.find_last_not_of("0") + 1, string::npos);
	} else
	{
		*number1 = "+" + number1->substr(1);
		*number2 = "+" + number2->substr(1);
		answer = addition();
		if (*sign != 1)
		{
			answer.insert (0, 1, '-');
			*number1 = "-" + number1->substr(1);
			*number2 = "+" + number2->substr(1);
		} else
		{
			*number1 = "+" + number1->substr(1);
			*number2 = "-" + number2->substr(1);
		}
	}

	delete sign;
	return answer;
}

template <class T>
string Algebraic_Operations<T>::multiplication(bool pow, ullint exp)
{
	if (pow == true)
	{
		short int * tempMod = new short int(1);
		string * tempAnswer = new string("1.");

		char * ogNumber1 = new char [number1->length() + 1];
		number1->copy(ogNumber1, number1->length());
		ogNumber1[number1->length()] = '\0';
		char * ogNumber2 = new char [number2->length() + 1];
		number2->copy(ogNumber2, number2->length());
		ogNumber2[number2->length()] = '\0';
		number1->erase(number1->find_last_not_of("0") + 1, string::npos);

		for (; exp > 0; exp /= 2)
		{
			*tempMod = exp % 2;
			if (*tempMod == 1)
			{
				*number2 = *tempAnswer;
				if (number2->at(0) != '-' && number2->at(0) != '+') number2->insert(0, 1, '+');
				*tempAnswer = multiplication();
			}
			*number2 = *number1;
			*number1 = multiplication();
			if (number1->at(0) != '-' && number1->at(0) != '+') number1->insert(0, 1, '+');
		}

		*number1 = ogNumber1;
		delete[] ogNumber1;
		*number2 = ogNumber2;
		delete[] ogNumber2;
		delete tempMod;

		answer = *tempAnswer;
		delete tempAnswer;
		return answer;
	}

	if (number2->find_first_not_of("+-0.") == string::npos || number1->find_first_not_of("+-0.") == string::npos) return "0.";

	answer = "";
	auto zeroReturn = [](string & retStr, string & ogStr, bool flipSign)
	{
		retStr = ogStr;
		if (ogStr.at(0) == '+')
		{
			retStr.erase(0, 1);
			if (flipSign == true && retStr.at(0) != '0') retStr = "-" + retStr;
		} else
		{
			string * tempAnswer = new string("0.");
		}
	};

	if (number2->find_first_not_of("+-10.") == string::npos || number1->find_first_not_of("+-10.") == string::npos)
	{
		number1->erase(number1->find_last_not_of("0") + 1, string::npos);
		short int * isSwap = new short int(0);
		if (number2->find_first_not_of("+-10.") == string::npos)
		{
			*isSwap = 1;
			swap(*number1, *number2);
		}
		string * tempStringSpeed = new string[2];
		llint_ptr tempRight = new long long int(0);
		tempStringSpeed[0] = number1->substr(0, number1->find("."));
		tempStringSpeed[1] = number1->substr(number1->find("."), number1->size());
		if (count(tempStringSpeed[0].begin(), tempStringSpeed[0].end(), '1') == 1  && tempStringSpeed[1].find_first_not_of(".0") == string::npos)
		{
			if (tempStringSpeed[0].at(0) == '-')
			{
				zeroReturn(answer, *number2, true);
			} else
			{
				zeroReturn(answer, *number2, false);
			}
			*tempRight = answer.substr(answer.find("."), answer.size()).size() - 1;
			answer.erase(remove(answer.begin(), answer.end(), '.'), answer.end());
			*tempRight = tempStringSpeed[0].size() - 2 - *tempRight;
			if (*tempRight >= 0)
			{
				answer += string(*tempRight, '0') + ".";
			} else
			{
				answer.insert(answer.length() + *tempRight, 1, '.');
			}
		} else if (count(tempStringSpeed[0].begin(), tempStringSpeed[0].end(), '1') == 0 && count(tempStringSpeed[1].begin(), tempStringSpeed[1].end(), '1') == 1)
		{
			if (tempStringSpeed[0].at(0) == '-')
			{
				zeroReturn(answer, *number2, true);
			} else
			{
				zeroReturn(answer, *number2, false);
			}
			short int * tempInt2 = new short int(answer.at(0) == '-' ? -1 : 1);
			if (*tempInt2 != 1) answer.replace(0, 1, "");
			*tempRight = answer.substr(answer.find("."), answer.size()).size() - 1;
			answer.erase(remove(answer.begin(), answer.end(), '.'), answer.end());
			*tempRight = answer.size() - tempStringSpeed[1].substr(0, tempStringSpeed[1].find("1")).size() - *tempRight;
			if (*tempRight > 0)
			{
				answer.insert(*tempRight, 1, '.');
			} else
			{
				answer = "." + string(abs(*tempRight), '0') + answer;
			}
			if (*tempInt2 != 1) answer.insert(0, 1, '-');
			delete tempInt2;
		}
		if (*isSwap == 1)
		{
			swap(*number1, *number2);
		}
		delete isSwap;
		delete[] tempStringSpeed;
		if (answer != "")
		{
			*tempRight = (answer.at(0) == '-' ? -1 : 1);
			if (*tempRight != 1) answer.replace(0, 1, "");
			answer.erase(answer.find_last_not_of("0") + 1, string::npos);
			answer.erase(0, min(answer.find_first_not_of("0"), answer.size() - 1));
			if (answer.at(0) == '.') answer.insert(0, 1, '0');
			if (*tempRight != 1) answer.insert(0, 1, '-');
		}
		delete tempRight;
	}

	if (answer != "") return answer;

	char * ogNumber1 = new char [number1->length() + 1];
	number1->copy(ogNumber1, number1->length());
	ogNumber1[number1->length()] = '\0';
	char * ogNumber2 = new char [number2->length() + 1];
	number2->copy(ogNumber2, number2->length());
	ogNumber2[number2->length()] = '\0';

	number2->erase(number2->find_last_not_of("0") + 1, string::npos);

	*number1 = number1->substr(1);
	*number2 = number2->substr(1);

	int * addMulti = new int(0);
	int * tempNumberMulti1 = new int(0);
	llint_ptr tempNumberMulti2 = new long long int(0);

	llint_ptr number1Size = new long long int(number1->size());
	llint_ptr number2Size = new long long int(number2->size());

	ullint_ptr dotPosition = new unsigned long long int(0);

	*dotPosition = *number1Size - number1->find(".") + *number2Size - number2->find(".") - 1;

	if (*number1Size > *number2Size)
	{
		swap(*number1, *number2);
		*number1Size = number1->size();
	}

	vector <string> tempAnswer;
	vector <llint> tempNumberM2Vec;
	vector <string> answerList = {8, "NULL"};

	number2->erase(remove(number2->begin(), number2->end(), '.'), number2->end());
	string * tempNumber2For1Multi = new string(*number2);

	split_str_to_vec(tempNumberM2Vec, number2);
	*number2Size = tempNumberM2Vec.size() - 1;

	auto newMulti = [](llint & firstParam, int & secondParam)
	{
		if (firstParam > 999999999999999999)
		{
			secondParam = firstParam / 1000000000000000000;
			firstParam %= 1000000000000000000;
		} else
		{
			secondParam = 0;
		}
	};

	for (llint tempN1 = *number1Size - 1; tempN1 >= 0; tempN1--)
	{
		if (number1->at(tempN1) != '.')
		{
			answer = "";

			*tempNumberMulti1 = number1->at(tempN1) - '0';
			switch (*tempNumberMulti1)
			{
				case 0 :
					answer = "0";
					break;
				case 1 :
					answer = *tempNumber2For1Multi;
					answer += string(*number1Size - 1 - tempN1, '0');
					break;
				default :
					if (answerList[*tempNumberMulti1 - 2] != "NULL")
					{
						answer = answerList[*tempNumberMulti1 - 2];
					} else
					{
						for (llint tempN3 = *number2Size; tempN3 > -1; tempN3--)
						{
							*tempNumberMulti2 = tempNumberM2Vec[tempN3] * *tempNumberMulti1 + *addMulti;
							newMulti(*tempNumberMulti2, *addMulti);
							add_leading_zero(*tempNumberMulti2, 18, *number2);
							answer = *number2 + answer;
						}
						if (*addMulti != 0) answer = to_string(*addMulti) + answer;
						*addMulti = 0;
						answerList[*tempNumberMulti1 - 2] = answer;
					}
					answer += string(*number1Size - 1 - tempN1, '0');
					break;
			}
			tempAnswer.push_back(answer);
		} else
		{
			--*number1Size;
		}
	}

	delete tempNumber2For1Multi;

	answer = "0.";
	for (int tempN2 = tempAnswer.size() - 1; tempN2 >= 0; tempN2--)
	{
		*number1 = "+" + answer;
		*number2 = tempAnswer[tempN2] + ".";
		number2->erase(0, min(number2->find_first_not_of("0"), number2->size() - 1));
		if (number2->at(0) == '.') number2->insert(0, 1, '0');
		*number2 = "+" + *number2;
		answer = addition();
	}

	vector <llint> ().swap(tempNumberM2Vec);
	vector <string> ().swap(tempAnswer);
	vector <string> ().swap(answerList);

	*number1 = ogNumber1;
	delete[] ogNumber1;
	*number2 = ogNumber2;
	delete[] ogNumber2;

	*number1Size = answer.size() - *dotPosition;
	if (*number1Size < 0)
	{
		answer.insert(0, abs(*number1Size), '0');
		answer.insert(0, 1, '.');
	} else
	{
		answer.insert(answer.size() - *dotPosition, ".");
	}

	answer.pop_back();
	answer.erase(answer.find_last_not_of("0") + 1, string::npos);
	answer.erase(0, min(answer.find_first_not_of("0"), answer.size() - 1));
	if (answer.at(0) == '.') answer.insert(0, 1, '0');
	if (number1->at(0) != number2->at(0)) answer.insert (0, 1, '-');

	delete dotPosition;
	delete addMulti;
	delete tempNumberMulti1;
	delete tempNumberMulti2;
	delete number1Size;
	delete number2Size;

	return answer;
}

template <class T>
tuple<string, string> Algebraic_Operations<T>::division(llint round_to, bool mod)
{
	string answer1 = "", answer2 = "";
	if (number2->find_first_not_of("+-0.") == string::npos) return make_tuple("ERROR", "Divisor cannot be 0!");
	if (number1->find_first_not_of("+-0.") == string::npos) return make_tuple("0.", "0.");

	char * ogNumber1 = new char [number1->length() + 1];
	number1->copy(ogNumber1, number1->length());
	ogNumber1[number1->length()] = '\0';
	char * ogNumber2 = new char [number2->length() + 1];
	number2->copy(ogNumber2, number2->length());
	ogNumber2[number2->length()] = '\0';

	auto zeroReturn = [](string & retStr, string & ogStr)
	{
		retStr = ogStr;
		retStr.erase(0, 1);
	};

	if (number2->find_first_not_of("+-10.") == string::npos)
	{
		string * tempStringSpeed = new string[2];
		llint_ptr tempRight = new long long int(0);
		tempStringSpeed[0] = number2->substr(0, number2->find("."));
		tempStringSpeed[1] = number2->substr(number2->find("."), number2->size());
		if (count(tempStringSpeed[0].begin(), tempStringSpeed[0].end(), '1') == 0 && count(tempStringSpeed[1].begin(), tempStringSpeed[1].end(), '1') == 1)
		{
			zeroReturn(answer1, *number1);
			*tempRight = answer1.substr(answer1.find("."), answer1.size()).size() - 1;
			answer1.erase(remove(answer1.begin(), answer1.end(), '.'), answer1.end());
			*tempRight = tempStringSpeed[1].substr(0, tempStringSpeed[1].find("1")).size() - *tempRight;
			if (*tempRight >= 0)
			{
				answer1 += string(*tempRight, '0') + ".";
			} else
			{
				answer1.insert(answer1.length() + *tempRight, 1, '.');
			}
		} else if (count(tempStringSpeed[0].begin(), tempStringSpeed[0].end(), '1') == 1  && tempStringSpeed[1].find_first_not_of(".0") == string::npos)
		{
			zeroReturn(answer1, *number1);
			*tempRight = answer1.substr(answer1.find("."), answer1.size()).size() - 3;
			answer1.erase(remove(answer1.begin(), answer1.end(), '.'), answer1.end());
			*tempRight = answer1.size() - tempStringSpeed[0].size() - *tempRight;
			if (*tempRight > 0)
			{
				answer1.insert(*tempRight, 1, '.');
			} else
			{
				answer1 = "." + string(abs(*tempRight), '0') + answer1;
			}
		}
		delete[] tempStringSpeed;
		if (answer1 != "")
		{
			answer1.erase(answer1.find_last_not_of("0") + 1, string::npos);
			answer1.erase(0, min(answer1.find_first_not_of("0"), answer1.size() - 1));
			if (answer1.at(0) == '.') answer1.insert(0, 1, '0');
		}
		delete tempRight;
	}

	auto addOne = [](string & firstParam, llint & secondParam)
	{
		int * tempAnswer2 = new int(0);
		for (llint tempN1 = secondParam; tempN1 > -1; tempN1--)
		{
			if (firstParam.at(tempN1) != '.')
			{
				*tempAnswer2 = firstParam.at(tempN1) - '0';
				++*tempAnswer2;
				if (*tempAnswer2 == 10)
				{
					firstParam.at(tempN1) = '0' + 0;
				} else
				{
					firstParam.at(tempN1) = '0' + *tempAnswer2;
					break;
				}
			}
		}
		delete tempAnswer2;
	};

	if (answer1 == "")
	{
		*number1 = number1->substr(1);
		*number2 = number2->substr(1);

		number2->erase(number2->find_last_not_of("0") + 1, string::npos);

		llint_ptr number1Size = new long long int(number1->size());
		llint_ptr number2Size = new long long int(number2->size());
		llint_ptr numberDot = new long long int(number2->substr(number2->find("."), *number2Size).size() - number1->substr(number1->find("."), *number1Size).size());

		number1->erase(remove(number1->begin(), number1->end(), '.'), number1->end());
		number2->erase(remove(number2->begin(), number2->end(), '.'), number2->end());

		if (*numberDot >= 0)
		{
			*number1 += string(*numberDot, '0') + ".";
		} else
		{
			number1->insert(number1->length() + *numberDot, 1, '.');
		}

		delete numberDot;
		delete number2Size;

		*number1Size = number1->size();

		llint_ptr tempStringEndZero = new long long int(round_to + 2 - number1->substr(number1->find("."), *number1Size).size());
		if (*tempStringEndZero < 0)
		{
			number1->erase(*number1Size + *tempStringEndZero);
		} else
		{
			*number1 += string(*tempStringEndZero, '0');
		}
		delete tempStringEndZero;

		number1->erase(0, number1->find_first_not_of("0"));
		number2->erase(0, number2->find_first_not_of("0"));
		if (number1->at(0) == '.') number1->insert(0, 1, '0');

		string * tempNumberDiv1 = new string(*number1);
		string * tempNumberDiv2 = new string(*number2);
		string * tempAnswer = new string("");
		llint_ptr tempNumber1Dot = new long long int(number1->substr(0, number1->find(".")).size());

		*tempNumberDiv2 = "+" + *tempNumberDiv2 + ".";

		string * tempDividend = new string(".");
		for (llint tempN1 = 0; tempN1 < tempNumberDiv1->size(); tempN1++)
		{
			if (tempN1 == *tempNumber1Dot)
			{
				answer1 += ".";
			} else
			{
				if (tempN1 > *tempNumber1Dot && *tempDividend == ".") break;
				tempDividend->pop_back();
				*tempDividend += tempNumberDiv1->at(tempN1);
				tempDividend->push_back('.');
				for (llint tempN2 = 9; tempN2 > -1; tempN2--)
				{
					*number1 = "+" + to_string(tempN2) + ".";
					*number2 = *tempNumberDiv2;
					*tempAnswer = multiplication();
					if ((tempDividend->size() > tempAnswer->size()) || (tempDividend->size() == tempAnswer->size() && tempDividend->compare(*tempAnswer) >= 0))
					{
						answer1 += to_string(tempN2);
						*number1 = "+" + *tempDividend;
						*number2 = "+" + *tempAnswer;
						*tempDividend = subtraction();
						if (*tempDividend == "0.") *tempDividend = ".";
						break;
					}
				}
			}
		}

		delete tempDividend;
		delete tempNumberDiv1;
		delete tempNumberDiv2;
		delete tempAnswer;
		delete tempNumber1Dot;

		*number1Size = answer1.size();
		if (round_to + 2 == answer1.substr(answer1.find("."), *number1Size).size())
		{
			if (answer1.at(*number1Size - 1) - '0' < 5)
			{
				answer1.pop_back();
			} else
			{
				answer1.pop_back();
				*number1Size -= 2;
				addOne(answer1, *number1Size);
			}
		}
		delete number1Size;

		answer1.erase(0, min(answer1.find_first_not_of("0"), answer1.size() - 1));
		if (answer1.at(0) == '.') answer1.insert(0, 1, '0');
		*number1 = ogNumber1;
		*number2 = ogNumber2;
	}

	if (mod == false)
	{
		answer2 = "NULL";
	} else
	{
		string * tempAnswer = new string(answer1);
		int * sign = (int *)malloc(2 * sizeof(int));
		sign[0] = (number1->at(0) == '+' ? 1 : -1);
		sign[1] = (number2->at(0) == '+' ? 1 : -1);
		if (tempAnswer->at(0) == '-') tempAnswer->substr(1);
		*tempAnswer = tempAnswer->substr(0, tempAnswer->find(".") + 1);
		if (sign[0] == -1) *number1 = "+" + number1->substr(1);
		if (sign[1] == -1) *number2 = "+" + number2->substr(1);
		string * tempNumberMod1 = new string(*number1);

		if (sign[0] != sign[1])
		{
			llint_ptr tempAnswerSize = new long long int(tempAnswer->size() - 1);
			addOne(*tempAnswer, *tempAnswerSize);
			delete tempAnswerSize;
			*number1 = tempAnswer->insert (0, 1, '+');
			*number1 = "+" + multiplication();
			*number2 = *tempNumberMod1;
		} else
		{
			*number1 = tempAnswer->insert (0, 1, '+');
			*number2 = "+" + multiplication();
			*number1 = *tempNumberMod1;
		}
		delete tempNumberMod1;
		delete tempAnswer;
		free(sign);
		llint_ptr numberSize = new long long int(number1->substr(number1->find("."), number1->size()).size() - number2->substr(number2->find("."), number2->size()).size());
		if (*numberSize > 0) *number2 += string(*numberSize, '0');
		if (*numberSize < 0) *number1 += string(abs(*numberSize), '0');
		delete numberSize;
		answer2 = subtraction();
	}

	*number1 = ogNumber1;
	delete[] ogNumber1;
	*number2 = ogNumber2;
	delete[] ogNumber2;

	if (number1->at(0) != number2->at(0)) answer1.insert (0, 1, '-');
	if (answer2 != "NULL") answer2.insert(0, 1, number2->at(0));
	if (answer2 == *number2) answer2 = "0";
	if (answer2.at(0) == '+') answer2.replace(0, 1, "");

	return make_tuple(answer1, answer2);
}

template <class T>
Algebraic_Operations<T>::~Algebraic_Operations()
{
	delete number1;
	delete number2;
}
