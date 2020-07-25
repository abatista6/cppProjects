#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "assert.h"
using namespace std;
int mod(int, int);
bool fermatTesting(int);
int add(int, int, int);
int inverse(int, int);
int subtract(int, int, int);
int multiply(int, int, int);
int exponent(int, int);
int EuclidAlgGCD(int, int);
int extendedEuclidAlgGCD(int, int, int&, int&);
int RelativePrime(int);
int Encode(int, int, int);
int Decode(int, int, int);
int Inverse(int, int, int);
void RSAAlgorithm();
int main()
{
	int x, y;
	int a = 35;
	int b = 15;
	cout << extendedEuclidAlgGCD(a, b, x, y) << endl;
	cout << EuclidAlgGCD(1008000, 5220) << endl;
	cout << RelativePrime(21) << endl;
	cout << extendedEuclidAlgGCD(28, 27) << endl;
}

int mod(int a, int n)
{
	int mod = a;
	if (mod >= 0)
	{
		while (mod >= n)
		{
			mod = mod -n;
		}
	}
	else
	{
		while (mod < 0)
		{
			mod = mod + n;
		}
	}
	return mod;
}
int add(int a, int b, int n)
{
	return mod(a+b, n);
}

int subtract(int a, int b, int n)
{
	return mod(a-b, n);
}
int multiply(int a, int b, int n)
{
	return mod(a*b, n);
}
int exponent(int a, int m)
{
	if (m == 1)
	{
		return a;
	}
	else
	{
		return a * exponent(a, m-1);
	}
}
//PreCondition: a>= b>= 0
//PostConditon: return d = gcd(a, b)
int EuclidAlgGCD(int a, int b)
{
	if (b==0)
	{
		return a;
	}
	else
	{
		do
		{
			int temp = a;
			a = b;
			b = mod(temp, b);
		}while (b!= 0);
		return a;
	}
}

int RelativePrime(int n)
{
	return n+1;
}

int extendedEuclidAlgGCD(int a, int b, int& s, int &t)
{
	if (b == 0)
	{
		s = 1;
		t = 0;
		return a;
	}
	else
	{
		int s1, t1;
		int d = extendedEuclidAlgGCD(b, a%b, s1, t1);
		s = t1;
		t = s1 - (b/a) * s1;
		return t;
	}
	cout << "S is" << s << endl;
	
}

bool fermatTesting(int p)
{
	int a;
	bool canBePrime;
	srand(time(NULL));
	do
	{
		a = rand() % 1000 + 1;
	}while (a% p == 0);
	int test = exponent(a, p -1);
	if (mod(test, p) == 1)
	{
		canBePrime = true;
	}
	else
	{
		canBePrime = false;
	}
	return canBePrime;

}

int inverse(int a, int n)
{
	int s, t;
	int d = extendedEuclidAlgGCD(a, n, s, t);
	if (d == 1)
	{
		return (mod(s,n));
	}
	else
	{
		cout << "A, n are not relatively prime!" << endl;
		return -1;
	}
}
int Encode(int a, int b, int c)
{
	int power = exponent(a, b);
	int answer = mod(answer, c);
	return answer;
}
int Decode(int a, int b, int c)
{
        int power = exponent(a, b);
        int answer = mod(answer, c);
        return answer;
}

void RSAAlgorithm()
{
	const int P = 23;
	const int Q = 13;
	int PQ = P*Q;
	int M;
	int P1Q1 = (P-1)*(Q-1);
	int d = RelativePrime(P1Q1);
	int e = inverse(d, P1Q1);
	cout << "Enter a integer that is smaller than" << PQ;
	cin >> M;
	int C = Encode(M, d, PQ);
	int M1 = Decode(C, e, PQ);
	assert (M==M1);

}
