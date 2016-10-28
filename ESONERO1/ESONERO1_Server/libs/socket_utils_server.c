/*
 * socket_utils.c
 *
 *  Created on: 26 ott 2016
 *      Author: luigi
 */

#include "socket_utils_server.h"


int MySend (int Socket, char* message, int buffersize, int flag)
{
	if (send(Socket, message, buffersize, 0) <= 0)
	{
		printf("error sending data...\n");
		CloseSocket(socket);
		ClearWinSock();
		return -1;
	}return 1;
}


int MyRecieve (int Socket, char* message, int buffersize, int flag)
{
	int bytes_recived = 0;
	if ((bytes_recived = recv(Socket, message, buffersize, 0)) <= 0)
	{
		printf("error receiving data...\n");
		CloseSocket(socket);
		ClearWinSock();
		return -1;
	}
	message[bytes_recived] = '\0';
	return 1;
}


void MyConnect(int socket, struct sockaddr_in* sad)
{
		if (connect(socket, sad, sizeof(*sad)) < 0)
		{
			ErrorHandler(socket, "Failed to connect...\n" );
		}
}


void MainServerLoop(int socket, void(*handleClient)(int))
{
			struct sockaddr_in cad;				 //structure for the client address
			int clientSocket;					//socket descriptor for the client
			int clientLen;					//the size of the client address
			printf( "Waiting for a client to connect...\n");
			fflush(stdout);
			while (1)
			{
				clientLen = sizeof(cad); 			//set the size of the client address
				if ((clientSocket = accept(socket, (struct sockaddr *)&cad, 	&clientLen)) < 0)
				{
					ErrorHandler(socket, "accept() failed.\n");
				}
				// clientSocket is connected to a client
				printf( "connected to ... %s\n", inet_ntoa(cad.sin_addr) );
				handleClient(clientSocket);
				printf( "\nclient %s has disconnected \n", inet_ntoa(cad.sin_addr) );
				printf( "Waiting for a client to connect...");
				fflush(stdout);
			}// end of the while loop
}


void ErrorHandler(int socket , char *errorMessage)
{
	printf(errorMessage);
	CloseSocket(socket);
	ClearWinSock();
	exit(0);
}

void SockAddressInit(struct sockaddr_in *sad,  int  family, char*  address,  int  port_number)
{
	sad->sin_family = family;									//	Converte un numero in notazione puntata in un numero a 32 bit
	sad->sin_addr.s_addr  =  inet_addr( address );				//	Converte un numero dal	formato del computer locale a	quello della rete (Big-Endian)
	sad->sin_port  =  htons( port_number);
}



void ClearWinSock()
{
		#if defined WIN32
		WSACleanup();
		#endif
}




void MyBind(int socket ,  struct sockaddr_in* sad)
{
		if (bind(socket, sad, sizeof(*sad)) <0)
				ErrorHandler(socket, "bind() failed.\n");
}




void setRequestListener(int socket, int queue_len)
{
	if (listen (socket, queue_len) < 0)
			ErrorHandler(socket , "listen() failed.\n");
}




void CloseSocket(int  curr_sock)
{
		#if defined WIN32
				closesocket(curr_sock);
				ClearWinSock();
		#else
				close(curr_sock);
		#endif
}



void WinsockInit()
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

