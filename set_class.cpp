//Adrianna Batista
//4/18/2017
//Implementation File for the Set Class
//
//

#include "set_class.h"

template<class T>

//default constructor for class Set
Set<T>::Set(int s) {
	
	set = NULL;

	//Check that given size is greater than 0, else set size to 10
	/*if (s > 0)
		pSize = s;
	else
		pSize = DEFAULT_SIZE;*/
	pSize = setPsize(s);

	set = new T[pSize];

	if(!set) //exit program if memory isn't allocated
	{
		cout << "ERROR! Memory allocation has failed. Now exiting program..." << endl;
		pSize = 0;
		exit(1);
	}

	for (int i=0; i < pSize; i++) //set all the elements up to pSize to 0
		set[i] = 0;

	numElements = 0; //since the array hasn't been populated, set elements to 0
	name = 'Z';
}
template<class T>
//custom constructor
Set<T>::Set(T a[], int s, char n) {

	pSize = setPsize(s); //invokes mutator method to check for pSize > 0
	numElements = 0; //?? should this be set to 0 or set to pSize or increment with each succesful add
	name = setName(n);

	set = new T[pSize];

	if(!set) //exit program if memory isn't allocated
	{
		 cout << "ERROR! Memory allocation has failed. Now exiting program..." << endl;
		 pSize = 0;
		 exit(1);
	}
	
	for (int i=0; i < pSize; i++)
	{
		//call to subscript operator to input data from consturctor
		//into the array
		add_check(a[i]);
	}
}

template<class T>
//copy constructor
Set<T>::Set(const Set<T> &SetToCopy) { //object recieved as reference to prevent infinte recursion

	if(pSize) //check if the set has elements to be copied
	{
		pSize = SetToCopy.numElements;
		numElements = 0;
		name = SetToCopy.name; //or name = SetToCopy.getName()

		set = new T[pSize]; //allocation of required memory
		
		if(!set) //exit program if memory isn't allocated
		{
			cout << "ERROR! Memory allocation has failed. Now exiting program..." << endl;
			pSize = 0;
			exit(1);
		}
		
		for (int i = 0; i < pSize; i++)
		{
			//call to subscript operator to input data from previous
			//set into new set using the a.getElements(i) in the 
			//parenthesis of the subscript/add method
			set[i] = SetToCopy.set[i];
		}

		numElements = pSize;
	}
}

template<class T>
//Destructor
Set<T>::~Set() {

	if (set)
		delete [] set;
	set = NULL;

}

//Mutator Methods
template<class T>
//Sets the Set name to upper case
char Set<T>::setName(char n){  //should I also do error handling?

	name = toupper(n);
	return name;
}

template<class T>
//Checks pSize value
int Set<T>::setPsize(int s) {

	if(s > 0)
	{
		pSize = s;
	}

	else
	{
		s = DEFAULT_SIZE;
		pSize = s;
	}

	return pSize;
}

//Overloaded Operator Methods
template<class T>
//Overloaded Method for addition of new element to the set
bool Set<T>::operator+(T element) {

	bool check;
	check = add_check(element);
	
	return check;
}

template<class T>
//Overloaded Method for deletetion of an element from the set
bool Set<T>::operator-(T element) {

	bool check = false;

	if(!Iselement(element)) //to correct unknown logistical error
	{
		if(remove(element))
			check = true;
	}

	return check;
}

template<class T>
//Overloaded Method for Union
Set<T> Set<T>::operator+(const Set<T> &b){
	
	Set C = unions(b);

	return C;

}

template<class T>
//Overloaded Method for Difference
Set<T> Set<T>:: operator-(const Set<T> &b) {

	Set C = difference(b);

	return C;

}

template <class T>
//Overloaded Method for Intersection
Set<T> Set<T>::operator^(const Set<T> &b) {

	Set C = intersection(b);

	return C;

}

template<class T>
//Overloaded Equality Operator
bool Set<T>::operator==(const Set<T> &right) const {

	return equality(right);
}

template<class T>
//Overloaded Inequality Operator
bool Set<T>::operator!=(const Set<T> &right) const {
	
	return!(*this == right); //invoke Set::operator==
}

template<class T>
//Overloaded Assignment Operator
const Set<T> &Set<T>::operator=(const Set<T> &right){

	//to avoid self assingment
	if(&right != this) 
	{	
		numElements = 0;

		for(int i=0; i < right.numElements; i++)
			add_check(right.set[i]);
	}
	
	return *this;
}
//Accessor Methods
template<class T>
//Method to return pSize
int Set<T>::getPsize() const {

	return pSize;
}

template <class T>
//Method to retun numElements
int Set<T>::getNumElements() const {
	
	return numElements;
}

template <class T>
//Method to return element at position int i
T Set<T>::getElements(int i) const {

	return set[i];

}

template <class T>
//Method to return name of set
char Set<T>::getName() const {

	return name;
}

template <class T>
//Method to populate set of integers from user input
void Set<T>::input(istream &in) {

	T value, user_size, size;
	cout << "How many integers will be in the set?" << endl;
	in >> user_size;

	size = setPsize(user_size);

	cout << "Enter integer elements to store in the Set array. Enter " << Set::DELIM << " to stop: ";
	//do {
		for(int i=0; i < size; i++)
		{
			in >> value;
			//if(value != -999)
			//{
				add_check(value);

			//}

			//else
				//break;
		}
	//}while(value != -999);
}

template <class T>
//Method to display the set
void Set<T>::display(ostream &out) const {
	
	out << "Set " << name << ": {";
	out << set[0];
	for(int i=1; i < numElements; i++)
		out << ", " << set[i];
	out << "} " << endl;
}

template <class T>
//Method to check if element exists in set
bool Set<T>::Iselement(T element) const {
	
	bool checkElement = false;

	for (int i = 0; i < numElements; i++)
	{
		if(set[i]==element)
		{
			checkElement = true; //return true to denote element already exists
		}
		else
		{
			checkElement = false; //return false to denote element does NOT exist
		}
	}
	return checkElement;
}

//Subscript Operators
template <class T>
//Operator for non-const objects
int & Set<T>::operator[](int index) {

	if(index < 0 || index >= pSize) 
	{
		cout << "ERROR! Subscript out of bounds. Now ending program..." << endl;
		exit(1);
	}
	
	return(set[index]); //returns the address reference/location, not the value 
}

template <class T>
//Operator for const objects
int Set<T>::operator[](int index) const {

	T element;
	
	if(index < 0 || index >= pSize)
	{
		cout << "ERROR! Subscript out of bounds. Now ending program..." << endl;
		exit(1);
	}
	element = set[index];

	return(element); //return copy of element at set[index]
}


//Private Methods

//Methods to preform the set operations
template <class T>
//Union set operation
Set<T> Set<T>::unions(const Set<T> &b) {

	Set union_set = *this;
	for (int i=0; i < b.numElements; i++)
	{
		union_set.add_check(b[i]); //or union_set.add_check(b[i]);
	}

	return union_set;
}

template <class T>
//Intersection set operation
Set<T> Set<T>:: intersection(const Set<T> &b) {

	T element;
	Set intersect_set = *this;
	Set temp;

	for(int i=0; i < b.numElements; i++)
	{
		element = b[i];

		if(intersect_set.Iselement(element) == true) //if the element DOES exist already
			temp.add(b.set[i]);
	}

	return temp;
}

template <class T>
//Difference set operation
//Find elements that are in one set but not the other
Set<T> Set<T>::difference(const Set<T> &b) {

	T element;
	Set diff_set =  *this;
	Set temp;

	for(int i=0; i < diff_set.numElements; i++)
	{
		element = diff_set[i];

		if(b.Iselement(element) == false) //if the element in diff_set does NOT exist in b
			temp.add(diff_set.set[i]);
	}

	return temp;
}

template <class T>
//Equality set operation
bool Set<T>::equality(const Set<T> &b) const {

	bool equals = true;

	if(numElements != b.numElements)
	{
		equals = false;
	}

	else
	{
		for(int i=0; i < numElements; i++)
		{
			if(set[i] != b.set[i])
			{
				equals = false;
				break;
			}
		}
	}

	return equals;
}

template <class T>
//Inequality set operation
bool Set<T>::inequality(const Set<T> &b) const {

	return !(equality(b));
}

template <class T>
//Method to add elements to array with OUT checking if exisitng element
bool Set<T>::add(T element) {

	bool add_nocheck = false;

	//if(element != DELIM) //if user did NOT enter -999
	//{
		 if((numElements == pSize)||(numElements > pSize)) //if true, new memory will be allocated
		 {
			 pSize += DEFAULT_SIZE;
			 T *newset = new T[pSize];
			 
			 if(!newset) //exit program if memory isn't allocated
                         {
				cout << "ERROR! Memory allocation has failed. Now exiting program..." << endl;
				pSize = 0;
				exit(1);
			 }
			 
			 if(set)
			 {
				 for(int i=0; i < pSize; i++) //copy elements from old array to new
				 {
					 newset[i] = set[i];
				 }

				 delete [] set; //delete array
				 set = NULL;
                         }
		  	 
			 set = newset; //assign set array pointer to new array
		 }

                        set[numElements++] = element; //add new element to pre-existing array while incrementing numElements
                        add_nocheck = true; //element successfully added
	//}

	return add_nocheck;
}

template <class T>
//Method to add elements to array WITH checking if element already exists
bool Set<T>::add_check(T element) {

	bool addElement = false;
	
	if (Iselement(element) == false) //if the element does not already exist
	{	
		addElement = add(element);
	}

	//else
	//	cout << "The integer " << element << " already exists in the set!" << endl;
	
	return addElement;
}

template <class T>
//Method to remove elements from array
bool Set<T>::remove_check(T element) {

	bool removeElement = false;

	if(Iselement(element) == true) //if the element is found in the set
	{
		remove(element);
		removeElement = true;
	}

	else //if the element is not found in the set
		cout << "Removal ERROR! The element " << element << " is not a member of the set" << endl;

	
	return removeElement;
}

template <class T>
//Method to remove elements from array with OUT checking
bool Set<T>::remove(T element) {

	bool remove_nocheck = false;

	for(int i=0; i < numElements; i++)
		set[i] = set[i+1];

	numElements--;
	pSize--;
	remove_nocheck = true;

	return(remove_nocheck);
}

int main () {

	//Two arrays of integers
	int a[7] = {1, 2, 3, 4, 5, 9, 9};
	double b[6] = {5.0, 6.3, 7.1, 8.2, 9.1, 1.0};
	char c[6] = {'a', 'b', 'c', 'd','e', 'f'};
	string d[5] = {"string", "pizza", "five", "eight", "six"};
	
	//Instantiation of two sets using previously declared arrays
	Set<int> s1(a, 7, 'a'); //Call to custom constructor
	Set<double> s2(b, 6, 'b'); //Call to custom constructor
	Set<char> s3(c, 6, 'c');
	Set<string> s4(d, 5, 'd');


	//Ouput sets
	cout << s1;
	cout << s2;
	cout << s3;
	cout << s4;
	
	Set<int> s; //Call to default constructor
	Set<string> p;

	cin >> p;
	cout << p;


	//Input elements from user input
	cin >> s;
	//Output elements given from user input
	cout << s;
	
	//Create a new set D from one of the above sets
	//Set<double> d(s2);
	//d.setName('d');
	//cout << d;

	//Add new elements to one of the existing sets
	if(s1 + 10)
		cout << "The integer 10 has been successfully added" << endl;
	if(s1+2)
		cout << "The integer 2 has been successfully added" << endl;
	cout << s1;

	//Remove elements from one of the existing sets
	if(s2-5)
		cout << "The integer 5 has been successfully removed" << endl;
	cout << s2;

	//Perform set operations on existing objects
	Set<int> e=s+s1;
       	
	//e.setName('e');
	cout << e;

/*	
 *	Set F;
 *	F.setName('F');
 *	F = s1 - s2;
 *	cout << F;
 *	Set G;
 *	G.setName('G');
 *	G = s1 ^ s2;
 *      cout << G;
 *	cout << "The sets " << s1.getName() << " and " << s2.getName() << " are ";
 *
 *	if(s1 != s2)
 *		cout << "not equal!" << endl;
 *	else if(s1 == s2)
 *		cout << "equal!" << endl;
 */
}

