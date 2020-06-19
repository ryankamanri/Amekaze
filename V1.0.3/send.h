#include <stdio.h> 
#include <stdlib.h>
#include <winsock2.h> 
#pragma comment(lib, "ws2_32.lib")
#include <conio.h>

void Send1024(int retConnect,SOCKET server,struct sockaddr_in service,char (*Buffer)[1024],char (*Buffer2)[5000],char testbuf[],const char *str);
void Send5000(int retConnect,SOCKET server,struct sockaddr_in service,char (*Buffer)[1024],char (*Buffer2)[5000],char testbuf[],const char *str);
void SendHELO(int retConnect,SOCKET server,struct sockaddr_in service,char (*Buffer)[1024]);//�ͻ��˷���һ�� HELO �� EHLO ����
void SendAUTH(int retConnect,SOCKET server,struct sockaddr_in service,char (*Buffer)[1024]);// �ͻ��˷���һ�� AUTH ��֤��������û���¼��ʹ�� smtpd ��ʽ��
void SendUserName(int retConnect,SOCKET server,struct sockaddr_in service,char (*Buffer)[1024],char testbuf[]);//���û������͵��ʼ����������û�����Base64���롣
void SendPass(int retConnect,SOCKET server,struct sockaddr_in service,char (*Buffer)[1024],char testbuf[],int *iserror);//�����뷢�͵��ʼ�������.������Base64���롣
void SendMAIL(int retConnect,char tmpuser[],SOCKET server,char user[],char mailName[],char (*Buffer)[1024],char _end[]);//�ͻ��˷���һ�� MAIL ����ָ��������
void SendRCPT(int retConnect,char tmpto[],SOCKET server,char send_to[],char _end[],char (*Buffer)[1024]);//���� RCPT TO�����ļ����͵��ʼ����������ռ��˵��ʼ���ַ
void SendDATA(int retconnect,SOCKET server,char (*Buffer)[1024]);//���ʼ���������������
void SendQUIT(int retConnect,SOCKET server);    //�����ʼ�QUIT����
int WSACleanUp(SOCKET server);     //�˳�SOCKET����


void Send1024(int retConnect,SOCKET server,struct sockaddr_in service,char (*Buffer)[1024],char (*Buffer2)[5000],char testbuf[],const char *str)
{
    retConnect = send(server,testbuf,strlen(testbuf),0);
	if(retConnect == SOCKET_ERROR)
	{ 
		printf("\n\n�� %s ���͵��ʼ�ʧ�ܡ� ",str); 
		WSACleanUp(server);
	}
	else
	{
		printf("\n\n���� %s �ɹ���",str);
	}
			
	ZeroMemory(*Buffer, sizeof(*Buffer));
	retConnect = recv(server,*Buffer,1000,0);
	if(retConnect == SOCKET_ERROR)
	{ 
		printf("\n\n���ʼ���������������ʧ�ܡ� "); 
		WSACleanUp(server);
	}
	else
	{
		(*Buffer)[retConnect] = ' ';
		printf("\n\n%s", *Buffer);
	}
}

void Send5000(int retConnect,SOCKET server,struct sockaddr_in service,char (*Buffer)[1024],char (*Buffer2)[5000],char testbuf[],const char *str)
{
    retConnect = send(server,testbuf,strlen(testbuf),0);
	if(retConnect == SOCKET_ERROR)
	{ 
		printf("\n\n�� %s ���͵��ʼ�ʧ�ܡ� ",str); 
		WSACleanUp(server);
	}
	else
	{
		printf("\n\n���� %s �ɹ���",str);
	}
			
	ZeroMemory(*Buffer2, sizeof(*Buffer2));
	retConnect = recv(server,*Buffer2,1000,0);
	if(retConnect == SOCKET_ERROR)
	{ 
		printf("\n\n���ʼ���������������ʧ�ܡ� "); 
		WSACleanUp(server);
	}
	else
	{
		(*Buffer)[retConnect] = ' ';
		printf("\n\n%s", *Buffer2);
	}
}




void SendHELO(int retConnect,SOCKET server,struct sockaddr_in service,char (*Buffer)[1024])
{
    	//�ͻ��˷���һ�� HELO �� EHLO ����
	//////////////////////////////////////////////////////////////////////////
	//Send HELO
    //Send "HELO Server.... " to the Mail Server 

	retConnect = send(server, "HELO Server\r\n", strlen("HELO Server\r\n"), 0);

    if(retConnect == SOCKET_ERROR)
	{ 
        printf("\n\n����HELO���ʼ�ʧ�ܡ� "); 
        WSACleanUp(server);  
    }
	else
	{
       printf("\n\n�ͻ��ˣ�HELO������... ");    
    }       

    //Receive Data From the Mail Server 
    ZeroMemory(*Buffer, sizeof(*Buffer)); 

    retConnect = recv(server, *Buffer, sizeof(*Buffer), 0); 
    if(retConnect == SOCKET_ERROR)
	{ 
        printf("\n\n����ʧ�ܡ�");     
        WSACleanUp(server);        
    }
	else
	{ 
        printf("\n\n�����: %s", *Buffer); 
    } 
}

void SendAUTH(int retConnect,SOCKET server,struct sockaddr_in service,char (*Buffer)[1024])
{
    // �ͻ��˷���һ�� AUTH ��֤��������û���¼��ʹ�� smtpd ��ʽ��
	////////////////////////////////////////////////////////////////////////
	// Send AUTH 
    // Send "AUTH LOGIN " to the Mail Server 
    
    retConnect = send(server, "AUTH LOGIN\r\n", strlen("AUTH LOGIN\r\n"), 0); 
    if(retConnect == SOCKET_ERROR)
	{ 
        printf("\n\n���͡� �����֤��¼ �����ʼ�ʧ�ܡ� "); 
        WSACleanUp(server);
    }
	else
	{ 
        printf("\n\n�ͻ���: �����֤��¼ "); 
    }   


    //Receive Data From the Mail Server 
    ZeroMemory(*Buffer, sizeof(*Buffer)); 

    retConnect = recv(server, *Buffer, sizeof(*Buffer), 0); 
    if(retConnect == SOCKET_ERROR)
	{ 
        printf("\n\n���ʼ���������������ʧ�ܡ� ");   
		WSACleanUp(server); 
    }
	else
	{  
        printf("\n\n�����: %s", *Buffer); 
    }   
}

void SendUserName(int retConnect,SOCKET server,struct sockaddr_in service,char (*Buffer)[1024],char testbuf[])
{
    //////////////////////////////////////////////////////////////////////////
	//Send UserName

    //Send UserName to the Mail Server. The UserName is Encoded by Base64.
	

	retConnect = send(server, testbuf, strlen(testbuf), 0);

    if(retConnect == SOCKET_ERROR)
	{ 
        printf("\n\n���û������͵��ʼ�ʧ�ܡ� "); 
        WSACleanUp(server); 
    }
	else
	{ 
        printf("\n\n�ͻ���: �����û��� ");  
    }   

    //Receive Data From the Mail Server 
    ZeroMemory(*Buffer, sizeof(*Buffer)); 

    retConnect = recv(server, *Buffer, sizeof(*Buffer), 0); 

    if(retConnect == SOCKET_ERROR){ 

        printf("\n\n���ʼ���������������ʧ�ܡ� ");    
        WSACleanUp(server);   
    }
	else
	{
        printf("\n\n�����: %s", *Buffer); 
    } 
}

void  SendPass(int retConnect,SOCKET server,struct sockaddr_in service,char (*Buffer)[1024],char testbuf[],int *iserror)
{
    //////////////////////////////////////////////////////////////////////////
	//Send Password  

    //Send Password to the Mail Server The Password is Encoded by Base64. 
	

	retConnect = send(server, testbuf, strlen(testbuf), 0);

    if(retConnect == SOCKET_ERROR)
	{ 
        printf("\n\n�����뷢�͵��ʼ�ʧ�ܡ� "); 
        WSACleanUp(server);  
    }
	else
	{ 
        printf("\n\n�ͻ���:��������");  
    }      

    //Receive Data From the Mail Server 

    ZeroMemory(*Buffer, sizeof(*Buffer)); 

    retConnect = recv(server, *Buffer, sizeof(*Buffer), 0); 

    if(retConnect == SOCKET_ERROR)
	{ 
        printf("\n\n���ʼ���������������ʧ�ܡ� "); 
        // WSACleanUp(server);   
        *iserror = 1; 
    }
	else
	{
        printf("\n\n�����: %s", *Buffer); 

		if (((*Buffer)[0] !='2' || (*Buffer)[1] !='3' || (*Buffer)[2] !='5')&&((*Buffer)[0] !='+' || (*Buffer)[1] !='O' || (*Buffer)[2] !='K'))
		{
			printf("\n\n������������µ�¼��");
			// WSACleanUp(server); 
            *iserror = 1;
		}
    }
}

void SendMAIL(int retConnect,char tmpuser[],SOCKET server,char user[],char mailName[],char (*Buffer)[1024],char _end[])
{
    //�ͻ��˷���һ�� MAIL ����ָ��������
	memset(tmpuser, 0, 200), memset(_end,0,10);	
	strcpy(tmpuser, "MAIL FROM:<"),  strcpy(_end,"\r\n");
	strcat(tmpuser,user);		
	strcat(tmpuser,mailName);
	strcat(strcat(tmpuser,">"),_end);
	
	retConnect = send(server, tmpuser, strlen(tmpuser), 0);
    if(retConnect == SOCKET_ERROR)
	{ 
        printf("\n\n�����ʼ������ˣ������͵��ʼ�ʧ�ܡ�"); 
        WSACleanUp(server); 
    }
	else
	{ 
        printf("\n\n�ͻ���: �ʼ������ˣ� <%s%s>",user, mailName);  //������ 
    }   
    
    //Receive Data From the Mail Server 
    ZeroMemory(*Buffer, sizeof(*Buffer)); 
    retConnect = recv(server, *Buffer, sizeof(*Buffer), 0); 
    if(retConnect == SOCKET_ERROR)
	{ 
        printf("\n\n���ʼ���������������ʧ�ܡ� ");   
        WSACleanUp(server);     
    }
	else
	{ 
        (*Buffer)[retConnect] = ' '; 
        printf("\n\n�����: %s ", *Buffer); 
    } 
}

void SendRCPT(int retConnect,char tmpto[],SOCKET server,char send_to[],char _end[],char (*Buffer)[1024])
{

    printf("\n�ռ���:");	
	memset(tmpto, 0, 200),memset(send_to,0,200);
	scanf("%s",send_to);
	strcpy(tmpto, "RCPT TO:<");
	strcat(tmpto,send_to);
	strcat(tmpto,">");
	strcat(tmpto,_end);	
    //Send "RCPT TO: " File to the Mail Server, receiver ''s Mail Address 
    retConnect = send(server, tmpto, strlen(tmpto), 0); 

    if(retConnect == SOCKET_ERROR)
	{ 
        printf("\n\n�����ռ���:�����͵��ʼ�ʧ�ܡ� "); 
        WSACleanUp(server);
    }
	else
	{
        printf("\n\n�ͻ���:�ռ���: %s", tmpto);    
    }        

    //Receive Data From the Mail Server 
    ZeroMemory(*Buffer, sizeof(*Buffer)); 
    retConnect = recv(server, *Buffer, sizeof(*Buffer), 0); 
    if(retConnect == SOCKET_ERROR)
	{
        printf("\n\n���ʼ���������������ʧ�ܡ� ");     
        WSACleanUp(server);
    
    }
	else
	{ 
        printf("\n\n�����: %s ", *Buffer); 
    }  
}

void SendDATA(int retConnect,SOCKET server,char (*Buffer)[1024])
{
    retConnect = send(server, "Data\r\n", strlen("Data\r\n"), 0); 

    if(retConnect == SOCKET_ERROR)
	{ 
        printf("\n\n�������ݡ��ֶη��͵��ʼ�ʧ�ܡ� "); 
        WSACleanUp(server); 
    }
	else
	{ 
        printf("\n\n�ͻ���: �������ݡ��ֶη��͵��ʼ���������");  
    }  

    //Receive Data From the Mail Server 
    ZeroMemory(*Buffer, sizeof(*Buffer)); 
    retConnect = recv(server, *Buffer, sizeof(*Buffer), 0); 

    if(retConnect == SOCKET_ERROR)
	{ 
        printf("\n\n���ʼ���������������ʧ��.");   
        WSACleanUp(server);
        
    }
	else
	{
        printf("\n\n�����: %s ", *Buffer); 
    } 
}

void SendQUIT(int retConnect,SOCKET server)
{
    retConnect = send(server, "QUIT ", strlen("QUIT "), 0); 

    if(retConnect == SOCKET_ERROR){ 

        printf("\n\n�����˳������͵��ʼ�ʧ��. "); 

        WSACleanUp(server);

    }
	else
	{ 
        printf("\n\n�ͻ���:�ѷ����ʼ�,�����˳���");    
    }       

    printf("\n\n�����ʼ��ɹ��� "); 
	
	
}

int WSACleanUp(SOCKET server)
{
    {
        if(server != INVALID_SOCKET)
		{
            closesocket(server);
        } 
        WSACleanup();   
    }
	system("pause");
    exit(-1);
	return -1;
}