/*
CSE 422 Project 2
By: 
Anthony Dionise
Big Mike Hanlon

Reciever Code
UDP
*/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "packet.c"

int main(int argc, char*argv[]){
//init variables	
  char* hostname;
  struct sockaddr_in server_ip_address;
  int sock, port, n;
  const char* filename;
  char buffer[1024];
  socklen_t address_length;

	if(argc < 3) {
		printf("Please enter hostname, port, and filename: \n");
		return -1; 
	}

	//declare variables
	hostname = argv[1];
	port = atoi(argv[2]);
	filename = argv[3];

//initiailize server setttings
  server_ip_address.sin_family = AF_INET;
 server_ip_address.sin_addr.s_addr = inet_addr(hostname);
  server_ip_address.sin_port = htons(port);
  memset(server_ip_address.sin_zero, '\0', sizeof server_ip_address.sin_zero);  
  address_length = sizeof server_ip_address;
 	
//open a new socket for communication
  sock = socket(PF_INET, SOCK_DGRAM, 0);

  //while(1){
    n = strlen(filename) + 1;

    sendto(sock,filename,n,0,(struct sockaddr *)&server_ip_address,address_length);

                n = recvfrom(sock,buffer,1024,0,NULL, NULL);

    printf("Received from server: %s\n",buffer);

  //}

  return 0;
}
