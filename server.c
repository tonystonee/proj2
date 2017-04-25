#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "packet.c";


int main (int argc, char*argv[]){
  struct sockaddr_in client_ip, host_ip;
  char buffer[1024], str[1024];;
  struct sockaddr_storage mem;
  socklen_t memSize, client_length;
  int sock, n, port, file_size, packet_amount, i;
struct packet p;
  FILE *fp;
 if(argc < 1){
	printf("enter port number \n");
   return -1;
 }

port = atoi(argv[1]);

//start up memory size
  memSize = sizeof mem;

	
	p.number = 0;
	//open a socket for data
  sock = socket(PF_INET, SOCK_DGRAM, 0);

	//set up the server addres
  host_ip.sin_family = AF_INET;
  host_ip.sin_addr.s_addr = inet_addr("127.0.0.1");
  host_ip.sin_port = htons(port);
  memset(host_ip.sin_zero, '\0', sizeof host_ip.sin_zero);  

printf("SERVER STARTED \n");

  bind(sock, (struct sockaddr *) &host_ip, sizeof(host_ip));

  while(1){

    n = recvfrom(sock,buffer,1024,0,(struct sockaddr *)&mem, &memSize);

	//file exists
	if( access( buffer, F_OK ) != -1 ) {
		//get file size
		fp = fopen(buffer, "r");
		fseek(fp, 0L, SEEK_END);
		file_size = ftell(fp);
		fseek(fp, 0L, SEEK_SET);
		rewind(fp);
		char fileArray[file_size];
		int count;
		for(count = 0; count < file_size; count++)
		{
			fscanf(fp, "%s", &fileArray[count]);
		}

		if (file_size% 1024)
		{
			packet_amount = file_size/1024;
		}
		else
		{
			packet_amount = file_size/1024 + 1;
		}
		int i ;

		for(i = 0; i < packet_amount; i++)
		{
	               memset(&p, 0, sizeof (p));
			p.number = htonl(i);

			memcpy(p.data, (fileArray + i*1024), 1024);

			sendto(sock, &p, 1024, 0, /* send packet */
		       (struct sockaddr *) &mem, memSize);
		}
	

	} 
  }

  return 0;
}
