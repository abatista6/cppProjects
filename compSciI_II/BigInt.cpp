Script started on Thu Feb  12 11:10:06 2017
[?1034hbash-3.2$ pwd
/Users/abatista/Desktop
bash-3.2$ cat bigInteger.cp[K[Kh bigInteger.cpp driver.cpp 
/*
 * Big Integer Lab
 *
 * Header File
 *
 */

#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;
using std::string;

class BigInteger
{
	friend istream& operator>>(istream &inp, BigInteger &obj){
		obj.input(inp);
		return(inp);
	}

	friend ostream& operator<<(ostream &out, BigInteger &obj){
		obj.display(out);
		return(out);
	}

	public:
		BigInteger();
		BigInteger(int[], int);
		~BigInteger();

		BigInteger add(BigInteger);
		BigInteger subtract(BigInteger);
		BigInteger multiply(BigInteger);

		bool isEqualTo(BigInteger);
		bool isNotEqualTo(BigInteger);
		bool isGreaterThanorEqualTo(BigInteger);
		bool isLessThanorEqualTo(BigInteger);
		bool isZero();

		BigInteger operator+(BigInteger);
		BigInteger operator-(BigInteger);
		BigInteger operator*(BigInteger);
		bool operator==(BigInteger);
		bool operator!=(BigInteger);
		bool operator>=(BigInteger);
		bool operator<=(BigInteger);

		void input(istream &inp);
		void display(ostream &out);
		void initialize();
		
	private:
		static const int MAXDIGITS = 40;
		int digits[MAXDIGITS];
		int size;
};

#endif/*
 * Big Integer Lab
 *
 * Source File
 *
 * @Adrianna Batista
 */

 #include "bigInteger.h"

BigInteger::BigInteger(){
	this->initialize();
}

BigInteger::BigInteger(int input[], int s){
	for(int i = MAXDIGITS-1; i >= 0; i--)
		digits[i] = input[i];
	size = s;
}

BigInteger::~BigInteger(){
	this->initialize();
 }

BigInteger BigInteger::add(BigInteger b){
	BigInteger result;
	int remainder = 0, total;
	for(int i = MAXDIGITS-1; i >= 0; i--)
	{
		total = digits[i] + b.digits[i] + remainder;

		if(total > 9){
			total -= 10;
			remainder = 1;
		}
		else 
			remainder = 0;
		result.digits[i] = total;
	}
	return(result);
}

BigInteger BigInteger::subtract(BigInteger b){
	BigInteger result;
	int carryUnder = 0, carryOver = 0;
	for(int i = MAXDIGITS-1; i >= 0; i--)
	{
		if(carryUnder == 10){
			carryOver = 1;
			carryUnder = 0;
		}
		if(digits[i] < b.digits[i]){
			carryUnder = 10;
		}
		result.digits[i] = (carryUnder + (digits[i] - carryOver)) - b.digits[i];

		carryOver = 0;
	}
	return(result);
}

BigInteger BigInteger::multiply(BigInteger b){
	BigInteger result, temp;
	int remainder = 0, pushOver = 0, total;
	for(int i = MAXDIGITS-1; i >= 0; i--)
	{
		for(int j = MAXDIGITS-1; j >= 0; j--)
		{
			total = (digits[i] * b.digits[j]) + remainder;		

			if(total > 9)
			{
				total -= 10;
				remainder = 1;
			}
			else
			{
				remainder = 0;
			}
			temp.digits[j-pushOver] = total;
		}
		result = result + temp;
		pushOver++;
		temp.initialize();
	}
	return(result);
}

bool BigInteger::isEqualTo(BigInteger b){
	bool check = true;
	for (int i = 0; i < MAXDIGITS; i++)
	{
		if(digits[i] != b.digits[i]){
			check = false;
			break;
		}
	}
	return(check);
}

bool BigInteger::isNotEqualTo(BigInteger b){
	return(!(this->isEqualTo(b)));
}

bool BigInteger::isGreaterThanorEqualTo(BigInteger b){
	bool check = true;

	for (int i = 0; i < MAXDIGITS; i++)
	{
		if(digits[i] < b.digits[i])
		{
			check = false;
			break;
		}
	}

	return(check);
}

bool BigInteger::isLessThanorEqualTo(BigInteger b){
	bool check = true;

	for (int i = 0; i < MAXDIGITS; i++)
	{
		if(digits[i] > b.digits[i])
		{
			check = false;
			break;
		}
	}

	return(check);
}

bool BigInteger::isZero(){
	bool check = true;
	for (int i = 0; i < MAXDIGITS; i++)
	{
		if(digits[i] != 0){
			check = false;
			break;
		}
	}
	return(check);
}

BigInteger BigInteger::operator+(BigInteger b){
	return(this->add(b));
}

BigInteger BigInteger::operator-(BigInteger b){
	return(this->subtract(b));
}

BigInteger BigInteger::operator*(BigInteger b){
	return(this->multiply(b));
}

bool BigInteger::operator==(BigInteger b){
	return(this->isEqualTo(b));
}

bool BigInteger::operator!=(BigInteger b){
	return(this->isNotEqualTo(b));
}

bool BigInteger::operator>=(BigInteger b){
	return(this->isGreaterThanorEqualTo(b));
}

bool BigInteger::operator<=(BigInteger b){
	return(this->isLessThanorEqualTo(b));
}

void BigInteger::input(istream &inp){
	string temp1, temp2;
	do{
	 	inp >> temp1;
		size = temp1.size();
	 } while (size > MAXDIGITS); 
	int j = MAXDIGITS;
	for(int i = size; i >= 0; i--)
	{
		temp2 = temp1[i];
		istringstream buffer(temp2);
		buffer >> digits[j--];
	}
}

void BigInteger::display(ostream &out){
	bool leadingZero = true;
	for(int i = 0; i < MAXDIGITS; i++)
	{
		if(digits[i] == 0 && leadingZero && i != MAXDIGITS-1)
			continue;
		else
		{
			leadingZero = false;
			out << digits[i];	
		}
	}
}

void BigInteger::initialize(){
	for (int i = 0; i < MAXDIGITS; i++)
	{
		digits[i] = 0;
	}
	size = 1;
}/*
 * Big Integer Lab
 *
 * Driver File
 *
 */

 #include "bigInteger.h"

int main(){
	BigInteger op1, op2, result;

	cout << "All big integers must be no bigger than 40 digits." << endl;


	cout << "Enter op1: ";
	cin >> op1;

	cout << "Enter op2: ";
	cin >> op2;

	result = op1 + op2;
	cout << op1 << '+' << op2 << '=' << result << endl;
	result = op1 - op2;
	cout << op1 << '-' << op2 << '=' << result << endl;
	result = op1 * op2;
	cout << op1 << '*' << op2 << '=' << result << endl;

	cout << "Equality Operator check: ";
	if(op1 == op2)
		cout << "Equal" << endl;
	else
		cout << "Not Equal" << endl;

	cout << "InEquality Operator check: ";
	if(op1 != op2)
		cout << "Not Equal" << endl;
	else
		cout << "Equal" << endl;

	cout << ">= Operator check: ";
	if(op1 >= op2)
		cout << "Greater Than or Equal To" << endl;
	else
		cout << "Not Greater Than or Equal To" << endl;

	cout << "<= Operator check: ";
	if(op1 <= op2)
		cout << "Less Than or Equal To" << endl;
	else
		cout << "Not Less Than or Equal To" << endl;
}bash-3.2$ g++ bigInteger.cpp driver.cpp 
bash-3.2$ ./a.out
All big integers must be no bigger than 40 digits.
Enter op1: 234587
Enter op2: 45566
234587+45566=280153
234587-45566=189021
234587*45566=10689191242
Equality Operator check: Not Equal
InEquality Operator check: Not Equal
>= Operator check: Not Greater Than or Equal To
<= Operator check: Not Less Than or Equal To
bash-3.2$ exit
exit

Script done on Thu Feb  12 11:11:31 2017
