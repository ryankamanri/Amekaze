#include <stdio.h> 
#include <stdlib.h>
#include <winsock2.h> 
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")//ws2_32.lib: Windows Sockets应用程序的接口,用于支持Internet和网络应用程序
#include <conio.h>
#include "base64.h"
#include "csocket.h"
#include "interface.h"

void quit();
void Client();
void Server();

struct sok_com//一个有很多东西的结构体 
{
	char user[50];
	char pass[50];
	char list[50];
	char top[50];
	char dele[50];

	char quit[50];
	char stat[50];
	char retr[50];
	char noop[50];
	char uidl[50];
};

int main(int argc, char *argv[]) 
{  
	//界面
	//================================================================
 	BOOL SetConsoleTextAttribute( HANDLE hConsoleOutput, WORD wAttributes );
	system("color f6"); 
	//system("pause"); 
	//printf("Hello\n");
    //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN);

	MainInterface();	//主界面

	int n;
	scanf("%d",&n); 
	if(n == 1){
		system("pause");
		system("cls");
		Client();
	}
	if(n == 2)
	{
		system("pause");
		system("cls");
		Server();
	}
	else
	{
		system("pause");
		return 0;
	}
	
}










void Client()
{
	//定义段
    //=========================================
	WSADATA wsaData;	//WSADATA，一种数据结构。这个结构被用来存储被WSAStartup函数调用后返回的Windows Sockets数据。它包含Winsock.dll执行的数据。
    WORD wVersionRequested = MAKEWORD(2, 2);    //makeword是将两个byte型合并成一个word型，一个在高8位(a)，一个在低8位(b)
    struct hostent *pHostent = NULL; 	//该结构记录主机的信息，包括主机名、别名、地址类型、地址长度和地址列表
    SOCKET server = INVALID_SOCKET; 	//server初始化
    struct sockaddr_in service;     //sockaddr_in 是internet环境下套接字的地址形式。所以在网络编程中我们会对sockaddr_in结构体进行操作，使用sockaddr_in来建立所需的信息，最后使用类型转化就可以了
    int retConnect = 0; 	//系统返回代号,如404
    char Buffer[1024] = {0};    //用来指向系统返回的数据
    
  	//====================================== 
  	char *user64;   //账户的base64加密
	char *pass64;   //密码的base64加密  
    char user[100];     // char *user = "test_zh123"; 
    char pass[100];     // char *pass = "S2JW9B3GQ5R4PYZ";
    int choosename;     //选择邮箱所在的主机名
    int iserror=0;  //判断输入是否出错
	int isdelete=0;//判断是否删除临时文件
	char testbuf[50]={0};   //存储用户名和密码的base64发送形式
	char username[30]={0};
	int counts=0;   //count表示指示器前进读取的字节数,返回成功读取的对象个数，若出现错误或到达文件末尾，则可能小于count。
	FILE *fp;   //将正文以文件数据流的形式发送
	char body_end[20]="\r\n.\r\n",bufer[10000]={0},subject[1000]={0};
	char body;  //正文内容的每个字节
	char send_to[200]/*要发送的对象*/,tmpto[200]/*发送RCPT命令指定收件人*/,tmpuser[200]/*发送MAIL命令指定发件人*/, _end[10]/*结尾后缀*/;   
	char MF[200];	//正文的from的发送
	char MT[200];	//正文的TO的发送
	char SUB[1000];	//文章的实际发送内容
	char mailName[50];  //主机名
	//======================================================================


	
    //程序段
    //======================================================================
First:
    system("color f6");
    iserror = 0;
    //查询SOCKET版本是否满足需求

    IsWSAStartup(wVersionRequested,wsaData,server);

    //创建一个SOCKET链接

    server=CreateSocket(server);
 
	//获取邮件服务器的主机名
	ChooseMailInterface();

    scanf("%d",&choosename);
   
    pHostent=GetHostByName(choosename,pHostent,server,mailName);

	//网络通信地址 结构体 赋值：
	//sin_family, sin_addr.s_addr, sin_port
    service.sin_family = AF_INET; 
    memcpy(&service.sin_addr.s_addr, pHostent->h_addr_list[0], pHostent->h_length);
    service.sin_port = htons(25); //将整型变量从主机字节顺序转变成网络字节顺序

	//////////////////////////////////////////////////////////////////////////
	//发送邮件步骤 ... 
	//客户端使用 connect 命令连接到SMTP服务器，建立会话
  
	RetConnectTo(retConnect,server,service,&Buffer);

	//客户端发送一个 HELO 或 EHLO 命令
	//////////////////////////////////////////////////////////////////////////
	//Send HELO
    //Send "HELO Server.... " to the Mail Server 

	SendHELO(retConnect,server,service,&Buffer);

	//客户端发送一个 AUTH 认证命令进行用户登录（使用 smtpd 方式）
	//////////////////////////////////////////////////////////////////////////
	//Send AUTH 
    //Send "AUTH LOGIN " to the Mail Server 
    
    
	SendAUTH(retConnect,server,service,&Buffer);
	
	// //////////////////////////////////////////////////////////////////////////
	// //Send UserName

    // //Send UserName to the Mail Server. The UserName is Encoded by Base64.
    printf("\n请按任意键以继续...");
    getchar();
    getchar();
    system("cls");      //清屏

   
	MailInterface();

	printf("[请输入用户名]:\n\n");
    scanf("%s",user);
    printf("\n[请输入密码]:\n\n");
    // scanf("%s",pass);
	// printf("\n用户名: %s\n\n", user);
	// printf("密码: %s\n\n", pass);

	/////////////////////////////////////////////////////////////////
	//密码显示为 *

	PassInterface(pass);

    user64 = base64_encode(user, strlen(user));
	pass64 = base64_encode(pass, strlen(pass));     //转换为base64格式
	
	strcpy(testbuf,user64);
	//strcpy(testbuf,username);
	strcat(testbuf,"\r\n");

    SendUserName(retConnect,server,service,&Buffer,testbuf);

	// //////////////////////////////////////////////////////////////////////////
	// //Send Password  

    // //Send Password to the Mail Server The Password is Encoded by Base64. 

	strcpy(testbuf,pass64);	
	//strcpy(testbuf, base64_encode("AHNNPFJIQKVQPZIX", strlen("AHNNPFJIQKVQPZIX")));
	//strcpy(testbuf,pass_word);
	strcat(testbuf,"\r\n");

    SendPass(retConnect,server,service,&Buffer,testbuf,&iserror);
    if(iserror == 1)
    {
        system("pause");
        system("cls");
        goto First;
    }

    printf("\n请按任意键以继续...");
    getchar();
    getchar();
    system("cls");



	printf("\n\n                                    ************   登录邮件服务器成功   **************"); 

	//客户端发送一个 MAIL 命令指定发件人
	

    SendMAIL(retConnect,tmpuser,server,user,mailName,&Buffer,_end);

	//客户端发送一个 RCPT 命令指定收件人
	//////////////////////////////////////////////////////////////////////////
	//Send RCPT TO

    SendRCPT(retConnect,tmpto,server,send_to,_end,&Buffer);
   
    
    //客户端发送一个 DATA 命令准备输入邮件正文
	//////////////////////////////////////////////////////////////////////////
	//Send "Data" Field
    //Send "Data" Field to the Mail Server, start to Send mail 


    SendDATA(retConnect,server,&Buffer);


    //////////////////////////////////////////////////////////////////////////
	//Send Mail data

    //Send Mail data to the the Mail Server 

	memset(MF, 0, 200);     //将指针指向区域全部设为零
	strcpy(MF, "FROM:");
	strcat(strcat(MF,user),_end);
	retConnect = send(server, MF, strlen(MF), 0);
    if (retConnect == SOCKET_ERROR)
    {
		printf("发送“邮件发件人：”到邮件失败...\n");
        iserror = 1;
    }

    memset(MT, 0, 200);
	strcpy(MT, "TO:");
	strcat(strcat(MT,send_to),_end);
	retConnect = send(server, MT, strlen(MT), 0);
    if (retConnect == SOCKET_ERROR)
    {
		printf("发送“邮件发件人：”到邮件失败...\n");
		iserror = 1;
    }
    if(iserror == 1)
    {
        system("pause");
        system("cls");
        goto First;
    }

    printf("\n请按任意键以继续...");
    getchar();
    getchar();
    system("cls");

    
    printf("\n                                       *********************************************\n");
	printf("                                          *  正文结束后按 'TAB' 及回车结束录入  *\n");
	printf("                                       *********************************************\n\n");


	memset(SUB, 0, 1000);
	strcpy(SUB, "Subject:");
	memset(subject, 0, strlen(subject));
	printf("*****主题*****：");	//主题发送
	scanf("%s", subject);
	strcat(strcat(SUB, subject),"\n");

	fp = fopen(subject, "w");
	printf("*****正文*****：");
	strcat(SUB, "\n");
	fprintf(fp, "%s", SUB);

	while ((body=getchar()) != '\t')
	{
		putc(body, fp);
	}
	
	fwrite(body_end, sizeof(body_end), 1, fp);
	fclose(fp);

	fp = fopen(subject, "r");
	while ((counts=fread(bufer, 1, 1000, fp))!=0)   //count表示指示器前进读取的字节数,返回成功读取的对象个数，若出现错误或到达文件末尾，则可能小于count。
	{	                                            //若size或count为零，则fread返回零且不进行其他动作。表示读取完毕
		retConnect = send(server, bufer, strlen(bufer), 0);
		if (retConnect == SOCKET_ERROR)
		{
			printf("从邮件服务器接收数据失败……\n");    
			WSACleanUp(server);  
		}
		else
		{
            Buffer[retConnect] = ' ';
			printf("\n\n客户端:数据发送完成!\n");
		}
	}
	///////////////////////////////////////////////是否删除临时文件
	printf("\n当前目录已生成临时文件,是否需要删除?\n");
	printf("\n1.是    2.否\n");
	scanf("%d",&isdelete);
	if(isdelete == 1)
	{
		fclose(fp);
		isdelete=remove(subject);
	}
	if(isdelete == 0) printf("\n删除成功!\n");
	fclose(fp);
	
	//客户端发送一个 . 命令（点命令）表示 DATA 命令结束
	//客户端发送一个 QUIT 命令结束会话
	//////////////////////////////////////////////////////////////////////////
	//Send Mail data

    //Send "QUIT" Context to the Mail Server 

   
	SendQUIT(retConnect,server);
	
// WSACleanUp:     //诊断异常处理,中断

    WSACleanUp(server);
    
/************************************************************************/
/* End of function Defination
/************************************************************************/


}
















void Server()
{

	//Server程序段
	//==================================================================
	system("color 3f");
	printf("\n\n\n欢迎登陆接收邮件界面！\n\n\n");
	//system("cls");	
	//设置接收邮件的标准命令
	struct sok_com command={
		"user ",
		"pass ",
		"list ",
		"top ",
		"dele ",

		"quit ",
		"stat ",
		"retr ",
		"noop ""uidl "
	};
	
	HANDLE hOut;
	char user_name[30], password, pass_word[30]={'\0'}, ent[5]="\r\n", exc[10];
	int i,sel,count,iserror=0;	
	
	//////////////////////////////////////////////////////////////////////////
	WORD wVersionRequested;
	WSADATA wsaData;//结构体 存储 被WSAStartup函数调用后返回的 Windows Sockets 数据
	int err;
	int retConnect = 0;
	wVersionRequested = MAKEWORD( 1, 1 );	//wVersionRequested = 0000 0001 0000 0001(257)
	
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) 
	{
		return;
	}	

	if ( LOBYTE( wsaData.wVersion ) != 1 ||
        HIBYTE( wsaData.wVersion ) != 1 ) 
	{
		WSACleanup();//应用程序在完成对请求的Socket库的使用后，要调用WSACleanup函数来解除与
		return;      //Socket库的绑定并且释放Socket库所占用的系统资源。  
	}

	/*
	int socket(int family,int type,int protocol); 
	第一个参数指明了协议簇，目前支持5种协议簇，最常用的有AF_INET(IPv4协议)和AF_INET6(IPv6协议)；
	第二个参数指明套接口类型，有三种类型可选：SOCK_STREAM(字节流套接口)、SOCK_DGRAM(数据报套接口)和SOCK_RAW(原始套接口)；
	如果套接口类型不是原始套接口，那么第三个参数就为0。
	*/
	SOCKET server = socket(AF_INET, SOCK_STREAM, 0);
	// if(server == INVALID_SOCKET)
	// { 
    //     printf("\n\n套接字错误： %ld ", WSAGetLastError()); 
    //     goto Cleanup;
    // }   
	CreateSocket(server);
	//////////////////////////////////////////////////////////////////////////

	//sockaddr_in 结构体
	SOCKADDR_IN service;
	
	/* 这是我做的部分 */
	for(int i = 0; i < 48; i++)
		printf("*");
	printf("请选择你要登陆的邮箱类型");
	for(int i = 0; i < 48; i++)
		printf("*");
	printf("\n\n\n");	 
	printf("1.@126.com\t2.@qq.com\t3.@sohu.com\t4.@163.com\t5.exit\n\n");
	char mail[2], id[20];
	printf("请输入相应的数字："); 
	scanf("%s", &mail);
	//printf("\n");
	system("cls"); 
	char a[2], b[2], c[2], d[2];
	strcpy(a, "1");
	strcpy(b, "2");
	strcpy(c, "3");
	strcpy(d, "4");
	if(strcmp(mail, a) == 0)
	{
		strcpy(id, "pop3.126.com");
	}
	else if(strcmp(mail, b) == 0)
	{
		strcpy(id, "pop3.qq.com");
	}
	else if(strcmp(mail, c) == 0)
	{
		strcpy(id, "pop3.sohu.com");
	}
	else if(strcmp(mail, d) == 0)
	{
		strcpy(id, "pop3.163.com");
	}
	else
	{
		printf("Good Luck!");
		return;
	}
	/* 这是我做的部分 */
	
login:
	//system("color Df");
DEAL:		
		memcpy(&service.sin_addr.S_un.S_addr, 
		gethostbyname(id)->h_addr_list[0], 
		gethostbyname(id)->h_length);

	//sa_family是地址家族，一般都是“AF_xxx”的形式。通常大多用的是都是AF_INET,代表TCP/IP协议族
	service.sin_family = AF_INET;	
	service.sin_port=htons(110);	//接收端口：110 

	char Buffer[1024] ;
	char Buffer2[5000] ;
	memset(Buffer,0,1000);
	memset(Buffer2,0,5000);

	/*
	int connect(
    SOCKET s,     // 没绑定套接口描述字
    const struct sockaddr FAR *name,   // 目标地址指针，目标地址中必须包含IP和端口信息。
    int namelen   // name的长度
    );
	第一个参数是socket函数返回的套接口描述字；第二和第三个参数分别是一个指向套接口地址结构的指针和该结构的大小。*/


	// //Buffer[retConnect] = 0;  
	printf("\n\n\n用户名：");  
	scanf("%s", user_name);

	RetConnectTo(retConnect,server,service,&Buffer);

	// strcpy(user_name, "test_zh123");//改成由用户自己输入 
	//printf("用户名: %s", user_name);

	//extern char *strcat(char *dest,char *src);
	//把src所指字符串添加到dest结尾处(覆盖dest结尾处的'\0')并添加'\0'。
	strcat(command.user, user_name);//strcat连接两个字符串 command.user+user_name
	strcat(command.user, ent);	//command.user+ent
	
	char * user, pass[30];
	printf("\n独立密码："); 
	//scanf("%s", pass_word);	输入独立密码
	// strcpy(pass_word, "CBVQRDVCKUPAMOHY");//改成用户自己输入密码 	
	

	PassInterface(pass_word);

	strcat(command.pass, pass_word);//连接字符串
	strcat(command.pass, ent);//连接字符串

	//////////////////////////////////////////////////////////////////////////
	//验证用户名

	SendUserName(retConnect,server,service,&Buffer,command.user);

	//////////////////////////////////////////////////////////////////////////
	//验证密码

	SendPass(retConnect,server,service,&Buffer,command.pass,&iserror);
    if(iserror == 1)
    {
        system("pause");
        system("cls");
        return;
    }

	//////////////////////////////////////////////////////////////////////////

	if (Buffer[0] == '+')
	{
		system("cls");
		printf("\n	账户登录成功\n\n");		
     	
menu:
        printf("选择:\n\n");
		printf("1、查看邮件总数\n");
		printf("2、列出所有邮件\n");
		printf("3、返回到主菜单\n");
		printf("4、重新登录\n");
		printf("5、退出与POP3服务器的连接\n\n");

		struct sok_com cmd_recv={
			"user ",
			"pass ",
			"list ",
			"top ",
			"dele ",			
			"quit ",
			"stat ",
			"retr ",
			"noop ""uidl "
		};
		
select:
		printf("请选择编号：");
		scanf("%d", &i);
		switch(i)
		{
		
		case 1:	//查看邮件总数
			strcat(cmd_recv.stat, ent);

		
			Send1024(retConnect,server,service,&Buffer,&Buffer2,cmd_recv.stat,"Stat");
		
			strcat(cmd_recv.noop,ent);
		
			Send1024(retConnect,server,service,&Buffer,&Buffer2,cmd_recv.noop,"Noop");

			goto select;
		case 2:	//列出所有邮件
			strcat(cmd_recv.list,ent);

		
			Send1024(retConnect,server,service,&Buffer,&Buffer2,cmd_recv.list,"List");

		view:			
			printf("1-查看对应ID邮件的邮件头信息\n");
			printf("2-查看对应ID邮件的全部内容\n");
			printf("3-删除对应ID邮件的全部内容\n");
			printf("4-返回主菜单\n");
			printf("选择操作：");
			scanf("%d",&sel);
			switch(sel)
			{
			case 1:	//查看对应ID邮件的邮件头信息
				printf("输入要查看头信息的邮件编号：");
				scanf("%d",&sel);

				//itoa 把一整数转换为字符串
				strcat(cmd_recv.top, itoa(sel, exc,10));
				strcat(strcat(strcat(cmd_recv.top," "), itoa(0, exc,10)), ent);


				Send5000(retConnect,server,service,&Buffer,&Buffer2,cmd_recv.top,"TOP");
				goto view;

			case 2:	//查看对应ID邮件的全部内容
				printf("输入要查看内容的邮件编号：");
				scanf("%d",&sel);

				strcat(strcat(cmd_recv.retr,itoa(sel,exc,10)),ent);
			

				Send5000(retConnect,server,service,&Buffer,&Buffer2,cmd_recv.retr,"RETR");
				
				goto view;

			case 3:	//删除对应ID邮件的全部内容
				printf("输入要删除邮件编号：");
				scanf("%d",&sel);

				strcat(strcat(cmd_recv.dele,itoa(sel,exc,10)),ent);
				

				Send1024(retConnect,server,service,&Buffer,&Buffer2,cmd_recv.dele,"DELE");
				
				goto view;

			default :
				system("cls");
				goto menu;
			}

		case 3:
			system("cls");
			goto menu;

		case 4:
			system("cls");
			goto login; 
			
		default: quit();
		break;
		}

	}//if (Buffer[0] == '+')
	else
	{
		printf("密码错误或帐号不存在	\n");
		printf("1、重新登录	\n");
		printf("2、退出系统	\n");
		printf("选择：");
		scanf("%d",&sel);
		if (sel==1)
		{
			goto login;
		} 
		else quit();
	}	
	
Cleanup:
    closesocket(server);
	WSACleanup();
	getch();
	return;

}


void quit()////退出登录
{
    system("cls");
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	
	wVersionRequested = MAKEWORD( 1, 1 );
	
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		return;
	}
	

	if ( LOBYTE( wsaData.wVersion ) != 1 ||
        HIBYTE( wsaData.wVersion ) != 1 ) {
		WSACleanup();
		return; 
	}
	SOCKET server=socket(AF_INET,SOCK_STREAM,0);

	//SOCKADDR_IN&service;
	char Buffer[100]={0};
    send(server,"quit\n",strlen("quit\n"),0);
	recv(server,Buffer,100,0);

}











