//Adrianna Batista
//4/5/18
//File Name: maxSubarray.cpp
//File Description: Maximal subarray problem finds the subarray of A[low...high] with the largest sum
//input: an integer array where each element is a positive or negative integer
//output: return the sum and the indices i and j, such that subarray A[i...j] has the largest sum
 
#include <iostream>
#include <limits.h>
using namespace std;

int max(int a, int b) 
{
	return (a>b)? a:b;
}

int max(int a, int b, int c) 
{	
	return max(max(a,b), c); 
}

//Definition of struct data type with object max_subarray
typedef struct 
{
    	int left;
    	int right;
    	int sum;
} max_subarray;

//Brute Force Solution

//The function uses two for loops to iterate through the array and compute
//the sum of each j value; data is reused to keep time complexity under O(n^3)
max_subarray maxSub_Brute(int A[], int left, int right )
{
	max_subarray result={0,0,INT_MIN}; //{result.left, result.right, result.sum};


        //initialize variables
        int Iindex, Jindex, max, sum;
        Iindex = max = 0;
        Jindex = -1;

        for(int i=0; i <= right; i++)
        {
                sum=0;

                for(int j=i; j <= right; j++)
                {
                        sum+=A[j];

                        if(sum>result.sum)
                        {
                                result.sum = sum;
                                result.left = i;
                                result.right = j;
                        }

                }
        }

	return result;
}

/*Algorithm Analysis:
 * Brute Force Function has O(n^2) running time
 * The indices i and j iterate over all possible n^2 index pairs, with the sum
 * of A being always computed for every j value in O(1) time
 */

//Divide and Conquer Solution

//The function takes as input the array A and the indices low, mid, and high, and it 
//returns a tuple containing the indices demarcating a maximum subarray that crosses 
//the midpoint, along with the sum of the values in a maximum subarray.
max_subarray find_max_crossing_subarray(int A[], int low, int mid, int high) 
{
    
	max_subarray result = {-1, -1, 0}; //{result.left, result.right, result.sum}

	//initialize variables
	int sum = 0; 
    	int left_sum = INT_MIN;
    	int right_sum = INT_MIN;
	
	//find a maximum subarray of the left half, A[low...mid]
	//for loop starts the index i at mid and decrements to low, considering every subarray in A[i...mid]
	for (int i = mid; i >= low; i--) //mid-low+1 total iterations; each iteration O(1)
	{ 
		sum += A[i];
	
		if (sum > left_sum) 
		{
			//update variables
		    	left_sum = sum;
	    		result.left = i;
        	}
    	}

	//reset sum variable
	sum = 0;

	//find a maximum subarray of the right half, A[mid+1...high]
        //for loop starts the index j at mid+1 and increments to high, considering every subarray in A[j...high]

     	for (int j = mid+1; j <= high; j++) //high-mid total iterations; each iteration O(1)
	{
		sum += A[j];

		if (sum > right_sum)
		{
			//update variables
	    		right_sum = sum;
	    		result.right = j;
		}
    	}

	//sum of values in the subarray A[result.left...result.right]
	result.sum = left_sum + right_sum;
	
	//return tuple result
    	return result;
}

/* Algorithm Analysis:
 * With array A[low...high] containing n elements, the function take O(n) time
 * since each iteration of the two for loops take O(1) time and 
 * the total number of iterations is: (mid-low+1)+(high-mid) = high-low+1 = n
 */

//The function finds a maximum subarray of A[1...n]
//The recursive function takes as input the array A and the indices low and high, and it returns a tuple 
//containing indices that demarcate a maximum subarray, along with the sum of the values in a maximum subarray
max_subarray find_maximum_subarray(int A[], int low, int high) 
{
	//test for the base case where A has only one element
    	if (high == low) 
	{ 
		//return a tuple with starting and ending endices of the element and its value
	    	max_subarray result = {low, high, A[low]};
		return result;
    	} //base case running time: O(1)
	
	//handle the recursive (general) case where A has more than one element
	else 
	{
		//compute index mid of the midpoint
		int mid = (low + high) / 2; //O(1)

		//Conquer by recursion to find max subarrays within left and right subarrays
	        max_subarray left = find_maximum_subarray(A, low, mid); //T(n/2) time
        	max_subarray right = find_maximum_subarray(A, mid+1, high); //T(n/2) time
		//2T(n/2) running time 

		//Find max subarray that crosses the midpoint
	        max_subarray cross = find_max_crossing_subarray(A, low, mid, high); //O(n) time as previously determined

		//The following lines take O(n) time
		//tests whether the left subarray contains a subarray with the maximum sum
		if (left.sum >= right.sum && left.sum >= cross.sum) 
		{
			//if true, return max subarray
		    	return left;
		} 
		
		//tests whether the right subarray contains a subarray with the maximum sum
		else if (right.sum >= left.sum && right.sum >= cross.sum) 
		{
			//if true, return max subarray
	 		return right;
		} 
		
		//if left and right subarrays do not contain maximum sum, then the maximum sum
		//must cross the midpoint
		else 
		{
			//if true, return max subarray
	    		return cross;
        	}
    	}
}
/* Algorithm Analysis:
 * See comments for line by line running times.
 * Adding up the recursive running times:
 * 	T(n) = O(1) + 2T(n/2) + O(n) + O(1)
 * 	     = 2T(n/2) + O(n)
 * Using master theorem, the function tunning time is T(n) = O(n logn)
 */

int main()
{
	int size, element;

	cout << "Enter array input array size: ";
	cin >> size;

	cout << "Enter " << size << " array elements: ";

	int A[size] = {};

	for(int i=0; i < size; i++)
	{
		cin >> element;
		A[i] = element;
	}

	//int A[] = {4,5,-44,-6,10,22};

	cout << "Implementing Brute Force..." << endl;
	max_subarray res = maxSub_Brute(A, 0, size-1);
	cout << "Max sum is: " << res.sum << " and spans A[" << res.left << "..." << res.right << "]" << endl;

	cout << "Implementing Divide and Conquer..." << endl;
	max_subarray ans=find_maximum_subarray(A, 0, size-1);
        cout << "Max sum is: " << ans.sum << " and spans A[" << ans.left << "..." << ans.right << "]" << endl;


	return 0;
}
