//Adrianna Batista
//Operating Systems
//This program prompts the user to input either a run instruction
//Or an instruction to exit the program. Ignores commands that are
//Not "run" or "exit" and it will not run anything if the arguments are invalid

#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;

//Pre-condition: str is not null
//Post-condition: Returns the name of the instruction or a dummy name 
//				   if not "run" or "exit"
string getName(string str){
	if(str.substr(0,3) == "run")
		return "run";
	else if(str.substr(0,4) == "exit")
		return "exit";
		
	return "fail";
}

//Returns only the argument of the string that was input
string getArg(string str, string name){
	return str.substr(name.length(),str.length()-1);
}

//Pre-condition: "run" was the instruction that was input
//Post-condition: A child thread is created to run the instruction
//				   and terminates once it finishes
//Executes the run instruction with the given argument
//Will not execute if the argument is invalid
void Execute(string arg){
	pid_t pid;
	string s;
	int i = arg.length()-1, pos;
	bool found = false;
	
	//Converts arg to a const char* from string
	char* path = &arg[0u];
	pos = arg.find_last_of("/");
	
	//Converts the file part of arg to a const char* from string
	s = arg.substr(pos+1,arg.length()-1);
	char* file = &s[0u];
	
	//Creates the fork to make a child process that runs the instruction
	//The parent waits for the child to finish
	pid = fork();
	if (pid<0){
		cout << "Error, fork failed\n";
		exit(0);
	}
	else if(pid == 0){
		execl(path,file,0,0);
		exit(0);
	}
	else{
		wait(NULL);
	}
}

int main(){
	bool exit = false;
	string str = " ", name, arg;
	int pos;
	
	//Uses a while loop to loop through inputs
	//Takes in input, removes all whitespace (tabs and spaces)
	//If the input is null, nothing will execute
	//If there is input, split up the instruction and argument
	//Then exit if exit is the instruction, or execute the instruction if run
	while(exit == false){
		cout << ">";
		getline(cin, str);
		
		str.erase(remove(str.begin(), str.end(), '\t'), str.end());
		str.erase(remove(str.begin(), str.end(), ' '), str.end());
		
		if(str.length() > 0){
			name = getName(str);
			arg = getArg(str,name);
		
			if(name == "exit")
				exit = true;
			else if(name == "run")
				Execute(arg);
		}
	}
}
