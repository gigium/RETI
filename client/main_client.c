/*
 * main_client.c
 *
 *  Created on: 18 ott 2016
 *      Author: luigi
 */

#include <stdio.h>
#include<stdlib.h>

#include "libs/server-utls.h"
#define BUFFERSIZE 	512
#define PORT 2323

void HandleServer(int clientSock)
{
	//int bytesRcvd;
//	int totalBytesRcvd = 0;
	char buf[BUFFERSIZE]; // buffer for data from the server
	char string1[50];

	printf("Received: "); // Setup to print the echoed string
	recv(clientSock, buf, BUFFERSIZE, 0);
	printf("%s", buf);
	printf("\n");
	fflush(stdout);


	printf("inserire stringhe : \n");
	int i = 0;
	while(1)
	{
		i = i + 1;
		printf("%d : ", i);
		scanf("%s", &string1);
		send(clientSock, string1, BUFFERSIZE, 0);
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


		if (connect(Mysocket,(struct sockaddr *) &sad, sizeof(sad)) < 0)

		{
			ErrorHandler( "Failed to connect.\n" );

			return 0;
		}

		HandleServer(Mysocket);

		closeSocket(Mysocket);
		return 0;
} // main end

