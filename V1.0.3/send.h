#include <stdio.h> 
#include <stdlib.h>
#include <winsock2.h> 
#pragma comment(lib, "ws2_32.lib")
#include <conio.h>

void Send1024(int retConnect,SOCKET server,struct sockaddr_in service,char (*Buffer)[1024],char (*Buffer2)[5000],char testbuf[],const char *str);
void Send5000(int retConnect,SOCKET server,struct sockaddr_in service,char (*Buffer)[1024],char (*Buffer2)[5000],char testbuf[],const char *str);
void SendHELO(int retConnect,SOCKET server,struct sockaddr_in service,char (*Buffer)[1024]);//客户端发送一个 HELO 或 EHLO 命令
void SendAUTH(int retConnect,SOCKET server,struct sockaddr_in service,char (*Buffer)[1024]);// 客户端发送一个 AUTH 认证命令进行用户登录（使用 smtpd 方式）
void SendUserName(int retConnect,SOCKET server,struct sockaddr_in service,char (*Buffer)[1024],char testbuf[]);//将用户名发送到邮件服务器。用户名由Base64编码。
void SendPass(int retConnect,SOCKET server,struct sockaddr_in service,char (*Buffer)[1024],char testbuf[],int *iserror);//将密码发送到邮件服务器.密码由Base64编码。
void SendMAIL(int retConnect,char tmpuser[],SOCKET server,char user[],char mailName[],char (*Buffer)[1024],char _end[]);//客户端发送一个 MAIL 命令指定发件人
void SendRCPT(int retConnect,char tmpto[],SOCKET server,char send_to[],char _end[],char (*Buffer)[1024]);//将“ RCPT TO：”文件发送到邮件服务器，收件人的邮件地址
void SendDATA(int retconnect,SOCKET server,char (*Buffer)[1024]);//从邮件服务器接收数据
void SendQUIT(int retConnect,SOCKET server);    //发送邮件QUIT命令
int WSACleanUp(SOCKET server);     //退出SOCKET服务


void Send1024(int retConnect,SOCKET server,struct sockaddr_in service,char (*Buffer)[1024],char (*Buffer2)[5000],char testbuf[],const char *str)
{
    retConnect = send(server,testbuf,strlen(testbuf),0);
	if(retConnect == SOCKET_ERROR)
	{ 
		printf("\n\n将 %s 发送到邮件失败。 ",str); 
		WSACleanUp(server);
	}
	else
	{
		printf("\n\n发送 %s 成功！",str);
	}
			
	ZeroMemory(*Buffer, sizeof(*Buffer));
	retConnect = recv(server,*Buffer,1000,0);
	if(retConnect == SOCKET_ERROR)
	{ 
		printf("\n\n从邮件服务器接收数据失败。 "); 
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
		printf("\n\n将 %s 发送到邮件失败。 ",str); 
		WSACleanUp(server);
	}
	else
	{
		printf("\n\n发送 %s 成功！",str);
	}
			
	ZeroMemory(*Buffer2, sizeof(*Buffer2));
	retConnect = recv(server,*Buffer2,1000,0);
	if(retConnect == SOCKET_ERROR)
	{ 
		printf("\n\n从邮件服务器接收数据失败。 "); 
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
    	//客户端发送一个 HELO 或 EHLO 命令
	//////////////////////////////////////////////////////////////////////////
	//Send HELO
    //Send "HELO Server.... " to the Mail Server 

	retConnect = send(server, "HELO Server\r\n", strlen("HELO Server\r\n"), 0);

    if(retConnect == SOCKET_ERROR)
	{ 
        printf("\n\n发送HELO到邮件失败。 "); 
        WSACleanUp(server);  
    }
	else
	{
       printf("\n\n客户端：HELO服务器... ");    
    }       

    //Receive Data From the Mail Server 
    ZeroMemory(*Buffer, sizeof(*Buffer)); 

    retConnect = recv(server, *Buffer, sizeof(*Buffer), 0); 
    if(retConnect == SOCKET_ERROR)
	{ 
        printf("\n\n连接失败。");     
        WSACleanUp(server);        
    }
	else
	{ 
        printf("\n\n服务端: %s", *Buffer); 
    } 
}

void SendAUTH(int retConnect,SOCKET server,struct sockaddr_in service,char (*Buffer)[1024])
{
    // 客户端发送一个 AUTH 认证命令进行用户登录（使用 smtpd 方式）
	////////////////////////////////////////////////////////////////////////
	// Send AUTH 
    // Send "AUTH LOGIN " to the Mail Server 
    
    retConnect = send(server, "AUTH LOGIN\r\n", strlen("AUTH LOGIN\r\n"), 0); 
    if(retConnect == SOCKET_ERROR)
	{ 
        printf("\n\n发送“ 身份验证登录 ”到邮件失败。 "); 
        WSACleanUp(server);
    }
	else
	{ 
        printf("\n\n客户端: 身份验证登录 "); 
    }   


    //Receive Data From the Mail Server 
    ZeroMemory(*Buffer, sizeof(*Buffer)); 

    retConnect = recv(server, *Buffer, sizeof(*Buffer), 0); 
    if(retConnect == SOCKET_ERROR)
	{ 
        printf("\n\n从邮件服务器接收数据失败。 ");   
		WSACleanUp(server); 
    }
	else
	{  
        printf("\n\n服务端: %s", *Buffer); 
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
        printf("\n\n将用户名发送到邮件失败。 "); 
        WSACleanUp(server); 
    }
	else
	{ 
        printf("\n\n客户端: 发送用户名 ");  
    }   

    //Receive Data From the Mail Server 
    ZeroMemory(*Buffer, sizeof(*Buffer)); 

    retConnect = recv(server, *Buffer, sizeof(*Buffer), 0); 

    if(retConnect == SOCKET_ERROR){ 

        printf("\n\n从邮件服务器接收数据失败。 ");    
        WSACleanUp(server);   
    }
	else
	{
        printf("\n\n服务端: %s", *Buffer); 
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
        printf("\n\n将密码发送到邮件失败。 "); 
        WSACleanUp(server);  
    }
	else
	{ 
        printf("\n\n客户端:发送密码");  
    }      

    //Receive Data From the Mail Server 

    ZeroMemory(*Buffer, sizeof(*Buffer)); 

    retConnect = recv(server, *Buffer, sizeof(*Buffer), 0); 

    if(retConnect == SOCKET_ERROR)
	{ 
        printf("\n\n从邮件服务器接收数据失败。 "); 
        // WSACleanUp(server);   
        *iserror = 1; 
    }
	else
	{
        printf("\n\n服务端: %s", *Buffer); 

		if (((*Buffer)[0] !='2' || (*Buffer)[1] !='3' || (*Buffer)[2] !='5')&&((*Buffer)[0] !='+' || (*Buffer)[1] !='O' || (*Buffer)[2] !='K'))
		{
			printf("\n\n密码错误！请重新登录！");
			// WSACleanUp(server); 
            *iserror = 1;
		}
    }
}

void SendMAIL(int retConnect,char tmpuser[],SOCKET server,char user[],char mailName[],char (*Buffer)[1024],char _end[])
{
    //客户端发送一个 MAIL 命令指定发件人
	memset(tmpuser, 0, 200), memset(_end,0,10);	
	strcpy(tmpuser, "MAIL FROM:<"),  strcpy(_end,"\r\n");
	strcat(tmpuser,user);		
	strcat(tmpuser,mailName);
	strcat(strcat(tmpuser,">"),_end);
	
	retConnect = send(server, tmpuser, strlen(tmpuser), 0);
    if(retConnect == SOCKET_ERROR)
	{ 
        printf("\n\n将“邮件发件人：”发送到邮件失败。"); 
        WSACleanUp(server); 
    }
	else
	{ 
        printf("\n\n客户端: 邮件发件人： <%s%s>",user, mailName);  //发送者 
    }   
    
    //Receive Data From the Mail Server 
    ZeroMemory(*Buffer, sizeof(*Buffer)); 
    retConnect = recv(server, *Buffer, sizeof(*Buffer), 0); 
    if(retConnect == SOCKET_ERROR)
	{ 
        printf("\n\n从邮件服务器接收数据失败。 ");   
        WSACleanUp(server);     
    }
	else
	{ 
        (*Buffer)[retConnect] = ' '; 
        printf("\n\n服务端: %s ", *Buffer); 
    } 
}

void SendRCPT(int retConnect,char tmpto[],SOCKET server,char send_to[],char _end[],char (*Buffer)[1024])
{

    printf("\n收件人:");	
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
        printf("\n\n将“收件人:”发送到邮件失败。 "); 
        WSACleanUp(server);
    }
	else
	{
        printf("\n\n客户端:收件人: %s", tmpto);    
    }        

    //Receive Data From the Mail Server 
    ZeroMemory(*Buffer, sizeof(*Buffer)); 
    retConnect = recv(server, *Buffer, sizeof(*Buffer), 0); 
    if(retConnect == SOCKET_ERROR)
	{
        printf("\n\n从邮件服务器接收数据失败。 ");     
        WSACleanUp(server);
    
    }
	else
	{ 
        printf("\n\n服务端: %s ", *Buffer); 
    }  
}

void SendDATA(int retConnect,SOCKET server,char (*Buffer)[1024])
{
    retConnect = send(server, "Data\r\n", strlen("Data\r\n"), 0); 

    if(retConnect == SOCKET_ERROR)
	{ 
        printf("\n\n将“数据”字段发送到邮件失败。 "); 
        WSACleanUp(server); 
    }
	else
	{ 
        printf("\n\n客户端: 将“数据”字段发送到邮件服务器。");  
    }  

    //Receive Data From the Mail Server 
    ZeroMemory(*Buffer, sizeof(*Buffer)); 
    retConnect = recv(server, *Buffer, sizeof(*Buffer), 0); 

    if(retConnect == SOCKET_ERROR)
	{ 
        printf("\n\n从邮件服务器接收数据失败.");   
        WSACleanUp(server);
        
    }
	else
	{
        printf("\n\n服务端: %s ", *Buffer); 
    } 
}

void SendQUIT(int retConnect,SOCKET server)
{
    retConnect = send(server, "QUIT ", strlen("QUIT "), 0); 

    if(retConnect == SOCKET_ERROR){ 

        printf("\n\n将“退出”发送到邮件失败. "); 

        WSACleanUp(server);

    }
	else
	{ 
        printf("\n\n客户端:已发送邮件,请求退出！");    
    }       

    printf("\n\n发送邮件成功！ "); 
	
	
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