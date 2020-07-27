#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
int rolldie();


void main()
{
	int result(0);
	int point(0);
    bool done = false;
	char ans;
	char enter;


	srand (time (0)); //sets the starting point for sequence of random numbers

	do
   {
	  result = rolldie() + rolldie();
      switch(result)
	  {  
        case 7:
        case 11:
			cout << "You rolled " << rolldie() << "+" << rolldie() << "=" result << "\n You win!" << endl;
            cout << "Do you want to play again? ";
			cin >> ans;
			
			 if(ans == 'n' || ans == 'N')
             {
				done = false;
                cout << "Thank you for playing...Program is ending. Have a nice day!" << endl;
             }
			 else if (ans == 'y' || ans == 'Y')
				done = true;
		break;
			
        case 2:
        case 3:
        case 12:
			cout << "You rolled a "<< result <<", you are a loser. " << endl;
			cout << "Do you want to play again? ";
			cin >> ans;
			
			 if(ans == 'n' || ans == 'N')
             {
				done = false;
                cout << "Thank you for playing...Program is ending. Have a nice day!" << endl;
             }
			 else if (ans == 'y' || ans == 'Y')
				done = true;
		break;
		
        default:
            point = result;
			  cout << "You rolled " << rolldie() << "+" << rolldie() << "=" << result << "\n Point is " << point << endl;
	        
			  do
			  {
			      rolldie();
                  rolldie();
                  
			      if(result == point)
                     cout << "You rolled " << rolldie() << "+" << rolldie() << "=" << result << "\n You win!" << endl;
				  else if
				     cout << "You rolled " << rolldie() << "+" << rolldie() << "=" << result << "\n You lose!" << endl;
			  
			  }while(result != point && result != 7);
			  
			  cout << "Do you want to play again? ";
			  cin >> ans;
			 
			  if(ans == 'n' || ans == 'N')
			  	 done = false;
			  else if (ans == 'y' || ans == 'Y')
				 done = true;
		}	
	}while(done);
}


int rolldie()
{ 
	return ((rand()%6)+1);
} 
