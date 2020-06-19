#include <stdio.h> 
#include <stdlib.h>
#include <winsock2.h> 
#pragma comment(lib, "ws2_32.lib")
#include <conio.h>
#include "send.h"

void IsWSAStartup(WORD wVersionRequested,WSADATA wsaData,SOCKET server);    //查询SOCKET版本是否满足需求
SOCKET CreateSocket(SOCKET server);     //创建SOCKET服务
struct hostent *GetHostByName(int choosename,struct hostent *pHostent,SOCKET server,char *mailName);//获取邮件服务器的主机名
void RetConnectTo(int retConnect,SOCKET server,struct sockaddr_in service,char (*Buffer)[1024]);    //客户端使用 connect 命令连接到SMTP服务器，建立会话


void IsWSAStartup(WORD wVersionRequested,WSADATA wsaData,SOCKET server)
{
    if(WSAStartup(wVersionRequested, &wsaData) != 0)
	{ //该函数的第一个参数指明程序请求使用的Socket版本，其中高位字节指明副版本、低位字节指明主版本；操作系统利用第二个参数返回请求的Socket的版本信息。
        printf("\n\nSOCKET版本错误"); 
        WSACleanUp(server);
    }      
}

SOCKET CreateSocket(SOCKET server)
{
    //Create a Socket
	server = socket(AF_INET, SOCK_STREAM, 0);   //面向网络的家族名：AF_INET;TCP套接字的名字SOCK_STREAM
    if(server == INVALID_SOCKET)
	{ 
        printf("\n\n套接字错误： %ld ", WSAGetLastError()); 
        WSACleanUp(server);
    }   
    return server;
}

struct hostent *GetHostByName(int choosename,struct hostent *pHostent,SOCKET server,char *mailName)
{
    if(choosename == 1)
    {
        pHostent = gethostbyname("smtp.163.com");
        strcpy(mailName,"@163.com");
    }
      else if(choosename == 2)
    {
        pHostent = gethostbyname("smtp.sohu.com"); 
        strcpy(mailName,"@sohu.com");
    }
    else if(choosename == 3)
    {
        pHostent = gethostbyname("smtp.126.com"); 
        strcpy(mailName,"@126.com");
    }
    else if(choosename == 4)
    {
        pHostent = gethostbyname("smtp.qq.com"); 
        strcpy(mailName,"@qq.com");
    }
 
	
    if(pHostent == NULL)
	{ 
        printf("\n\n主机名是无效的… "); 
        WSACleanUp(server);
    }     
	else
	{
		printf("\n服务器 IP 地址 ： %s\n",
		inet_ntoa(*((struct in_addr *)pHostent->h_addr))); 
	}
    return pHostent;
}

void RetConnectTo(int retConnect,SOCKET server,struct sockaddr_in service,char (*Buffer)[1024])
{
    // 发送邮件步骤 ... 
	// 客户端使用 connect 命令连接到SMTP服务器，建立会话
    retConnect = connect(server, (struct sockaddr*)&service, sizeof(service));
    if(retConnect == SOCKET_ERROR)
	{ 
        printf("\n\n连接失败。"); 
        WSACleanUp(server);
    } 

 	printf("\n\n客户端：连接到 %s.... ", inet_ntoa(service.sin_addr));      
 
    //Receive Data From the Mail Server 
    ZeroMemory(*Buffer, sizeof(*Buffer)); 

    retConnect = recv(server, *Buffer, sizeof(*Buffer), 0); 
    if(retConnect == SOCKET_ERROR)
	{
        printf("\n\n连接失败。 ");     
        WSACleanUp(server);     
    }
	else
	{
        printf("\n\n服务端: %s", *Buffer); 
	}		
}