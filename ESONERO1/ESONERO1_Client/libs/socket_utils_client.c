/*
 * socket_utils.c
 *
 *  Created on: 26 ott 2016
 *      Author: luigi
 */

#include "socket_utils_client.h"


void MySend (int Socket, char* message, int buffersize, int flag)
{
	if (send(Socket, message, buffersize, 0) <= 0 )
	{
		ErrorHandler(Socket, "error sending data ...");
	}
}


void MyRecieve (int Socket, char* message, int buffersize, int flag)
{
	int bytes_recived = 0;
	if ((bytes_recived = recv(Socket, message, buffersize, 0)) <= 0)
	{
		ErrorHandler(Socket, "error reciving data ...");
	}
	message[bytes_recived] = '\0';
}


void MyConnect(int socket, struct sockaddr_in* sad)
{
		if (connect(socket, sad, sizeof(*sad)) < 0)
		{
			ErrorHandler(socket, "Failed to connect.\n" );
		}
}




void ErrorHandler(int socket , char *errorMessage)
{
	printf(errorMessage);
	closesocket(socket);
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

