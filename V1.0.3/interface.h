#include <stdio.h> 
#define row 7
#define col 50

void MainInterface();   //主界面
void ChooseMailInterface();
void MailInterface();
char *PassInterface();


void MainInterface()
{
    printf("                   *                *          *                   *         *               * * * * * * * * * * \n");
	printf("    ********      **********     *****      *     *******         *   * * * * * * * * *      *        *        *\n");
	printf("     *    *      *    *   *         *       *     *     *        *           *               *        *        *\n");
	printf("      *  *      *    *             *        *     *     *      *  *    * * * * * * * *       * * * * * * * * * *  \n");
	printf("       *            * *            *        *     *   * *         *    *      *      *       *        *        *\n");
	printf("      * *          *   *           *        *     *     *         *    * * * * * * * *       *        *        *\n");
	printf("     *   *        *     *          *        *  *  *               *       *  *               * * * * * * * * * * \n");
	printf("    *     *      *       *         *        *     *               *         *                *        *        *\n");
	printf("   *       *    *         *       *  *            *               *        *   *             *        *        *\n");
	printf("               *           *     *    * * * * * * * * * * * *     *       *     *            *        *        *\n");
	printf("                                                                  *     *         *  *      *         *        *\n");
	printf("\n\n\n");
	printf("                                          --------------------------------\n");
	printf("                                          |     请选择你要进行的操作     |\n");
	printf("                                          |         1.发送邮件           |\n"); 
	printf("                                          |         2.接收邮件           |\n");
	printf("                                          |         3.退出操作           |\n");
	printf("                                          --------------------------------\n");
	printf("                                                      ``````\n");
	printf("                                                         ");
}

void ChooseMailInterface()
{
    printf("\n\n\n                               **********************************************************\n");
	printf("                                                     ");
    printf("*请选择主机名*\n\n                                  1.@163.com    2.@sohu.com    3.@126.com    4.@qq.com\n\n");
    printf("                               **********************************************************\n");
    printf("                                                      which one:");
}


void MailInterface()
{
    char tu_2[row][col] = {'a'};
	int i, j;
	//M
	for(i = 0,j = 14; j < 23; j++)
	{
		if(j == 16 || j == 19)
		{
			tu_2[i][j] = '*';
		} 	 
	}
	for(i = 1, j = 16; j < 22; j++)
	{
		if(j == 16 || j == 17 || j == 19 || j == 20)
		tu_2[i][j] = '*';
	}
	for(i = 2, j = 16; j < 21; j++)
	{
		if(j == 16 || (j > 17 && j < 22))
		{
			tu_2[i][j] = '*';
		} 
	}
	for(i = 3, j = 15; j < 22; j++)
	{
		if(j == 15 || j == 18 || j == 21)
		{
			tu_2[i][j] = '*';
		}
	}
	for(i = 4, j = 15; j < 23; j++)
	{
		if(j == 15 || j == 21)
		{
			tu_2[i][j] = '*';
		}
	}
	for(i = 5, j = 14; j < 23; j++)
	{
		if(j == 15 || j == 21 || j == 22 || j == 14)
		{
			tu_2[i][j] = '*';
		}
	}
	for(i = 6, j = 14; j < 23; j++)
	{
		if(j < 16 || j >= 20)
		{
			tu_2[i][j] = '*';
		}
	}
	//-
	for(i = 3, j = 9; j < 12; j++)
	{
		tu_2[i][j] = '*';
	}
	//E
	for(i = 0, j = 0; j < 9; j++)
	{
		tu_2[i][j] = '*';
	}
	for(j = 0, i = 1; i < 18; i++)
	{
		tu_2[i][j] = '*';
	}
	for(i = 3, j = 1; j < 7; j++)
	{
		tu_2[i][j] = '*';
	} 
	for(i = 6, j = 1; j < 9; j++)
	{
		tu_2[i][j] = '*';
	}
	
	//A
	tu_2[0][28] = '*';
	for(i = 1, j = 24; j < 35; j++)
	{
		if(j == 27 || j == 29)
		tu_2[i][j] = '*';
	} 
	for(i = 2, j = 24; j < 37; j++)
	{
		if(j == 27 || j == 29)
		tu_2[i][j] = '*';
	}
	for(i = 3, j = 24; j < 35; j++)
	{
		if(j > 25 && j < 31)
		tu_2[i][j] = '*';
	}
	for(i = 4, j = 24; j < 35; j++)
	{
		if(j == 26 || j == 30)
		tu_2[i][j] = '*';
	}
	for(i = 5, j = 24; j < 35; j++)
	{
		if(j == 25 || j == 31)
		tu_2[i][j] = '*';
	}
	for(i = 6, j = 24; j < 34; j++)
	{
		if(j < 27 || j > 30)
		tu_2[i][j] = '*';
	}
	//I
	for(i = 0, j = 36; j < 41; j++)
	{
		tu_2[i][j] = '*';
	}
	for(j = 38, i = 1; i < row; i++)
	{
		tu_2[i][j] = '*';
	}
	for(i = 6, j = 35; j < 42; j++)
	{
		tu_2[i][j] = '*';
	}
	//L
	for(j = 44, i = 0; i < 7; i++)
	{
		tu_2[i][j] = '*';
	}
	for(i = 6, j = 44; j < 50; j++)
	{
		tu_2[i][j] = '*';
	}
    for(i = 0; i < row; i++)
	{
		for(j = 0; j < col; j++)
		{
			printf("%c", tu_2[i][j]);
		}
		printf("\n");
	}
}
char *PassInterface(char *pass)
{
    int count=0;
    char pass_word[30]={0},password[2];
    while (password[0] = getch())		
	{		
		if(password[0] == '\r')	//Enter
		{
			pass_word[count]='\0';				
			break;
		}	
		else if((password[0]=='\b') && (count>0))	//Backspace
		{	
			printf("\b \b");
			count--;
		}
		else if((count==0) && (password[0]=='\b')) ;	
		else
		{
			pass_word[count] = password[0];
			count++;
			printf("*");
		}
	}

	strcpy(pass,pass_word);
    return pass;
}