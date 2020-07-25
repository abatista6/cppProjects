//Adrianna Batista
//February 1, 2018
//Computer Algorithms
//File Name: lab1.cpp
//File Description: Sorting lab 1 implements, tests, and compares the performance of sorting algorithms: bubble, selection, and insertion sort by sorting a list of integers.

#include <iomanip>
#include <iostream>
#include <sys/time.h>
#include "stdlib.h"

using namespace std;

//Display the content of the array
void print(int * arr, int size)
{
	for(int i=0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
	
	cout << endl;
}

/* Generate an array of given size, fill it with random integers between 1 and 10,000 return the address of the array
 * @param size: the size of the array to be generated @return the address of the array */
int * GenerateRandom(int size)
{
	int upper = 10000;
	int * arr;

	arr = new int [size];

	if(!arr)
	{
		cout << "ERROR: Memory allocation failed!" << endl;
		size = 0;
		exit(1);
	}

	srand(time(NULL));

	for(int i=0; i < size; i++)
	{
		arr[i] = rand() % upper + 1;
	}

	return arr;
}

/* Duplicate the given array. Create an array that is a duplicate of the given orig array 
 * @param orig: address of original array @param size; size of original array
 * @return: address of the newly created array */
int * DuplicateArray(int * orig, int size)
{
	int * copy = new int [size];

	for(int i=0; i < size; i++)
	{
		copy[i] = orig[i];
	}
	
	return copy;
}

/* Test if an array is sorted in ascending order or not @param array: address of array to be checked
 * @param size: size of array to be checked @return: true if the array is sorted in the given mode; false otherwise*/
bool IsSorted(int * arr, int size)
{

	for(int i=0; i < size -1; i++)
	{
		if(*(arr + i) > *(arr + i +1))
			return false;
	}

	return true;
}

/* Swap the information at location x with the information at location y in the array and  
 * @param x: address of array to be increased in position @param y: address of array to be decreased in position
 * @postcondition: the contents of array x and array y have been swapped */
void swap(int * x, int * y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

/* sort the array of int in ascending order using bubble sort @param array: address of the array
 * @param size: size/length of the array @postcondition: the elements in the array is arranged in ascending order */
void BubbleSort(int * arr, int size)
{
	bool swapped;
	
	for(int i=0; i < size-1; i++)
	{
		swapped = false;

		for(int x=0; x < size-1-i; x++)
		{
			if(arr[x] > arr[x+1])
			{
				swap(arr[x], arr[x+1]);
				swapped = true;
			}
		}

		if(swapped == false)
			break;
	}
}

/* sort the array of int in ascending order using insertion sort @param array: address of the array
 * @param size: size/length of the array @postcondition: the elements in the array is arranged in ascending order */
void InsertionSort(int * arr, int size)
{
	int temp, x;

	for(int i=1; i < size; i++)
	{
		temp = arr[i];
		x = i-1;

		while(x >= 0 && arr[x] > temp)
		{
			swap(arr[x], arr[x+1]);
			x--;
		}

		arr[x+1] = temp;
	}
}

/* sort the array of int in ascending order using selection sort @param array: address of the array 
 * @param size: size/length of the array @postcondition: the elements in the array is arranged in ascending order */
void SelectionSort(int * arr, int size)
{
	int min;

	for(int i=0; i < size-1; i++)
	{
		min = i;

		for(int x = i+1; x < size; x++)
		{
			if(arr[x] < arr[min])
				min = x;
		}

		swap(arr[min], arr[i]);
	}
}

//RECRUSIVE MERGE SORT
/* sort the array of int in ascending order using merge sort and recursive calls
 * @ param array: address of the array
 * @ param left: left index
 * @ param right: right index
 */
void MergeSort_r(int * arr, int left, int right)
{
	if (left < right)
   	{
      	int middle = (left + right)/2;
    		mergeSort_r(arr, left, middle);
      	mergeSort_r(arr, middle+1, right);
      	
		merge(arr, left, middle, right);
   	}
}
//END RECURSIVE MERGE SORT

//MERGE FUNCTION
/* function to merge the two halves of the array of int
   First half is arr[left...middle], Second half is arr[middle+1..right]*/
void merge(int * arr, int left, int middle, int right)
{
	int size1 = middle-left+1; //size of left half
	int size2 = right-middle; //size of right half
	int index = left; //full array index
	int index1 = 0; //left half index
	int index2 = 0; //right half index

	//create temporary arrays; L = left half, R = right half
	int * L[size1], * R[size2];

	//copy data to temporary arrays
	for(int i=0; i < size1; i++)
		L[i] = arr[1+i];

	for(int j=0; j < size2; j++)
		R[j] = arr[middle+1+j];

	/* While both arrays are at an index less than their size,
	   merge the temporary arrays back into original array */
    	while (index1 < size1 && index2 < size2)
    	{
		if (L[index1] <= R[index2])
           {
           		arr[index] = L[index1];
			index1++;
        	}
		
	     else
	     {
           		arr[index] = R[index2];
            	index2++;
        	}
        
		index++;
    	}
 
	/* While the left array is at an index less than size1, 
	   copy the remaining elements back into original array */
	while (index1 < size1)
	{
		arr[index] = L[index1];
        	index1++;
        	index++;
    	}
	
	/* While the right array is at an index less than size2, 
	   copy the remaining elements back into original array */
    	while (index2 < size2)
    	{
      	arr[index] = R[index2];
		index2++;
		index++;
    	}
}
//END MERGE FUNCTION

//ITERATIVE MERGE SORT
/* sort the array of int in ascending order using merge sort
 * @param array: address of the array
 * @ param size: size of array
 */
void MergeSort(int * arr, int size)
{
	int curr_size;  //For current size of subarrays to be merged
                     //curr_size varies from 1 to n/2
   	int left_start; //For picking starting index of left array
                     //to be merged
 
   // Merge subarrays in bottom up manner.  First merge subarrays of
   // size 1 to create sorted subarrays of size 2, then merge subarrays
   // of size 2 to create sorted subarrays of size 4, and so on.
   for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size)
   {
       // Pick starting point of different subarrays of current size
       for (left_start=0; left_start<n-1; left_start += 2*curr_size)
       {
           // Find ending point of left subarray. mid+1 is starting 
           // point of right
           int mid = left_start + curr_size - 1;
 
           int right_end = min(left_start + 2*curr_size - 1, n-1);
 
           // Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
           merge(arr, left_start, mid, right_end);
       }
   }
}

}
//END ITERATIVE MERGE SORT

//QUICK SORT
/* partition into two parts using pivot A[r]
 * A is the array to be partitioned, p and r are index of the left and right end
 * of the array; return the lcoation (index) of pivot value after partition
 * post condition: A[p...return_value-1] < A[return] <= A[return+1...r]
 */
void Partition(A, p, r)
{



}
//END QUICK SORT

/*Measure running time of three sorting algorithms, using randomly generated array of given size (input_size)
 *Find and return avg, min and max running time for the @run_numer random runs */
void MeasureSort(int size, int run_num)
{
        struct timeval begin, end;
        double sum1, sum2, sum3, min1, min2, min3, max1, max2, max3;

	sum1 = sum2 = sum3 = min1 = min2 = min3 = max1 = max2 = max3 = 0;

        for(int i=0; i < run_num; i++)
        {
                int * same_input = GenerateRandom(size);

                for(int x=1; x < 4; x++)
                {
                        double elapsed = 0;

                        if(x == 1)
                        {
                                int * work_copy = DuplicateArray(same_input, size);
                                gettimeofday (&begin, NULL);
                                BubbleSort(work_copy, size);
                                gettimeofday (&end, NULL);
                                elapsed = (end.tv_sec-begin.tv_sec) + ((end.tv_usec-begin.tv_usec)/1000000.0);
                                sum1 += elapsed;

                                if(min1 > elapsed)
                                        min1 = elapsed;

                                if(max1 < elapsed)
                                        max1 = elapsed;
                        }

                        else if(x == 2)
                        {
                                int * work_copy = DuplicateArray(same_input, size);
                                gettimeofday (&begin, NULL);
                                InsertionSort(work_copy, size);
                                gettimeofday (&end, NULL);
                                elapsed = (end.tv_sec-begin.tv_sec) + ((end.tv_usec-begin.tv_usec)/1000000.0);
                                sum2 += elapsed;

                                if(min2 > elapsed)
                                        min2 = elapsed;

                                if(max2 < elapsed)
                                        max2 = elapsed;
                        }

                        else if(x == 3)
                        {
                                int * work_copy = DuplicateArray(same_input, size);
                                gettimeofday (&begin, NULL);
                                SelectionSort(work_copy, size);
                                gettimeofday (&end, NULL);
                                elapsed = (end.tv_sec-begin.tv_sec) + ((end.tv_usec-begin.tv_usec)/1000000.0);
                                sum3 += elapsed;

                                if(min3 > elapsed)
                                        min3 = elapsed;

                                if(max3 < elapsed)
                                        max3 = elapsed;
                        }
                }
        }

        cout << ' ' << setw(21) << "Input_Size" << setw(9) << "Run_Num" << setw(10) << "Average" 
	<< setw(10) << "Minimum" << setw(10) << "Maximum" << endl;
        
	cout << right << "Bubble" << setw(12) << size << setw(11) << run_num << setw(12) << sum1/run_num 
	<< setw(8) << min1 << setw(11) << max1 << endl;
        
	cout << right << "Selection" << setw(9) << size << setw(11) << run_num << setw(12) << sum2/run_num 
	<< setw(8) << min2 << setw(11) << max2 << endl;
        
	cout << right << "Insertion" << setw(9) << size << setw(11) << run_num << setw(12) << sum3/run_num 
	<< setw(8) << min3 << setw(11) << max3 << endl;

}

int main()
{
	int input_size, run_num;

	cout << "Enter array size: ";
	cin >> input_size;
	cout << endl;
	
        cout << "-------------------Testing Algorithms------------------" << endl;

	for(int i=1; i < 4; i++)
	{
		int * arrPointer = GenerateRandom(input_size);
		cout << "Randomly generated array: " << endl;
		print(arrPointer, input_size);
		
		if(i == 1)
		{
			cout << "Array after Bubble Sort" << endl;
			BubbleSort(arrPointer, input_size);
			print(arrPointer, input_size);

		        if(IsSorted(arrPointer, input_size))
        		        cout << "BubbleSort passed testing!" << endl;
		        else
        	        	cout << "Bubble Sort did NOT pass testing!" << endl;

	        	cout << endl;
		}

		else if(i == 2)
		{
			cout << "Array after Insertion Sort" << endl;
			InsertionSort(arrPointer, input_size);
			print(arrPointer, input_size);

		        if(IsSorted(arrPointer, input_size))
                		cout << "Insertion Sort passed testing!" << endl;
		        else
                		cout << "Insertion Sort did NOT pass testing!" << endl;
		
			cout << endl;
		}

		else if(i == 3)
		{
			cout << "Array after Selection Sort" << endl;
			SelectionSort(arrPointer, input_size);
			print(arrPointer, input_size);

		        if(IsSorted(arrPointer, input_size))
                		cout << "Selection Sort passed testing!" << endl;
		        else
                		cout << "Selection Sort did NOT pass testing!" << endl;

			cout << endl;
		}
		
		//deallocate dynamic memory
		delete [] arrPointer;
	}

        cout << "-------------------Measuring Algorithms------------------" << endl;
	int num;

	cout << "Enter number of random runs: ";
	cin >> num;
	
	cout << "...Measuring input size = 10..." << endl;
	cout << "...Measuring input size = 20..." << endl;

        cout << "--------------------Summary of Results-------------------" << endl;
	input_size = 10;
	MeasureSort(10, num);

	input_size = 20;
	MeasureSort(20, num);

}
