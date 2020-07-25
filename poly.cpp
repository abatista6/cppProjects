//Adrianna Batista
//March 22, 2017
//File Name: polygon_implement.cpp
//Implementation file for the Polygon Class that includes definitions for the class

#include "polygon_class.h"

//define and init static data member at global scope
int Polygon::numPolygons=0;
int Polygon::sum_area=0;
int Polygon::sum_perimeter=0;
double Polygon::avg_area;
double Polygon::avg_perimeter;

//Default Constructor to init data members with approporiate default
Polygon::Polygon():length(0), width(0), MIN(DEFAULT_MIN), MAX(DEFAULT_MAX), perimeter(0), area(0) {
	//intentionally left blank
}

//Constructor to init object with specific MIN and MAX values
Polygon::Polygon(int MIN, int MAX): Polygon() {
	//intentionally left blank
}

//Constructor to init object with specific length, width, MIN, and MAX values
Polygon::Polygon(int len, int wid, int MIN, int MAX): Polygon(MIN, MAX) {
	setLength(len);
	setWidth(wid);
	numPolygons++;
}

//Destructor to clear out data members and adjust class level data as needed
Polygon::~Polygon() {
	--numPolygons;
	--width;
	--length;
}

//Method to populate data members from external user input
void Polygon::inputPolygon() {

	do {
		cout << "Enter length: ";
		cin >> length;
	} while(setLength(length) == false);

	do {
		cout << "Enter width: ";
		cin >> width;
	} while(setWidth(width) == false);	

	numPolygons++;
	calcArea();
	calcPerimeter();
	calcAvgArea();
	calcAvgPerimeter();
}

//Mutator methods to ensure data integrity
bool Polygon::setLength(int len) {
	bool validLength = false;
	if (len >= MIN && len <= MAX) {
		validLength = true;
		length = len;
	}

	else
		cout << "ERROR! Invalid length input" << endl;

	return validLength;
}

bool Polygon::setWidth(int wid) {
	bool validWidth = false;
	if (wid >= MIN && wid <= MAX) {
		validWidth = true;
		wid = width;
	}

	else
		cout << "ERROR! Invalid width input" << endl;

	return validWidth;
}

//Method to calculate the area of the polygon
int Polygon::calcArea() {
	sum_area -= area;
	area = length * width;
	sum_area += area;
	return area;
}

//Method to calculate the perimeter of the polygon
int Polygon::calcPerimeter() {
	sum_perimeter -= perimeter;
	perimeter = (2*width) + (2*length);
	sum_perimeter += perimeter;
	return perimeter;
}

//Method to calculate the average area of the polygons
double Polygon::calcAvgArea() {
	avg_area = sum_area/numPolygons;
	return avg_area;
}

//Method to calculate the average perimeter of the polygons
double Polygon::calcAvgPerimeter() {
	avg_perimeter = sum_perimeter/numPolygons;
	return avg_perimeter;
}

//Accessor methods to access and return data
int Polygon::getLength() const {
	return length;
}

int Polygon::getWidth() const {
	return width;
}

int Polygon::getNumPolygons() {
	return numPolygons;
}

int Polygon::getArea() const {
	return area;
}

int Polygon::getPerimeter() const {
	return perimeter;
}

double Polygon::getAvgArea() {
	return avg_area;
}

double Polygon::getAvgPerimeter() {
	return avg_perimeter;
}

int Polygon::getMaxPolygons() {
	return MAX_POLYGONS;
}

//Method to display data members for single polygon
void Polygon::displayPolygon() const {
	cout << "Length: " << length << endl;
	cout << "Width: " << width << endl;
	cout << "Perimeter: " << perimeter << endl;
	cout << "Area: " << area << endl;

	//call to the Polygon draw function to show the shape
	drawPolygon();
}

//Method to display options menu for user
void Polygon::displayMenu() {
	cout << "------------------------------Display Menu Options------------------------------" << endl;
	cout << "  1. Build a new polygon object and assign it as the next entry in the array." << endl;
	cout << "  2. Draw the shape of any one of the previously built polygons." << endl;
	cout << "  3. Display summary of information for all polygons that have been built." << endl;
	cout << "  4. Quit the program." << endl;
	cout << "------------------------------End of Menu Options------------------------------" << endl;
}

//Method to draw a polygon of specified length and width
void Polygon::drawPolygon() const {
	
	for (int i=1; i <= length; i++)
	{
		cout << "* ";
	}
	cout << endl;
	
	for (int i=1; i <= width-2; i++)
	{
		cout << '*';
		
		for (int j=1; j <= ((length*2)-3); j++)
		{
			cout << ' ';
		}
		
		cout << '*' << endl;
	}

	for (int i=1; i <= length; i++)
	{
		cout << "* ";
	}
	cout << endl;
}

//Function Prototype
void displayStats(Polygon *p[]);

//Driver
int main () {
	int answer, object, i, redisplay=0;
	const int MAX_OBJ = Polygon::getMaxPolygons();
	Polygon *p[MAX_OBJ];
	
	//Declare an array of polygon objects as specified
	for (i = 0; i < MAX_OBJ; i++){
		p[i] = new Polygon;
		p[i]->inputPolygon();
		p[i]->displayPolygon();

		do {
			Polygon::displayMenu();
			cout << "Menu option: ";
			cin >> answer;
			
			switch (answer)
			{
				case 1:
					redisplay=0;
				break;

				case 2:	
					cout << "Specify desired polygon by using objects numerical position in the array: ";
					cin >> object;
					p[object]->displayPolygon();
					redisplay = 1;
				break;

				case 3:
					//call to summary stats function
					displayStats(p);
					redisplay = 1;
				break;

				case 4:
					cout << "Program is now ending...Have a nice day!" << endl;
					return 0;
				break;

				default:
					cout << "ERROR! The option selected is invalid." << endl;
					redisplay = 1;
				break;
			}
		} while (redisplay == 1);

		redisplay = 0;
		
	} //end loop
	delete []p;
}//end main

void displayStats(Polygon *p[])
{
	for (int i = 0; i<= Polygon::getNumPolygons()-1; i++)
	{
		cout << "-----Statistics for Polygon #" << i << " -----"<< endl;
		cout << "  Length: " << p[i]->getLength() << endl;
		cout << "  Width: " << p[i]->getWidth() << endl;
		cout << "  Perimeter: " << p[i]->getPerimeter() << endl;
		cout << "  Area: " << p[i]->getArea() << endl;
	}

	cout << "-----Statistics for all Polygons:-----" << endl;
	cout << "  Number of Polygons built: " << Polygon::getNumPolygons() << endl;
	cout << "  Average Perimeter: " << Polygon::getAvgPerimeter() << endl;
	cout << "  Average Area: " << Polygon::getAvgArea() << endl;
}
