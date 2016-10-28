/*
 * server-utils.c
 *
 *  Created on: 20 ott 2016
 *      Author: luigi
 */



#include "server-utls.h"

void mainServerLoop(int curr_sock, void(*handleClient)(int))
{
			struct sockaddr_in cad;				 //structure for the client address
			int clientSocket;					//socket descriptor for the client
			int clientLen;					//the size of the client address
			printf( "Waiting for a client to connect...");
			fflush(stdout);
			while (1)
			{
						clientLen = sizeof(cad); 			//set the size of the client address
						if ( (clientSocket = accept(curr_sock, (struct sockaddr *)&cad, 	&clientLen)) < 0)
						{
									ErrorHandler("accept() failed.\n");
									closesocket(curr_sock);
									ClearWinSock();
									exit(0);
						}
						// clientSocket is connected to a client
						printf( "Handling client %s\n", inet_ntoa(cad.sin_addr) );
						handleClient(clientSocket);
			}// end of the while loop
}


void ErrorHandler(char *errorMessage)
{
		printf(errorMessage);
}

void sockAddress(struct sockaddr_in *sad,  int  family, char*  address,  int  port_number)
{
			sad->sin_family = family;															//	Converte un numero in notazione puntata in un numero a 32 bit
			sad->sin_addr.s_addr  =  inet_addr( address );				//	Converte un numero dal	formato del computer locale a	quello della rete (Big-Endian)
			sad->sin_port  =  htons( port_number);
}



void ClearWinSock()
{
		#if defined WIN32
		WSACleanup();
		#endif
}




void binding(int curr_sock ,  struct sockaddr_in* sad)
{
		if (bind(curr_sock, sad, 	sizeof(*sad)) <0)
		{
				ErrorHandler("bind() failed.\n");
				closesocket(curr_sock);
				exit(0);
		}
}




void setRequestListener(int curr_sock, int queue_len)
{

			if (listen (curr_sock, queue_len) < 0)
			{
					ErrorHandler("listen() failed.\n");
					closesocket(curr_sock);
					exit(0);
			}
}




void closeSocket(int  curr_sock)
{
		#if defined WIN32
				closesocket(curr_sock);
				ClearWinSock();
		#else
				close(curr_sock);
		#endif
}




void winsockInit()
{
		#if defined WIN32
				// Initialize Winsock
				WSADATA wsaData;
				int iResult =	WSAStartup(MAKEWORD(2,2),	&wsaData);
				if (iResult != 0)
				{
						printf("Error at WSAStartup()\n");
						exit(0);
				}
		#endif
}




