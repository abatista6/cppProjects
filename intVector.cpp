// Write a program that uses integer vector to store distinct integers and uses function print_pairs(v) to ouput pairs of integers that sum up to "SUM"

#include <iostream>
#include <vector>
#include <algorithm>     
#include <stdlib.h>     
#include <time.h>       

using namespace std;

void generate_vector(vector<int> &, int);
void print_pairs(vector<int>, int, int);

int main()
{
	int DIST_INT, SUM;
	vector<int> v;

	cout << " Enter DIST_INT: ";
	cin  >> DIST_INT;

	while(DIST_INT < 1 || DIST_INT > 8)
	{
		cout << " Invalid DIST_INT - enter a number between 1 and 8: ";
		cin  >> DIST_INT;
	}
	cout << " Enter SUM: ";
	cin  >> SUM;
                  		
	generate_vector(v, DIST_INT);    

	for(int i = 0; i < v.size(); i++)
        {
           cout << v[i] << "  ";
        }
					
	print_pairs(v, SUM, DIST_INT);    		
	
 	return 0;
}

void generate_vector(vector<int> &v, int DIST_INT)
{
	srand(time(0));

	for(int i = 0; i < DIST_INT; i++)
	{
		vector<int>::iterator it; 
		int num = 1 + rand()/((RAND_MAX + 1u)/8);
		while(it != v.end())
		{   
			num = 1 + rand()/((RAND_MAX + 1u)/8);
			it = find (v.begin(), v.end(), num); 
		}
		v.push_back(num); 
	}
}

void print_pairs(vector<int> v, int sum, int size)
{
	int iterations = (size) * (size - 1) / 2;
	cout << "\nPrint pairs" << endl;
	
	int pair1 = 0; 
	int pair2 = 1; 
	int passesMade = 0; 
	
	for(int loopCount = 0; loopCount < iterations; loopCount++)
	{
		if(pair2 == size) 
		{                 	  
			passesMade++; 	  
			pair1 = 0;
			pair2 = passesMade + 1;
		}
		if(v[pair1] + v[pair2] == sum) 
		{
			cout << v[pair1] << "--" << v[pair2] << endl;
		}
		
		pair1++;
		pair2++;
	}
}