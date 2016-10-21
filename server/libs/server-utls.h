/*
 * server-utls.h
 *
 *  Created on: 20 ott 2016
 *      Author: luigi
 */

#ifndef SERVER_UTLS_H_
#define SERVER_UTLS_H_
#if defined WIN32
		#include <winsock.h>
#else
		#define closesocket close
		#include <sys/socket.h>
		#include <arpa/inet.h>
		#include <unistd.h>
#endif
#include <stdio.h>
#include<stdlib.h>

void mainServerLoop(int , void(*)(int));
void ErrorHandler(char*);
void sockAddress(struct sockaddr_in*,  int  , char*  ,  int  );
void ClearWinSock();
void binding(int  ,  struct sockaddr_in* );
void setRequestListener(int , int );
void closeSocket(int );
void winsockInit();



#endif /* SERVER_UTLS_H_ */
