#include <stdio.h> 
#include <stdlib.h>
#include <winsock2.h> 
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")//ws2_32.lib: Windows SocketsӦ�ó���Ľӿ�,����֧��Internet������Ӧ�ó���
#include <conio.h>
#include "base64.h"
#include "csocket.h"
#include "interface.h"

void quit();
void Client();
void Server();

struct sok_com//һ���кܶණ���Ľṹ�� 
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
	//����
	//================================================================
 	BOOL SetConsoleTextAttribute( HANDLE hConsoleOutput, WORD wAttributes );
	system("color f6"); 
	//system("pause"); 
	//printf("Hello\n");
    //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN);

	MainInterface();	//������

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
	//�����
    //=========================================
	WSADATA wsaData;	//WSADATA��һ�����ݽṹ������ṹ�������洢��WSAStartup�������ú󷵻ص�Windows Sockets���ݡ�������Winsock.dllִ�е����ݡ�
    WORD wVersionRequested = MAKEWORD(2, 2);    //makeword�ǽ�����byte�ͺϲ���һ��word�ͣ�һ���ڸ�8λ(a)��һ���ڵ�8λ(b)
    struct hostent *pHostent = NULL; 	//�ýṹ��¼��������Ϣ����������������������ַ���͡���ַ���Ⱥ͵�ַ�б�
    SOCKET server = INVALID_SOCKET; 	//server��ʼ��
    struct sockaddr_in service;     //sockaddr_in ��internet�������׽��ֵĵ�ַ��ʽ�������������������ǻ��sockaddr_in�ṹ����в�����ʹ��sockaddr_in�������������Ϣ�����ʹ������ת���Ϳ�����
    int retConnect = 0; 	//ϵͳ���ش���,��404
    char Buffer[1024] = {0};    //����ָ��ϵͳ���ص�����
    
  	//====================================== 
  	char *user64;   //�˻���base64����
	char *pass64;   //�����base64����  
    char user[100];     // char *user = "test_zh123"; 
    char pass[100];     // char *pass = "S2JW9B3GQ5R4PYZ";
    int choosename;     //ѡ���������ڵ�������
    int iserror=0;  //�ж������Ƿ����
	int isdelete=0;//�ж��Ƿ�ɾ����ʱ�ļ�
	char testbuf[50]={0};   //�洢�û����������base64������ʽ
	char username[30]={0};
	int counts=0;   //count��ʾָʾ��ǰ����ȡ���ֽ���,���سɹ���ȡ�Ķ�������������ִ���򵽴��ļ�ĩβ�������С��count��
	FILE *fp;   //���������ļ�����������ʽ����
	char body_end[20]="\r\n.\r\n",bufer[10000]={0},subject[1000]={0};
	char body;  //�������ݵ�ÿ���ֽ�
	char send_to[200]/*Ҫ���͵Ķ���*/,tmpto[200]/*����RCPT����ָ���ռ���*/,tmpuser[200]/*����MAIL����ָ��������*/, _end[10]/*��β��׺*/;   
	char MF[200];	//���ĵ�from�ķ���
	char MT[200];	//���ĵ�TO�ķ���
	char SUB[1000];	//���µ�ʵ�ʷ�������
	char mailName[50];  //������
	//======================================================================


	
    //�����
    //======================================================================
First:
    system("color f6");
    iserror = 0;
    //��ѯSOCKET�汾�Ƿ���������

    IsWSAStartup(wVersionRequested,wsaData,server);

    //����һ��SOCKET����

    server=CreateSocket(server);
 
	//��ȡ�ʼ���������������
	ChooseMailInterface();

    scanf("%d",&choosename);
   
    pHostent=GetHostByName(choosename,pHostent,server,mailName);

	//����ͨ�ŵ�ַ �ṹ�� ��ֵ��
	//sin_family, sin_addr.s_addr, sin_port
    service.sin_family = AF_INET; 
    memcpy(&service.sin_addr.s_addr, pHostent->h_addr_list[0], pHostent->h_length);
    service.sin_port = htons(25); //�����ͱ����������ֽ�˳��ת��������ֽ�˳��

	//////////////////////////////////////////////////////////////////////////
	//�����ʼ����� ... 
	//�ͻ���ʹ�� connect �������ӵ�SMTP�������������Ự
  
	RetConnectTo(retConnect,server,service,&Buffer);

	//�ͻ��˷���һ�� HELO �� EHLO ����
	//////////////////////////////////////////////////////////////////////////
	//Send HELO
    //Send "HELO Server.... " to the Mail Server 

	SendHELO(retConnect,server,service,&Buffer);

	//�ͻ��˷���һ�� AUTH ��֤��������û���¼��ʹ�� smtpd ��ʽ��
	//////////////////////////////////////////////////////////////////////////
	//Send AUTH 
    //Send "AUTH LOGIN " to the Mail Server 
    
    
	SendAUTH(retConnect,server,service,&Buffer);
	
	// //////////////////////////////////////////////////////////////////////////
	// //Send UserName

    // //Send UserName to the Mail Server. The UserName is Encoded by Base64.
    printf("\n�밴������Լ���...");
    getchar();
    getchar();
    system("cls");      //����

   
	MailInterface();

	printf("[�������û���]:\n\n");
    scanf("%s",user);
    printf("\n[����������]:\n\n");
    // scanf("%s",pass);
	// printf("\n�û���: %s\n\n", user);
	// printf("����: %s\n\n", pass);

	/////////////////////////////////////////////////////////////////
	//������ʾΪ *

	PassInterface(pass);

    user64 = base64_encode(user, strlen(user));
	pass64 = base64_encode(pass, strlen(pass));     //ת��Ϊbase64��ʽ
	
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

    printf("\n�밴������Լ���...");
    getchar();
    getchar();
    system("cls");



	printf("\n\n                                    ************   ��¼�ʼ��������ɹ�   **************"); 

	//�ͻ��˷���һ�� MAIL ����ָ��������
	

    SendMAIL(retConnect,tmpuser,server,user,mailName,&Buffer,_end);

	//�ͻ��˷���һ�� RCPT ����ָ���ռ���
	//////////////////////////////////////////////////////////////////////////
	//Send RCPT TO

    SendRCPT(retConnect,tmpto,server,send_to,_end,&Buffer);
   
    
    //�ͻ��˷���һ�� DATA ����׼�������ʼ�����
	//////////////////////////////////////////////////////////////////////////
	//Send "Data" Field
    //Send "Data" Field to the Mail Server, start to Send mail 


    SendDATA(retConnect,server,&Buffer);


    //////////////////////////////////////////////////////////////////////////
	//Send Mail data

    //Send Mail data to the the Mail Server 

	memset(MF, 0, 200);     //��ָ��ָ������ȫ����Ϊ��
	strcpy(MF, "FROM:");
	strcat(strcat(MF,user),_end);
	retConnect = send(server, MF, strlen(MF), 0);
    if (retConnect == SOCKET_ERROR)
    {
		printf("���͡��ʼ������ˣ������ʼ�ʧ��...\n");
        iserror = 1;
    }

    memset(MT, 0, 200);
	strcpy(MT, "TO:");
	strcat(strcat(MT,send_to),_end);
	retConnect = send(server, MT, strlen(MT), 0);
    if (retConnect == SOCKET_ERROR)
    {
		printf("���͡��ʼ������ˣ������ʼ�ʧ��...\n");
		iserror = 1;
    }
    if(iserror == 1)
    {
        system("pause");
        system("cls");
        goto First;
    }

    printf("\n�밴������Լ���...");
    getchar();
    getchar();
    system("cls");

    
    printf("\n                                       *********************************************\n");
	printf("                                          *  ���Ľ����� 'TAB' ���س�����¼��  *\n");
	printf("                                       *********************************************\n\n");


	memset(SUB, 0, 1000);
	strcpy(SUB, "Subject:");
	memset(subject, 0, strlen(subject));
	printf("*****����*****��");	//���ⷢ��
	scanf("%s", subject);
	strcat(strcat(SUB, subject),"\n");

	fp = fopen(subject, "w");
	printf("*****����*****��");
	strcat(SUB, "\n");
	fprintf(fp, "%s", SUB);

	while ((body=getchar()) != '\t')
	{
		putc(body, fp);
	}
	
	fwrite(body_end, sizeof(body_end), 1, fp);
	fclose(fp);

	fp = fopen(subject, "r");
	while ((counts=fread(bufer, 1, 1000, fp))!=0)   //count��ʾָʾ��ǰ����ȡ���ֽ���,���سɹ���ȡ�Ķ�������������ִ���򵽴��ļ�ĩβ�������С��count��
	{	                                            //��size��countΪ�㣬��fread�������Ҳ�����������������ʾ��ȡ���
		retConnect = send(server, bufer, strlen(bufer), 0);
		if (retConnect == SOCKET_ERROR)
		{
			printf("���ʼ���������������ʧ�ܡ���\n");    
			WSACleanUp(server);  
		}
		else
		{
            Buffer[retConnect] = ' ';
			printf("\n\n�ͻ���:���ݷ������!\n");
		}
	}
	///////////////////////////////////////////////�Ƿ�ɾ����ʱ�ļ�
	printf("\n��ǰĿ¼��������ʱ�ļ�,�Ƿ���Ҫɾ��?\n");
	printf("\n1.��    2.��\n");
	scanf("%d",&isdelete);
	if(isdelete == 1)
	{
		fclose(fp);
		isdelete=remove(subject);
	}
	if(isdelete == 0) printf("\nɾ���ɹ�!\n");
	fclose(fp);
	
	//�ͻ��˷���һ�� . ����������ʾ DATA �������
	//�ͻ��˷���һ�� QUIT ��������Ự
	//////////////////////////////////////////////////////////////////////////
	//Send Mail data

    //Send "QUIT" Context to the Mail Server 

   
	SendQUIT(retConnect,server);
	
// WSACleanUp:     //����쳣����,�ж�

    WSACleanUp(server);
    
/************************************************************************/
/* End of function Defination
/************************************************************************/


}
















void Server()
{

	//Server�����
	//==================================================================
	system("color 3f");
	printf("\n\n\n��ӭ��½�����ʼ����棡\n\n\n");
	//system("cls");	
	//���ý����ʼ��ı�׼����
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
	WSADATA wsaData;//�ṹ�� �洢 ��WSAStartup�������ú󷵻ص� Windows Sockets ����
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
		WSACleanup();//Ӧ�ó�������ɶ������Socket���ʹ�ú�Ҫ����WSACleanup�����������
		return;      //Socket��İ󶨲����ͷ�Socket����ռ�õ�ϵͳ��Դ��  
	}

	/*
	int socket(int family,int type,int protocol); 
	��һ������ָ����Э��أ�Ŀǰ֧��5��Э��أ���õ���AF_INET(IPv4Э��)��AF_INET6(IPv6Э��)��
	�ڶ�������ָ���׽ӿ����ͣ����������Ϳ�ѡ��SOCK_STREAM(�ֽ����׽ӿ�)��SOCK_DGRAM(���ݱ��׽ӿ�)��SOCK_RAW(ԭʼ�׽ӿ�)��
	����׽ӿ����Ͳ���ԭʼ�׽ӿڣ���ô������������Ϊ0��
	*/
	SOCKET server = socket(AF_INET, SOCK_STREAM, 0);
	// if(server == INVALID_SOCKET)
	// { 
    //     printf("\n\n�׽��ִ��� %ld ", WSAGetLastError()); 
    //     goto Cleanup;
    // }   
	CreateSocket(server);
	//////////////////////////////////////////////////////////////////////////

	//sockaddr_in �ṹ��
	SOCKADDR_IN service;
	
	/* ���������Ĳ��� */
	for(int i = 0; i < 48; i++)
		printf("*");
	printf("��ѡ����Ҫ��½����������");
	for(int i = 0; i < 48; i++)
		printf("*");
	printf("\n\n\n");	 
	printf("1.@126.com\t2.@qq.com\t3.@sohu.com\t4.@163.com\t5.exit\n\n");
	char mail[2], id[20];
	printf("��������Ӧ�����֣�"); 
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
	/* ���������Ĳ��� */
	
login:
	//system("color Df");
DEAL:		
		memcpy(&service.sin_addr.S_un.S_addr, 
		gethostbyname(id)->h_addr_list[0], 
		gethostbyname(id)->h_length);

	//sa_family�ǵ�ַ���壬һ�㶼�ǡ�AF_xxx������ʽ��ͨ������õ��Ƕ���AF_INET,����TCP/IPЭ����
	service.sin_family = AF_INET;	
	service.sin_port=htons(110);	//���ն˿ڣ�110 

	char Buffer[1024] ;
	char Buffer2[5000] ;
	memset(Buffer,0,1000);
	memset(Buffer2,0,5000);

	/*
	int connect(
    SOCKET s,     // û���׽ӿ�������
    const struct sockaddr FAR *name,   // Ŀ���ַָ�룬Ŀ���ַ�б������IP�Ͷ˿���Ϣ��
    int namelen   // name�ĳ���
    );
	��һ��������socket�������ص��׽ӿ������֣��ڶ��͵����������ֱ���һ��ָ���׽ӿڵ�ַ�ṹ��ָ��͸ýṹ�Ĵ�С��*/


	// //Buffer[retConnect] = 0;  
	printf("\n\n\n�û�����");  
	scanf("%s", user_name);

	RetConnectTo(retConnect,server,service,&Buffer);

	// strcpy(user_name, "test_zh123");//�ĳ����û��Լ����� 
	//printf("�û���: %s", user_name);

	//extern char *strcat(char *dest,char *src);
	//��src��ָ�ַ�����ӵ�dest��β��(����dest��β����'\0')�����'\0'��
	strcat(command.user, user_name);//strcat���������ַ��� command.user+user_name
	strcat(command.user, ent);	//command.user+ent
	
	char * user, pass[30];
	printf("\n�������룺"); 
	//scanf("%s", pass_word);	�����������
	// strcpy(pass_word, "CBVQRDVCKUPAMOHY");//�ĳ��û��Լ��������� 	
	

	PassInterface(pass_word);

	strcat(command.pass, pass_word);//�����ַ���
	strcat(command.pass, ent);//�����ַ���

	//////////////////////////////////////////////////////////////////////////
	//��֤�û���

	SendUserName(retConnect,server,service,&Buffer,command.user);

	//////////////////////////////////////////////////////////////////////////
	//��֤����

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
		printf("\n	�˻���¼�ɹ�\n\n");		
     	
menu:
        printf("ѡ��:\n\n");
		printf("1���鿴�ʼ�����\n");
		printf("2���г������ʼ�\n");
		printf("3�����ص����˵�\n");
		printf("4�����µ�¼\n");
		printf("5���˳���POP3������������\n\n");

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
		printf("��ѡ���ţ�");
		scanf("%d", &i);
		switch(i)
		{
		
		case 1:	//�鿴�ʼ�����
			strcat(cmd_recv.stat, ent);

		
			Send1024(retConnect,server,service,&Buffer,&Buffer2,cmd_recv.stat,"Stat");
		
			strcat(cmd_recv.noop,ent);
		
			Send1024(retConnect,server,service,&Buffer,&Buffer2,cmd_recv.noop,"Noop");

			goto select;
		case 2:	//�г������ʼ�
			strcat(cmd_recv.list,ent);

		
			Send1024(retConnect,server,service,&Buffer,&Buffer2,cmd_recv.list,"List");

		view:			
			printf("1-�鿴��ӦID�ʼ����ʼ�ͷ��Ϣ\n");
			printf("2-�鿴��ӦID�ʼ���ȫ������\n");
			printf("3-ɾ����ӦID�ʼ���ȫ������\n");
			printf("4-�������˵�\n");
			printf("ѡ�������");
			scanf("%d",&sel);
			switch(sel)
			{
			case 1:	//�鿴��ӦID�ʼ����ʼ�ͷ��Ϣ
				printf("����Ҫ�鿴ͷ��Ϣ���ʼ���ţ�");
				scanf("%d",&sel);

				//itoa ��һ����ת��Ϊ�ַ���
				strcat(cmd_recv.top, itoa(sel, exc,10));
				strcat(strcat(strcat(cmd_recv.top," "), itoa(0, exc,10)), ent);


				Send5000(retConnect,server,service,&Buffer,&Buffer2,cmd_recv.top,"TOP");
				goto view;

			case 2:	//�鿴��ӦID�ʼ���ȫ������
				printf("����Ҫ�鿴���ݵ��ʼ���ţ�");
				scanf("%d",&sel);

				strcat(strcat(cmd_recv.retr,itoa(sel,exc,10)),ent);
			

				Send5000(retConnect,server,service,&Buffer,&Buffer2,cmd_recv.retr,"RETR");
				
				goto view;

			case 3:	//ɾ����ӦID�ʼ���ȫ������
				printf("����Ҫɾ���ʼ���ţ�");
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
		printf("���������ʺŲ�����	\n");
		printf("1�����µ�¼	\n");
		printf("2���˳�ϵͳ	\n");
		printf("ѡ��");
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


void quit()////�˳���¼
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











