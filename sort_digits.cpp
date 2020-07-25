/* Adrianna Batista
 * 9/27/2017
 * Assignment: Project 1
 * Problem 1:
 * File Name:
 * File Description:
 */

#include "sort_digits.h"

void Sort_digits::input()
{
	cout << "Enter a string composed of the digits 0, 1, and 2 ending with '#': ";
	cin >> S;

	length = S.length(); //number of digits in string S
	arr_length = length - 2; //length - 1 if # IS included
	char Digits[arr_length];

	for (int i=0; i <= arr_length; i++)
	{
		/* if (S.at(i) == '#')
		 * 	break;
		 */

		Digits[i] = S.at(i); 
	}

	Sort_102(Digits);
}

void Sort_digits::Swap(string &S, int i, int j)
{
	char temp = S[i];
	S[i] = S[j]; //temp = S[j]
	S[j] = temp;
}

void Sort_digits::Sort_102(char Digits[])
{
	int low = 0;
	int mid = 0;
	int high = arr_length;

	while (mid <= high)
	{
		switch (Digits[mid])
		{
			case 0:
				Swap(Digits, low++, mid++);
			break;

			/*case '0':
				Swap(Digits, low, mid);
			 		low++;
			 		mid++;
			break;*/
			 

			case 1:
				mid++;
			break;

			case 2:
				 Swap(Digits, mid, high--);
			break;

			/*case '2':
				Swap(Digits, mid, high);
					high--;
			break;*/
			
		}
	}

	//cout << Digits;
}

int main()
{
	Sort_digits x;

}
