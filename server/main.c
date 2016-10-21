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

void HandleTCPClient(int clientSock)
{

	int bytesRcvd;
	int totalBytesRcvd = 0;
	char buf[BUFFERSIZE]; // buffer for data from the server
	char string1 [50];
	char string2 [60];
	char* welcome_string = "";

	send(clientSock, welcome_string, sizeof(welcome_string), 0);
	printf("connessione avvenuta");
	fflush(stdout);

	printf("Received: "); // Setup to print the echoed string
	recv(clientSock, string1, BUFFERSIZE - 1, 0);
	printf("%s", string1);
	recv(clientSock, string2, BUFFERSIZE - 1, 0);
	printf("%s", string2);
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
		sockAddress(&sad,  AF_INET, "127.0.0.1",  4521);      //avvalora la struct sockaddr_in


		//assegna porta  e ip alla socket e verifica la presenza di eventuali errori
		binding(Mysocket,  &sad);

		//Settare la socket all’ascolto
		setRequestListener(Mysocket ,6);

		/* Main server loop - accept and handle requests */
		mainServerLoop(Mysocket, HandleTCPClient);

		closeSocket(Mysocket);
		return 0;
} // main end

