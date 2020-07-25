//Adrianna Batista
//March 22, 2017
//File Name: polygon_class.h
//Header file for the Polygon Class

#include <iostream>
using namespace std;

class Polygon {

	public:
		//Default Constructor to init data members with appropriate default
		Polygon();
		/*Note: the const DEFAULT_MAX, which is MAX is set equivalent to, had to be set to 70 because any number greater than that will not fit on the screen or display properly when drawing the polygon. To change this the extra spaces and one of the for loop equations would have to be changed*/ 

		//Constructor to init object with specific MIN and MAX values
		Polygon(int, int);

		//Constructor to init object with specific length, width, MIX, and MAX values
		Polygon(int, int, int, int);

		//Destructor to clear out data members and adjust class level data as needed
		~Polygon();

		//Method to populate data members from external user input
		void inputPolygon();

		//Mutator methods to ensure data integrity
		bool setLength(int);
		bool setWidth(int);

		//Method to calculate the area of the polygon
		int calcArea();

		//Method to calculate the perimeter of the polygon
		int calcPerimeter();

		//Method to calculate the average area of all the polygons
		double calcAvgArea();

		//Method to calculate the average perimeter of all the polygons
		double calcAvgPerimeter();

		//Method to display data members for single polygon
		void displayPolygon() const;

		//Method to draw a polygon of specified length and width
		void drawPolygon() const;

		//Method to display options menu for user
		static void displayMenu();	

		//Accessor methods to access and return data
		int getLength() const;
		int getWidth() const;
		static int getNumPolygons();
		int getArea() const;
		int getPerimeter() const;
		static double getAvgArea();
		static double getAvgPerimeter();
		static int getMaxPolygons();

	private:
		static const int MAX_POLYGONS=25, DEFAULT_MIN=10, DEFAULT_MAX=70;
		int length, width, perimeter, area;
		static double avg_area, avg_perimeter;
		const int MIN, MAX;
		static int numPolygons, sum_area, sum_perimeter;
};
