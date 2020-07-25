#include <iostream>
#include <string>
#include <ctime>
#include <ratio>
#include <chrono>
#include <fstream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
using namespace std::chrono;
using namespace std; 

int main (int argc, char *argv[]) {

	//need ip and port number
	if (argc != 3){
		cerr << "Usage: ip_address port" << endl;
		exit(0);
 	}

 	//get ip and port
 	char *serverIp = argv[1]; 
 	int port = atoi(argv[2]);
 	//message buffer just like server
 	char msg[1500];

 	//setup socket and connection
 	struct hostent* host = gethostbyname(serverIp);
 	sockaddr_in sendSockAddr;
 	bzero((char*) &sendSockAddr, sizeof(sendSockAddr));
 	sendSockAddr.sin_family = AF_INET;
 	sendSockAddr.sin_addr.s_addr= inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
 	sendSockAddr.sin_port = htons(port);
 	int clientSd = socket(AF_INET, SOCK_STREAM, 0);

 	//connect

 	int status = connect(clientSd, (sockaddr*) &sendSockAddr, sizeof(sendSockAddr));

 	if (status < 0) {
 		cout << "Error connecting to socket." << endl; 
 		//break;
 	}
 	cout << "Connection to server successful!" << endl;
 	int bytesRead, bytesWritten = 0;
 	struct timeval start1, end1;
 	gettimeofday(&start1, NULL);

 	

 		cout << "Password: ";
 		string data;
 		getline(cin,data);
 		memset(&msg, 0, sizeof(msg));//clear the buffer
        strcpy(msg, data.c_str());
        int pass = send(clientSd, (char*)&msg, strlen(msg), 0);
    	pass = recv(clientSd, (char*)&msg, sizeof(msg), 0);
    	if(!strcmp(msg, "failed"))
    {
        cout << "password failed" << endl;
        exit(1);
    }
    else
    {
        cout << "password correct." << endl;
		while(1){
			cout << "Enter command: ";
	    	string data;
        	getline(cin, data);
        	memset(&msg, 0, sizeof(msg));
        	strcpy(msg, data.c_str());

        	if(data == "exit")
        	{
         	   send(clientSd, (char*)&msg, strlen(msg), 0);
        	    break;
        	}
        	high_resolution_clock::time_point t1 = high_resolution_clock::now();
        	bytesWritten += send(clientSd, (char*) &msg, strlen(msg), 0);
        	cout << "Awaiting server response..." << endl;
        	memset(&msg, 0, sizeof(msg));
 			bytesRead+=recv(clientSd, (char*)&msg, sizeof(msg), 0);
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
            duration<double> time_span = duration_cast<duration<double> >(t2 - t1);


 			if (!strcmp(msg, "exit")){
 				cout << "Server quit the session" << endl;
 				break;
 			}


 		
 			cout << "Server: " << msg << endl;
 		}
 	}

 	gettimeofday(&end1, NULL);
 	close(clientSd);
 	cout << "...End of session..." << endl;
	cout << "Bytes written: " << bytesWritten << endl << "Bytes read: " 
	<< bytesRead << endl << "Elapsed time :" << (end1.tv_sec - start1.tv_sec)
	 << " seconds" << endl;
	cout << "Connection closed.. ";

	return 0;


 }
