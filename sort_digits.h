/* Adrianna Batista
 * 9/27/2017
 * Assignment: Project 1
 * Problem 1
 *
 *
 */

#ifndef SORT_DIGITS_H
#define SORT_DIGITS_H

#include <iostream>
#include <string>
using namespace std;


class Sort_digits
{
	public:
		void input();
		void Swap(string &S, int i, int j);
		void Sort_102(char []);
		void output();

	private:
		string S;
		int length;
		int arr_length;
		char* DigitsPtr;
		//static const int MAX = 100;
		//char Digits[MAX];

};
#endif
