#include<stdio.h>
#include "inputbox.h"
#include "acllib.h"
#include<time.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<windows.h>
#define GAP 30
#define NUM 20
#define POSX 10
#define POSY 50
#define TIMES 10
//const int NUM=30;

ACL_Image img1;//mine
ACL_Image img2;//background
//ACL_Image img3;

ACL_Image img3;//flag
ACL_Image img4;//question mark

ACL_Image img11;
ACL_Image img12;
ACL_Image img13;
ACL_Image img14;
ACL_Image img15;
ACL_Image img16;
ACL_Image img17;
ACL_Image img18;
ACL_Image img19;

ACL_Image img_zero;
int ismine[NUM][NUM]={0};//

int found_mine=0; 
int is_shown[NUM][NUM]={0};

time_t start,end;

const int timerID1=1,timerID2=2;
int timer=0;
int timer_2=0;
int mine_left;

int click_times=0;

void cal_mine(int i,int j)
{
	if(i<0||j<0||i>20||j>20)
	{
		return;
	}
	if(ismine[i][j]==-1)
	{
		return;
	}
	else
	{
		ismine[i][j]++;
		
	}
}

//char *numstr(int num)
//{
//	
//	int temp[TIMES];
//	char* ret;
//	ret=(char*)malloc(TIMES*sizeof(char));
//	for(int i=0; num>0; i++)
//	{
//		temp[TIMES-i]=num%10;
//		num/=10;
//	}
//	for(int i=0; i<TIMES; i++)
//	{
//		ret[i]=temp[i]+'0';
//	}
//	return ret;
//}

int numofmines=0;
int iszero[NUM][NUM]={0};

//void resetup(int timerID2)
//{
//		system("1.bat");
//}

void find_zero(int x,int y)
{
	if(x<0||x>=NUM||y<0||y>=NUM)return;
	if(iszero[x][y]==1)return;
	if(ismine[x][y]!=-1&&ismine!=0)
	{
		beginPaint();
		loadImage("1.bmp",&img11);
		loadImage("2.bmp",&img12);
		loadImage("3.bmp",&img13);
		loadImage("4.bmp",&img14);
		loadImage("5.bmp",&img15);
		loadImage("6.bmp",&img16);
		loadImage("7.bmp",&img17);
		loadImage("8.bmp",&img18);
		loadImage("9.bmp",&img19);
		int a=x,b=y;
		switch(ismine[a][b])
		{
			case 1:putImage(&img11,POSX+GAP*a+1,POSY+GAP*b+1);is_shown[a][b]=1;break;
			case 2:putImage(&img12,POSX+GAP*a+1,POSY+GAP*b+1);is_shown[a][b]=1;break;
			case 3:putImage(&img13,POSX+GAP*a+1,POSY+GAP*b+1);is_shown[a][b]=1;break;
			case 4:putImage(&img14,POSX+GAP*a+1,POSY+GAP*b+1);is_shown[a][b]=1;break;
			case 5:putImage(&img15,POSX+GAP*a+1,POSY+GAP*b+1);is_shown[a][b]=1;break;
			case 6:putImage(&img16,POSX+GAP*a+1,POSY+GAP*b+1);is_shown[a][b]=1;break;
			case 7:putImage(&img17,POSX+GAP*a+1,POSY+GAP*b+1);is_shown[a][b]=1;break;
			case 8:putImage(&img18,POSX+GAP*a+1,POSY+GAP*b+1);is_shown[a][b]=1;break;
			case 9:putImage(&img19,POSX+GAP*a+1,POSY+GAP*b+1);is_shown[a][b]=1;break;
		}
		endPaint();
	}
	if(ismine[x][y]==0)
	{
		iszero[x][y]=1;
		beginPaint();
		loadImage("zero.jpg",&img_zero);
		putImage(&img_zero,POSX+GAP*x,POSY+GAP*y);
		is_shown[x][y]=1;
		endPaint();
		find_zero(x,y-1); 
		find_zero(x-1,y);
		find_zero(x+1,y);
		find_zero(x,y+1);
	}
	if((iszero[x+1][y]==1||ismine[x+1][y]!=-1)&&(iszero[x][y+1]==1||ismine[x][y+1]!=-1)&&(iszero[x][y-1]==1||ismine[x][y-1]==-1)&&(iszero[x-1][y]==1||ismine[x-1][y]!=-1))return;
	
	
	
}

int right_key[NUM][NUM]={0};
void calrightkey(int a,int b)
{
	if(a<0||a>NUM||b<0||b>NUM)return;
	if(is_shown[a][b])return;
	if(right_key[a][b]<2)right_key[a][b]++;
	else
	{
		if(right_key[a][b]==2)right_key[a][b]=0;
	}
}

void rightkey(int a,int b)
{ 
	if(is_shown[a][b])return;
	if(a<0||a>NUM||b<0||b>NUM)return;
	beginPaint();
	loadImage("flag.bmp",&img3);
	loadImage("qsmark.jpg",&img4);
	loadImage("background.jpg",&img2);
	switch(right_key[a][b])
	{
		case 0:putImage(&img2,POSX+GAP*a+1,POSY+GAP*b+1);break;
		case 1:putImage(&img3,POSX+GAP*a+1,POSY+GAP*b+1);break;
		case 2:putImage(&img4,POSX+GAP*a+1,POSY+GAP*b+1);break;
	}
	endPaint();
	return;
}
int isfinished=0;

void put_mine_left(void)
{
	beginPaint();
	setPenColor(WHITE);
	setBrushColor(WHITE);
	rectangle(POSX+GAP*(NUM/2),POSY/2,POSX+GAP*NUM-2,POSY-2);
	
	setTextSize(24);
	
//	char str1[11]="Mine left:";
//	char *str2;
//	str2=(char*)malloc(30*sizeof(char));
//	strcpy(str2,strcat(str1,numstr(mine_left)));
//	if(mine_left>0)
//	{
//		beginPaint();
//		setTextColor(BLACK);
//		paintText(POSX+GAP*(NUM/2),POSY/2,&str2);
//		endPaint();
//		printf("%s\n",str2);
//	}
//	
	char* text_mine;
	text_mine=(char*)malloc(TIMES*sizeof(char));
	if(mine_left>=0)
	{
//		text_mine[0]=(char)(mine_left/10)+'0';
//		text_mine[1]=(char)(mine_left%10)+'0';
//		text_mine[2]=0;
		sprintf(text_mine,"%d",mine_left);
		setTextColor(BLACK);
		paintText(POSX+GAP*(NUM/2)-GAP/2,POSY/2,text_mine);
//		printf("%s\n",text_mine);
		
	}
	else
	{
		paintText(POSX+GAP*(NUM/2),POSY/2,"Check it again!");
	}
	free(text_mine);
	endPaint();
}

void mine_shown(void)
{
	for(int i=0; i<NUM; i++)
	{
		for(int j=0; j<NUM; j++)
		{	
			if(ismine[i][j]==-1)
			{
				
				beginPaint();
				loadImage("mine.jpg",&img1);
				putImage(&img1,POSX+GAP*i,POSY+GAP*j);
				endPaint();
			}
		}
	}
	
}

void EVENT1(int x,int y,int bt,int event)
{
	int a,b;
	a=(x-POSX)/GAP;
	b=(y-POSY)/GAP;
	
	if(isfinished)return;
	//timer
	
//	end=clock();
//	double time_last=(double)(end-start)/CLOCKS_PER_SEC;
//	beginPaint();
//	setPenColor(WHITE);
//	setBrushColor(WHITE);
//	rectangle(POSX+GAP*(NUM/2),0,POSX+GAP*NUM-2,POSY/2-1);
//	setTextSize(24);
//	char *str1="Time used:";
//	char *str2,*str3;
//	str2=(char*)malloc(TIMES*sizeof(char));
//	str3=(char*)malloc(TIMES*sizeof(char));
//	for(int i=0; i<TIMES; i++)
//	{
//		str2[i]=(char)((int)time_last)/(pow(10,TIMES-i-1))+'0';
//	}
//	char *str4=strcat(str1,str2);
//	printf("%s",str4);
//	endPaint();
	
	if(a<0||a>=NUM||b<0||b>=NUM)return;
	for(int i=0; i<=NUM; i++)
	{
		
		beginPaint();
		line(POSX+GAP*i,POSY,POSX+GAP*i,POSY+NUM*GAP);
		line(POSX,POSY+GAP*i,POSX+GAP*NUM,POSY+GAP*i);
		endPaint();
	}
	int left_sq=0;
	mine_left=numofmines;
	for(int i=0; i<NUM; i++)
	{
		for(int j=0; j<NUM; j++)
		{
			if(right_key[i][j]==1)
			{
				mine_left--;
				put_mine_left();
			}
			if(is_shown[i][j])
			{
				left_sq++;
			}
		}
	}
	put_mine_left();
	if((left_sq+numofmines)==NUM*NUM)
	{
		beginPaint();
		setTextSize(48);
		paintText(POSX,POSY+GAP*NUM/2,"You win!");
		isfinished=1;
		endPaint();
		return;
	}
	
	if(event==BUTTON_DOUBLECLICK&&bt==LEFT_BUTTON)
	{
//		printf("ok\n");		
		for(int i=a-1; i<=a+1; i++)
		{
			for(int j=b-1; j<=b+1; j++)
			{
				if(i<0||i>NUM||j<0||j>NUM)continue;
				if(i==a&&j==b)continue;
				if(right_key[i][j]==1)continue;
				if(ismine[i][j]==-1)
				{
					isfinished=1;
					beginPaint();
					setTextSize(48);
//					if(click_times==1)
//					{
//						paintText(POSX,POSY+GAP*NUM/2,"已触发非酋保护,程序即将重启");
//						TerminateProcess(GetCurrentProcess(), 0);
////						registerTimerEvent(resetup);
////						startTimer(timerID2,2000);
//						system("1.bat");
//					}
//					else
					paintText(POSX,POSY+GAP*NUM/2,"You failed!Try it again!");
					endPaint();
					mine_shown();
				}
				if(ismine[i][j]!=0)
				{
					beginPaint();
					loadImage("1.bmp",&img11);
					loadImage("2.bmp",&img12);
					loadImage("3.bmp",&img13);
					loadImage("4.bmp",&img14);
					loadImage("5.bmp",&img15);
					loadImage("6.bmp",&img16);
					loadImage("7.bmp",&img17);
					loadImage("8.bmp",&img18);
					loadImage("9.bmp",&img19);
					switch(ismine[i][j])
					{
						case 1:putImage(&img11,POSX+GAP*i,POSY+GAP*j);is_shown[i][j]=1;break;
						case 2:putImage(&img12,POSX+GAP*i,POSY+GAP*j);is_shown[i][j]=1;break;
						case 3:putImage(&img13,POSX+GAP*i,POSY+GAP*j);is_shown[i][j]=1;break;
						case 4:putImage(&img14,POSX+GAP*i,POSY+GAP*j);is_shown[i][j]=1;break;
						case 5:putImage(&img15,POSX+GAP*i,POSY+GAP*j);is_shown[i][j]=1;break;
						case 6:putImage(&img16,POSX+GAP*i,POSY+GAP*j);is_shown[i][j]=1;break;
						case 7:putImage(&img17,POSX+GAP*i,POSY+GAP*j);is_shown[i][j]=1;break;
						case 8:putImage(&img18,POSX+GAP*i,POSY+GAP*j);is_shown[i][j]=1;break;
						case 9:putImage(&img19,POSX+GAP*i,POSY+GAP*j);is_shown[i][j]=1;break;
					}
					endPaint();
				}
				if(ismine[i][j]==0)
				{
					find_zero(i,j);
				}
				if(ismine[i][j]==-1)continue;
			}
		}
	}
	
	
	
	if(event!=BUTTON_DOWN)return;
	if(bt==LEFT_BUTTON)
	{
//		click_times++;
		if(a>=0&&b>=0)
		{
			click_times++;
			if(ismine[a][b]==-1)
			{
				beginPaint();
				loadImage("mine.jpg",&img1);
				putImage(&img1,POSX+GAP*a,POSY+GAP*b);
				setTextSize(48);
				if(click_times==1)
					{
						paintText(POSX,POSY+GAP*NUM/2,"已触发非酋保护,程序即将重启");
//						
//						registerTimerEvent(resetup);
//						startTimer(timerID2,2000);
						system("1.bat");
						TerminateProcess(GetCurrentProcess(), 0);
					}
				else
				paintText(POSX,POSY+GAP*NUM/2,"You failed!Try it again!");
				
				endPaint();
				isfinished=1;
				mine_shown();
				return;
			}
			else
			{
				if(ismine[a][b]!=-1&&ismine[a][b]!=0)
				{
					beginPaint();
					loadImage("1.bmp",&img11);
					loadImage("2.bmp",&img12);
					loadImage("3.bmp",&img13);
					loadImage("4.bmp",&img14);
					loadImage("5.bmp",&img15);
					loadImage("6.bmp",&img16);
					loadImage("7.bmp",&img17);
					loadImage("8.bmp",&img18);
					loadImage("9.bmp",&img19);
					switch(ismine[a][b])
					{
						case 1:putImage(&img11,POSX+GAP*a+1,POSY+GAP*b+1);is_shown[a][b]=1;break;
						case 2:putImage(&img12,POSX+GAP*a+1,POSY+GAP*b+1);is_shown[a][b]=1;break;
						case 3:putImage(&img13,POSX+GAP*a+1,POSY+GAP*b+1);is_shown[a][b]=1;break;
						case 4:putImage(&img14,POSX+GAP*a+1,POSY+GAP*b+1);is_shown[a][b]=1;break;
						case 5:putImage(&img15,POSX+GAP*a+1,POSY+GAP*b+1);is_shown[a][b]=1;break;
						case 6:putImage(&img16,POSX+GAP*a+1,POSY+GAP*b+1);is_shown[a][b]=1;break;
						case 7:putImage(&img17,POSX+GAP*a+1,POSY+GAP*b+1);is_shown[a][b]=1;break;
						case 8:putImage(&img18,POSX+GAP*a+1,POSY+GAP*b+1);is_shown[a][b]=1;break;
						case 9:putImage(&img19,POSX+GAP*a+1,POSY+GAP*b+1);is_shown[a][b]=1;break;
					}
					endPaint();
				}
				if(ismine[a][b]==0)
				{
					find_zero(a,b);
//					for(int i=0; i<NUM; i++)
//					{
//						for(int j=0; j<NUM; j++)
//						{
//							printf("%d ",iszero[i][j]);
//						}
//						printf("\n");
//					}
				}
			}
		
			
		} 
	}

	if(bt==3)
	{
		calrightkey(a,b);
		rightkey(a,b);
	}
}



void Time_event(int timer1)
{
//	printf("timer reporting\n");
	if(isfinished)return;
	timer++;
	beginPaint();
	setPenColor(WHITE);
	setBrushColor(WHITE);
	rectangle(POSX+GAP*(NUM/2),1,POSX+GAP*NUM-2,POSY/2-1);
	setTextSize(24);
	setTextColor(BLACK);
	int temp1=timer;
	
//	int temp[TIMES];
	char str1[TIMES+1];
//	for(int i=0; temp1>0; i++)
//	{
//		temp[TIMES-i]=temp1%10;
//		temp1/=10;
//	}
//	for(int i=0; i<TIMES; i++)
//	{
//		str1[i]=(char)(temp[i]+'0');
//	}
//	str1[TIMES]='\0';
	sprintf(str1,"%d",timer);
	
	char str2[11]="Time used:";
	char *str3;
	str3=(char*)malloc((TIMES+12)*sizeof(char));
	strcpy(str3,str2);
	strcat(str3,str1);
//	printf("%d\n",timer);
//	printf("%s\n",str3);
	paintText(POSX+GAP*(NUM/2-2),1,str3);
	free(str3);
	endPaint();
}


//main
int Setup()
{
	initWindow("Minesweeper v1.0",DEFAULT,DEFAULT,720,720);
	for(int i=0; i<=NUM; i++)
	{
		beginPaint();
		line(POSX+GAP*i,POSY,POSX+GAP*i,POSY+NUM*GAP);
		line(POSX,POSY+GAP*i,POSX+GAP*NUM,POSY+GAP*i);
		endPaint();
	}
	
	numofmines=inputbox();
	while(numofmines<=0||numofmines>=NUM*NUM)
	{
		printf("The input data is illegal.Try it again.");
		numofmines=inputbox();
	}
	mine_left=numofmines;
	initConsole();
	beginPaint();
	loadImage("background.jpg",&img2);
	for(int i=0; i<NUM; i++)
	{
		for(int j=0; j<NUM; j++)
		{
			putImage(&img2,POSX+GAP*i+1,POSY+GAP*j+1);
		}
	}
	endPaint(); 
	int randnum=0;
	for(int i=0; i<numofmines; i++)
	{
		randoms:
		srand(i+randnum+time(NULL));
		int a=rand();
		a%=NUM;
		
		srand(3+i+time(NULL));
		int b=rand();
		b%=NUM;

		
		if(i==0)
		{
			ismine[a][b]=-1;//x//y	
		}
		else
		{
				if(ismine[a][b]!=-1)
				{
					ismine[a][b]=-1;
				}
				else 
				{
					randnum++;
					goto randoms;
				}
			
		}
//		printf("%d %d\n",a,b);
	}
//	printf("%d %d",a,b);
	

	for(int i=0; i<NUM; i++)
	{
		for(int j=0; j<NUM; j++)
		{
			if(ismine[i][j]==-1)
			{
				cal_mine(i-1,j-1);
				cal_mine(i-1,j);
				cal_mine(i-1,j+1);
				cal_mine(i,j-1);
				cal_mine(i,j+1);
				cal_mine(i+1,j-1);
				cal_mine(i+1,j);
				cal_mine(i+1,j+1);	
			}
			
		}
	}
	for(int i=0; i<NUM; i++)
	{
		for(int j=0; j<NUM; j++)
		{
			printf("%d ",ismine[j][i]);
		}
		printf("\n");
	}
//	ShowWindow(GetConsoleWindow(),SW_HIDE);
//	start=clock();
	startTimer(timerID1,1000);
	registerMouseEvent(EVENT1);
//	registerMouseEvent(testevent);
	registerTimerEvent(Time_event);

	return 0;
};
