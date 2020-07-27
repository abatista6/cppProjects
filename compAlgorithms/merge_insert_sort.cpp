/* Adrianna Batista
 * Computer Algorithms
 * Insertion sort and Merge sort algorithms and tests
 */


/*1. Insertion sort */
//////////////////////

#include <iostream>
using std::cin;
using std::cout;
using std::string;
using std::endl;


void insertionSort (int arr[]) {
	void print (int []);
	
	int inc_index, temp;
   	    for (int index = 0 ; index< 20 ; index++) {
       	 	//you start look at the element AFTER index
                inc_index= index;
		//traverse through from the member after index  to the beginning of the list
		while (arr[inc_index] < arr [inc_index -1] && inc_index > 0){
			//if it is less than the element on the left, then swap 
			temp = arr[inc_index];
			//cout << "temp: " << arr [index];
			arr [inc_index ] = arr [inc_index-1];
			arr [inc_index -1] = temp;
			inc_index--;
		}
	}
	cout << "Printed array: " ;
}
/////////////////////


//left and right indeces of subarray arr 
void mergeSort(int arr[], int left, int right){
     
    void merge (int [], int, int, int);
    if (left < right)
    {
        //got this line below from a peer 
        int middle = left+(right-left)/2;
 
        // sort two halves recursivley 
        mergeSort(arr, left, middle);
        mergeSort(arr, middle+1, right);
 
	//merge together two halves
        merge(arr, left, middle, right);
    }
}


void merge (int arr[], int left, int middle, int right)
{
    int leftArrLen= middle - left + 1, rightArrLen =  right - middle;
    int indexFirst = 0,  indexSecond = 0, indexMerged = left;

     //temporary arrays
    int LeftArray[leftArrLen], RightArray[rightArrLen];
 
    //set temporary array data to arrays passed
    for (indexFirst = 0; indexFirst < leftArrLen; indexFirst++)
        LeftArray[indexFirst] = arr[left + indexFirst];
    for (indexSecond = 0; indexSecond < rightArrLen; indexSecond++)
        RightArray[indexSecond] = arr[middle + 1+ indexSecond];
 
    //merge
    //int indexFirst = 0,  indexSecond = 0, indexMerged = left; 
    while (indexFirst < leftArrLen && indexSecond < rightArrLen){
        if (LeftArray[indexFirst] <= RightArray[indexSecond])
        {
            arr[indexMerged] = LeftArray[indexFirst];
            indexFirst++;
        }
        else
        {
            arr[indexSecond] = RightArray[indexSecond];
            indexSecond++;
        }
        indexMerged++;
    }
 
    //copy rest of elenents that were not copied
    while (indexFirst < leftArrLen){
        arr[indexMerged] = LeftArray[indexFirst];
        indexFirst++;
        indexMerged++;
    }
 
    while (indexSecond < rightArrLen){
        arr[indexMerged] = RightArray[indexSecond];
        indexSecond++;
        indexMerged++;
    }
}

/////////////////////
//helper function: 
void print (int  arr[]){
	cout << "[ ";
	for (int x = 0 ; x<20; x++)
		cout << arr[x] << ", ";
	cout << "]";
}

main (){
	int test1 [20] = {7, 4567890, 65789, 4678, 87, 456, 24, 632, 35, 1, 54, -1, 29, 20, 3798, 12, 532, 2333, 21};
	int test2 [20] = {9, 1, 3, 4, 6, 2, 0, 38973, -9, 282, 31, 45, 2398, 381, 90, 119, 212};
	int test3 [20] = {2,4, 5, 39782, 8, 292 ,13493, 4321, 49, 398, 10, 1000, 10000, 1999999};
	int test4 [20] = {1, 55, 33232, 903, 34, 32, 7, 394, 32, 71, 13, 55,46, 2098, 33333, 22, 21, 11, 0,34};

	cout << "Unsorted array: " ;
	print (test1);
	cout <<endl;
	insertionSort(test1);
	print(test1);
	cout <<endl;
	mergeSort(test1, 0, 19);
	print (test1);	
	cout <<endl;

	
    cout << "Unsorted array: " ;
    print (test2);
    cout <<endl;
    insertionSort(test2);
    print(test2);
    cout <<endl;
    mergeSort(test2, 0, 19);
    print (test2);
    cout <<endl;


  	cout << "Unsorted array: " ;
    print (test3);
    cout <<endl;
    insertionSort(test3);
    print(test3);
    cout <<endl;
    mergeSort(test3, 0, 19);
    print (test3);
    cout <<endl;


  	cout << "Unsorted array: " ;
    print (test4);
    cout <<endl;
    insertionSort(test4);
    print(test4);
    cout <<endl;
    mergeSort(test4, 0, 19);
    print (test4);
    cout <<endl;
};
