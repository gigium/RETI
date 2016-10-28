/*
 * socket_utils.h
 *
 *  Created on: 26 ott 2016
 *      Author: luigi
 */

#ifndef SOCKET_UTILS_H_
#define SOCKET_UTILS_H_

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
#include <string.h>

int MyRecieve (int, char* ,int ,int );
int MySend (int, char* , int , int );
void MainServerLoop(int , void(*)(int));
void MyConnect(int, struct sockaddr_in*);
void ErrorHandler(int, char*);
void SockAddressInit(struct sockaddr_in*,  int  , char*  ,int);
void ClearWinSock();
void MyBind(int, struct sockaddr_in* );
void setRequestListener(int , int );
void CloseSocket(int);
void WinsockInit();

#endif /* SOCKET_UTILS_H_ */
