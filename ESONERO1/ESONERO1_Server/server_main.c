/*
 * server_main.c
 *
 *  Created on: 27 ott 2016
 *      Author: luigi
 */



#include <stdio.h>
#include<stdlib.h>

#include "libs/socket_utils_server.h"
#define BUFFERSIZE 512
#define PORT 5050

int IsNumber(char* string)
{
	int i;
	for(i=0; i < strlen(string); i++)
	{
		if(string[i] < 48 || string[i] > 57)
		{
			return -1;
		}
	}
	return 0;
}


void HandleTCPClient(int Socket)
{
	char* welcome_message = "successful connection";
	char* quitstring = "QUIT";
	char* continuestring = "CONTINUE";
	char number [BUFFERSIZE];
	int int_number = 0;
	if(MySend(Socket, welcome_message, BUFFERSIZE, 0)==-1)
		return;

	while(1)
	{
		if(MyRecieve(Socket, number, BUFFERSIZE, 0)==-1)
			return;

		if(IsNumber(number) == -1)
		{
			if(MySend(Socket, quitstring, BUFFERSIZE, 0)==-1)
				return;
			printf("lost connection... \n");
			return;
		}
		int_number = atoi(number);
		printf("CLIENT : %d\n", int_number);
		fflush(stdout);
		if(int_number > 100)
		{
			if(MySend(Socket, quitstring, BUFFERSIZE, 0)==-1)
				return;
			return;
		}
		else
			if(MySend(Socket, continuestring, BUFFERSIZE, 0)==-1)
				return;
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

		//memset(&sad, 0, sizeof(sad)); // ensures that extra bytes contain 0
		SockAddressInit(&sad,  AF_INET, "127.0.0.1",  PORT);      //avvalora la struct sockaddr_in

		MyBind(Mysocket,  &sad);

		setRequestListener(Mysocket ,6);

		MainServerLoop(Mysocket, HandleTCPClient);

		CloseSocket(Mysocket);
		return 0;
} // main end
