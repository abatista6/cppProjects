#include<iostream>
using namespace std;

void swap(int x[], int sizex, int y[],int sizey, int MAX);
void swap(int& i, int x[], int y[]);
void display(int x[], int y[], int MAX);
void initialize( int z[][4], int ROW, int COL, int x[],int y[], int s);
void display(int z[][4], int ROW, int COL);
main(){
	const int MAX=10;
	//initialize x array with even values and y array with odd values
	int x[MAX]={1,3,5,7,9,11,13,15,17,19};
	int y[MAX]={2,4,6,8,10,12,14,16,18,20};

	//display x and y arrays to user
	int i;
	for(i=0;i<MAX;i++){
		cout<<x[i]<<" "<<y[i]<<endl;
	
	}
	//call swap function to swap elements in the x and y arrays
	swap(x,MAX,y,MAX,10);

	//display swapped array to user
	display(x,y,MAX);

	//initialize 2 dimensional array
	const int ROW=7;
	const int COL=4;
	int z[ROW][COL];
	
	initialize(z,ROW,COL,x,y,MAX);

	//display 2 dimesnsional array
	display(z,ROW,COL);
}
//swap function will swap the even indexed elements of the x array with the y array 
void swap(int x[], int sizex, int y[], int sizey, int MAX){
	
	int i;
	void swap(int& i, int x[], int y[]);
	for(i=0;i<MAX;i++){
		if((i%2)==0){
			swap(i,x,y);
		}
	}
}

void swap(int& i,int x[], int y[]){

	int z;
	z=x[i];
	x[i]=y[i];
	y[i]=z;

}
//display function will output the swapped arrays to the screen
void display(int x[], int y[], int MAX){

	for(int i=0;i<MAX;i++){
		cout<<x[i]<<" "<<y[i]<<endl;
	}
}
//initialize function will initialize all the even indexed rows in the 2 dimensional array with values from the x array 
//initialize function will also initialize all odd indexed rows in the 2 dimensional array with values from the y array
void initialize( int z[][4], int ROW, int COL, int x[],int y[], int s){

	int index=0;
	int index2=0;
	int r;
	int c;


	if((r%2)==0){
	for(r=0;r<ROW;r++){
			for(c=0;c<COL;c++){
				z[r][c]=x[index];
				index++;
			}
			
		}
	}	
		
		else{
			for(r=0;r<ROW;r++){
				for(c=0;c<COL;c++){
					z[r][c]=y[index2];
					index2++;
				}
		
			}		

		}	
	
	
}
//display function will output the 2 dimensional array to the screen 
void display(int z[][4], int ROW, int COL){
	
	int r;
	int c;
	for(r=0;r<ROW;r++){
		for(c=0;c<COL;c++){
			cout<<z[r][c]<<"   ";
		}
		cout<<endl;
	}
	
}
