//Adrianna Batista
//4/13/2017
//Header File for the Set Class
//The purpose of the Set Class is to represent a set of integers. 
//All objects that are instantiated from this class represent 
//subsets of the set of integers.

#ifndef SET_CLASS_H
#define SET_CLASS_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>

using namespace std;

template<class T>
class Set {
	//Overloaded operator functions as global functions of the class
	friend istream &operator >> (istream &in, Set<T> &a){

		a.input(in);

		return(in);
	}
	friend ostream &operator << (ostream &out, const Set<T> &a){

		a.display(out);

		return(out);
	}

	public:
	       	//Constructors
		Set(int = DEFAULT_SIZE);//Default Constructor
	
		Set(T [], int, char);	//Custom Constructor
		
		Set(const Set<T>&);//Copy Constructor

		~Set();	//Destructor

		//Mutator Methods
		char setName(char); //changes Set name to upper case
		int setPsize(int); //checks pSize value if = 0 uses default size
		
		//Accessor Methods
		int getNumElements() const; //returns var numElements
		T getElements(int) const; //returns element at position int i
		char getName() const; //returns the name of the Set
		int getPsize() const; ///returns physical size of the set

		//Overloaded Methods which invoke the set operations union,
		//intersection, difference, equality, inequality, add, remove
		Set<T> operator+(const Set<T> &); //for union method
		Set<T> operator-(const Set<T> &); //for difference method 
		Set<T> operator^(const Set<T> &); //for intersection method
		bool operator!=(const Set<T> &) const; //for inequality method
		bool operator==(const Set<T> &) const; //for equality method
		bool operator-(T); //for remove method
		bool operator+(T); //for add method

		const Set<T> &operator=(const Set<T> &); //assignment operator

		//Method to determine if the specified integer is an element
                //of the set and returns true of false accordingly
                bool Iselement(T) const;

		//subscript operators
		//operator for non-const objects
		int &operator[](int);
		//operator for const objects
		int operator[](int) const;

	private:
		//Private data members
		T *set; //pointer to dynamically allocated array of int
		int pSize; //physical size of the set/array
		int numElements; //number of populated elements in the set
		static const int DEFAULT_SIZE = 10; //default value used to
		//dynamically allocate memory
		static const int DELIM = -999;//used to denote end of user input
		char name; //name of set using uppercase letters


		//Private Methods

		//This program implements the methods input, display, union,
                //intersection, difference, equality, inequality, add, remove
                //as private methods which are invoked by their respective
                //overloaded method

		 //Methods to preform the set operations

                //Union set operation
                //This methods creates a new set that represents the union of
                //the two sets (set of object method was invoked on and set
                //of object passed to method)
                //This methods returns the new set
                Set unions(const Set<T> &);

                //Intersection set operation
                //This method creates a new set that represents the intersection
                //of the two sets and returns the new set
                Set intersection(const Set<T> &);

                //Difference set operation
                //This method creates a new set that represents the difference
                //of the two sets and returns the new set
                Set difference(const Set<T> &);

                //Equality set operation
                //This method determines whether the two sets are equal and
                //returns true or false accordingly
		bool equality(const Set<T> &) const;

                //Inequality set operation
                //This method determines whether the two sets are not equal
                //and returns the true or false accordingly
		bool inequality(const Set<T> &) const;

		//Class level input/output methods
		void display(ostream &) const;
		void input(istream &);
		
		//This method adds a new element to an existing set and returns
		//true or false accordingly. This method first ensures that
		//the element being added is not already and element of the set
		//If the element can't be added, the return value false will
		//denote this. This method is able to add a new element
		//to the set even if the physical array is at capacaity
		//ex. (numElements == pSize || numElements > pSize)
		bool add_check(T);

		//This method removes an element from an existing set and 
		//returns true or false accordingly. For the element to be 
		//removed it MUST be an element of the set
		bool remove_check(T);


		
                //Add and remove methods that don't check if an element exists
                //These methods are used in the set operation methods
                bool remove(T);
                bool add(T);

};

#endif
