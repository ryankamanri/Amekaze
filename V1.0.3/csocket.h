#include <stdio.h> 
#include <stdlib.h>
#include <winsock2.h> 
#pragma comment(lib, "ws2_32.lib")
#include <conio.h>
#include "send.h"

void IsWSAStartup(WORD wVersionRequested,WSADATA wsaData,SOCKET server);    //��ѯSOCKET�汾�Ƿ���������
SOCKET CreateSocket(SOCKET server);     //����SOCKET����
struct hostent *GetHostByName(int choosename,struct hostent *pHostent,SOCKET server,char *mailName);//��ȡ�ʼ���������������
void RetConnectTo(int retConnect,SOCKET server,struct sockaddr_in service,char (*Buffer)[1024]);    //�ͻ���ʹ�� connect �������ӵ�SMTP�������������Ự


void IsWSAStartup(WORD wVersionRequested,WSADATA wsaData,SOCKET server)
{
    if(WSAStartup(wVersionRequested, &wsaData) != 0)
	{ //�ú����ĵ�һ������ָ����������ʹ�õ�Socket�汾�����и�λ�ֽ�ָ�����汾����λ�ֽ�ָ�����汾������ϵͳ���õڶ����������������Socket�İ汾��Ϣ��
        printf("\n\nSOCKET�汾����"); 
        WSACleanUp(server);
    }      
}

SOCKET CreateSocket(SOCKET server)
{
    //Create a Socket
	server = socket(AF_INET, SOCK_STREAM, 0);   //��������ļ�������AF_INET;TCP�׽��ֵ�����SOCK_STREAM
    if(server == INVALID_SOCKET)
	{ 
        printf("\n\n�׽��ִ��� %ld ", WSAGetLastError()); 
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
        printf("\n\n����������Ч�ġ� "); 
        WSACleanUp(server);
    }     
	else
	{
		printf("\n������ IP ��ַ �� %s\n",
		inet_ntoa(*((struct in_addr *)pHostent->h_addr))); 
	}
    return pHostent;
}

void RetConnectTo(int retConnect,SOCKET server,struct sockaddr_in service,char (*Buffer)[1024])
{
    // �����ʼ����� ... 
	// �ͻ���ʹ�� connect �������ӵ�SMTP�������������Ự
    retConnect = connect(server, (struct sockaddr*)&service, sizeof(service));
    if(retConnect == SOCKET_ERROR)
	{ 
        printf("\n\n����ʧ�ܡ�"); 
        WSACleanUp(server);
    } 

 	printf("\n\n�ͻ��ˣ����ӵ� %s.... ", inet_ntoa(service.sin_addr));      
 
    //Receive Data From the Mail Server 
    ZeroMemory(*Buffer, sizeof(*Buffer)); 

    retConnect = recv(server, *Buffer, sizeof(*Buffer), 0); 
    if(retConnect == SOCKET_ERROR)
	{
        printf("\n\n����ʧ�ܡ� ");     
        WSACleanUp(server);     
    }
	else
	{
        printf("\n\n�����: %s", *Buffer); 
	}		
}