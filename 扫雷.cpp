#include<stdio.h> 
#include<conio.h>
#include<stdlib.h>
#include<time.h>
const int size=10;
void start(int *x,int *y,int sq[size][size],char chara[size][size]);
void restart(int *x,int *y,int sq[size][size],char chara[size][size]);
void change(int *x,int *y,int judge,int sq[size][size]);
void readkey(int *x,int *y,int *a,int sq[size][size],char chara[size][size]);
int calculate(int *x,int *y,int sq[size][size]);


int main()
{
    int x=0,y=0,a=0;
    int sq[size][size];
    char chara[size][size];
    start(&x,&y,sq,chara);
    while(a==0)
    {	
		readkey(&x,&y,&a,sq,chara);
        system("cls");//«Â∆¡ 
        restart(&x,&y,sq,chara);
    }
       for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            printf("%d ",sq[i][j]);
        }
        printf("\n");
    }
    printf("game over");
    
    return 0;
}
void start(int *x,int *y,int sq[size][size],char chara[size][size])
{
    int i,j;
    srand(time(NULL));
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
        {
            sq[i][j]=rand()%2;
            chara[i][j]='*';
			printf("%c ",chara[i][j]); 
        }
        printf("\n");
    }
    printf("(%d,%d)",*x+1,*y+1);
}
void restart(int *x,int *y,int sq[10][10],char chara[size][size])
{
	printf("wasd“∆∂Ø\ j≈–∂œ\ k≤Â∆Ï\n"); 
	int i,j;
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
        {
            printf("%c ",chara[i][j]);
        }
        printf("\n");
    }
    printf("(%d,%d)\n",*x+1,*y+1);
}
void change(int *x,int *y,int judge,char chara[size][size])
{
	switch(judge)
	{
		case 1:
			(*y)--;
			if(chara[*x][*y]=='*') chara[*x][*y]='$';
			if(chara[*x][*y+1]=='$') chara[*x][*y+1]='*';
			break;
		case 2:
			(*y)++;
			if(chara[*x][*y]=='*') chara[*x][*y]='$';
			if(chara[*x][*y-1]=='$') chara[*x][*y-1]='*';
			break;
		case 3:
			(*x)--;
			if(chara[*x][*y]=='*') chara[*x][*y]='$';
			if(chara[*x+1][*y]=='$') chara[*x+1][*y]='*';
			break;
		case 4:
			(*x)++;
			if(chara[*x][*y]=='*') chara[*x][*y]='$';
			if(chara[*x-1][*y]=='$') chara[*x-1][*y]='*';
			break;
	}
}
void readkey(int *x,int *y,int *a,int sq[size][size],char chara[size][size])
{
	if(kbhit())
	{
			
		switch(getch())
		{
			int judge;
			case (int)'w':
				if(*x==0) break;
				judge=3;
				change(x,y,judge,chara);
				break;
			case (int)'a':
				if(*y==0) break;
				judge=1;
				change(x,y,judge,chara);
				break;
			case (int)'s':
				if(*x==size-1) break;
				judge=4;
				change(x,y,judge,chara);
				break;
			case (int)'d':
				if(*y==size-1) break;
				judge=2;
				change(x,y,judge,chara);
				break;
			case (int)'j'://≈–∂œ 
				if(sq[*x][*y]==1)
				{
					chara[*x][*y]='@';//µ„ª˜∫Û÷–¡Àµÿ¿◊ 
					*a=1;
				} 
				else
				{
					chara[*x][*y]='0'+calculate(x,y,sq);  
				} 
				break;
			case (int)'k':
				if(chara[*x][*y]='!') chara[*x][*y]='$';
				else if(chara[*x][*y]='$') chara[*x][*y]='!';//≤Â…œ∆Ï÷ƒ
				break;
			default:
				break;
		}
	} 
        
}
int calculate(int *x,int *y,int sq[size][size])
{
	if(*x==0&&*y==0)return sq[*x+1][*y]+sq[*x][*y+1]+sq[*x+1][*y+1];
	else if(*x==0&&*y==size-1) return sq[*x+1][*y]+sq[*x][*y-1]+sq[*x+1][*y-1];
	else if(*x==size-1&&*y==0) return sq[*x-1][*y]+sq[*x][*y+1]+sq[*x-1][*y+1];
	else if(*x==size-1&&*y==size-1) return sq[*x-1][*y]+sq[*x][*y-1]+sq[*x-1][*y-1];
	else
	{
		if(*x==0) return sq[*x+1][*y]+sq[*x][*y+1]+sq[*x+1][*y+1]+sq[*x][*y-1]+sq[*x+1][*y-1];
		else if(*x==size-1) return sq[*x-1][*y]+sq[*x][*y+1]+sq[*x-1][*y+1]+sq[*x][*y-1]+sq[*x-1][*y-1];
		else if(*y==0) return sq[*x+1][*y]+sq[*x][*y+1]+sq[*x+1][*y+1]+sq[*x-1][*y]+sq[*x-1][*y+1];
		else if(*y==size-1) return sq[*x+1][*y]+sq[*x][*y-1]+sq[*x+1][*y-1]+sq[*x-1][*y]+sq[*x-1][*y-1];
		else
		{
			return sq[*x+1][*y]+sq[*x][*y+1]+sq[*x+1][*y+1]+sq[*x][*y-1]+sq[*x+1][*y-1]+sq[*x-1][*y]+sq[*x-1][*y+1]+sq[*x-1][*y-1];
		}
	} 
}

