/*
 * main.c
 *
 *  Created on: 18 ott 2016
 *      Author: luigi
 */


#include <stdio.h>
#include<stdlib.h>

#include "libs/server-utls.h"
#define BUFFERSIZE 512
#define PORT 2323

void HandleTCPClient(int clientSock)
{
	char string1 [50];
	char string2 [60];
	char* welcome_string = "CIAOstronzi";

	send(clientSock, welcome_string, BUFFERSIZE, 0);
	printf("connessione avvenuta");
	fflush(stdout);

	while(1)
	{
		printf("\nReceived: "); // Setup to print the echoed string
		recv(clientSock, string1, BUFFERSIZE, 0);
		printf("%s \n", string1);
		fflush(stdout);
	}

}


int main()
{
		#if defined WIN32
				winsockInit();
		#endif

		int Mysocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (Mysocket < 0)
		{
				ErrorHandler("socket creation failed.\n");
				return 0;
		}

		// Creare un elemento di tipo sockaddr_in : sad
		struct sockaddr_in sad;
		memset(&sad, 0, sizeof(sad)); // ensures that extra bytes contain 0
		sockAddress(&sad,  AF_INET, "127.0.0.1",  PORT);      //avvalora la struct sockaddr_in


		//assegna porta  e ip alla socket e verifica la presenza di eventuali errori
		binding(Mysocket,  &sad);

		//Settare la socket all’ascolto
		setRequestListener(Mysocket ,6);

		/* Main server loop - accept and handle requests */
		mainServerLoop(Mysocket, HandleTCPClient);

		closeSocket(Mysocket);
		return 0;
} // main end

