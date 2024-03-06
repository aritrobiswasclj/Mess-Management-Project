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
#define blue_violet 138,43,226
/*
	function iDraw() is called again and again by the system.

*/

typedef struct student
{
	char name[200],pass[200];
	int meal ;//35 per meal
	int laundry ;//30 per dress
	int total;
};




//double Mess_x = 300, Mess_y = 100;
int home_page = 1;
int Create_page = 0, Join_page = 0;
int wrMessname = 0, wrMessPass = 0,wrInvalid =0;
int wrInvalidUser = 0;

char Mess_Name[100], Mess_pass[100];
int Mess_name_index = 0, Mess_pass_index = 0;
int invalid_option = 0;
//Create page
char dup_create_pass[100];
int show_create_pass = 0;
//for mess page
char fname[200],freq[200] ;//mess file name
FILE * fptr;FILE *fptr2;//for opening  and reading mess file

//for mess page
int Mess_page = 0;
int total_costs = 0,laundrys_orders = 0;
int meals_orders = 0; 
int laundrys_cost = 0,meals_cost =0;
char total_meals[100],total_laundry[100];
char total_cost_str[100];
char total_mcost_str[100];
char total_lcost_str[100];
int update_Messpass = 0;
char hidden_pass[100];
int show_hidden = 0;//show_real_pass = 0;
int change_mess_pass = 0,write_mess_pass = 0;


//Login or request page
int req_log_page = 0,sname_index = 0 ,spass_index = 0;
student s1 ={"","",0,0,0};
int wrong_student = 0,check_student = 0;
int write_sname = 0,write_spass = 0,check = 0;
int req =0,wrong_pass =0;
char check_name[100],check_pass[100],manager_pass[100];
char dup_man_pass[100],dup_mem_pass[100];
char req_content[100],buffer[100];
student requests[500];int reqidx =0;
int show_man_pass = 0;
int show_mem_pass = 0;

student st;

//requests page
int req_page = 0;
char num[100];//for index meal,laundry total cost;
int selectidx = -1;//for req page
int current_idx = -1;//for login info
//for scrolling 
double starty = 0,dy =0,endy =0;


//for Student page
int stidx  = 0;
int totalStudents = 0;
char meal1[10],laundry1[10],total1[10];
int mealcost1,laundrycost1,totalcost1;
int change_pass = 0;
int stpasslen;
int change = 0;
int Student_page = 0;
int meal_order = 0,laundry_order = 0;
int showSt_pass = 1;
char hiddenSt_pass[100];


char meal_cost_str[100],laundry_cost_str[100];
//char total_cost_str[100];
int draw_mem = 0,draw_man =0;

//for student_info_page

int student_info_page = 0;

student Students[500];
char *info_page[5] ={"No","Name","Meal",
"Laundry","Total(Tk)"};
int wrName = 0,wrPass = 0,wridx ;
int Nameidx = 0,Passidx =0;
char each_name[100],each_pass[100];
char num_index[100],each_mlt[100];
int current_stidx =-1,clicked_st = 0;


void student_update(char * filename)
{
	char temp[100] = "temp__";
	
	strcat(temp,filename);
	
	strcat(temp,".txt");
	FILE * f1 = fopen(temp,"a");
	FILE * f2 = fopen(filename,"r");
	char content[100];
	fgets(content,100,f2);
	fprintf(f1,"%s",content);
	fclose(f2);
	for(int i =0;i<totalStudents;i++)
	{
		fprintf(f1,"%s %d %d %d %s\n",
		Students[i].pass,Students[i].meal,Students[i].laundry,
		Students[i].total,Students[i].name);
	}
	fclose(f1);
	remove(filename);
	rename(temp,filename);
}

void entering_mess()
{
	int total_ =0,meals_ = 0,laundrys_ = 0;
	FILE *f1;
	FILE *f2;
	char content[200],name[100],pass[100],meal[10];
	char laundry[10],total[10];
	strcpy(fname,Mess_Name);
	strcat(fname,".txt");
	strcpy(freq,Mess_Name);
	strcat(freq,"_req.txt");
	f1 = fopen(fname,"r");
	f2 = fopen(freq,"r");
	int i = 0;
	while(fgets(content,200,f2))
	{
		sscanf(content,"%s %[^\n]s",pass,name);
		strcpy(requests[i].name,name);
		strcpy(requests[i].pass,pass);
		requests[i].meal =0;
		requests[i].laundry =0;
		requests[i].total =0;
		
		i++;
	}
	reqidx =i;
	fclose(f2);
	i = 0;
	int start = 0;
	//fgets(content,200,f1);
	while(fgets(content,200,f1))
	{
		if(!start){start+=1;
		sscanf(content,"Manager_pass:%[^\n]s",Mess_pass);
		int len = strlen(Mess_pass);
		Mess_pass_index = len;
		for(int i =0 ;i<len ;i++){hidden_pass[i]='*';}
		hidden_pass[len]='\0';
		continue;}
		sscanf(content,"%s %s %s %s %[^\n]s",
		Students[i].pass,meal,laundry,total,
		Students[i].name);
		Students[i].meal = atoi(meal);
		Students[i].laundry = atoi(laundry);
		Students[i].total = atoi(total);
		total_+= Students[i].total;
		meals_ += Students[i].meal;
		laundrys_ += Students[i].total;
		//cout<<Students[i].name<<" "<<Students[i].pass<<" "
		//<<Students[i].meal<<" "<<Students[i].laundry<<endl;
		i++;
	}
	totalStudents = i;
	meals_orders = meals_;
	laundrys_orders = laundrys_;
	meals_cost = meals_orders*35;
	laundrys_cost = laundrys_orders*15;
	total_costs = meals_cost+laundrys_cost;
	sprintf(total_cost_str,"%d",total_costs);
	sprintf(total_meals,"%d",meals_orders);
	sprintf(total_laundry,"%d",laundrys_orders);
	sprintf(total_lcost_str,"%d",laundrys_cost);
	sprintf(total_mcost_str,"%d",meals_cost);
	fclose(f1);
}

void create_mess()
{
	strcpy(fname,Mess_Name);
	strcpy(freq,Mess_Name);
	strcat(fname,".txt");
	strcat(freq,"_req.txt");
	FILE *f = fopen(fname,"w");
	FILE *f1 = fopen(freq,"w");
	fprintf(f,"Manager_pass:%s\n",Mess_pass);
	fclose(f1);
	fclose(f);
}

void Mess_pass_update()
{
	FILE *f ;
	char f1name[100],f2name[100];
	strcpy(f1name,"temp__");
	strcat(f1name,Mess_Name);
	strcpy(f2name,Mess_Name);
	strcat(f1name,".txt");
	strcat(f2name,".txt");
	f = fopen(f1name,"w");
	fprintf(f,"Manager_pass:%s\n",Mess_pass);
	for(int i =0;i<totalStudents;i++)
	{
		fprintf(f,"%s %d %d %d %s\n",
		Students[i].pass,Students[i].meal,Students[i].laundry,
		Students[i].total,Students[i].name);
	}
	fclose(f);
	remove(f2name);
	rename(f1name,f2name);
}

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
void set_students()
{
	FILE *fptr3;
	strcpy(fname,Mess_Name);
	strcat(fname,".txt");
	//delete_line(selectidx,freq);
	//set_requests();
	stidx =0;
	int temp =0;
	char meal[10],laundry[10],total[10];
	fptr3 = fopen(fname,"r");
	while(fgets(buffer,100,fptr3))
	{	
		if(temp == 0){temp++;continue;}
		sscanf(buffer,"%s %s %s %s %[^\n]s",
		Students[stidx].pass,meal,laundry,total
		,Students[stidx].name);
		Students[stidx].meal = atoi(meal);
		Students[stidx].laundry = atoi(laundry);	
		Students[stidx].total = atoi(total);
		//printf("%s\n",requets[reqidx].name);
		stidx++;
	}
	fclose(fptr3);
}
void set_requests()
{
	FILE *fptr3;
	strcpy(freq,Mess_Name);
	strcat(freq,"_req.txt");
	delete_line(selectidx,freq);
	//set_requests();
	int i =0;
	fptr3 = fopen(freq,"r");
	while(fgets(req_content,100,fptr3))
	{	
		sscanf(req_content,"%s %[^\n]s",
		requests[i].pass
		,requests[i].name);
		requests[i].meal = 0;
		requests[i].laundry = 0;
		requests[i].total = 0;
		//printf("%s\n",requets[reqidx].name);
		i++;
	}
	reqidx =i;
	fclose(fptr3);
}



//int Join_page = 0;

void iDraw()
{
	// place your drawing codes here
	iClear();
	iSetColor(white);
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
		if(show_create_pass)
		{
			iShowBMP(1050,400,"passeye.bmp");
			iText(605, 400, Mess_pass, 
			GLUT_BITMAP_TIMES_ROMAN_24);
		}
		else
		{
			iShowBMP(1050,400,"passeyeclose.bmp");
			iText(605, 400,dup_create_pass, 
			GLUT_BITMAP_TIMES_ROMAN_24);
		}
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
			iText(600,560,"Mess Name Already taken",
			GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}
	else if (Join_page)
	{
		iSetColor(black);
		iRectangle(450, 550, 650, 50); // upper big rectangle
		
		iSetColor(blue);
		iFilledRectangle(450, 550, 150, 50);// upper small rectangle
		iSetColor(dodger_blue);
		iFilledRectangle(455, 555, 140, 40);
		iSetColor(white);
		iText(450, 570, "Mess Name", GLUT_BITMAP_TIMES_ROMAN_24);	
		
		
		iSetColor(black);
		iText(605, 570, Mess_Name, 
		GLUT_BITMAP_TIMES_ROMAN_24);// Mess name box text
		iSetColor(blue);
		iFilledRectangle(600, 300, 150, 50);// Join button
		iSetColor(dodger_blue);
		iFilledRectangle(605, 305, 140, 40);// Join button
		iSetColor(white);
		iText(640, 320, "Join", GLUT_BITMAP_TIMES_ROMAN_24); // Join text
		iSetColor(black);
		iCircle(900, 400,10);//Member circle
		iCircle(450, 400,10);//Manager circle
		iText(465, 390, "Manager", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(915, 390,"Member",GLUT_BITMAP_TIMES_ROMAN_24);
		//iText(wr_xpass+5, wr_ypass, Mess_pass, GLUT_BITMAP_TIMES_ROMAN_24);// mess pass text box
		iSetColor(blue);
		iFilledRectangle(250, 220, 75, 100/ 2.3);// Back Button box
		iFilledRectangle(255, 225, 65, 100/ 2.3-10);
		iSetColor(white);
		iText(250, 230, "Back", GLUT_BITMAP_TIMES_ROMAN_24); // Back text box
		iSetColor(black);
		if (wrMessname )
		{
			iRectangle(605,555,490,40);
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
		iFilledRectangle(25,640,200,65);
		iSetColor(blue_violet);
		iFilledRectangle(30,645,190,55);
		iSetColor(yellow);
		iText(35,670,"MEAL\n OREDERS",GLUT_BITMAP_HELVETICA_18);
		iSetColor(indigo);
		iText(235,670,total_meals,GLUT_BITMAP_HELVETICA_18);
		iSetColor(indigo);
		iRectangle(225,640,300,65);
		iRectangle(230,645,290,55);
		iRectangle(525,640,500,65);
		iRectangle(530,645,490,55);
		iText(540,655,"COST = ",GLUT_BITMAP_HELVETICA_18);
		iSetColor(indigo);
		iText(630,655,total_mcost_str
		,GLUT_BITMAP_HELVETICA_18);
		iText(980,655,"TK",GLUT_BITMAP_HELVETICA_18);
		
		
		//For Laundry order box
		
		iSetColor(indigo);
		iFilledRectangle(25,565,200,65);
		iSetColor(blue_violet);
		iFilledRectangle(30,570,190,55);
		iSetColor(yellow);
		iText(34,595,"LAUNDRY\n OREDERS",GLUT_BITMAP_HELVETICA_18);
		iSetColor(indigo);
		iText(235,595,total_laundry,GLUT_BITMAP_HELVETICA_18);
		iSetColor(indigo);
		iRectangle(225,565,300,65);
		iRectangle(230,570,290,55);
		iRectangle(525,565,500,65);
		iRectangle(530,570,490,55);
		iText(540,580,"COST = ",GLUT_BITMAP_HELVETICA_18);
		iSetColor(indigo);
		iText(630,580,total_lcost_str,
		GLUT_BITMAP_HELVETICA_18);
		iText(980,580,"TK",GLUT_BITMAP_HELVETICA_18);


		//For Total cost Box
		iSetColor(indigo);
		//iRectangle(24,640,200,200.00/3);
		//iSetColor(antique_white);
		iFilledRectangle(25,490,200,65);
		iSetColor(blue_violet);
		iFilledRectangle(30,495,190,55);
		iSetColor(yellow);
		iText(34,520,"TOTAL COST",GLUT_BITMAP_HELVETICA_18);
		iSetColor(indigo);
		iText(235,520,total_cost_str,GLUT_BITMAP_HELVETICA_18);
		iText(980,520,"TK",GLUT_BITMAP_HELVETICA_18);
		iSetColor(indigo);
		iRectangle(225,490,800,65);
		iRectangle(230,495,790,55);
		
		
		//For students info
		iSetColor(blue_violet);
		iFilledRectangle(25,375,200,65);
		iSetColor(indigo);
		iFilledRectangle(30,380,190,55);
		iSetColor(yellow);
		iText(35,390,"STUDENTS INFO",GLUT_BITMAP_HELVETICA_18);
		//For requests
		iSetColor(blue_violet);
		iFilledRectangle(25,300,200,70);
		iSetColor(indigo);
		iFilledRectangle(30,305,190,60);
		iSetColor(yellow);
		iText(35,320,"REQUESTS",
		GLUT_BITMAP_HELVETICA_18);

		//for password box
		iSetColor(indigo);
		iFilledRectangle(325,300,150,50);
		iSetColor(blue_violet);
		iFilledRectangle(330,305,140,40);
		iSetColor(yellow);
		iText(335,310,"PASSWORD",
		GLUT_BITMAP_HELVETICA_18);
		iSetColor(indigo);
		iFilledRectangle(875,300,100,50);
		iSetColor(blue_violet);
		iFilledRectangle(880,305,90,40);
		iSetColor(yellow);
		iText(885,310,"Change",
		GLUT_BITMAP_TIMES_ROMAN_24);
		if(show_hidden)
		{
			iSetColor(indigo);
			iRectangle(475,300,400,50);
			iShowBMP2(820,310,"passeyeclose.bmp",-1);//
			iSetColor(black);
			iText(485,310,hidden_pass,
			GLUT_BITMAP_TIMES_ROMAN_24);
		}
		else
		{
			iSetColor(indigo);
			iRectangle(475,300,400,50);
			iShowBMP2(820,310,"passeye.bmp",-1);//
			iSetColor(black);
			iText(485,310,Mess_pass,
			GLUT_BITMAP_TIMES_ROMAN_24);
		}
		if(change_mess_pass)
		{
			iSetColor(indigo);
			iFilledRectangle(475,200,450,50);
			iSetColor(yellow);
			iText(485,210,"Password changed successfully!",
			GLUT_BITMAP_TIMES_ROMAN_24);
		}
		if(write_mess_pass)
		{
			iSetColor(indigo);
			iRectangle(480,305,390,40);
		}
		


		
		//for back button
		iSetColor(indigo);
		iFilledRectangle(25,200,100,65);
		iSetColor(blue_violet);
		iFilledRectangle(30,205,90,55);
		iSetColor(yellow);
		iText(35,210,"BACK",GLUT_BITMAP_TIMES_ROMAN_24);
	
	}
	else if(Student_page)
	{
		iSetColor(indigo);
		//For Student name
		iFilledRectangle(35,590,200,65);
		iSetColor(antique_white);
		//iFilledRectangle(40,595,190,55);
		iSetColor(yellow);
		iText(45,600,"Name",GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(black);
		iText(245,600,Students[stidx].name,
		GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(indigo);
		iRectangle(235,590,600,65);
		
		

		//For Meal order
		iSetColor(indigo);
		iFilledRectangle(35,515,200,65);
		//iRectangle(40,520,190,55);
		iSetColor(yellow);
		iText(45,520,"Meal Order",GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(black);
		iText(245,530,meal1,GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(indigo);
		iRectangle(235,515,600,65);
		
		iRectangle(240,520,590,55);
		iFilledCircle(860,540,20,1000);//Plus button
		iSetColor(yellow);
		iText(855,535,"+",GLUT_BITMAP_TIMES_ROMAN_24);
		//minus button
		iSetColor(indigo);
		iFilledCircle(910,540,20,1000);
		iSetColor(yellow);
		iText(905,535,"-",GLUT_BITMAP_TIMES_ROMAN_24);
		//iText(244,533.33,meal_num,GLUT_BITMAP_TIMES_ROMAN_24);
		
		//For laundry order
		iSetColor(indigo);
		iFilledRectangle(35,440,200,65);
		//iRectangle(40,445,190,55);
		iSetColor(yellow);
		iText(45,450,"Laundry Order",GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(black);
		iText(245,450,laundry1,GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(indigo);
		iRectangle(235,440,600,65);
		iRectangle(240,445,590,55);
		//iRectangle(240,520,590,55);
		iFilledCircle(860,470,20,1000);//Plus button
		iSetColor(yellow);
		iText(855,465,"+",GLUT_BITMAP_TIMES_ROMAN_24);
		//minus button
		iSetColor(indigo);
		iFilledCircle(910,470,20,1000);
		iSetColor(yellow);
		iText(905,465,"-",GLUT_BITMAP_TIMES_ROMAN_24);
		
		
		//For Password
		iSetColor(indigo); 
		iFilledRectangle(35,360,200,65);
		
		//iRectangle(40,365,190,55);
		iSetColor(yellow);
		iText(45,370,"Password",GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(black);
		//iText(245,370,Students[stidx].pass,
		//GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(indigo);
		iRectangle(235,360,600,65);
		//iRectangle(240,365,590,55);
		iFilledRectangle(835,360,200,65);
		//iRectangle(235,350,800,66.66);
		//iRectangle(240,355,590,56.66);
		iSetColor(yellow);
		iText(850,375,"Change",GLUT_BITMAP_TIMES_ROMAN_24);
		if(showSt_pass)
		{
			iShowBMP(750,370,"passeye.bmp");
			iSetColor(indigo);
			iText(245,370,Students[stidx].pass,
			GLUT_BITMAP_TIMES_ROMAN_24);
		}
		else
		{
			iShowBMP(750,370,"passeyeclose.bmp");
			iSetColor(indigo);
			iText(245,370,hiddenSt_pass,
			GLUT_BITMAP_TIMES_ROMAN_24);
		}
		
		//for total meal and laundry costs
		
		iSetColor(blue_violet);
		iFilledRectangle(400,200,150,50);
		iSetColor(indigo);
		iFilledRectangle(405,205,140,40);
		iSetColor(blue_violet);
		iFilledRectangle(400,250,150,50);
		iSetColor(indigo);
		iFilledRectangle(405,255,140,40);
		iRectangle(550,250,250,50);
		iRectangle(550,200,250,50);
		//iRectangle(400,200,150,50);
		iSetColor(black);
		iText(410,270,"Meal cost",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(740,270,"Tk",GLUT_BITMAP_TIMES_ROMAN_24);
		//iSetColor(black);
		iText(560,270,meal_cost_str,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(410,210,"Laundry cost",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(740,210,"Tk",GLUT_BITMAP_TIMES_ROMAN_24);
		//iSetColor(black);
		iText(560,210,laundry_cost_str,GLUT_BITMAP_TIMES_ROMAN_24);
		iRectangle(800,200,200,100);
		iText(820,250,total_cost_str,
		GLUT_BITMAP_TIMES_ROMAN_24);
		iText(950,250,"TK",GLUT_BITMAP_TIMES_ROMAN_24);

		//back Button
		iSetColor(indigo);
		iFilledRectangle(35,100,100,50);
		iSetColor(yellow);
		iText(40,105,"BACK",
		GLUT_BITMAP_TIMES_ROMAN_24);
		if(change_pass)
		{
			iSetColor(indigo);
			iRectangle(240,365,590,55);
		}
		if(change )
		{
			iSetColor(indigo);
			iFilledRectangle(400,100,350,50);
			iSetColor(yellow);
			iText(400,120,"Password Changed Successfully!",
			GLUT_BITMAP_TIMES_ROMAN_24);
		}

		


	}
	else if (student_info_page)
	{
		iSetColor(indigo);
		
		for(int i =0;i<5;i++)
		{
			if(i==0)
			{
				iSetColor(indigo);
				iRectangle(20,700
				,50,50);
				//iSetColor(yellow);
				iText(30,710,info_page[i],
				GLUT_BITMAP_TIMES_ROMAN_24);
			}
			else if(i==1)
			{
				iSetColor(indigo);
				iRectangle(70,700
				,250,50);
				//iSetColor(yellow);
				iText(80,710,info_page[i],
				GLUT_BITMAP_TIMES_ROMAN_24);
			}
			else
			{
				iSetColor(indigo);
				iRectangle(320+(i-2)*120,700
				,120,50);
				//iSetColor(yellow);
				iText(330+(i-2)*120,710,info_page[i],
				GLUT_BITMAP_TIMES_ROMAN_24);
			}
			
		}
		for(int j=0;j<totalStudents;j++)
		{
			for(int i =0;i<5;i++)
			{
				if(i==0)
				{
					iSetColor(indigo);
					iRectangle(20,650-50*j
					,50,50);
				//iSetColor(yellow);
					sprintf(num_index,"%d",j+1);
					iText(30,660-50*j,num_index,
					GLUT_BITMAP_TIMES_ROMAN_24);
				}
				else if(i==1)
				{
					iSetColor(indigo);
					iRectangle(70,650-50*j
					,250,50);
					//iSetColor(yellow);
					iText(80,660-50*j,Students[j].name,
					GLUT_BITMAP_TIMES_ROMAN_24);
				}
				else
				{
					iSetColor(indigo);
					iRectangle(320+(i-2)*120,650-50*j
					,120,50);
					//iSetColor(yellow);
					if(i==2){sprintf(each_mlt,"%d",
					Students[j].meal);}
					if(i==3){sprintf(each_mlt,"%d",
					Students[j].laundry);}
					if(i==4){sprintf(each_mlt,"%d",
					Students[j].total);}
					iText(330+(i-2)*120,660-50*j,each_mlt,
					GLUT_BITMAP_TIMES_ROMAN_24);
				}
			
			}
		}
		//for remove option
		iSetColor(indigo);
		iFilledRectangle(900,700,100,40);
		iSetColor(yellow);
		iText(910,710,"Remove",GLUT_BITMAP_TIMES_ROMAN_24);
		//back option
		iSetColor(indigo);
		iFilledRectangle(700,700,100,40);
		iSetColor(yellow);
		iText(710,710,"Back",GLUT_BITMAP_TIMES_ROMAN_24);
		if(current_stidx!=-1)
		{
			iSetColor(indigo);
			iRectangle(25,655-50*current_stidx,40,40);
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
			iRectangle(510,500,400,50);//password
			//iRectangle(920,500,50,50);//password checkbox
			if(show_man_pass)
			{
				iShowBMP(920,500,"passeye.bmp");
				iText(520,510,manager_pass,
				GLUT_BITMAP_TIMES_ROMAN_24);
			}
			else
			{
				iShowBMP(920,500,"passeyeclose.bmp");
				iText(520,510,dup_man_pass,
				GLUT_BITMAP_TIMES_ROMAN_24);
			}
			
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
				iRectangle(515,505,390,40);
				if(show_man_pass)
				{
					iShowBMP(920,500,"passeye.bmp");
					iText(520,510,manager_pass,
					GLUT_BITMAP_TIMES_ROMAN_24);
				}
				else
				{
					iShowBMP(920,500,"passeyeclose.bmp");
					iText(520,510,dup_man_pass,
					GLUT_BITMAP_TIMES_ROMAN_24);
				}
				/* iText(520,510,manager_pass,
				GLUT_BITMAP_TIMES_ROMAN_24); */
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
			iRectangle(510,400,400,50);//password
			if(show_mem_pass)
			{
				iShowBMP(910,400,"passeye.bmp");
				iText(520,410,s1.pass,
				GLUT_BITMAP_TIMES_ROMAN_24);
			}
			else
			{
				iShowBMP(910,400,"passeyeclose.bmp");
				iText(520,410,dup_mem_pass,
				GLUT_BITMAP_TIMES_ROMAN_24);	
			}
			iRectangle(510,500,400,50);//name
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
				iRectangle(515,505,390,40);//name
				iText(520,510,s1.name,
				GLUT_BITMAP_TIMES_ROMAN_24);
			}
			else if(write_spass)
			{
				iSetColor(indigo);
				iRectangle(515,405,390,40);//password
				/* iText(520,410,s1.pass,
				GLUT_BITMAP_TIMES_ROMAN_24); */
				if(show_mem_pass)
				{
					iShowBMP(910,400,"passeye.bmp");
					iText(520,410,s1.pass,
					GLUT_BITMAP_TIMES_ROMAN_24);
				}
				else
				{
					iShowBMP(910,400,"passeyeclose.bmp");
					iText(520,410,dup_mem_pass,
					GLUT_BITMAP_TIMES_ROMAN_24);	
				}
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
			if(wrong_student)
			{
				iSetColor(indigo);
				iText(520,410,"Wrong password",
				GLUT_BITMAP_TIMES_ROMAN_24);
				iText(520,510,"Wrong Username",
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
					fclose(fptr);
					
					create_mess();
					Create_page = 0;
					Mess_page = 1;
					entering_mess();
				}
				else//exits mess of the name
				{
				fclose(fptr);
				wrInvalidUser = 1;
				wrMessname =0,wrMessPass=0;
				Mess_name_index = 0;
				Mess_pass_index = 0;
				Mess_Name[Mess_name_index] = '\0';
				Mess_pass[Mess_pass_index] = '\0';
				dup_create_pass[Mess_pass_index] = '\0';
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
				dup_create_pass[Mess_pass_index] = '\0';
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
			dup_create_pass[Mess_pass_index] = '\0';
			home_page = 1;
			Mess_page = 0;
		}
		else if(mx>=1050 && mx<1100
		&& my>= 400 && my<=440)//pasword checkbox
		{
			if(show_create_pass){show_create_pass =0;}
			else{show_create_pass =1;}
		}
		else//other
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
		if (mx <= (1100) && mx >= 600 &&
			my >= (550) && my <= (600)) // writing mess name
		{
			wrMessname = 1;
			wrInvalidUser = 0;
			//wrMessPass = 0;
		}
		
		else if((mx-900)
		*(mx-900)
		+ (my-400)*(my-400)<= 169)//member
		{
			draw_mem = 1;
			invalid_option =0;
			wrInvalidUser = 0;
			draw_man =0;
			wrMessname = 0;
		}
		else if((mx-450)
		*(mx-450)
		+ (my-400)*(my-400)<= 169)//manager
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
				entering_mess();
				fclose(fptr);
			}
			else if(Mess_name_index ==0 || fptr == NULL)
			{
				wrInvalidUser =1;
				Mess_name_index = 0;
				//Mess_pass_index = 0;
				Mess_Name[Mess_name_index] = '\0';
				fclose(fptr);
				//wrMessname = 0;
			}
			else
			{
				invalid_option = 1;
				fclose(fptr);
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
	else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && Mess_page)
	{
		if(mx>=25 && mx<=225 && my>=375 && my<=440)
		{
			Mess_page = 0;
			student_info_page = 1;
			current_stidx = -1;
		}
		else if(mx>=25 && mx<=225 && my>=300 && my<=370)
		{
			
			req_page = 1;
			Mess_page = 0;
		}
		else if(mx>=25 && mx<=125 && my>= 200
		&& my<= 265)//back button
		{
			home_page = 1;
			Mess_name_index = 0;
			draw_man = 0;
			Mess_Name[Mess_name_index] = '\0';
			Mess_page = 0;
			Mess_pass_index = 0;
			Mess_pass[0] = '\0';
			change_mess_pass = 0;
			write_mess_pass = 0;
		}
		
		else if(mx>=820 && mx<=870 &&
		 my>= 310 && my<=360)//show pass button
		{
		 	if(show_hidden){show_hidden = 0;}
			else{show_hidden = 1;}
			//printf("Why not working\n");
		}
		else if(mx>=475 && mx<=875
		&& my>= 300 && my<=350)//write new pass
		{
			write_mess_pass = 1;
		}
		else if(mx>=875 && mx<=975 &&my>=300&&
		my<=350)//change pass succesfully
		{
			change_mess_pass = 1;
			Mess_pass_update();
		}
		else
		{
			change_mess_pass = 0;
			write_mess_pass = 0;
		}
	}
	else if( req_page)//REQ page
	{
		if(mx>=700 && mx<=800 && my>=600 && my<=640 &&
		button == GLUT_LEFT_BUTTON && 
		state == GLUT_UP)//back
		{
			Mess_page =1;req_page = 0;
			reqidx = 0;
			selectidx = -1;
			entering_mess();
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
				&& my>=700-i*40+dy &&my<= 740-i*40+dy
				&& button == GLUT_LEFT_BUTTON && 
				state == GLUT_UP)
				{selectidx = i;break;}
			}
		}
		
	}
	//Student_info_page;
	else if(button == GLUT_LEFT_BUTTON && 
	state == GLUT_DOWN && student_info_page)
	{
		
		if(mx>=700 &&mx<=800 &&
		my>= 700 && my<=740)//back button
		{
			current_idx = -1;
			entering_mess();
			Mess_page =1;
			student_info_page = 0;
		}
		else if(mx>=900 && mx<=1000 &&
		my>=700 && my<=740)//remove option
		{
			if(current_stidx!=-1)
			{
				strcpy(fname,Mess_Name);
				strcat(fname,".txt");
				delete_line(current_stidx+1,fname);
				entering_mess();
				current_stidx =-1;
			}
		}
		else{
			int temp_clk=0;
			for(int i=0;i<totalStudents;i++)
			{
				if(mx>=20 && mx<=680
				&& my>=650-i*50 &&my<= 700-i*50
				)
				{current_stidx = i;
				temp_clk = 1;break;}
			}
			if(temp_clk!=1)
			{
				current_stidx = -1;
			}
		}
	}
	//Req_log_page();
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
				dup_mem_pass[spass_index] = '\0';

				//Mess_name_index = 0;
				//Mess_Name[Mess_name_index]= '\0';
				req =0,check = 0;
				wrong_student = 0;
				write_sname = 0;
				write_spass = 0;
			}
			else if(mx>=510 && mx<=910 &&
			my>= 500 && my<=550)//writring name
			{
				write_sname =1;
				write_spass =0;
				req = 0,check = 0;
				wrong_student = 0;
			}
			else if(mx>=510&& mx<=910
			&& my>=400 && my<=450)//writing password
			{
				write_sname =0;
				write_spass= 1;
				req  =0,check = 0;
				wrong_student =0;
			}
			else if(mx>=910&&mx<=960
			&& my>=400 && my<=440)//pass show
			{
				if(show_mem_pass){show_mem_pass =0;}
				else{show_mem_pass =1;}
			}
			else if(mx>=500 && mx<=600
			&& my>=300 && my<=350)//login
			{
				write_sname =0;
				write_spass = 0;
				
				for(int i=0;i<totalStudents;i++)
				{
					if(strcmp(Students[i].name,s1.name)
					== 0 && strcmp(Students[i].pass,
					s1.pass) == 0)
					{
						Student_page = 1;
						req_log_page =0;
						check_student = 1;
						stidx = i;
						strcpy(hiddenSt_pass,s1.pass);
						for(int j=0;j<spass_index;j++)
						{hiddenSt_pass[j]='*';}
						sname_index = 0;
						spass_index = 0;
						
						s1.name[sname_index] = '\0';
						s1.pass[spass_index] = '\0';
						dup_mem_pass[spass_index] ='\0';
						sprintf(meal1,"%d",Students[i].meal);
						sprintf(laundry1,"%d",Students[i].laundry);
						
						sprintf(total1,"%d",Students[i].total);
						mealcost1 = Students[i].meal *35;
						laundrycost1 = Students[i].laundry*15;
						Students[i].total = mealcost1 + laundrycost1;
						sprintf(laundry_cost_str,"%d",laundrycost1);
						sprintf(meal_cost_str,"%d",mealcost1);
						sprintf(total_cost_str,"%d",
						Students[i].total);
						stpasslen = strlen(Students[i].pass);
						
						break;
					}
					//cout<<Students[i].pass<<endl;
				}
				if(!check_student)
				{
					sname_index = 0;
					spass_index = 0;
					s1.name[sname_index] = '\0';
					s1.pass[spass_index] = '\0';
					dup_mem_pass[spass_index] ='\0';
					wrong_student = 1;
				}
				
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
				dup_mem_pass[spass_index] = '\0';
			}
			else
			{
				write_sname = 0;
				write_spass = 0;
				wrong_student = 0;
				check = 0;
				check_student= 0;
				req = 0;
			}
		}
		if(draw_man)
		{
			if(mx>=510 && mx<=810
			&& my>= 500 && my<=550)//write pass
			{
				write_spass =1;
				wrong_pass = 0 ;
			}
			else if(mx>500 && mx<=600
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
					entering_mess();
					Mess_page = 1;
					spass_index = 0;
					manager_pass[spass_index] = '\0';
					dup_man_pass[spass_index]='\0';
				}
				else
				{
					spass_index = 0;
					manager_pass[spass_index]='\0';
					dup_man_pass[spass_index]='\0';
					wrong_pass = 1;
					
				}
			}
			else if(mx>=300 && mx<=400
			&& my>=300 && my<=350)//back
			{
				spass_index =0;
				check_pass[spass_index]='\0';
				manager_pass[spass_index]= '\0';
				dup_man_pass[spass_index] = '\0';
				req_log_page =0;
				Join_page =1;
				draw_man =0;
				write_spass=0;
			}
			else if(mx>=920 && mx<=970
			&& my>=500 && my<=530)
			{
				if(show_man_pass){show_man_pass =0;}
				else{show_man_pass =1;}
			}
			else
			{
				write_spass =0;
				wrong_pass = 0;
			}
		}
		
	}
	//Students page
	else if(Student_page && state == GLUT_DOWN
	&& button == GLUT_LEFT_BUTTON)
	{
		if((mx-860)*(mx-860)+
		(my-540)*(my-540)<= 400)//increment meal order
		{
			Students[stidx].meal+=1;
			sprintf(meal1,"%d",Students[stidx].meal);
			mealcost1 = Students[stidx].meal *35;
			sprintf(meal_cost_str,"%d",mealcost1);
			Students[stidx].total = mealcost1 + laundrycost1;
			sprintf(total_cost_str,"%d",Students[stidx].total);
			strcpy(fname,Mess_Name);strcat(fname,".txt");
			student_update(fname);
		}
		else if((mx-910)*(mx-910)+
		(my-540)*(my-540)<= 400)//decrement meal order
		{
			Students[stidx].meal-=1;
			if(Students[stidx].meal <= 0)
			{Students[stidx].meal = 0;}
			sprintf(meal1,"%d",Students[stidx].meal);
			mealcost1 = Students[stidx].meal *35;
			sprintf(meal_cost_str,"%d",mealcost1);
			Students[stidx].total = mealcost1 + laundrycost1;
			sprintf(total_cost_str,"%d",Students[stidx].total);
			strcpy(fname,Mess_Name);
			strcat(fname,".txt");
			student_update(fname);
		}
		else if((mx-860)*(mx-860)+
		(my-470)*(my-470)<= 400)//increment laundry order
		{
			Students[stidx].laundry+=1;
			sprintf(laundry1,"%d",Students[stidx].laundry);
			laundrycost1 = Students[stidx].laundry *15;
			sprintf(laundry_cost_str,"%d",laundrycost1);
			Students[stidx].total = mealcost1 + laundrycost1;
			sprintf(total_cost_str,"%d",Students[stidx].total);
			strcpy(fname,Mess_Name);strcat(fname,".txt");
			student_update(fname);
		}
		else if((mx-910)*(mx-910)+
		(my-470)*(my-470)<= 400)//decrement laundry order
		{
			Students[stidx].laundry-=1;
			if(Students[stidx].laundry <= 0)
			{Students[stidx].laundry = 0;}
			sprintf(laundry1,"%d",Students[stidx].laundry);
			laundrycost1 = Students[stidx].laundry *15;
			sprintf(laundry_cost_str,"%d",laundrycost1);
			Students[stidx].total = mealcost1 + laundrycost1;
			sprintf(total_cost_str,"%d",Students[stidx].total);
			strcpy(fname,Mess_Name);strcat(fname,".txt");
			student_update(fname);
		}
		else if(mx>=235 && mx<=750
		&& my>=360 && my<=425)//changing pass
		{
			change_pass = 1;
		}
		else if(mx>=750 && mx<=800
		&& my>=360 && my<=400)
		{
			if(showSt_pass){showSt_pass =0;}
			else{showSt_pass = 1;}
		}
		else if(mx>=835 && mx<=1035
		&& my>= 360 && my<=425)//change button
		{
			change_pass = 0;
			change = 1;
			strcpy(fname,Mess_Name);strcat(fname,".txt");
			student_update(fname);
		}
		else if(mx>=35 &&mx<135
		&&my>=100 && my<=150)
		{
			change = 0;
			change_pass = 0;
			Student_page = 0;
			req_log_page = 1;
		}
		else
		{
			change = 0;
			change_pass = 0;
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
				if(Mess_name_index>=40){Mess_name_index -=1;}
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
			if (key != '\b' && key != ' ')
			{
				if(Mess_pass_index>=31){Mess_pass_index -=1;}
				Mess_pass[Mess_pass_index] = key;
				dup_create_pass[Mess_pass_index] ='*';
				Mess_pass_index++;
				Mess_pass[Mess_pass_index] = '\0';
				dup_create_pass[Mess_pass_index] = '\0';
			}
			else
			{
				Mess_pass_index -= 1;
				if (Mess_pass_index <= 0)
				{
					Mess_pass_index = 0;
				}
				Mess_pass[Mess_pass_index] = '\0';
				dup_create_pass[Mess_pass_index] = '\0';
			}
		}
	}
	else if (Join_page)
	{
		if (wrMessname)

		{
			if (key != '\b')
			{
				if(Mess_name_index<=35)
				{
				Mess_Name[Mess_name_index] = key;
				Mess_name_index++;
				Mess_Name[Mess_name_index] = '\0';
				}
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
		
		/* else if (wrMessPass)
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
		} */ 
	}
	else if(Mess_page)
	{
		if(write_mess_pass)
		{
			if(key!='\b' && key!= ' ')
			//&& stpasslen<=30)
			{
				hidden_pass[Mess_pass_index] = '*';
				Mess_pass[Mess_pass_index] = key;
				Mess_pass_index++;
				hidden_pass[Mess_pass_index] = '\0';
				Mess_pass[Mess_pass_index] = '\0';
				
			}
			else if(key == '\b')
			{
				Mess_pass_index--;
				if(Mess_pass_index<=0){Mess_pass_index=0;}
				hidden_pass[Mess_pass_index] = '\0';
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
				if(sname_index<=25){
				s1.name[sname_index] = key;
				sname_index++;
				s1.name[sname_index] = '\0';
				}
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
				if(spass_index<=25){
				s1.pass[spass_index] = key;
				dup_mem_pass[spass_index] ='*';
				spass_index++;
				s1.pass[spass_index] = '\0';
				dup_mem_pass[spass_index] ='\0';
				}
			}
			else if(key == '\b')
			{
				
				spass_index--;
				if(spass_index<=0){spass_index =0;}
				s1.pass[spass_index] ='\0';
				dup_mem_pass[spass_index] = '\0';
				
			}
		}
		else if(draw_man && write_spass)
		{
			if(key!='\b' && key!= ' ')
			{
				if(spass_index<=30){
				manager_pass[spass_index] = key;
				dup_man_pass[spass_index] = '*';
				spass_index++;
				manager_pass[spass_index] = '\0';
				dup_man_pass[spass_index] = '\0';
				}
			}
			else if(key == '\b')
			{
				spass_index--;
				if(spass_index<=0){spass_index =0;}
				manager_pass[spass_index] ='\0';
				dup_man_pass[spass_index] = '\0';
			}
		}
	}
	else if (Student_page)
	{
		if(change_pass)
		{
			if(key!='\b' && key!= ' '
			&& stpasslen<=30)
			{
				Students[stidx].pass[stpasslen] = key;
				hiddenSt_pass[stpasslen] = '*';
				stpasslen++;
				hiddenSt_pass[stpasslen] = '\0';
				Students[stidx].pass[stpasslen] = '\0';
			}
			else if(key == '\b')
			{
				stpasslen--;
				if(stpasslen<=0){stpasslen =0;}
				Students[stidx].pass[stpasslen] = '\0';
				hiddenSt_pass[stpasslen] = '\0';
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
