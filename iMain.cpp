#include "iGraphics.h"
#include <iostream>
#include<bits/stdc++.h>
#include <windows.h>
#include <mmsystem.h>
#include<stdlib.h>
using namespace std;
#pragma comment(lib, "Winmm.lib")

#define screenWidth 1200.00
#define screenHeight 800.00
#define black 0, 0, 0
#define white 255, 255, 255
#define blue 0, 0, 255
#define red 255, 0,0
#define dodger_blue 30,144,255
#define violet 238,130,238
#define antique_white 250,235,215
#define indigo 75,0,130
#define yellow 255,255,0
/*
	function iDraw() is called again and again by the system.

*/

typedef struct student
{
	char name[200],pass[200];
	int meal ;//35 per meal
	int laundry ;//30 per dress
	int total = 35*meal+30*laundry;
};






//double Mess_x = 300, Mess_y = 100;
int home_page = 1;
int Create_page = 0, Join_page = 0;
int wrMessname = 0, wrMessPass = 0,wrInvalid =0;
int wrInvalidUser = 0;

char Mess_Name[100], Mess_pass[100];
int Mess_name_index = 0, Mess_pass_index = 0;
int invalid_option = 0;
//for mess page
char fname[200],freq[200] ;//mess file name
FILE * fptr;FILE *fptr2;//for opening  and reading mess file
//double wr_x = screenWidth / 2, wr_y = screenHeight / 2 + Mess_y * 1.7;
//double wr_xpass = screenWidth / 2, wr_ypass = screenHeight / 2;
int Mess_page = 0;
//double MessPage_x = screenWidth/50 ,MessPage_dy= screenHeight/10;
//double MessPage_y = screenHeight - 2*MessPage_dy;//640

//Login or request page
int req_log_page = 0,sname_index = 0 ,spass_index = 0;
student s1 ={"","",0,0,0};
int write_sname = 0,write_spass = 0,check = 0;
int req =0,wrong_pass =0;
char check_name[100],check_pass[100],manager_pass[100];
char req_content[100];
student requests[500];int reqidx =0,req_page = 0;
char num[100];//for index meal,laundry total cost;
int selectidx = -1;
//for scrolling 
double starty = 0,dy =0,endy =0;


double total_cost = 0,laudry_cost = 0,meal_cost =0;
char tcoststr[100] = "123",lcoststr[100],tmcost[100];
int Student_page = 0;
int meal_order = 0,laundry_order = 0;
char meal_num[100] ="0" ,laundry_num[100] = "0",student_name[100]="Aritro";
char meal_cost_str[100] = "0",laundry_cost_str[100] ="0",total_cost_str[100]="0";
int draw_mem = 0,draw_man =0;
//for student_info_page
int student_info_page = 0;
int students_num = 1;
student Students[500];
char *info_page[5] ={"Name","Meal order",
"Laundry order","Total cost","Password"};
int wrName = 0,wrPass = 0,wridx ;
int Nameidx = 0,Passidx =0;
char each_name[100],each_pass[100];


void delete_line(int index,char *filename)
{
    char tempfile[100]="temp__",buffer[100];
    strcat(tempfile,filename);
    FILE *fptr1=fopen(filename,"r");
    FILE *temp1 = fopen(tempfile,"w");
    int i = 0;
    while(fgets(buffer,100,fptr))
    {
        if(i!=index)
        {
            fputs(buffer,temp1);
			//sscanf(buffer,"%s %[^\n]s",requests[j].pass
			//,requests[j].pass);
			//j+=1;
        }
		//else{j+=1;}
        i+=1;
    }
	//reqidx = j;
    fclose(fptr1);
    fclose(temp1);
    remove(filename);
    rename(tempfile,filename);
}
void set_requests()
{
	FILE *fptr3;
	strcpy(freq,Mess_Name);
	strcat(freq,"_req.txt");
	delete_line(selectidx,freq);
	//set_requests();
	reqidx =0;
	fptr3 = fopen(freq,"r");
	while(fgets(req_content,100,fptr3))
	{	
		sscanf(req_content,"%s %[^\n]s",
		requests[reqidx].pass
		,requests[reqidx].name);
		requests[reqidx].meal = 0;
		requests[reqidx].laundry = 0;
		requests[reqidx].total = 0;
		//printf("%s\n",requets[reqidx].name);
		reqidx++;
	}
	fclose(fptr3);
}

//int Join_page = 0;

void iDraw()
{
	// place your drawing codes here
	iClear();
	iSetColor(antique_white);
	iFilledRectangle(0, 0, 1920, 1080);
	if (home_page)
	{
		iSetColor(black);
		iRectangle(450, 600, 300, 100);
		iSetColor(dodger_blue);
		iFilledRectangle(450, 600, 300, 100);
		iRectangle(455, 605, 290, 90);
		iSetColor(blue);
		iFilledRectangle(455, 605, 290, 90);
		iSetColor(white);
		iText(480,650, "MESS MANAGEMENT", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(dodger_blue);
		iFilledRectangle(458.63,295, 310, 55.45);
		iSetColor(blue);
		iFilledRectangle(5100.00/11,300, 300, 500.00/11);
		iSetColor(white);
		iText(550, 310, "Create Mess", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(dodger_blue);
		iFilledRectangle(458.63, 395, 310, 55.45);
		iSetColor(blue);
		iFilledRectangle(5100.00/11, 400, 300, 500.00/11);
		iSetColor(white);
		iText(550,410, "Join Mess", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if (Create_page)
	{

		iSetColor(indigo);
		iFilledRectangle(450, 550, 150, 50); // upper small rectangle
		iSetColor(yellow);
		iText(450, 570, "Mess Name", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(indigo);
		iRectangle(600, 550, 450, 50);// upper 2nd big rectangle
		//iSetColor(black);
		iText(605, 570, Mess_Name, GLUT_BITMAP_TIMES_ROMAN_24);
		//iSetColor(indigo);
		iFilledRectangle(450, 390, 150, 50);// lower big rectangle
		iSetColor(yellow);
		iText(450, 400, "Password", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(indigo);
		iText(605, 400, Mess_pass, GLUT_BITMAP_TIMES_ROMAN_24);
		iRectangle(600, 390, 450, 50); // lower big rectangle not whole
		
		iFilledRectangle(600, 300, 150, 50);// Enter button
		iSetColor(yellow);
		iText(600, 320, "Enter", GLUT_BITMAP_TIMES_ROMAN_24);// Enter text
		iSetColor(indigo);
		iFilledRectangle(250, 220, 75, 100/2.3);// Back Button box
		iSetColor(yellow);
		iText(250, 230, "Back", GLUT_BITMAP_TIMES_ROMAN_24); // Back text box
		if (wrMessname)
		{
			iSetColor(indigo);
			iRectangle(605,555,440,40);
			//iText(wr_x, wr_y, Mess_Name, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		if (wrMessPass)
		{
			iSetColor(indigo);
			iRectangle(605,395,440,40);
			//iText(wr_xpass, wr_ypass, Mess_pass, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		if(wrInvalid)
		{
			iSetColor(indigo);
			iText(600,400,"INVALID PASSWORD",
			GLUT_BITMAP_TIMES_ROMAN_24);
			iText(600,560,"INVALID USERNAME",
			GLUT_BITMAP_TIMES_ROMAN_24);
		}
		if(wrInvalidUser)
		{
			iSetColor(indigo);
			iText(600,560,"USERNAME Already taken",
			GLUT_BITMAP_TIMES_ROMAN_24);
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
		iRectangle(600, 300, 150, 50);			 // Join button
		iText(600, 320, "Join", GLUT_BITMAP_TIMES_ROMAN_24);		 // Join text
		iCircle(900, 400,10);//Member circle
		iCircle(450, 400,10);//Manager circle
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
			iSetColor(blue);
			iFilledCircle(900, 400,7);//Member circle	
		}
		if(draw_man )
		{
			iSetColor(blue);
			iFilledCircle(450,400,7);//Manager circle
	
		}
		if(invalid_option)
		{
			iSetColor(indigo);
			iText(600,400,"Choose an option", 
			GLUT_BITMAP_TIMES_ROMAN_24);
		}
		if(wrInvalidUser)
		{
			iText(605, 570, "Invalid Messname", 
			GLUT_BITMAP_TIMES_ROMAN_24);
		}
		
	}
	else if(Mess_page)
	{
		iSetColor(dodger_blue);
		//For Mess name
		iFilledRectangle(295,725,410,50);
		iSetColor(blue);
		iFilledRectangle(300,730,400,40);
		//strcat(Mess_Name," Mess");
		iSetColor(white);
		iText(330,740,Mess_Name,GLUT_BITMAP_TIMES_ROMAN_24);
		//For Meal order box
		iSetColor(indigo);
		//iRectangle(24,640,200,200.00/3);
		//iSetColor(antique_white);
		iRectangle(24,640,1000,200.00/3);
		iRectangle(29,645,990,170.00/3);
		iText(1087/3+170,650,"COST = ",GLUT_BITMAP_HELVETICA_18);
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
		iText(229,526.66,tcoststr,GLUT_BITMAP_HELVETICA_18);
		iText(34,541.66,"TOTAL COST",GLUT_BITMAP_HELVETICA_18);
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
		//For requests
		iRectangle(25,300,200,70);
		iText(35,310,"Requests",
		GLUT_BITMAP_TIMES_ROMAN_24);
		iRectangle(30,305,190,60);
		//MessPage_y -= MessPage_dy;
	
	}
	else if(Student_page)
	{
		iSetColor(black);
		//For Student name
		iRectangle(34,590,200,200.0/3);
		iRectangle(39,595,190,170.0/3);
		iText(44,600,"Name",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(244,600,student_name,GLUT_BITMAP_TIMES_ROMAN_24);
		iRectangle(34,590,800,200.0/3);
		iRectangle(234,590,800,200.0/3);
		iRectangle(239,595,590,170.0/3);
		//iRectangle(MessPage_x+15+screenWidth/1.5,MessPage_y-45,screenWidth/6-10,screenHeight/12-10); Use it for Change box
		iText(849,605,"Change",GLUT_BITMAP_TIMES_ROMAN_24);

		//For Meal order
		iRectangle(34,1570.0/3,200,800.0/12);
		iRectangle(39,1585.0/3,190,170.0/3);
		iText(44,1600.0/3,"Meal Order",GLUT_BITMAP_TIMES_ROMAN_24);
		iRectangle(34,1570.0/3,800,200.0/3);
		iRectangle(834,523.33,200,66.66);
		iRectangle(234,523.33,800,66.66);
		iRectangle(239,528.33,590,56.66);
		iText(244,533.33,meal_num,GLUT_BITMAP_TIMES_ROMAN_24);
		//For laundry order
		iRectangle(34,456.66,200,66.66);
		iRectangle(39,461.66,190,56.66);
		iText(44,466.67,"Laundry Order",GLUT_BITMAP_TIMES_ROMAN_24);
		iRectangle(34,456.66,800,66.66);
		iRectangle(834,456.66,200,66.66);
		iRectangle(234,456.66,800,66.66);
		iRectangle(239,461.66,590,56.66);
		iText(244,466.66,laundry_num,GLUT_BITMAP_TIMES_ROMAN_24);
		//For Password 
		iRectangle(34,390,200,66.66);
		iRectangle(39,395,190,56.66);
		iText(44,400,"Password",GLUT_BITMAP_TIMES_ROMAN_24);
		iRectangle(34,390,800,66.66);
		iRectangle(834,390,200,66.66);
		iRectangle(234,390,800,66.66);
		iRectangle(239,395,590,56.66);
		iText(849,405,"Change",GLUT_BITMAP_TIMES_ROMAN_24);
		//iRectangle(MessPage_x+15+screenWidth/1.5,MessPage_y-45-3*screenHeight/12,screenWidth/6-10,screenHeight/12-10); //Use it for Change box

		iRectangle(400,200,400,100);
		iRectangle(400,200,400,50);
		iRectangle(400,250,150,50);
		iRectangle(400,200,150,50);
		iText(410,270,"Meal cost",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(560,270,meal_cost_str,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(410,210,"Laundry cost",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(560,210,laundry_cost_str,GLUT_BITMAP_TIMES_ROMAN_24);
		iRectangle(800,200,200,100);
		iText(820,250,total_cost_str,
		GLUT_BITMAP_TIMES_ROMAN_24);
		


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
				iText(150+j*200,700-60*i,
				Students[i].name,
				GLUT_BITMAP_TIMES_ROMAN_24);
				}
				else if(j==4)
				{
				iText(150+j*200,700-60*i,
				Students[i].pass,
				GLUT_BITMAP_TIMES_ROMAN_24);
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
	else if(req_log_page)
	{
		if(draw_man)
		{
			iSetColor(dodger_blue);
			iFilledRectangle(300,500,210,50);
			iSetColor(blue);
			iFilledRectangle(305,505,200,40);
			iSetColor(white);
			iText(310,510,"Manager Password",
			GLUT_BITMAP_TIMES_ROMAN_24);
			iSetColor(blue);
			iRectangle(510,500,300,50);//password
			iText(520,510,manager_pass,
			GLUT_BITMAP_TIMES_ROMAN_24);
			iSetColor(dodger_blue);//back option
			iFilledRectangle(300,300,100,50);
			iSetColor(blue);
			iFilledRectangle(305,305,90,40);
			iSetColor(white);
			iText(310,310,"Back",GLUT_BITMAP_TIMES_ROMAN_24);
			iSetColor(dodger_blue);//login option
			iFilledRectangle(500,300,100,50);
			iSetColor(blue);
			iFilledRectangle(505,305,90,40);
			iSetColor(white);
			iText(510,310,"Login",GLUT_BITMAP_TIMES_ROMAN_24);
			if(write_spass)
			{
				iSetColor(indigo);
				iRectangle(515,505,290,40);
				iText(520,510,manager_pass,
				GLUT_BITMAP_TIMES_ROMAN_24);
			}
			if(wrong_pass)
			{
				iSetColor(indigo);
				//iRectangle(515,505,290,40);
				iText(520,510,"Wrong Password",
				GLUT_BITMAP_TIMES_ROMAN_24);
			}

		}
		else if(draw_mem)
		{
			iSetColor(dodger_blue);
			iFilledRectangle(300,500,210,50);
			iSetColor(blue);
			iFilledRectangle(305,505,200,40);
			iSetColor(white);
			iText(310,510,"Member Name",
			GLUT_BITMAP_TIMES_ROMAN_24);
			iSetColor(dodger_blue);
			iFilledRectangle(300,400,210,50);
			iSetColor(blue);
			iFilledRectangle(305,405,200,40);
			iSetColor(white);
			iText(310,410,"Member Password",
			GLUT_BITMAP_TIMES_ROMAN_24);
			iSetColor(blue);
			iRectangle(510,400,300,50);//password
			iText(520,410,s1.pass,
			GLUT_BITMAP_TIMES_ROMAN_24);
			iRectangle(510,500,300,50);//name
			iText(520,510,s1.name,
			GLUT_BITMAP_TIMES_ROMAN_24);
			iSetColor(dodger_blue);//back option
			iFilledRectangle(300,300,100,50);
			iSetColor(blue);
			iFilledRectangle(305,305,90,40);
			iSetColor(white);
			iText(310,310,"Back",GLUT_BITMAP_TIMES_ROMAN_24);

			iSetColor(dodger_blue);//login option
			iFilledRectangle(500,300,100,50);
			iSetColor(blue);
			iFilledRectangle(505,305,90,40);
			iSetColor(white);
			iText(510,310,"Login",GLUT_BITMAP_TIMES_ROMAN_24);

			iSetColor(dodger_blue);//request to login option
			iFilledRectangle(700,300,100,50);
			iSetColor(blue);
			iFilledRectangle(705,305,90,40);
			iSetColor(white);
			iText(710,310,"Request",
			GLUT_BITMAP_TIMES_ROMAN_24);
			if(write_sname)
			{
				iSetColor(indigo);
				iRectangle(515,505,290,40);//name
				iText(520,510,s1.name,
				GLUT_BITMAP_TIMES_ROMAN_24);
			}
			else if(write_spass)
			{
				iSetColor(indigo);
				iRectangle(515,405,290,40);//password
				iText(520,410,s1.pass,
				GLUT_BITMAP_TIMES_ROMAN_24);
			}
			if(req)
			{
				iSetColor(indigo);
				iFilledRectangle(500,200,300,50);
				iSetColor(yellow);
				iText(510,210,"Request has been added",
				GLUT_BITMAP_TIMES_ROMAN_24);
			}
			if(check)
			{
				iSetColor(indigo);
				iFilledRectangle(500,200,400,50);
				iSetColor(yellow);
				iText(510,210,"Request has already been added",
				GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
	}
	if(req_page)
	{
		iSetColor(indigo);
		for(int i=0;i<reqidx;i++)
		{
			iSetColor(indigo);
			iRectangle(30,700-i*40+dy,100,40);//for index box
			iSetColor(black);
			sprintf(num,"%d",i+1);
			iText(40,710-40*i+dy,num,
			GLUT_BITMAP_TIMES_ROMAN_24);//index text
			iSetColor(indigo);
			iRectangle(130,700-i*40+dy,350,40);
			iText(140,710-i*40+dy,requests[i].name,
			GLUT_BITMAP_TIMES_ROMAN_24);//name
		}
		//Add option
		iFilledRectangle(700,700,100,40);
		iSetColor(yellow);
		iText(710,710,"Add",GLUT_BITMAP_TIMES_ROMAN_24);
		//for remove option
		iSetColor(indigo);
		iFilledRectangle(900,700,100,40);
		iSetColor(yellow);
		iText(910,710,"Remove",GLUT_BITMAP_TIMES_ROMAN_24);
		//back option
		iSetColor(indigo);
		iFilledRectangle(700,600,100,40);
		iSetColor(yellow);
		iText(710,610,"Back",GLUT_BITMAP_TIMES_ROMAN_24);
		if(selectidx != -1)
		{
			iSetColor(indigo);
			iRectangle(35,705-selectidx*40+dy,90,30);
		}
	}

	
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my)
{
	if(req_page)
	{
		
	}
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
		if (mx >= (600) && mx <= 1050 &&
			my >= (550) && my <= (600)) // writing mess name
		{
			wrMessname = 1;
			wrMessPass = 0;
			wrInvalid = 0;
			wrInvalidUser = 0;
		} 
		else if (mx >= 600 && mx <= 1050 &&
		 my >= 390 && my <= 440) // writing mess Password
		{
			wrMessPass = 1;
			wrMessname = 0;
			wrInvalid = 0;
			wrInvalidUser = 0;
		} 
		else if (mx >= (600) && mx <= 750 &&
		 my >= 300 && my <= 350) // For Enter button
		{
			wrMessname = 0;
			wrMessname = 0;
			if(Mess_name_index>=1 && Mess_pass_index>=1)
			{
				
				strcpy(fname,Mess_Name);
				strcat(fname,".txt");
				fptr = fopen(fname,"r");
				if(fptr == NULL)//no existing mess
				{
					Mess_page = 1;
					Create_page = 0;
					fptr = fopen(fname,"w");
					fprintf(fptr,"%s:%s\n",
					"Manager_pass",Mess_pass);
					strcat(freq,Mess_Name);
					strcat(freq,"_req");
					strcat(freq,".txt");
					fptr = fopen(freq,"w");
					fclose(fptr);
				}
				else//exits mess of the name
				{
				wrInvalidUser = 1;
				wrMessname =0,wrMessPass=0;
				Mess_name_index = 0;
				Mess_pass_index = 0;
				Mess_Name[Mess_name_index] = '\0';
				Mess_pass[Mess_pass_index] = '\0';
				fname[Mess_name_index] = '\0';
				}
			}
			else
			{
				wrInvalid = 1;
				wrMessname =0,wrMessPass=0;
				Mess_name_index = 0;
				Mess_pass_index = 0;
				Mess_Name[Mess_name_index] = '\0';
				Mess_pass[Mess_pass_index] = '\0';
			}
		}
		else if (mx >= 250 && mx <= 325 
		&& my >= 220 && my <= 270) // for back button
		{
			Create_page = 0, wrMessname = 0, wrMessname = 0;
			wrInvalid =0,wrInvalidUser = 0 ;
			Mess_name_index = 0;
			Mess_pass_index = 0;
			Mess_Name[Mess_name_index] = '\0';
			Mess_pass[Mess_pass_index] = '\0';
			home_page =1;
			Mess_page = 0;
		}
		else
		{
			wrMessname = 0;
			wrMessPass = 0;
			wrInvalid  =0;
			wrInvalidUser = 0;
		}
	}
	//JOIN PAGE
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && Join_page)
	{
		if (mx <= (900) && mx >= 600 &&
			my >= (550) && my <= (600)) // writing mess name
		{
			wrMessname = 1;
			wrInvalidUser = 0;
			//wrMessPass = 0;
		}
		
		else if((mx-900)
		*(mx-900)
		+ (my-400)*(my-400)<= 169)
		{
			draw_mem = 1;
			invalid_option =0;
			wrInvalidUser = 0;
			draw_man =0;
			wrMessname = 0;
		}
		else if((mx-450)
		*(mx-450)
		+ (my-400)*(my-400)<= 169)
		{
			//cout<<"OK"<<endl;
			draw_man =1;
			draw_mem =0;wrInvalidUser = 0;
			wrMessname = 0;invalid_option=0;
		}
		else if (mx >= 600 && mx <= 750 &&
		 my >= 300 && my <= 350) // For Enter button
		{
			//Join_page = 0;
			wrMessname = 0;
			wrMessname = 0;
			strcpy(fname,Mess_Name);
			strcat(fname,".txt");
			fptr = fopen(fname, "r");
			if((draw_man==1 || draw_mem==1)&& 
			Mess_name_index>=1 && fptr!=NULL)
			{	req_log_page = 1;
				Join_page=0;
				wrMessname = 0;
			}
			else if(Mess_name_index ==0 || fptr == NULL)
			{
				wrInvalidUser =1;
				Mess_name_index = 0;
				//Mess_pass_index = 0;
				Mess_Name[Mess_name_index] = '\0';
				//wrMessname = 0;
			}
			else
			{
				invalid_option = 1;
			}
		}
		else if (mx >= 250 && mx <= 325 && 
		my >=  220 && my <= 270) // for back button
		{
			Join_page = 0, wrMessname = 0, wrMessname = 0;
			Mess_name_index = 0;
			Mess_pass_index = 0;
			Mess_Name[Mess_name_index] = '\0';
			Mess_pass[Mess_pass_index] = '\0';
			draw_man=0,draw_mem =0;
			invalid_option = 0;
			home_page = 1;
			wrInvalidUser = 0;
		}
		else
		{
			wrMessname = 0, draw_mem =0;
			draw_man =0;
			wrInvalidUser = 0;
		}
	}
	//Mess_page
	else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && Mess_page)
	{
		if(mx>=24 && mx<=224 && my>=1120.0/3&&my<=440)
		{
			Mess_page = 0;
			student_info_page = 1;
		}
		if(mx>=25 && mx<=225 && my>=300 && my<=370)
		{
			strcpy(freq,Mess_Name);
			strcat(freq,"_req.txt");
			fptr2 = fopen(freq,"r");
			while(fgets(req_content,100,fptr2))
			{
				sscanf(req_content,"%s %[^\n]s",
				requests[reqidx].pass
				,requests[reqidx].name);
				requests[reqidx].meal = 0;
				requests[reqidx].laundry = 0;
				requests[reqidx].total = 0;
				//printf("%s\n",requets[reqidx].name);
				reqidx++;
			}
			fclose(fptr2);
			req_page = 1;
			Mess_page = 0;
		}
	}
	else if( req_page)
	{
		if(mx>=700 && mx<=800 && my>=600 && my<=640 &&
		button == GLUT_LEFT_BUTTON && 
		state == GLUT_UP)//back
		{
			Mess_page =1;req_page = 0;
			reqidx = 0;
			selectidx = -1;
		}
		if(mx>=700 &&mx<=800 && my>=700 && my<=740
		&& button == GLUT_LEFT_BUTTON && 
		state == GLUT_UP)//add
		{	
			if(selectidx != -1)
			{
			
			strcpy(fname,Mess_Name);
			strcpy(freq,Mess_Name);
			strcat(fname,".txt");
			strcat(freq,"_req.txt");
			fptr = fopen(fname,"a");
			fprintf(fptr,"%s %d %d %d %s\n",
			requests[selectidx].pass,requests[selectidx].meal,
			requests[selectidx].laundry,requests[selectidx].total,
			requests[selectidx].name);
			fclose(fptr);
			//delete_line(selectidx,freq);
			set_requests();
			

			selectidx =-1;
			}
		}
		if(mx>=900 &&mx<=1000 && my>=700 && my<=740
		&& button == GLUT_LEFT_BUTTON && 
		state == GLUT_UP)//remove
		{
			if(selectidx!=-1)
			{
				set_requests();
				selectidx =-1;
			}
		}
		else{
			for(int i=0;i<reqidx;i++)
			{
				if(mx>=30 && mx<=480
				&& my>=700-i*40+dy &&my<= 740-i*40+dy)
				{selectidx = i;break;}
			}
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
			//Students[students_num-1] ={"Aritro","123",0,0,0};
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
	//req_log_page();
	else if(button == GLUT_LEFT_BUTTON &&
	 state == GLUT_UP && req_log_page)
	{
		if(draw_mem)
		{
			if(mx>=300&& mx<=400
			&& my>=300 && my<=350)//back
			{
				draw_mem = 0;
				draw_man =0;
				req_log_page = 0;
				Join_page = 1;
				sname_index = 0;
				spass_index = 0;
				s1.name[sname_index] = 0;
				s1.pass[spass_index] = 0;
				Mess_name_index = 0;
				Mess_Name[Mess_name_index]= '\0';
				req =0,check = 0;
			}
			else if(mx>=510 && mx<=810 &&
			my>= 500 && my<=550)
			{
				write_sname =1;
				write_spass =0;
				req = 0,check = 0;
			}
			else if(mx>=510&& mx<=810
			&& my>=400 && my<=450)
			{
				write_sname =0;
				write_spass= 1;
				req  =0,check = 0;
			}
			else if(mx>=700 && mx<=800
			&& my>=300 && my<=350)//request 
			{
				write_sname =0;
				write_spass = 0;
				strcpy(freq,Mess_Name);
				strcat(freq,"_req.txt");
				fptr2 = fopen(freq,"r");
				while(fgets(req_content,100,fptr2))
				{
					sscanf(req_content,
					"%s %[^\n]s",
					check_pass,check_name);
					printf("%s: %s\n",check_name,check_pass);
					if(strcmp(check_name,s1.name)==0
					&& strcmp(check_pass,s1.pass)==0)
					{check = 1;fclose(fptr2);
					break;}
				}
				fclose(fptr2);
				//if(check==0){
				//fptr = fopen(freq,"w");
				if(sname_index>0 && 
				spass_index>0 && check!=1)
				{
				fptr = fopen(freq,"a");
				fprintf(fptr,"%s %s\n",
				s1.pass,s1.name);
				fclose(fptr);
				req = 1;
				}
				sname_index =0;
				spass_index=0;
				s1.name[sname_index] = '\0';
				s1.pass[spass_index] = '\0';
			}
		}
		if(draw_man)
		{
			if(mx>=510 && mx<=810
			&& my>= 500 && my<=550)
			{
				write_spass =1;
				wrong_pass = 0 ;
			}
			if(mx>500 && mx<=600
			&& my>=300 && my<=350)//login
			{
				write_spass =0;
				strcpy(fname,Mess_Name);
				strcat(fname,".txt");
				fptr = fopen(fname,"r");
				fscanf(fptr,"Manager_pass:%s",check_pass);
				fclose(fptr);
				if(strcmp(manager_pass,check_pass)==0)
				{
					req_log_page=0;
					Mess_page = 1;
				}
				else
				{
					spass_index = 0;
					manager_pass[spass_index]='\0';
					wrong_pass = 1;
					
				}
			}
			if(mx>=300 && mx<=400
			&& my>=300 && my<=350)
			{
				spass_index =0;
				check_pass[spass_index]='\0';
				manager_pass[spass_index]= '\0';
				req_log_page =0;
				Join_page =1;
				draw_man =0;
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
				if(Mess_name_index>=27){Mess_name_index -=1;}
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
				if(Mess_pass_index>=27){Mess_pass_index -=1;}
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
	else if(req_log_page)
	{
		if(draw_mem && write_sname)
		{
			if(key!='\b')
			{
				s1.name[sname_index] = key;
				sname_index++;
				s1.name[sname_index] = '\0';
			}
			else
			{
				sname_index--;
				if(sname_index<=0){sname_index =0;}
				s1.name[sname_index] ='\0';
			}
		}
		else if(draw_mem && write_spass)
		{
			if(key!='\b' && key!= ' ')
			{
				s1.pass[spass_index] = key;
				spass_index++;
				s1.pass[spass_index] = '\0';
			}
			else if(key == '\b')
			{
				spass_index--;
				if(spass_index<=0){spass_index =0;}
				s1.pass[spass_index] ='\0';
			}
		}
		else if(draw_man && write_spass)
		{
			if(key!='\b' && key!= ' ')
			{
				manager_pass[spass_index] = key;
				spass_index++;
				manager_pass[spass_index] = '\0';
			}
			else if(key == '\b')
			{
				spass_index--;
				if(spass_index<=0){spass_index =0;}
				manager_pass[spass_index] ='\0';
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
