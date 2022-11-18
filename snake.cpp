#include <cstdlib>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <time.h>
#include <ctime>
#include <cctype>
#include <cmath>
#include <ldata.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include "word.h"

#define EXCLUDE_LEDIT_LEGACY_UPI

#define up 1
#define down 2
#define left 3
#define right 4

using namespace std;

extern "C" {
	void snake_game(void);
	int UPI_Entry_Point(void);
	void snake_gen(vector<vector<int> >);
	void start(void);
	void run_up(void);
	void run_down(void);
	void run_left(void);
	void run_right(void);
	void delete_snake(void);
	void food_generate(void);
	void snake_dead_check(vector<vector<int> >);
	void bomb_generate();
}


 vector<vector<int> > snake;
 vector<int> snake_temp;
 vector<vector<int> > bomb;
 vector<int> bomb_temp;
 LPoint bomb_center;

typedef struct snake_heada
{
	int x;
	int y;
}snake_head ;

snake_head head;
int direction = left;
int ax,bx;
int ay,by;
int score;
char score_char[20];

long scal2 = 1000;

void start(void)
{
	LCell Cell_Now = LCell_GetVisible();
	LFile File_Now = LCell_GetFile(Cell_Now);
	LLayer Layer_1 = LLayer_Find(File_Now,"1");
	LLayer Layer_2 = LLayer_Find(File_Now,"2");
	LLayer Layer_3 = LLayer_Find(File_Now,"3");
	LLayer Layer_4 = LLayer_Find(File_Now,"4");
	LLayer Layer_5 = LLayer_Find(File_Now,"5");
	LLayer Layer_10 = LLayer_Find(File_Now,"10");
	
	for(LObject temp=LObject_GetList( Cell_Now, Layer_1);temp!=NULL; temp=LObject_GetNext(temp)){LObject_Delete( Cell_Now, temp);}
	for(LObject temp=LObject_GetList( Cell_Now, Layer_2);temp!=NULL; temp=LObject_GetNext(temp)){LObject_Delete( Cell_Now, temp);}
	for(LObject temp=LObject_GetList( Cell_Now, Layer_10);temp!=NULL; temp=LObject_GetNext(temp)){LObject_Delete( Cell_Now, temp);}
	for(LObject temp=LObject_GetList( Cell_Now, Layer_3);temp!=NULL; temp=LObject_GetNext(temp)){LObject_Delete( Cell_Now, temp);}
	for(LObject temp=LObject_GetList( Cell_Now, Layer_4);temp!=NULL; temp=LObject_GetNext(temp)){LObject_Delete( Cell_Now, temp);}
	for(LObject temp=LObject_GetList( Cell_Now, Layer_5);temp!=NULL; temp=LObject_GetNext(temp)){LObject_Delete( Cell_Now, temp);}
	snake.clear();
	bomb.clear();

	LPoint point_arr[30];
	score=1;

	long x0=-11*scal2*1000;
	long y0=10*scal2*1000;
	long x1=11*scal2*1000;
	long y1=11*scal2*1000;
	
	long x2=10*scal2*1000;
	long y2=-10*scal2*1000;
	long x3=11*scal2*1000;
	long y3=10*scal2*1000;

	long x4=-11*scal2*1000;
	long y4=-11*scal2*1000;
	long x5=11*scal2*1000;
	long y5=-10*scal2*1000;	
	
	long x6=-11*scal2*1000;
	long y6=-10*scal2*1000;
	long x7=-10*scal2*1000;
	long y7=10*scal2*1000;
	
	
	char your_secore_char[13]="your score:";
	SetScal(50);
	Mark(your_secore_char,15000000,2000000,"5");
	
	//LCircle_New( Cell_Now, Layer_1, LPoint center, LCoord radius );

	LBox_New( Cell_Now, Layer_2, x0, y0, x1, y1 );
	LBox_New( Cell_Now, Layer_2, x2, y2, x3, y3 );
	LBox_New( Cell_Now, Layer_2, x4, y4, x5, y5 );
	LBox_New( Cell_Now, Layer_2, x6, y6, x7, y7 );
	LCell_HomeView( Cell_Now );
}


void snake_game(void)
{
	start();
	snake_temp.push_back(0);
	snake_temp.push_back(0);
	head.x=0;
	head.y=0;
	snake_temp[0]=0;
	snake_temp[1]=0;
	snake.push_back(snake_temp);
	snake_temp.clear();
	
	snake_temp[0]=1;
	snake_temp[1]=0;
	snake.push_back(snake_temp);
	snake_temp.clear();
	
	snake_gen(snake);
	
	food_generate();
	
	
}
void snake_gen(vector<vector<int> >snk )
{
	LCell Cell_Now = LCell_GetVisible();
	LFile File_Now = LCell_GetFile(Cell_Now);
	LLayer Layer_1 = LLayer_Find(File_Now,"1");
	LLayer Layer_2 = LLayer_Find(File_Now,"2");
	LLayer Layer_3 = LLayer_Find(File_Now,"3");
	LLayer Layer_4 = LLayer_Find(File_Now,"4");
	LLayer Layer_5 = LLayer_Find(File_Now,"5");
	int i;
	for(i=0;i<snk.size();i++)
	{
		LBox_New( Cell_Now, Layer_1, (snk[i][0]*10-5)*scal2*50, (snk[i][1]*10-5)*scal2*50, (snk[i][0]*10+5)*scal2*50, (snk[i][1]*10+5)*scal2*50 );
	}
	LDisplay_Refresh();
}

void run_up()
{	
	if(direction!=down)
	{
		delete_snake();
		
		direction=up;
		
		head.y++;
		
		snake_temp.push_back(head.x);
		snake_temp.push_back(head.y);
		snake.insert(snake.begin(),snake_temp);
		snake_temp.clear();
		
		if((head.x!=ax)||(head.y!=ay)){snake.pop_back();}
		else {food_generate();}
		snake_gen(snake);
	
		snake_dead_check(snake);
		LDisplay_Refresh();
	}
	
}

void run_left()
{	
	if(direction!=right)
	{
		delete_snake();
		
		
		head.x--;
		snake_temp.push_back(head.x);
		snake_temp.push_back(head.y);
		snake.insert(snake.begin(),snake_temp);
		snake_temp.clear();
		
		if((head.x!=ax)||(head.y!=ay)){snake.pop_back();}
		else {food_generate();}
		
		snake_gen(snake);
		direction=left;

		snake_dead_check(snake);
		LDisplay_Refresh();
	}
	
}
void run_right()
{	
	if(direction!=left)
	{
		delete_snake();
		
		
		head.x++;
		snake_temp.push_back(head.x);
		snake_temp.push_back(head.y);
		snake.insert(snake.begin(),snake_temp);
		snake_temp.clear();
		
		if((head.x!=ax)||(head.y!=ay)){snake.pop_back();}
		else {food_generate();}
		snake_gen(snake);
	
		direction=right;

		snake_dead_check(snake);
		LDisplay_Refresh();
	}
	
}

void run_down()
{	
	if(direction!=up)
	{
		delete_snake();
		
		head.y--;
		snake_temp.push_back(head.x);
		snake_temp.push_back(head.y);
		snake.insert(snake.begin(),snake_temp);
		snake_temp.clear();
		
		if((head.x!=ax)||(head.y!=ay)){snake.pop_back();}
		else {food_generate();}
		snake_gen(snake);
	
		direction=down;

		snake_dead_check(snake);
		
		LDisplay_Refresh();
	}
	
}

void delete_snake(void)
{
	LCell Cell_Now = LCell_GetVisible();
	LFile File_Now = LCell_GetFile(Cell_Now);
	LLayer Layer_1 = LLayer_Find(File_Now,"1");
	for(LObject temp=LObject_GetList( Cell_Now, Layer_1);temp!=NULL; temp=LObject_GetNext(temp))
	{
		LObject_Delete( Cell_Now, temp );
	}
}

void food_generate(void)
{
	LCell Cell_Now = LCell_GetVisible();
	LFile File_Now = LCell_GetFile(Cell_Now);
	LLayer Layer_3 = LLayer_Find(File_Now,"3");
	LLayer Layer_4 = LLayer_Find(File_Now,"4");
	
	bool x_flag=0;
	int i;
	score++;
	itoa(score,score_char,10);
	SetScal(50);
	
	
	for(LObject temp=LObject_GetList( Cell_Now, Layer_4);temp!=NULL; temp=LObject_GetNext(temp)){LObject_Delete( Cell_Now, temp );}
	Mark(score_char,15000000,0,"4");
	while(1)
	{
		ax = 19-rand()%38;
		ay = 19-rand()%38;
		
		if((ax!=head.x)&&(ay!=head.y))
		{break;}
	}
	
	
	for(LObject temp=LObject_GetList( Cell_Now, Layer_3);temp!=NULL; temp=LObject_GetNext(temp))
	{
		LObject_Delete( Cell_Now, temp );
	}
	LBox_New( Cell_Now, Layer_3, (ax*10-5)*scal2*50, (ay*10-5)*scal2*50,(ax*10+5)*scal2*50,(ay*10+5)*scal2*50);
	
	for(i=0;i<score;i++)
	{
		bomb_generate();
	}
	
}

void snake_dead_check(vector<vector<int> >snk)
{
	int i,j;
	if((head.x>19)||(head.x<-19)||(head.y>19)||(head.y<-19))
	{
		LDialog_MsgBox(LFormat("game over1"));
		LDialog_MsgBox(LFormat("your score:%d",score));
		delete_snake();
		snake.clear();
	}
	for(i=1;i<snk.size();i++)
	{
		if((head.x==snk[i][0])&&(head.y==snk[i][1]))
		{
			LDialog_MsgBox(LFormat("game over2"));
			LDialog_MsgBox(LFormat("your score:%d",score));
			delete_snake();
			snake.clear();
			break;
		}
	}
	for(j=0;j<bomb.size();j++)
	{
		if((head.x==bomb[j][0])&&(head.y==bomb[j][1]))
		{
			LDialog_MsgBox(LFormat("game over2"));
			LDialog_MsgBox(LFormat("your score:%d",score));
			delete_snake();
			snake.clear();
			break;
		}
	}
}


void bomb_generate()
{
	LCell Cell_Now = LCell_GetVisible();
	LFile File_Now = LCell_GetFile(Cell_Now);
	LLayer Layer_10 = LLayer_Find(File_Now,"10");
	
	int i = 0;
	int j = 0;
	bool boom_flag;
	while(1)
	{
		boom_flag = 0;
		bx = 19-rand()%38;
		by = 19-rand()%38;
		
		for(j=0;j<bomb.size();j++)
		{
			if(((bomb[j][0]==bx)&&(bomb[j][1]==by))||((bx==ax)&&(by==ay)))
			{
				boom_flag=1;
				break;
			}
		}
		
		if(boom_flag==0)
		{break;}
	}
	
	bomb_center.x=bx*scal2*500;
	bomb_center.y=by*scal2*500;
	LCircle_New(Cell_Now, Layer_10, bomb_center, scal2*250);
	
	bomb_temp.push_back(bx);
	bomb_temp.push_back(by);
	bomb.push_back(bomb_temp);
	bomb_temp.clear();
	
}
int UPI_Entry_Point(void)
{
	LMacro_BindToMenuAndHotKey_v9_30("Tools", "Num 1" , "snake_game", "snake_game", NULL);
	LMacro_BindToMenuAndHotKey_v9_30("Tools", "Num 8" , "run_up", "run_up", NULL);
	LMacro_BindToMenuAndHotKey_v9_30("Tools", "Num 5" , "run_down", "run_down", NULL);
	LMacro_BindToMenuAndHotKey_v9_30("Tools", "Num 4" , "run_left", "run_left", NULL);
	LMacro_BindToMenuAndHotKey_v9_30("Tools", "Num 6" , "run_right", "run_right", NULL);
//	return 1;
}

//	LDialog_MsgBox(LFormat("game over"));