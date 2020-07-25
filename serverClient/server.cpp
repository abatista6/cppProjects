#include <iostream>
#include <string>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>

using namespace std;

string exec(const char* cmd)
{
    char buffer[128];
    string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw runtime_error("popen() failed!");
    try {
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}


int  main (int argc, char *argv[]) {

	// server. declaring port number

	if (argc != 2){
		cerr << "Usage: port" << endl;
		exit(0);

	}

	//get port
	int port = atoi(argv[1]);
	//buffer to send and receive messages
	char msg[1500];

	//set up connection
	sockaddr_in servAddr;
	bzero((char*) &servAddr, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(port);

	//opens socket w internet adddress and keeps track of descriptor
	int serverSd = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSd < 0) { 
		cerr << "Error establishing the server socket" << endl;
		exit(0);
	}

	// bind socket and address 
	int bindStatus = bind(serverSd, (struct sockaddr*) &servAddr, sizeof (servAddr));
	if (bindStatus < 0){

		cerr << "Error binding socket to address" << endl;
		exit(0);
	}

	cout << "Waiting for a client to connect: ... " << endl;

	//fetch up to 5 requests at a time
	listen(serverSd, 5);

	//create new address to connexct with client
	sockaddr_in newSockAddr;
	socklen_t newSockAddrSize = sizeof(newSockAddr);

	//accept and create new socket descriptor

	int newSD = accept (serverSd, (sockaddr *) &newSockAddr, &newSockAddrSize);
	if (newSD < 0){
		cerr << "Error accepting request from client." << endl;
		exit(1);
	}

	//let user know connection successful 
	cout << "Connected with client." << endl;
	//keeps track of time
	struct timeval start1, end1;
	gettimeofday(&start1, NULL);
	//keeps track of bytes
	int bytesRead, bytesWritten = 0;
	int n = 0;
	int var = 0;
    int count = 0;


	//password
	cout << "Received password" << endl;
    memset(&msg, 0, sizeof(msg));//clear the buffer
    int pass = recv(newSD, (char*)&msg, sizeof(msg), 0);

    if(strcmp(msg, "key")){
        cerr << "Password incorrect" << endl;
        string data = "failed";
        strcpy(msg, data.c_str());
        send(newSD, (char*)&msg, strlen(msg), 0);
        exit(1);
    
    } else{
    	string data = "good";
        strcpy(msg, data.c_str());
        send(newSD, (char*)&msg, strlen(msg), 0);
        cout << "password ok" << endl;


		while(1){

		//listens for message from client
			cout << "Waiting for response from client ~~ " << endl;
			memset(&msg, 0, sizeof(msg));
			bytesRead += recv(newSD, (char*)&msg, sizeof(msg), 0);
			if (!strcmp(msg, "exit")){
				cout << "Client quit the session" << endl;
				break;
			}


			cout << "Client: " << msg << endl;
		

			if (data == "exit") {
				//send to client that connection is closed
				send(newSD,(char*) &msg, strlen(msg), 0);
				break;

			}
 			if(count == 0){

                n = bytesRead;
                count++;
            }
            else{            
                n = bytesRead - var;
            }
            var += bytesRead;


			n = fork();

     	   if(n < 0){
                cout << "Fork failed!" << endl;
                exit(1);
            }

        	if(n == 0){
                cout << "forked child" << endl;
                string output;
                output = exec(msg);
                cout << "command: " << msg << endl;
                cout << "executing command ..." << endl;
				//send the msg
				bytesWritten += send(newSD, (char*) output.c_str(), output.length(), 0);

			}
		}
	}

	gettimeofday(&end1, NULL);
	close(newSD);
	close(serverSd);
	//end of session statistics
	cout << "...End of session..." << endl;
	cout << "Bytes written: " << bytesWritten << endl << "Bytes read: " 
	<< bytesRead << endl << "Elapsed time :" << (end1.tv_sec - start1.tv_sec)
	 << " seconds" << endl;
	cout << "Connection closed.. ";

	return 0;


}










