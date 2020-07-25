//Adrianna Batista
//4/25/2017
//Lab 1: Class on Modular Arithmetic and RSA

#include <stdlib.h> //srand, rand
#include <time.h> //time
#include <iostream> //cin, cout
#include <utility>

using namespace std;

/*n is greater than 1
 * a can be negative
 * return a mod n (as defined in class)
 * a mod n = r if and only if a = nk + r, 0 =< r < d */

int mod(int a, int n)
{
	if (a%n < 0)
	{
		return (a%n)+n;
	}

	else
	{
		return a%n;
	}

}

/* modulo-n addition
 The parameter n > 1 
   return (a+b) mod n
 Note that the return value needs to be between 0 and n-1 */ 

int add(int a, int b, int n)
{
	return mod(a+b, n);
}

int sub(int a, int b, int n)
{
	return mod(a-b, n);
}

int multi(int a, int b, int n)
{
	return  mod(a*b, n);
}

int xGCD(int a, int b, int &x, int &y) {  //attempt at figuring out Extended Euclidean; unknown if working
    if(b == 0) {
       x = 1;
       y = 0;
       return a;
    }

    int x1, y1, gcd = xGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

/*precondition: a >= b >=0 
 * postcondition: return d=gcd(a,b)*/
int EuclidAlgGCD(int a, int b)  //this works
{
	if (b==0)
		return a;
	else
	{
		do
		{
			int temp = a;

			a=b;
			b=mod(temp,b);
		}while(b!=0);
		return a;
	}
}

int EuclidAlgGCDRecursive(int a, int b)  //this works
{
	if(b==0)
		return a;

	return EuclidAlgGCDRecursive(b, mod(a,b));
}

/* precondition: a >=b>=0 */
/* postcondition: return d=gcd (a,b), s and t are set 
   so that d=ac+bd*/
int ExtendedEuclidAlgGCD(int a, int b, int &s, int &t)  //unknown if this works
{
	int d;
	int sTemp=1;
	int tTemp=0;
	s=1;
	t=0;
	int w, x, y, z;
	
	while(a!=0) {
		w = b/a;
		x = b%a;
		y = s - w * sTemp;
		z = t - w * tTemp;
		s = sTemp;
		t = tTemp;
		//sTemp = y;
		//tTemp = z;
	}

	d = EuclidAlgGCD(a,b);

	return d;

}

int modmulinverse(int a,int m)
{
    int x = 0,y = 1,u = 1,v = 0;
    int e = m,f = a;
    int c,d,q,r;
    while(f != 1)
    {
        q = e/f;
        r = e%f;
        c = x-q*u;
        d = y-q*v;
        x = u;
        y = v;
        u = c;
        v = d;
        e = f;
        f = r;
    }
    u = (u+m)%m;
    return u;
}//practice attempt at Extended GCD again

/* n>1, a is nonnegative */ 
/* a >= n */
/* a and n are relative prime to each other */
/* return s such that a*s mod n is 1 */
int inverse (int a, int n)   //this works assuming Extended GCD works
{
    int s, t,d; 
    //int d = ExtendedEuclidAlgGCD (a, n, s ,t);
    //int d = RelativePrime(n);

    for (int i = 2; i < 999; i++)
    {
      	if (EuclidAlgGCD(i, n) == 1)
        {
                        if(i == a)
				return (mod(s,n));
			else
				cout << "The inverse modulo can not be calculated because a and n are NOT relative prime!" << endl;
                        break;
        }

    }
}

/* If p is any prime number, then for any integer a integer such that p does not divide a,a^{p−1} ≡1(mod p). Return true if a^{p-1}=1 mod p 

  1. Randomly generate a integer a with a value from range [0,10000]
  2. if a is a multiple of a, go back 1 
  3. calculate a^{p-1} mod p,  using your modular exponents function 
  4. if the above function returns 1, return true (and p might be a prime, but might not be)
      otherwise, return false (i.e., p is definitely not a prime) 
*/
bool FermatTesting (int p, int b, int a) //this works
{
	bool check = false;
	int r;
		
	srand (time(NULL)); //initialize random number generator using current time value 
	do {
		r = rand() % 1000 + 1; //%1000 yields a value between 0 and 999, adding 1 yields a value between 1 and 1000 
	} while (r %p ==0);

	/*int f = exp(a,p,p);
	if(f==1)
	{
		check = true;
	}
	else
	{
		check = false;
	}

	return check;*/ //couldn't get it to work using exp defined function

	int total = 1;
	int x=0;

	for(int i=b; i >0; i--)
		total *=a;
	x = mod(total,a);

	if(x==1)
		check = true;
	else
		check = false;

	return check;
}

int exp(int a, int m, int n)  //this works
{
	int total=1;
	int x = 0;

	for(int i = m; i > 0; i--)
		total *= a;

	x = mod(total,n);
	
	return x;
}

int RelativePrime(int n)  //this works
{

	for (int i = 2; i < 999; i++)
	{
		if (EuclidAlgGCD(i, n) == 1)
		{
			return i;
			break;
		}
		
	}
}


int main()
{
	int a, n, b, m,p;
	int s=1;
	int t=0;

	cout << "Please enter a, n (n!=1) ";
	cin >> a >> n;
	cout << "a mod n = " << mod(a,n) << endl;
	cout << RelativePrime(n) << " is a number that is relative prime to " << n << endl;
	cout << "Enter a number to test if prime";
	cin >> p;
	if(FermatTesting(p,n,a))
		cout << "The entered number is prime" << endl;
	else
		cout << "The entered number is NOT prime" << endl;

	//attempt at RSA
	const int rsa_p = 23;
	const int rsa_q = 17;
	int rsa_pq = rsa_p * rsa_q;
	int rsa_temp = (rsa_p - 1)*(rsa_q - 1);
	int rsa_d = RelativePrime(rsa_temp);
	int rsa_e = inverse(rsa_d, rsa_temp);

	cout << "Please enter a, b, n (n!=1) ";
	cin >> a >> b >> n;


	cout << "(a+b) mod n = " << add(a,b,n) << endl;
	cout << "(a-b) mod n = " << sub(a,b,n) << endl;
	cout << "(a*b) mod n = " << multi(a,b,n) << endl;
	cout << "(a^b) mod n = " << exp(a,b,n) << endl;
	
	int d = xGCD(a, b, s, t);
        int f = ExtendedEuclidAlgGCD(a,b,s,t);

        //cout << d << " other " << f << endl;
	
	//cout << f << "...The integer coefficients are..." << s << t << endl;


	return 0;
}
