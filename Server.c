//Server.c

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main(int argc, char** argv) {
	
	int socketfd, newsocketfd, portno, n;
	char buffer[1024];
	struct sockaddr_in serv_addr, cli_addr;
	socklen_t addr_size;
	
	//Create a socket
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if(socketfd<0)
	{
	    perror("Error opening socket");
	}
	    
	// Initialize the socket structure
	bzero((char *)&serv_addr, sizeof(serv_addr)); //set all bits of serv_addr to 0
	portno = 5001;  //  should we assign the port no. or not needed ??
	serv_addr.sin_family = AF_INET; ///server byte order
	serv_addr.sin_addr.s_addr = INADDR_ANY; //fill with the current host's IP address 
	serv_addr.sin_port = htons(portno); //convert port integer value into the network byte order
	
	//bind the host address using the bind() call 
	if(bind(socketfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
	    perror("Error on Binding");
	}
	
	//Listen to the clients
	if(listen (socketfd, 5) <0)// listening to the socket with 5 conenctions
	{
	     perror("Error on Listening");
	}
	
	addr_size = sizeof(cli_addr);
	
	//Accept the connection from the client and creates a new socket for the client
	newsocketfd = accept(socketfd, (struct sockaddr*)&cli_addr, &addr_size);
	
	if(newsocketfd <0)
	{
	    perror("Error on Accept");
	}
	
	//If connection is successful, then start communicating
	bzero(buffer, 256);
	
	n = read(socketfd, buffer, 256);
	
	if(n <0)
	{
	    perror("Error reading from the socket");
	}
	
	printf("Here is the message : %s \n", buffer);
	
	//Write a response to the client 
	n = write (newsocketfd, "Hello!", 18); //why 18 ??
	if(n < 0)
	{
	    perror("Error writing to a client");
	}
	
	return 0;
}
