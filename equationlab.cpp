//Adrianna Batista
//February 8th 2017
//Equation Lab

//library declaration
#include <iostream>
#include <cstdlib> 
#include <ctime>

using namespace std;

//function prototype declarations
void menu_display();
void statistics(int [] [3], int);
void all_statistics(int [][3]);
int randomgen(int, int);
bool checkanswer(double, double, int, double);
void storearray(int [][4], int [][3], int, int, int, int, int);
int oppgen(const int, const int);

//global variable declarations
int rNum, rNum1, rNum2, rOpp, rOperator, shift, scalingFactor, selectmenu, counter, samelevel=1, answer_flag, level=1, row, column;
double answer, rNumdub, rNum1dub, rNum2dub, rOperatordub;
char opp;
const int OPP_SHIFT = 1;
const int OPP_SCALE = 4;

//array declarations
int array_equations[500][4] = {{rOperator, rNum1, rNum2, answer_flag}}; //can I declare arrays like this?
int array_stats[500][3] = {{level, rOperator, answer_flag}};

main ()
{
	while (counter < 10)
	{
		//static int level = 1;
		if (level == 1)
		{
			//Level 1
			level = 1;
			shift = 0;
			scalingFactor = 10;
		}

		else if (level == 2)
		{
			//Level 2
			level = 2;
			shift = 0;
			scalingFactor = 25;
		}

		else if (level == 3)
		{
			//Level 3
			level = 3;
			shift = 10;
			scalingFactor = 15;
		}

		else if (level == 4)
		{
			//Level 4
			level = 4;
			shift = -25;
			scalingFactor = 50;
		}

		//Find value of rNum1
		rNum1 = randomgen(shift, scalingFactor);
		rNum1dub = rNum1; //see variable explanation below

		//Find value of rNum2
		rNum2 = randomgen(shift, scalingFactor);
		rNum2dub = rNum2; //see variable explanation below

		//Find value of rOperator
		rOperator = oppgen(OPP_SHIFT, OPP_SCALE);
		rOperatordub = rOperator; /*these variables are the same but one is int and one is double. The double, rOperatordub, corrects issues with 
				decimals while agreeing with the double arrays and the int (rOperator) allows for switch statements to still be used*/
	
		switch(rOperator)
		{
			case 1:
                		opp = '+';
			break;

			case 2:
				opp = '-';
			break;

			case 3:
				opp = '*';
			break;

			case 4:
				opp = '/';
			break;
		}

		//Check if equation has been given before, if it was and was correctly answered then give new equation

		for(int row = 0; row < 500; row++)
		{
			while (((rNum2 == 0) && (rOperator == 4)) ||((array_equations[row][0] == rOperator) && (array_equations[row][1] == rNum1) && (array_equations[row][2] == rNum2) && (array_equations[row][3] == 1))) //the following conditional statement accounts for divide by zero errors and equation repition

				{
					//Find new value of rNum1
					rNum1 = randomgen(shift, scalingFactor);
					rNum1dub = rNum1;

					//Find new value of rNum2
					rNum2 = randomgen(shift, scalingFactor);
					rNumdub = rNum2;
				}
		}
	
		//display equation
		cout << rNum1dub << " " << opp << " " << rNum2dub << " = ";
		cin >> answer;

		//invoke check answer function
		bool b = checkanswer(rNum1dub, rNum2dub, rOperator, answer);

		if(b)
		{
			cout << "Correct!" << endl;
			counter++; //increase counter by 1
			answer_flag = 1; //flag to keep track of correct or incorrect
		}
		else
		{
			cout << "Incorrect!" << endl;
			counter=0; //reset counter to force 10 correct answers in a row
			answer_flag = 0; //flag to keep track of correct or incorrect
		}

		//store equation and stats function
		storearray(array_equations, array_stats, rNum1, rNum2, rOperator, level, answer_flag);

		//display menu once counter amount 10 is reached
		if (counter == 10)
		{
			//Display menu function
			menu_display();
		
			//Intake menu option
			cin >> selectmenu;
		
			switch (selectmenu)
        		{
                		case 1:
					//choice to stay at same level
                        		level = level;
                        		counter = 0;
                		break;
                	
				case 2:
					//choice to increase level by one
                        		level++;
                        		counter = 0;
                		break;

                		case 3:
					//choice to display current level stats and redisplay menu
                        		statistics(array_stats, level);
					counter = 10;
                		break;

                		case 4:
                        		//choice to quit program and 
					level = 1;
					statistics(array_stats, level);

					level = 2;
					statistics(array_stats, level);

					level = 3;
					statistics(array_stats, level);

					level = 4;
					statistics(array_stats, level);

				       	//should display stats for each of the levels the game was played on
                        		cout << "Program is ending...Have a nice day!" << endl;
                		break;
			}
		}

		}
}//end main

//function to generate random number
int randomgen(int shift, int scalingFactor)
{
	//static bool statement used to ensure that rNum1 and rNum2 values will be different
	static bool a = true;
	if (a)
	{
		srand(time(0));     //or could I do srand(time(NULL));?
		a = false;
	}

	rNum = shift + rand()% scalingFactor;

	return rNum;
}

//separate random function for operator 
int oppgen(const int OPP_SHIFT, const int OPP_SCALE)
{
	
 	static bool a = true;
	if(a)
	{
		srand(time(0));
		a = false;
	}

	rOpp = OPP_SHIFT + rand()% OPP_SCALE;

	return rOpp;
}
	
bool checkanswer(double rNum1dub, double rNum2dub, int rOperator, double answer)
{
	double calc;

	switch (rOperator)
	{
		case 1:
			calc = rNum1dub + rNum2dub;
		break;

		case 2:
			calc = rNum1dub - rNum2dub;
		break;

		case 3:
			calc = rNum1dub * rNum2dub;
		break;

		case 4:
			calc = rNum1dub / rNum2dub;
		break;
	}

	if (calc == answer)
	       return true;
	
	else if (calc != answer)
		return false;	
}

void storearray(int array_equations[][4], int array_stats[][3], int rNum1, int rNum2, int rOperator, int level, int answer_flag)
{
	static int row = 0;
        for (int column = 0; column < 4; column++)
        {
                switch(column)
                {
                        case 0:
                                array_equations[row][column] = rOperator;
                        break;

                        case 1:
                                array_equations[row][column] = rNum1;
                        break;

                        case 2:
                                array_equations[row][column] = rNum2;
                        break;

                        case 3:
                                array_equations[row][column] = answer_flag;
                        break;
                }
        }

        for (int column = 0; column < 3; column++)
        {
                switch(column)
                {
                        case 0:
                                array_stats[row][column] = level;
                        break;

                        case 1:
                                array_stats[row][column] = rOperator;
                        break;

                        case 2:
                                array_stats[row][column] = answer_flag;
                        break;
		 }
        }

	row++;
}

void menu_display()
{
	cout << "1. Continue at the current level. " << endl;
        cout << "2. Go to the next level." << endl;
        cout << "3. Display summary statistics for the current level." << endl;
        cout << "4. Quit." << endl;

}

void statistics(int array_stats[][3], int level)
{
	double addcount_total, addcount_correct, subcount_total, subcount_correct, mulcount_total, mulcount_correct, divcount_total, divcount_correct, addpercent, subpercent, mulpercent, divpercent;

	for (int row = 0; row < 500; row++)
	{
		if(array_stats[row][0] != 0) //cancel out rows that don't have data yet, they're denoted by 0's
		{
			if(array_stats[row][0] == level)
			{
				if(array_stats[row][1] == 1) //limit rows to only ones with rOperator of 1/addition equations
				{
					addcount_total++;

					if(array_stats[row][2] == 1)
					{
						addcount_correct++;
					}
				}
			
				else if (array_stats[row][1] == 2) //limit rows to only ones with rOperator of 2/subtraction equations
				{
					subcount_total++;

					if(array_stats[row][2] == 1)
					{
						subcount_correct;
					}
				}
			
				else if(array_stats[row][1] == 3) //limit rows to only ones with rOperator of 3/multiplication equations
				{
					mulcount_total++;

					if(array_stats[row][2] == 1)
					{
						mulcount_correct++;
					}
				}

				else if(array_stats[row][1] == 4) //limit rows to only ones with rOperator of 4/division equations
				{
					divcount_total++;

					if(array_stats[row][2] == 1)
					{
						divcount_correct++;
					}
				}
			}
		}
	}

	addpercent = (addcount_correct / addcount_total) * 100;
	subpercent = (subcount_correct / subcount_total) * 100;
	mulpercent = (mulcount_correct / mulcount_total) * 100;
	divpercent = (divcount_correct / divcount_total) * 100;
	
	cout << "----Display summary statistics for Level " << level << " ----" << endl;
	cout << addpercent << "% of addition equations correctly answered" << endl;
	cout << subpercent << "% of subtraction equations correctly answered" << endl;
	cout << mulpercent << "% of multiplication equations correctly answered" << endl;
	cout << divpercent << "% of division equations correctly answered" << endl;

}
