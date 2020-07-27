//Adrianna Batista
//Oct. 3, 2016
//Input string and password

#include <iostream>
#include <string>
using namespace std;

int main ()
{

	//variables
	int password_length, password_flag, digit_flag, special_flag, uppercase_flag, digit;
	string password;
	char ch, symbol;
	
	//init
	password_flag = 0;
	uppercase_flag = 0;
	digit_flag = 0;
	special_flag = 0;

	//input
	cout << "Enter a password to check its validity : ";
	cin >> password;

	//check password length
	password_length = password.length();
	if (password_length >= 8)
	{
		password_flag = 1;
	}
	else
	{
		password_flag = 0;
	}
	//check for atleast one upper case letter
	for (int i=0; i < password_length; i++)
	{
		ch = password.at(i);
		if (ch >= 'A' && ch <= 'Z')
		{
			uppercase_flag = 1;
		}
	}
	//check for atleast one digit
	for (int i=0; i < password_length; i++)
	{
		digit = password.at(i);
		if (digit >= '0' && digit <= '9')
		{
			digit_flag = 1;
		}
	}
	//check for atleast one special character
	for (char i=0; i < password_length; i++)
	{
		symbol = password.at(i);
		if (symbol == '!' || symbol == '@' || symbol == '#' || symbol == '$' || symbol == '%' || symbol == '^' || symbol == '&' || symbol == '*' || symbol == '(' || symbol == ')' || symbol == '_' || symbol == '+')
		{
			special_flag = 1;
		}
	}
	//output
	if (password_flag && uppercase_flag && digit_flag && special_flag)
	{
		cout << "Valid Password! Your password has met all the criteria" << endl;
	}
	else
	{
		cout << "Invalid Password! Your password hasn't met the criteria" << endl;

		//display the rules that haven't been met
		if (password_flag == 0)
		{
			cout << "Your password needs at least 8 characters." << endl;
		}
		
		if (uppercase_flag == 0)
		{
			cout << "Your password needs at least 1 upper case letter." << endl;
		}

		if (digit_flag == 0)
		{
			cout << "Your password needs at least 1 digit." << endl;
		}
		
		if (special_flag == 0)
		{
			cout << "Your password needs at least 1 special characters." << endl;
		}

		//Program ending output
		cout << "Program is ending. Have a nice day!" << endl;
	}


return 0;
}
