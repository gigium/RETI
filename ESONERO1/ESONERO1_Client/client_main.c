/*
 * client_main.c
 *
 *  Created on: 26 ott 2016
 *      Author: luigi
 */


#include <stdio.h>
#include<stdlib.h>
#include <string.h>

#include "libs/socket_utils_client.h"
#define BUFFERSIZE 	512
#define PORT 5050


void HandleServer(int Socket)
{
	char* quitstring = "QUIT";
	char welcome_message[BUFFERSIZE];
	char number[50];
	char server_message[50];
	MyRecieve(Socket, welcome_message, BUFFERSIZE, 0);
	printf("%s\n",welcome_message);

	while(1)
	{
		printf("write a number : ");
		scanf("%s", number);

		MySend(Socket, number, BUFFERSIZE, 0);

		MyRecieve(Socket, server_message, BUFFERSIZE, 0);
		printf("SERVER : %s\n\n" , server_message);
		fflush(stdout);
		if(strcmp(server_message, quitstring) == 0)
			ErrorHandler(Socket ,"invalid number...exit session\n");

	}
}

int main()
{
		#if defined WIN32
				winsockInit();
		#endif

		int Mysocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (Mysocket < 0)
			ErrorHandler(Mysocket, "socket creation failed.\n");

		struct sockaddr_in sad;

		SockAddressInit(&sad,  AF_INET, "127.0.0.1",  PORT);      //avvalora la struct sockaddr_in

		MyConnect(Mysocket, &sad);

		HandleServer(Mysocket);

		CloseSocket(Mysocket);
		return 0;
} // main end

