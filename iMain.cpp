#include "iGraphics.h"
#include <iostream>
#include<bits/stdc++.h>
#include <windows.h>
#include <mmsystem.h>
using namespace std;
#pragma comment(lib, "Winmm.lib")

#define screenWidth 1200.00
#define screenHeight 800.00
#define black 0, 0, 0

/*
	function iDraw() is called again and again by the system.

*/

struct student
{
	char name[200],pass[200];
	int meal ;//35 per meal
	int laundry ;//30 per dress
	int total_cost = 35*meal+30*laundry;
};

vector<int> data;
double Mess_x = 300, Mess_y = 100;
int home_page = 0;
int Create_page = 0, Join_page = 0;
int wrMessname = 0, wrMessPass = 0;
char Mess_Name[100], Mess_pass[100];
int Mess_name_index = 0, Mess_pass_index = 0;
double wr_x = screenWidth / 2, wr_y = screenHeight / 2 + Mess_y * 1.7;
double wr_xpass = screenWidth / 2, wr_ypass = screenHeight / 2;
int Mess_page = 0;
double MessPage_x = screenWidth/50 ,MessPage_dy= screenHeight/10;
double MessPage_y = screenHeight - 2*MessPage_dy;//640
double total_cost = 0,laudry_cost = 0,meal_cost =0;
char tcoststr[100] = "123",lcoststr[100],tmcost[100];
int Student_page = 0;
int meal_order = 0,laundry_order = 0;
char meal_num[100] ="0" ,laundry_num[100] = "0",student_name[100]="Aritro";
char meal_cost_str[100] = "0",laundry_cost_str[100] ="0",total_cost_str[100]="0";
int draw_mem = 0,draw_man =0;
//for student_info_page
bool student_info_page = true;
int students_num = 1;
vector<student> students;
char *info_page[5] ={"Name","Meal order",
"Laundry order","Total cost","Password"};
int wrName=0,wrPass = 0,wridx;
int Nameidx = 0,Passidx =0;
char each_name[100],each_pass[100];



//int Join_page = 0;

void iDraw()
{
	// place your drawing codes here
	iClear();
	iSetColor(255, 255, 255);
	iFilledRectangle(0, 0, 1920, 1080);
	if (home_page)
	{
		iSetColor(black);
		iRectangle(450, 600, 300, 100);
		iText(480,650, "MESS MANAGEMENT", GLUT_BITMAP_TIMES_ROMAN_24);
		iRectangle(5100.00/11,300, 300, 500.00/11);
		iText(480, 310, "Create Mess", GLUT_BITMAP_TIMES_ROMAN_24);
		iRectangle(5100.00/11, 400, 300, 500.00/11);
		iText(480,410, "Join Mess", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if (Create_page)
	{

		iSetColor(black);
		iRectangle(450, 550, 450, 50); // upper big rectangle
		iText(450, 570, "Mess Name", GLUT_BITMAP_TIMES_ROMAN_24);
		iRectangle(450, 550, 150, 50);	// upper small rectangle
		iRectangle(450, 390, 450, 50); // lower big rectangle not whole
		iRectangle(450, 390, 150, 50);	// lower big rectangle
		iText(450, 400, "Password", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(605, 570, Mess_Name, GLUT_BITMAP_TIMES_ROMAN_24);								 // Mess name box text
		iRectangle(600, 300, 150, 50);			 // Enter button
		iText(600, 320, "Enter", GLUT_BITMAP_TIMES_ROMAN_24);		 // Enter text
		iText(605, 400, Mess_pass, GLUT_BITMAP_TIMES_ROMAN_24);						 // mess pass text box
		iRectangle(250, 220, 75, 100/2.3);		 // Back Button box
		iText(250, 230, "Back", GLUT_BITMAP_TIMES_ROMAN_24); // Back text box
		if (wrMessname)
		{
			iRectangle(605,555,290,40);
			//iText(wr_x, wr_y, Mess_Name, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		if (wrMessPass)
		{
			iRectangle(605,395,290,40);
			//iText(wr_xpass, wr_ypass, Mess_pass, GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}
	else if (Join_page)
	{
		iSetColor(black);
		iRectangle(450, 550, 450, 50); // upper big rectangle
		iText(450, 570, "Mess Name", GLUT_BITMAP_TIMES_ROMAN_24);
		iRectangle(450, 550, 150, 50);	// upper small rectangle
		//iRectangle(screenWidth / 2 - Mess_x / 2, screenHeight / 2 - Mess_y * .1, Mess_x * 1.5, Mess_y / 2); // lower big rectangle not whole
		//iRectangle(screenWidth / 2 - Mess_x / 2, screenHeight / 2 - Mess_y * .1, Mess_x / 2, Mess_y / 2);	// lower big rectangle
		//iText(screenWidth / 2 - Mess_x / 2, screenHeight / 2, "Password", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(605, 570, Mess_Name, GLUT_BITMAP_TIMES_ROMAN_24);								 // Mess name box text
		iRectangle(600, 300, Mess_x / 2, Mess_y / 2);			 // Join button
		iText(600, 320, "Join", GLUT_BITMAP_TIMES_ROMAN_24);		 // Join text
		iCircle(900, 400,13);//Member circle
		iCircle(450, 400,13);//Manager circle
		iText(465, 390, "Manager", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(915, 390,"Member",GLUT_BITMAP_TIMES_ROMAN_24);
		//iText(wr_xpass+5, wr_ypass, Mess_pass, GLUT_BITMAP_TIMES_ROMAN_24);						 // mess pass text box
		iRectangle(250, 220, 75, 100/ 2.3);		 // Back Button box
		iText(250, 230, "Back", GLUT_BITMAP_TIMES_ROMAN_24); // Back text box
		if (wrMessname )
		{
			iRectangle(605,555,290,40);
			//iText(wr_x, wr_y, Mess_Name, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		if(draw_mem )
		{
			iSetColor(black);
			iFilledCircle(900, 400,10);//Member circle	
		}
		if(draw_man )
		{
			iSetColor(black);
			iFilledCircle(450,400,10);//Manager circle
	
		}
		
	}
	else if(Mess_page)
	{
		iSetColor(black);
		//For Mess name
		iRectangle(300,730,400,40);
		iRectangle(295,725,410,50);
		//strcat(Mess_Name," Mess");
		iText(310,740,Mess_Name,GLUT_BITMAP_TIMES_ROMAN_24);
		//For Meal order box
		iRectangle(24,640,200,200.00/3);
		iRectangle(24,640,1000,200.00/3);
		iRectangle(29,645,990,170.00/3);
		iText(1087/3,650,"COST = ",GLUT_BITMAP_HELVETICA_18);
		iRectangle(24,640,500,200.00/3);
		iRectangle(29,645,490,170.0/3);
		iRectangle(29,645,190,170.0/3);
		iText(34,670,"MEAL\n OREDERS",GLUT_BITMAP_HELVETICA_18);
		//For Laundry order box
		iRectangle(24,1720.0/3,200,200.0/3);
		iRectangle(24,1720.0/3,1000,200.0/3);
		iRectangle(29,1735.0/3,990,170.0/3);
		iRectangle(24,1720.0/3,500,200.0/3);
		iRectangle(29,1735.0/3,490,170.0/3);
		iText(529,1750.0/3,"COST = ",GLUT_BITMAP_HELVETICA_18);
		iRectangle(29,1735.0/3,190,170.0/3);
		iText(34,1825.0/3,"LAUNDRY\n OREDERS",GLUT_BITMAP_HELVETICA_18);
		//For Total cost box;
		iRectangle(24,1520.0/3,200,200.0/3);
		iRectangle(29,1535.0/3,190,170.0/3);
		iRectangle(24,1520.0/3,1000,200.0/3);
		iRectangle(29,1535.0/3,990,170.0/3);
		iText(229,MessPage_y-2*screenHeight/12+20,tcoststr,GLUT_BITMAP_HELVETICA_18);
		iText(34,MessPage_y+35-2*screenHeight/12,"TOTAL COST",GLUT_BITMAP_HELVETICA_18);
		//For Total students
		iRectangle(24,440,200,200.0/3);
		iRectangle(29,445,190,170.0/3);
		iRectangle(24,440,1000,200.0/3);
		iRectangle(29,445,990,170.0/3);
		iText(229,460,tcoststr,GLUT_BITMAP_HELVETICA_18);
		iText(34,475,"TOTAL STUDENTS",GLUT_BITMAP_HELVETICA_18);
		//For students info
		iRectangle(24,1120.0/3,200,200.0/3);
		iRectangle(29,1135.0/3,190,170.0/3);
		iText(34,1225.0/3,"STUDENTS INFO",GLUT_BITMAP_HELVETICA_18);
		
		//MessPage_y -= MessPage_dy;
	
	}
	else if(Student_page)
	{
		iSetColor(black);
		//For Student name
		iRectangle(34,590,200,200.0/3);
		iRectangle(39,MessPage_y-45,190,170.0/3);
		iText(44,600,"Name",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(244,600,student_name,GLUT_BITMAP_TIMES_ROMAN_24);
		iRectangle(34,590,800,200.0/3);
		iRectangle(234,590,800,200.0/3);
		iRectangle(239,595,590,170.0/3);
		//iRectangle(MessPage_x+15+screenWidth/1.5,MessPage_y-45,screenWidth/6-10,screenHeight/12-10); Use it for Change box
		iText(849,605,"Change",GLUT_BITMAP_TIMES_ROMAN_24);

		//For Meal order
		iRectangle(MessPage_x+10,MessPage_y-50-screenHeight/12,screenWidth/6,screenHeight/12);
		iRectangle(MessPage_x+15,MessPage_y-45-screenHeight/12,screenWidth/6-10,screenHeight/12-10);
		iText(MessPage_x+20,MessPage_y-40-screenHeight/12,"Meal Order",GLUT_BITMAP_TIMES_ROMAN_24);
		iRectangle(MessPage_x+10,MessPage_y-50-screenHeight/12,screenWidth/1.5,screenHeight/12);
		iRectangle(MessPage_x+10+screenWidth/1.5,MessPage_y-50-screenHeight/12,screenWidth/6,screenHeight/12);
		iRectangle(MessPage_x+10+screenWidth/6,MessPage_y-50-screenHeight/12,screenWidth/1.5,screenHeight/12);
		iRectangle(MessPage_x+15+screenWidth/6,MessPage_y-45-screenHeight/12,screenWidth/1.5-screenWidth/6-10,screenHeight/12-10);
		iText(MessPage_x+20+screenWidth/6,MessPage_y-40-screenHeight/12,meal_num,GLUT_BITMAP_TIMES_ROMAN_24);
		//For laundry order
		iRectangle(MessPage_x+10,MessPage_y-50-2*screenHeight/12,screenWidth/6,screenHeight/12);
		iRectangle(MessPage_x+15,MessPage_y-45-2*screenHeight/12,screenWidth/6-10,screenHeight/12-10);
		iText(MessPage_x+20,MessPage_y-40-2*screenHeight/12,"Laundry Order",GLUT_BITMAP_TIMES_ROMAN_24);
		iRectangle(MessPage_x+10,MessPage_y-50-2*screenHeight/12,screenWidth/1.5,screenHeight/12);
		iRectangle(MessPage_x+10+screenWidth/1.5,MessPage_y-50-2*screenHeight/12,screenWidth/6,screenHeight/12);
		iRectangle(MessPage_x+10+screenWidth/6,MessPage_y-50-2*screenHeight/12,screenWidth/1.5,screenHeight/12);
		iRectangle(MessPage_x+15+screenWidth/6,MessPage_y-45-2*screenHeight/12,screenWidth/1.5-screenWidth/6-10,screenHeight/12-10);
		iText(MessPage_x+20+screenWidth/6,MessPage_y-40-2*screenHeight/12,laundry_num,GLUT_BITMAP_TIMES_ROMAN_24);
		//For Password 
		iRectangle(MessPage_x+10,MessPage_y-50-3*screenHeight/12,screenWidth/6,screenHeight/12);
		iRectangle(MessPage_x+15,MessPage_y-45-3*screenHeight/12,screenWidth/6-10,screenHeight/12-10);
		iText(MessPage_x+20,MessPage_y-40-3*screenHeight/12,"Password",GLUT_BITMAP_TIMES_ROMAN_24);
		iRectangle(MessPage_x+10,MessPage_y-50-3*screenHeight/12,screenWidth/1.5,screenHeight/12);
		iRectangle(MessPage_x+10+screenWidth/1.5,MessPage_y-50-3*screenHeight/12,screenWidth/6,screenHeight/12);
		iRectangle(MessPage_x+10+screenWidth/6,MessPage_y-50-3*screenHeight/12,screenWidth/1.5,screenHeight/12);
		iRectangle(MessPage_x+15+screenWidth/6,MessPage_y-45-3*screenHeight/12,screenWidth/1.5-screenWidth/6-10,screenHeight/12-10);
		iText(MessPage_x+25+screenWidth/1.5,MessPage_y-35-3*screenHeight/12,"Change",GLUT_BITMAP_TIMES_ROMAN_24);
		//iRectangle(MessPage_x+15+screenWidth/1.5,MessPage_y-45-3*screenHeight/12,screenWidth/6-10,screenHeight/12-10); //Use it for Change box

		iRectangle(400,screenHeight/2-200,400,100);
		iRectangle(400,screenHeight/2-200,400,50);
		iRectangle(400,screenHeight/2-150,150,50);
		iRectangle(400,screenHeight/2-200,150,50);
		iText(410,screenHeight/2-140,"Meal cost",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(560,screenHeight/2-140,meal_cost_str,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(410,screenHeight/2-190,"Laundry cost",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(560,screenHeight/2-190,laundry_cost_str,GLUT_BITMAP_TIMES_ROMAN_24);
		iRectangle(800,screenHeight/2-200,200,100);
		iText(820,screenHeight/2-150,total_cost_str,GLUT_BITMAP_TIMES_ROMAN_24);


	}
	else if (student_info_page)
	{
		iSetColor(black);
		iRectangle(50,700,100,60);
		iText(60,720,"Add",GLUT_BITMAP_TIMES_ROMAN_24);
		for(int i=0;i<5;i++)
		{
			iRectangle(150+i*200,700,200,60);
			iText(160+i*200,710,
			info_page[i],GLUT_BITMAP_TIMES_ROMAN_24);
		}
		for(int i=0;i<students_num;i++)
		{
			for(int j=0;j<5;j++)
			{
				if(j==0)
				{
				//iText(150+j*200,700-60*i,
				//students[i].name,
				//GLUT_BITMAP_TIMES_ROMAN_24);
				}
				else if(j==4)
				{
				//iText(150+j*200,700-60*i,
				//students[i].pass,
				//GLUT_BITMAP_TIMES_ROMAN_24);
				}
				iRectangle(150+j*200,700-60*i,200,60);
			}
		}
		if(wrName)
		{
			iText(160,710-60*wridx,each_name,
			GLUT_BITMAP_TIMES_ROMAN_24);
			iRectangle(155,705-60*wridx,190,50);
		}
		if(wrPass)
		{
			iText(960,710-60*wridx,each_pass,
			GLUT_BITMAP_TIMES_ROMAN_24);
			iRectangle(955,705-60*wridx,190,50);
		}
	}
	
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my)
{

	// place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && home_page)
	{
		if (mx >= 5100.0/11 && mx <= 8400.00/11 && my >= 300 &&
			my <= 3800.0/11) // Create mess
		{
		
			home_page = 0;
			Create_page = 1;
		}
		if (mx >= 5100.0/11 && mx <= 8400.0/11 &&
			my >= 400 && my <= 4900.0/11) // join mess
		{
			home_page = 0;
			Join_page = 1;
		}
	}
	//CREATE PAGE
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && Create_page)
	{
		if (mx <= (900) && mx >= 600 &&
			my >= (550) && my <= (600)) // writing mess name
		{
			wrMessname = 1;
			wrMessPass = 0;
		} 
		if (mx >= 450 && mx <= 900 &&
		 my >= 390 && my <= 440) // writing mess Password
		{
			wrMessPass = 1;
			wrMessname = 0;
		} 
		if (mx >= (600) && mx <= 750 &&
		 my >= screenHeight / 2 - 100 && my <= screenHeight / 2 - 100 + Mess_y / 2) // For Enter button
		{
			Create_page = 0;
			wrMessname = 0;
			wrMessname = 0;
			Mess_page = 1;
		}
		else if (mx >= (screenWidth / 4) - 50 && mx <= (screenWidth / 4) - 50 + Mess_x / 4 
		&& my >= screenHeight / 2 - 180 && my <= screenHeight / 2 - 180 + Mess_y / 2) // for back button
		{
			Create_page = 0, wrMessname = 0, wrMessname = 0;
			Mess_name_index = 0;
			Mess_pass_index = 0;
			Mess_Name[Mess_name_index] = '\0';
			Mess_pass[Mess_pass_index] = '\0';
			home_page =1;
			Mess_page = 0;
		}
	}
	//JOIN PAGE
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && Join_page)
	{
		if (mx <= (900) && mx >= 600 &&
			my >= (550) && my <= (600)) // writing mess name
		{
			wrMessname = 1;
			//wrMessPass = 0;
		}
		
		else if((mx-900)
		*(mx-900)
		+ (my-400)*(my-400)<= 169)
		{
			draw_mem = 1;
			//cout<<"ok"<<endl;
			draw_man =0;
		}
		else if((mx-450)
		*(mx-450)
		+ (my-400)*(my-400)<= 169)
		{
			//cout<<"OK"<<endl;
			draw_man =1;
			draw_mem =0;
		}
		else if (mx >= 600 && mx <= 750 &&
		 my >= 300 && my <= 350) // For Enter button
		{
			Join_page = 0;
			wrMessname = 0;
			wrMessname = 0;
			Student_page = 1;
		}
		else if (mx >= (screenWidth / 4) - 50 && mx <= (screenWidth / 4) - 50 + Mess_x / 4 && 
		my >= screenHeight / 2 - 180 && my <= screenHeight / 2 - 180 + Mess_y / 2) // for back button
		{
			Join_page = 0, wrMessname = 0, wrMessname = 0;
			Mess_name_index = 0;
			Mess_pass_index = 0;
			Mess_Name[Mess_name_index] = '\0';
			Mess_pass[Mess_pass_index] = '\0';

			home_page = 1;
		}
	}
	//Student_info_page;
	else if(button == GLUT_LEFT_BUTTON && 
	state == GLUT_DOWN && student_info_page)
	{
		if(mx>=50&& mx<=150 &&
		my>=700 && my<=760)//Add
		{
			
			students_num+=1;
			//students.push_back(s1);
		}
		for(int i=1;i<students_num;i++)
		{
			if(mx>=150&& mx<=350 && my>=700-60*i
			&& my<=760 -60*i)
			{
				wridx = i;
				wrName =1;
				wrPass = 0;
			}
			else if(mx>=950&& mx<=1150
			&& my>= 700 -60*i && my<= 760 -60*i)
			{
				wridx = i;
				wrName =0;
				wrPass = 1;
			}
		}
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key)
{
	if (Create_page)
	{
		if (wrMessname)

		{
			if (key != '\b')
			{
				Mess_Name[Mess_name_index] = key;
				Mess_name_index++;
				Mess_Name[Mess_name_index] = '\0';
			}
			else
			{
				Mess_name_index -= 1;
				if (Mess_name_index <= 0)
				{
					Mess_name_index = 0;
				}
				Mess_Name[Mess_name_index] = '\0';
			}
		}
		if (wrMessPass)
		{
			if (key != '\b')
			{
				Mess_pass[Mess_pass_index] = key;
				Mess_pass_index++;
				Mess_pass[Mess_pass_index] = '\0';
			}
			else
			{
				Mess_pass_index -= 1;
				if (Mess_pass_index <= 0)
				{
					Mess_pass_index = 0;
				}
				Mess_pass[Mess_pass_index] = '\0';
			}
		}
	}
	else if (Join_page)
	{
		if (wrMessname)

		{
			if (key != '\b')
			{
				Mess_Name[Mess_name_index] = key;
				Mess_name_index++;
				Mess_Name[Mess_name_index] = '\0';
			}
			else
			{
				Mess_name_index -= 1;
				if (Mess_name_index <= 0)
				{
					Mess_name_index = 0;
				}
				Mess_Name[Mess_name_index] = '\0';
			}
		}
		
		else if (wrMessPass)
		{
			if (key != '\b')
			{
				Mess_pass[Mess_pass_index] = key;
				Mess_pass_index++;
				Mess_pass[Mess_pass_index] = '\0';
			}
			else
			{
				Mess_pass_index -= 1;
				if (Mess_pass_index <= 0)
				{
					Mess_pass_index = 0;
				}
				Mess_pass[Mess_pass_index] = '\0';
			}
		}
	}
	else if(student_info_page)
	{
		if(wrName)
		{
			if(key!='\b')
			{
				each_name[Nameidx] = key;
				Nameidx++;
				each_name[Nameidx] = '\0';
			}
			else
			{
				Nameidx-=1;
				if(Nameidx<=0){Nameidx =0;}
				each_name[Nameidx] ='\0';
			}
			
		}
		if(wrPass)
		{
			if(key!='\b')
			{
				each_pass[Passidx] = key;
				Passidx++;
				each_pass[Passidx] = '\0';
			}
			else
			{
				Passidx-=1;
				if(Passidx<=0){Passidx =0;}
				each_pass[Passidx] ='\0';
			}
			
		}
	}
	// place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_LEFT)
	{
	}
	else if (key == GLUT_KEY_RIGHT)
	{
	}

	// place your codes for other keys here
}

int main()
{
	// place your own initialization codes here.
	
	iInitialize(screenWidth, screenHeight, "demo");
	return 0;
}
