#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<process.h>
//list of header files


FILE *login;
char password[10];


struct stud_member  //structer of student type member
{
	int stud_id;
	int stud_sem;
	char stud_name[30];
	char stud_gender[3];
	char stud_course[10];
};
struct stud_member stud;

struct teacher_member  //structer of teacher type member
{
	int teacher_id;
	char teacher_name[30];
	char teacher_gender[3];
	char teacher_department[10];
};
struct teacher_member teacher;

struct book   //structure of book
{
	int book_id;
	char book_name[30];
	char book_pub[10];
	char book_auth[50];
	char bk_user[50];
	int book_price;
	int bk_sts;
	int m_id;
};
struct book book;

void lineHor(int column1,int column2,int row)
{
 char c=205;
 for(column1=column1;column1<=column2;column1++)
 {
  gotoxy(column1,row);
  cprintf("%c",c);
 }
}

void lineVer(int row1,int row2,int column)
{
 char c=186;
 for(row1=row1;row1<=row2;row1++)
 {
  gotoxy(column,row1);
  cprintf("%c",c);
 }
}

void box(int column1,int row1,int column2,int row2)
{
	char c1=201,c2=187,c3=200,c4=188;
	gotoxy(column1,row1);
	printf("%c",c1);
	gotoxy(column2,row1);
	printf("%c",c2);
	gotoxy(column1,row2);
	printf("%c",c3);
	gotoxy(column2,row2);
	printf("%c",c4);
	column1++;
	column2--;
	lineHor(column1,column2,row1);//drawing horizental line
	lineHor(column1,column2,row2);
	column1--;
	column2++;
	row1++;
	row2--;
	lineVer(row1,row2,column1);
	lineVer(row1,row2,column2);
}

void main_menu(void);

void student_menu(void);
 void adds_member(void);
	void last_sid(void);
 void searchstud(void);
	void searchByID(void);
	void searchByName(void);
 void dels_member(void);
	void deleteByID(void);
 void update_stud(void);

void teacher_menu(void);
 void addt_member(void);
	void last_tid(void);
 void delt_member(void);
 void searchteacher(void);
	void searchByID1(void);
	void searchByName1(void);
 void update_teacher(void);

void book_menu(void);
 void add_book(void);
	void last_bkid(void);
 void delb_book(void);
 void searchbook(void);
	void searchByID2(void);
	void searchByName2(void);
 void update_book(void);

void list(void);
  void stud_list(void);
  void teacher_list(void);
  void book_list(void);

void transaction_menu(void);
  void transactions_menu(void);
	void trans_issue(void);
	void trans_return(void);
  void transactiont_menu(void);
	void trant_issue(void);
	void trant_return(void);

void main_close();
void lineHor(int,int,int);
void lineVer(int,int,int);
void box(int,int,int,int);
void box1();
void get_password(char *);
void adminsignup();
void adminsignin();
int change_password(void);

void get_password(char *pass)
{
  char temp_passP[25];
  int i=0;
  while(1)
  {
     temp_passP[i]=getch();
     if(temp_passP[i]==13){break;}
     else if(temp_passP[i]==8)
     {
	if(i!=0)
	{
	  printf("\b \b");
	  i--;
	}
	else{printf("\a");}
     }
     else
     {
       printf("*");
       *(pass+i)=temp_passP[i];
       i++;
     }
     *(pass+i)='\0';
  }
}


void adminsignup(void)
{
    char temp[10];
    FILE *login;

    login=fopen("C:\PASSWORD.dat","ab+");
    gotoxy(10,10);
    printf("Enter password: ");
    get_password(password);
    gotoxy(10,11);
    printf("Re Enter Password: ");
    get_password(temp);
    while(strcmp(password,temp)!=0)
    {
	gotoxy(10,10);
	printf("Password did not matched! Enter again:");
	gotoxy(10,11);
	printf("Enter password: ");
	get_password(password);
	gotoxy(10,12);
	printf("Re Enter Password: ");
	get_password(temp);
	clrscr();
    }
    fwrite(&password,sizeof(password),1,login);
    fclose(login);
}

void adminsignin(void)
{
    char temp[10];
    FILE *login;
    login = fopen("C:\PASSWORD.dat","rb");
    gotoxy(10,10);
    printf("Enter password: ");
    get_password(temp);

    while(fread(&password,sizeof(password),1,login)==1)
    {
	while(strcmp(temp,password)!=0)
	{
	    clrscr();
	    box1();
	    gotoxy(10,10);
	    printf("Password did not match!");
	    printf("Enter Again:");
	    get_password(temp);
	}
	gotoxy(10,11);
	printf("password match");
	break;
    }
    fclose(login);
    gotoxy(10,12);
    printf("press any key...");
    getch();
}

int change_password(void)
{
   FILE *login;
   int c,i=0;
   char old_pass[10],new_pass[10];
   clrscr();
   box1();
   gotoxy(10,10);
   printf("Enter Old Password:");
   get_password(old_pass);
   gotoxy(10,12);
   printf("Enter New Password:");
   get_password(new_pass);

   login=fopen("C:\PASSWORD.dat","rb+");
   while(fread(&password,sizeof(password),1,login)==1)
   {
     if(strcmp(old_pass,password)==0)
	{
	  strcpy(password,new_pass);
	  fseek(login,ftell(login)-sizeof(password),0);
	  fwrite(&password,sizeof(password),1,login);
	  fclose(login);
	  gotoxy(10,15);
	  printf("The password is sucessfully changed!");
	  i=1;
	}
	else
	{
	   gotoxy(10,15);
	   printf("Password changing process failed!");
	   i=0;
	}
    }
    return i;
}

void main()
{
	FILE *login;
	clrscr();
	box1();
	textcolor(11);
	textbackground(5);


	login = fopen("C:\PASSWORD.dat","rb");
	if(login == NULL)
	{
		gotoxy(10,9);
		printf("Database Do not exits. Be an adminstrator. Sign Up");
		adminsignup();
	}
	else
	{
		adminsignin();
	}
	main_menu();
	getch();
}


void main_menu(void)
{
 char ch='\0';
 clrscr();
 flushall();
 while(1)
 {
   clrscr();
   box1();
   box(25,5,60,23);
   lineHor(26,59,7);
   lineHor(26,59,21);
   gotoxy(30,6);
   printf("MAIN MENU");
   gotoxy(30,8);
   printf("1.Student Section");
   gotoxy(30,10);
   printf("2.Teacher Section");
   gotoxy(30,12);
   printf("3.Book Section");
   gotoxy(30,14);
   printf("4.Transtion Section");
   gotoxy(30,16);
   printf("5.list");
   gotoxy(30,18);
   printf("6.Change Password");
   gotoxy(30,20);
   printf("0.Quit");
   gotoxy(30,22);
   printf("Enter your choice:");
   ch=getch();

		if(ch==27)  //else if ladder
		      return;

		else if(ch=='1')
		{
			student_menu();
			break;
		}
		else if(ch=='2')
		{
			teacher_menu();
			break;
		}
		else if(ch=='4')
		{
			transaction_menu();
			break;
		}
		else if(ch=='3')
		{
			book_menu();
			break;
		}
		else if(ch=='5')
		{
			list();
			break;
		}
		else if(ch=='6')
		{
			change_password();
			gotoxy(10,17);
			printf("Press any key to continue.......");
			getch();
			main_menu();
			break;
		}
		else if(ch=='0')
		{
			main_close();
			break;
		}
		else
		{
			gotoxy(10,23);
			printf("\aWrong Entry!!Please re-entered correct option");
			getch(); //holds the screen until a key is pressed
		}
	}
 getch();
}
void box1()
{
	box(2,2,79,24);
	lineHor(3,78,4);
	gotoxy(30,3);
	printf("LIBRARY MANAGEMENT SYSTEM");
}
void main_close()
{

	clrscr();
	flushall();
	box1();
	gotoxy(16,8);
	printf("Programmer....");
	gotoxy(16,10);
	printf("Kapaletiya Trupti");
	gotoxy(16,12);
	printf("Rathod Priti");
	gotoxy(16,15);
	printf("E-mail: ");
	gotoxy(16,16);
	printf("Exiting in 5 second...........");
	sleep(5);
	exit(0);
}

void student_menu(void)
{
	char ch;   //variable declaration
	int i;
	clrscr();
	flushall();
	while(1)
	{
		box(25,5,60,22);
		box(2,2,79,24);
		lineHor(26,59,8);
		lineHor(26,59,20);
		gotoxy(32,6);
		printf("STUDENT MENU");
		gotoxy(32,7);
		printf("~~~~~~~~~~~~~");
		gotoxy(32,10);
		printf("1. ADDITION.");
		gotoxy(32,12);
		printf("2. DELETION.");
		gotoxy(32,14);
		printf("3. UPDATION.");
		gotoxy(32,16);
		printf("4. SEARCH.");
		gotoxy(32,18);
		printf("0. EXIT.");
		gotoxy(32,21);
		printf("Enter Your Choice : ");
		ch=getche();
		if(ch==27)
			return;
		else if(ch=='1')
		{
			adds_member();
			break;
		}
		else if(ch=='2')
		{
			dels_member();
			break;
		}
		else if(ch=='3')
		{
			update_stud();
			break;
		}
		else if(ch=='4')
		{
			searchstud();
			break;
		}
		else if(ch=='0')
		{
			main_menu();
			break;
		}
		else
		{
		 gotoxy(10,23);
		 printf("\aWrong Entry!!Please re-entered correct option");
		 getch(); //holds the screen until a key is pressed
		}
	}
}

void adds_member(void) //function to add student detail.
{
	struct stud_member m;
	int id=0,i,n;
	FILE *fp;
	flushall();
	clrscr();
	gotoxy(20,6);
	printf("STUDENT ADDITION SCREEN");
	gotoxy(20,7);
	printf("----------------------");
	id=last_studid();
	id++;
	m.stud_id=id;
	fp=fopen("C:\STUDENT.DAT","ab+");
	if(fp==NULL)
	{
		printf("\nError In Opening The File.");
		getch();
		exit(1);
	}
	gotoxy(2,10);
	printf("Enter The Member Name : ");
	gets(m.stud_name);
	strupr(m.stud_name);
	gotoxy(2,12);
	printf("Enter The Member Gender(F/M) : ");
	gets(m.stud_gender);
	strupr(m.stud_gender);
	n=strlen(m.stud_gender);
	for(i=0;i<n;i++)
	{
	   if(!isalpha(m.stud_gender[i]))
	   {
	     printf("\nPlease enter string");
	     getch();
	     adds_member();
	   }
	}
	gotoxy(2,14);
	printf("Enter The Course : ");
	gets(m.stud_course);
	strupr(m.stud_course);
	n=strlen(m.stud_course);
	for(i=0;i<n;i++)
	{
	   if(!isalpha(m.stud_course[i]))
	   {
	     printf("\nPlease enter string");
	     getch();
	     adds_member();
	   }
	}
	gotoxy(2,16);
	printf("Enter The Semester : ");
	scanf("%d",&m.stud_sem);
	if(m.stud_sem>0 && m.stud_sem<7)
	{
	}
	else
	{
	   printf("\nInvelid Semester.");
	   getch();
	   adds_member();
	}
	gotoxy(2,18);
	printf("Student added successfully.");
	getch();
	fwrite(&m,sizeof(m),1,fp);
	fclose(fp);
	student_menu();
}

int last_studid(void)  //function to find last student id.
{
	struct stud_member m;
	int i=0;
	FILE *fp;  //create a file
	flushall();
	fp=fopen("C:\STUDENT.DAT","rb");   //open the binary file in read mode
	while(!feof(fp))   //checks the file till the end
	{
		fread(&m,sizeof(m),1,fp);
		if(feof(fp))
			break;
		i++;
	}
	fclose(fp);  //close the opened file
	return i;
}

void dels_member(void) //function to delete the student record.
{
  int d,findstud=0;
  char another='y';
  FILE *ft,*fp;
  clrscr();
  flushall();

  while(another=='y')
  {
    clrscr();
    gotoxy(10,5);
    printf("Enter the stud id to delete:");
    scanf("%d",&d);
    fp=fopen("C:\STUDENT.dat","rb+");
    while(fread(&stud,sizeof(stud),1,fp)==1)
    {
      if(stud.stud_id==d)
      { findstud=1;
	gotoxy(10,7);
	printf("The student record is available");
	gotoxy(10,9);
	printf("Student name is:%s",stud.stud_name);
	findstud=1;
	gotoxy(10,11);
	printf("Do you want to delete it?(Y/N):");

	if(getch()=='y')
	{
	  ft=fopen("C:\TEST.dat","wb"); //temporary file for delete
	  rewind(fp);
	  while(fread(&stud,sizeof(stud),1,fp)==1)
	  {
	    if(stud.stud_id!=d)
	    {
	      fwrite(&stud,sizeof(stud),1,ft); //write all in tempory file except that we want to delete
	    }
	  }
	  fclose(fp);
	  fclose(ft);
	  remove("C:\STUDENT.dat");
	  rename("C:\TEST.dat","C:\STUDENT.dat");//copy all item from temporary file to fp except we want to delete
	  gotoxy(10,12);
	  printf("The record is sucessfully deleted");
	}
      }
    }
    if(findstud==0)
    {
     gotoxy(10,10);
     printf("No record is found");
     getch();
    }
    findstud=0;
    gotoxy(10,14);
    printf("Delete another record?(Y/N)");
    //fflush(stdin);
    another=getch();
  }
  student_menu();
}

void searchstud(void) //function for finding the record
{
   clrscr();
   flushall();
   gotoxy(20,10);
   printf("**************Search Student********************");
   gotoxy(20,12);
   printf("1.Search By Id");
   gotoxy(20,14);
   printf("2.Search By Name");
   gotoxy(20,16);
   printf("0.Exit");
   gotoxy(15,20);
   printf("Enter Your choice:");
   switch(getch())
   {
    case '1':
	  searchByID();
	  break;
    case '2':
	  searchByName();
	  break;
    case '0':
	  student_menu();
	  break;
    default:
	  gotoxy(10,23);
	  printf("\aWrong Entry!!Please re-entered correct option");
	  getch(); //holds the screen until a key is pressed
   }
}

void searchByID(void)  //function to find record using id.
{

  int id;
  int findstud=0;
  FILE *fp;
  clrscr();
  flushall();
  gotoxy(20,4);
  printf("**********Search By Id*****************");
  gotoxy(20,5);
  printf("Enter the Student id:");
  scanf("%d",&id);


  fp=fopen("C:\STUDENT.dat","rb");

  while(fread(&stud,sizeof(stud),1,fp)==1)
  {
    if(stud.stud_id==id)
    {
      sleep(2);
      gotoxy(20,7);
      printf("The Student is available");
      gotoxy(20,8);
      printf("************************************");
      gotoxy(20,9);
      printf("ID:%d",stud.stud_id);
      gotoxy(20,10);
      printf("Name:%s",stud.stud_name);
      gotoxy(20,11);
      printf("Gender:%s",stud.stud_gender);
      gotoxy(20,12);
      printf("Course:%s",stud.stud_course);
      gotoxy(20,13);
      printf("Semester:%d",stud.stud_sem);
      gotoxy(20,15);
      printf("************************************");
      findstud=1;
    }
  }
  if(findstud==0)
  {
    gotoxy(20,8);
    printf("********************************");
    gotoxy(20,11);
    printf("********************************");
    gotoxy(20,9);
    printf("No Record Found");
  }
  fclose(fp);
  findstud=0;
  gotoxy(20,17);
  printf("Try another search?(y/n)");
  if(getch()=='y')
  {
     searchByID();
  }
  else
  {
     searchstud();
  }
  student_menu();
}

void searchByName(void) //function to find record by using name.
{
  char s[100];
  int d=0;
  FILE *fp;
  clrscr();
  flushall();
  gotoxy(20,4);
  printf("********Search Student By Name**********");
  gotoxy(20,5);
  printf("Enter Student Name:");
  gets(s);
  strupr(s);

  fp=fopen("C:\STUDENT.dat","rb");

  while(fread(&stud,sizeof(stud),1,fp)==1)
  {
   if(strcmp(stud.stud_name,(s))==0)
   {
      gotoxy(20,7);
      printf("The Student is available");
      gotoxy(20,8);
      printf("************************************");
      gotoxy(20,9);
      printf("ID:%d",stud.stud_id);
      gotoxy(20,10);
      printf("Name:%s",stud.stud_name);
      gotoxy(20,11);
      printf("Gender:%s",stud.stud_gender);
      gotoxy(20,12);
      printf("Course:%s",stud.stud_course);
      gotoxy(20,13);
      printf("Semester:%d",stud.stud_sem);
      gotoxy(20,16);
      printf("************************************");
      d++;
   }
  }
  if(d==0)
  {
    gotoxy(20,8);
    printf("************************************");
    gotoxy(20,9);
    printf("No Record Found");
    gotoxy(20,10);
    printf("************************************");
  }

  fclose(fp);
  d=0;
  gotoxy(20,18);
  printf("Try another search?(Y/N)");
  if(getch()=='y')
  {
     searchByName();
  }
  else
  {
     searchstud();
  }
  student_menu();
}

void update_stud(void)  //to modify the record of student
{
  FILE *fp;
  int c=0,d;
  char another='y';
  flushall();
  clrscr();
  gotoxy(20,4);
  printf("**************Update Student Record*****************");

  while(another=='y')
  { clrscr();
    gotoxy(15,6);
    printf("Enter Student Id to be edited:");
    scanf("%d",&d);
    fp=fopen("C:\STUDENT.dat","rb+");
    while(fread(&stud,sizeof(stud),1,fp)==1)
    {
	if(stud.stud_id==d)
	{
	  gotoxy(15,7);
	  printf("the Student is available");
	  gotoxy(15,8);
	  printf("***********************************");
	  gotoxy(15,9);
	  printf("ID:%d",stud.stud_id);
	  gotoxy(15,10);
	  printf("Name:%s",stud.stud_name);
	  gotoxy(15,11);
	  printf("***********************************");
	  gotoxy(15,12);
	  printf("Enter Course of Student:");
	  scanf("%s",stud.stud_course);
	  strupr(stud.stud_course);
	  gotoxy(15,14);
	  printf("Enter Semester of Student:");
	  scanf("%d",&stud.stud_sem);
	  gotoxy(15,16);
	  printf("The record is modified");
	  fseek(fp,ftell(fp)-sizeof(stud),0);
	  fwrite(&stud,sizeof(stud),1,fp);
	  fclose(fp);
	  c=1;
	}
    }
    if(c==0)
    {
	   gotoxy(15,17);
	   printf("No record found");
	   getch();
    }
    gotoxy(15,20);
    c=0;
    printf("Modify another Record?(Y/N)");
    fflush(stdin);
    another=getch();
  }
   student_menu();
}

void teacher_menu(void)   //function
{
	char ch;   //variable declaration
	int i;
	clrscr();
	flushall();
	while(1)
	{
		box(25,5,60,22);
		box(2,2,79,24);
		lineHor(26,59,8);
		lineHor(26,59,20);
		gotoxy(32,6);
		printf("TEACHER MENU");
		gotoxy(32,7);
		printf("~~~~~~~~~~~~~");
		gotoxy(32,10);
		printf("1. ADDITION.");
		gotoxy(32,12);
		printf("2. DELETION.");
		gotoxy(32,14);
		printf("3. UPDATION.");
		gotoxy(32,16);
		printf("4. SEARCH.");
		gotoxy(32,18);
		printf("0. EXIT.");
		gotoxy(32,21);
		printf("Enter Your Choice : ");
		ch=getche();
		if(ch==27)
			return;
		else if(ch=='1')
		{
			addt_member();
			break;
		}
		else if(ch=='2')
		{
			delt_member();
			break;
		}
		else if(ch=='3')
		{
			update_teacher();
			break;
		}
		else if(ch=='4')
		{
			searchteacher();
			break;
		}
		else if(ch=='0')
		{
			main_menu();
			break;
		}
		else
		{
		  gotoxy(10,23);
		  printf("\aWrong Entry!!Please re-entered correct option");
		  getch(); //holds the screen until a key is pressed
		}
	}
}
void addt_member(void) //function to insert teacher detail.
{
	struct teacher_member m;
	int id=0,n,i;
	FILE *fp;
	flushall();
	clrscr();
	gotoxy(20,6);
	printf("TEACHER ADDITION SCREEN");
	gotoxy(20,7);
	printf("----------------------");
	id=last_teacherid();
	id++;
	m.teacher_id=id;
	fp=fopen("C:\TEACHER.DAT","ab+"); //opening the file.
	if(fp==NULL)
	{
		printf("\nError In Opening The File.");
		getch();
		exit(1);
	}
	gotoxy(2,10);
	printf("Enter The Member Name : ");
	fflush(stdin);
	gets(m.teacher_name);
	strupr(m.teacher_name);
	gotoxy(2,12);
	printf("Enter The Member Gender(F/M) : ");
	fflush(stdin);
	gets(m.teacher_gender);
	strupr(m.teacher_gender);
	n=strlen(m.teacher_gender);
	for(i=0;i<n;i++)
	{
	   if(!isalpha(m.teacher_gender[i]))
	   {
	     printf("\nPlease enter string");
	     getch();
	     addt_member();
	   }
	}
	gotoxy(2,14);
	printf("Enter The Department : ");
	fflush(stdin);
	gets(m.teacher_department);
	strupr(m.teacher_department);
	n=strlen(m.teacher_department);
	for(i=0;i<n;i++)
	{
	   if(!isalpha(m.teacher_department[i]))
	   {
	     printf("\nPlease enter string");
	     getch();
	     addt_member();
	   }
	}
	fwrite(&m,sizeof(m),1,fp);
	fclose(fp);
	printf("Teacher added successfully.");
	getch();
	teacher_menu();

}

int last_teacherid(void)  //function to find last teacher id.
{
	struct teacher_member m;
	int i=0;
	FILE *fp;  //create a file
	 flushall();
	fp=fopen("C:\TEACHER.DAT","rb");   //open the binary file in read mode
	while(!feof(fp))   //checks the file till the end
	{
		fread(&m,sizeof(m),1,fp);
		if(feof(fp))
			break;
		i++;
	}
	fclose(fp);  //close the opened file
	return i;
}

void delt_member(void) //function to delete teacher detail.
{
  int d,findteacher=0;
  char another='y';
  FILE *ft,*fp;
  clrscr();
  flushall();

  while(another=='y')
  { clrscr();
    gotoxy(10,5);
    printf("Enter the Teacher id to delete:");
    scanf("%d",&d);
    fp=fopen("C:\TEACHER.dat","rb+");
    while(fread(&teacher,sizeof(teacher),1,fp)==1)
    {
      if(teacher.teacher_id==d)
      {
	gotoxy(10,7);
	printf("The Teacher record is available");
	gotoxy(10,9);
	printf("Teacher name is:%s",teacher.teacher_name);
	findteacher=1;
	gotoxy(10,11);
	printf("Do you want to delete it?(Y/N):");

	if(getch()=='y')
	{
	  ft=fopen("C:\TEST.dat","wb");
	  rewind(fp);
	  while(fread(&teacher,sizeof(teacher),1,fp)==1)
	  {
	    if(teacher.teacher_id!=d)
	    {
	      fwrite(&teacher,sizeof(teacher),1,ft);
	    }
	  }
	  fclose(fp);
	  fclose(ft);
	  remove("C:\TEACHER.dat");
	  rename("C:\TEST.dat","C:\TEACHER.dat");
	  gotoxy(10,12);
	  printf("The record is sucessfully deleted");
	}
      }
    }

    if(findteacher==0)
    {
      gotoxy(10,10);
      printf("No record is found");
      getch();
    }
    findteacher=0;
    gotoxy(10,14);
    printf("Delete another record?(Y/N)");
    another=getch();
  }
   teacher_menu();
}

void searchteacher(void)  //searching the record of teacher.
{
   clrscr();
   flushall();
   gotoxy(20,8);
   printf("************Search Teacher***************");
   gotoxy(20,10);
   printf("1.Search By Id");
   gotoxy(20,12);
   printf("2.Search By Name");
   gotoxy(20,14);
   printf("0.Exit");
   gotoxy(20,16);
   printf("Enter Your choice:");
   switch(getch())
   {
    case '1':
	  searchByID1();
	  break;
    case '2':
	  searchByName1();
	  break;
    case '0':
	  teacher_menu();
	  break;
    default:
	  gotoxy(10,19);
	  printf("\aWrong Entry!!Please re-entered correct option");
	  getch(); //holds the screen until a key is pressed
   }
}

void searchByID1()  //function that search by id.
{

  int id;
  int findteacher=0;
  FILE *fp;
  clrscr();
  flushall();
  gotoxy(25,3);
  printf("**********Search By Id************");
  gotoxy(20,5);
  printf("Enter the Teacher id:");
  scanf("%d",&id);


  fp=fopen("C:\TEACHER.dat","rb");

  while(fread(&teacher,sizeof(teacher),1,fp)==1)
  {
    if(teacher.teacher_id==id)
    {
      sleep(2);
      gotoxy(20,7);
      printf("The Teacher is available");
      gotoxy(20,8);
      printf("************************************");
      gotoxy(20,9);
      printf("ID:%d",teacher.teacher_id);
      gotoxy(20,10);
      printf("Name:%s",teacher.teacher_name);
      gotoxy(20,11);
      printf("Gender:%s",teacher.teacher_gender);
      gotoxy(20,12);
      printf("Department:%s",teacher.teacher_department);
      gotoxy(20,14);
      findteacher=1;
    }
  }
  if(findteacher==0)
  {
    gotoxy(20,8);
    printf("*********************************");
    gotoxy(20,11);
    printf("*********************************");
    gotoxy(20,9);
    printf("No Record Found");
  }
  fclose(fp);
  gotoxy(20,17);
  printf("Try another search?(y/n)");
  if(getch()=='y')
  {
     searchByID1();
  }
  else
  {
     searchteacher();
  }
  teacher_menu();
}

void searchByName1(void) //function to find record by using name.
{
  char s[100];
  int d=0;
  FILE *fp;
  clrscr();
  flushall();
  gotoxy(20,4);
  printf("********Search Teacher By Name**********");
  gotoxy(20,5);
  printf("Enter Teacher Name:");
  gets(s);
  strupr(s);

  fp=fopen("C:\TEACHER.dat","rb");

  while(fread(&teacher,sizeof(teacher),1,fp)==1)
  {
   if(strcmp(teacher.teacher_name,(s))==0)
   {
      gotoxy(20,7);
      printf("The Teacher is available");
      gotoxy(20,8);
      printf("************************************");
      gotoxy(20,9);
      printf("ID:%d",teacher.teacher_id);
      gotoxy(20,10);
      printf("Name:%s",teacher.teacher_name);
      gotoxy(20,11);
      printf("Gender:%s",teacher.teacher_gender);
      gotoxy(20,12);
      printf("Department:%s",teacher.teacher_department);
      gotoxy(20,14);
      printf("************************************");
      d++;
   }
  }
  if(d==0)
  {
    gotoxy(20,8);
    printf("************************************");
    gotoxy(20,9);
    printf("No Record Found");
    gotoxy(20,10);
    printf("************************************");
  }

  fclose(fp);
  d=0;
  gotoxy(20,18);
  printf("Try another search?(Y/N)");
  if(getch()=='y')
     searchByName1();
  else
     searchteacher();
}

void update_teacher(void) //modify record of teacher.
{
  FILE *fp;
  int c=0,d;
  char another='y';
   flushall();
  clrscr();
  gotoxy(20,4);
  printf("**************Update Staff Record*****************");

  while(another=='y')
  { clrscr();
    gotoxy(15,6);
    printf("Enter teacher Id to be edited:");
    scanf("%d",&d);
    fp=fopen("C:\TEACHER.dat","rb+");
    while(fread(&teacher,sizeof(teacher),1,fp)==1)
    {
	if(teacher.teacher_id==d)
	{
	  gotoxy(15,7);
	  printf("the Teacher is available");
	  gotoxy(15,8);
	  printf("***********************************");
	  gotoxy(15,9);
	  printf("ID:%d",teacher.teacher_id);
	  gotoxy(15,10);
	  printf("Name:%s",teacher.teacher_name);
	  gotoxy(15,11);
	  printf("***********************************");
	  gotoxy(15,12);
	  printf("Enter Department of Teacher:");
	  scanf("%s",teacher.teacher_department);
	  strupr(teacher.teacher_department);
	  gotoxy(15,14);
	  printf("The record is modified");
	  fseek(fp,ftell(fp)-sizeof(teacher),0);
	  fwrite(&teacher,sizeof(teacher),1,fp);
	  fclose(fp);
	  c=1;
	}
    }
	if(c==0)
	{
	   gotoxy(15,17);
	   printf("No record found");
	}
    gotoxy(15,20);
    c=0;
    printf("Modify another Record?(Y/N)");
    another=getch();
  }
   teacher_menu();
}

void book_menu(void)   //function
{
	char ch;   //variable declaration
	int i;
	clrscr();
	flushall();
	while(1)
	{
		box(25,5,60,22);
		box(2,2,79,24);
		lineHor(26,59,8);
		lineHor(26,59,20);
		gotoxy(32,6);
		printf("BOOK MENU");
		gotoxy(32,7);
		printf("~~~~~~~~~~~~~");
		gotoxy(32,10);
		printf("1. ADDITION.");
		gotoxy(32,12);
		printf("2. DELETION.");
		gotoxy(32,14);
		printf("3. UPDATION.");
		gotoxy(32,16);
		printf("4. SEARCH.");
		gotoxy(32,18);
		printf("0. EXIT.");
		gotoxy(32,21);
		printf("Enter Your Choice : ");
		ch=getche();
		if(ch==27)
			return;
		else if(ch=='1')
		{
			add_book();
			break;
		}
		else if(ch=='2')
		{
			delb_book();
			break;
		}
		else if(ch=='3')
		{
			update_book();
			break;
		}
		else if(ch=='4')
		{
			searchbook();
			break;
		}
		else if(ch=='0')
		{
			main_menu();
			break;
		}
		else
		{
		  gotoxy(10,23);
		  printf("\aWrong Entry!!Please re-entered correct option");
		  getch(); //holds the screen until a key is pressed
		}
	}
}

void add_book(void)
{
	struct book m;
	int id=0;
	FILE *fp;
	flushall();
	clrscr();
	gotoxy(20,6);
	printf("BOOK ADDITION SCREEN");
	gotoxy(20,7);
	printf("--------------------");
	id=last_bookid();
	id++;
	m.book_id=id;
	fp=fopen("C:\BOOK.DAT","ab+");
	if(fp==NULL)
	{
		printf("\nError In Opening The File.");
		getch();
		exit(1);
	}
	gotoxy(2,10);
	printf("Enter The Book Name : ");
	gets(m.book_name);
	strupr(m.book_name);
	gotoxy(2,12);
	printf("Enter The Publisher : ");
	gets(m.book_pub);
	strupr(m.book_pub);
	gotoxy(2,14);
	printf("Enter The Author Name : ");
	gets(m.book_auth);
	strupr(m.book_auth);
	gotoxy(2,16);
	printf("Enter The Price : ");
	if(scanf("%d",&m.book_price)!=1)
	{
	  printf("Please enter number value.");
	  getch();
	  add_book();
	}
	m.bk_sts=0;
	strcpy(m.bk_user,"null");
	m.m_id=0;
	fwrite(&m,sizeof(m),1,fp);
	fclose(fp);
	printf("\nBook added successfully.");
	getch();
	book_menu();
}

int last_bookid(void)
{
	int i=0;
	struct book m;
	FILE *fp;
	 flushall();
	fp=fopen("C:\BOOK.DAT","rb");
	while(!feof(fp))
	{
		fread(&m,sizeof(m),1,fp);  //read the data
		if(feof(fp))
			break;
		i++;
	}
	fclose(fp);
	return i;
}

void delb_book(void)
{
  int d,findbook=0;
  char another='y';
  FILE *ft,*fp;
  clrscr();
  flushall();

  while(another=='y')
  {
    clrscr();
    gotoxy(10,5);
    printf("Enter the Book id to delete:");
    scanf("%d",&d);
    fp=fopen("C:\BOOK.dat","rb+");
    while(fread(&book,sizeof(book),1,fp)==1)
    {
      if(book.book_id==d)
      {
	gotoxy(10,7);
	printf("The Book record is available");
	gotoxy(10,9);
	printf("Book name is:%s",book.book_name);
	findbook=1;
	gotoxy(10,11);
	printf("Do you want to delete it?(Y/N):");

	if(getch()=='y')
	{
	  ft=fopen("C:\TEST.dat","wb");
	  rewind(fp);
	  while(fread(&book,sizeof(book),1,fp)==1)
	  {
	    if(book.book_id!=d)
	    {
	      fwrite(&book,sizeof(book),1,ft);
	    }
	  }
	  fclose(fp);
	  fclose(ft);
	  remove("C:\BOOK.dat");
	  rename("C:\TEST.dat","C:\BOOK.dat");
	  gotoxy(10,12);
	  printf("The record is sucessfully deleted");
	}
      }
    }

    if(findbook==0)
    {
      gotoxy(10,10);
      printf("No record is found");
      getch();
    }

    gotoxy(10,14);
    findbook=0;
    printf("Delete another record?(Y/N)");
    another=getch();
  }
   book_menu();
}

void searchbook(void)
{
   clrscr();
   flushall();
   gotoxy(20,10);
   printf("**********search Book*************");
   gotoxy(20,12);
   printf("1.Search By Id");
   gotoxy(20,14);
   printf("2.Search By Name");
   gotoxy(20,16);
   printf("0.Exit");
   gotoxy(15,20);
   printf("Enter Your choice:");
   switch(getch())
   {
    case '1':
	  searchByID2();
	  break;
    case '2':
	  searchByName2();
	  break;
    case '0':
	  book_menu();
	  break;
    default:
	  gotoxy(10,23);
	  printf("\aWrong Entry!!Please re-entered correct option");
	  getch(); //holds the screen until a key is pressed
   }
}

void searchByID2()
{

  int id;
  int findbook=0;
  FILE *fp;
  clrscr();
  flushall();
  gotoxy(25,4);
  printf("**********Search By Id*****************");
  gotoxy(20,5);
  printf("Enter the Book id:");
  scanf("%d",&id);


  fp=fopen("C:\BOOK.dat","rb");

  while(fread(&book,sizeof(book),1,fp)==1)
  {
    if(book.book_id==id)
    {
      sleep(2);
      gotoxy(20,7);
      printf("The Book is available");
      gotoxy(20,8);
      printf("************************************");
      gotoxy(20,9);
      printf("ID:%d",book.book_id);
      gotoxy(20,10);
      printf("Name:%s",book.book_name);
      gotoxy(20,11);
      printf("Publisher:%s",book.book_pub);
      gotoxy(20,12);
      printf("Author:%s",book.book_auth);
      gotoxy(20,14);
      printf("Price:%d",book.book_price);
      findbook=1;
    }
  }
  if(findbook==0)
  {
    clrscr();
    gotoxy(20,8);
    printf("************************************");
    gotoxy(20,11);
    printf("************************************");
    gotoxy(20,9);
    printf("No Record Found");
  }
  fclose(fp);
  gotoxy(20,17);
  printf("Try another search?(y/n)");
  if(getch()=='y')
  {
     searchByID2();
  }
  else
  {
     searchbook();
  }
}

void searchByName2(void) //function to find record by using name.
{
  char s[100];
  int d=0;
  FILE *fp;
  clrscr();
  flushall();
  gotoxy(20,4);
  printf("********Search Book By Name**********");
  gotoxy(20,5);
  printf("Enter Book Name:");
  gets(s);
  strupr(s);

  fp=fopen("C:\BOOK.dat","rb");

  while(fread(&book,sizeof(book),1,fp)==1)
  {
   if(strcmp(book.book_name,(s))==0)
   {
      gotoxy(20,7);
      printf("The Book is available");
      gotoxy(20,8);
      printf("************************************");
      gotoxy(20,9);
      printf("ID:%d",book.book_id);
      gotoxy(20,10);
      printf("Publisher:%s",book.book_pub);
      gotoxy(20,11);
      printf("Author:%s",book.book_auth);
      gotoxy(20,12);
      printf("Price:%d",book.book_price);
      gotoxy(20,14);
      printf("************************************");
      d++;
   }
  }
  if(d==0)
  {
    gotoxy(20,8);
    printf("************************************");
    gotoxy(20,9);
    printf("No Record Found");
    gotoxy(20,10);
    printf("************************************");
  }

  fclose(fp);
  gotoxy(20,18);
  printf("Try another search?(Y/N)");
  if(getch()=='y')
  {
     searchByName2();
  }
  else
  {
     searchbook();
  }
}

void update_book(void) //modify record of book.
{
  FILE *fp;
  int c=0,d;
  char another='y';
   flushall();
  clrscr();
  gotoxy(20,4);
  printf("**************Update Book Record*****************");

  while(another=='y')
  {
    struct book book;
    clrscr();
    gotoxy(15,6);
    printf("Enter Book Id to be edited:");
    scanf("%d",&d);
    fp=fopen("C:\BOOK.dat","rb+");
    while(fread(&book,sizeof(book),1,fp)==1)
    {
	if(book.book_id==d)
	{
	  gotoxy(15,7);
	  printf("the Book is available");
	  gotoxy(15,8);
	  printf("***********************************");
	  gotoxy(15,9);
	  printf("ID:%d",book.book_id);
	  gotoxy(15,10);
	  printf("Name:%s",book.book_name);
	  gotoxy(15,11);
	  printf("Publisher:%s",book.book_pub);
	  gotoxy(15,12);
	  printf("Author:%s",book.book_auth);
	  gotoxy(15,13);
	  printf("***********************************");
	  gotoxy(15,15);
	  printf("Enter Price of book:");
	  scanf("%d",&book.book_price);
	  gotoxy(15,19);
	  printf("The record is modified");
	  fseek(fp,ftell(fp)-sizeof(book),0);//fseek is used to change specified stream.
	  fwrite(&book,sizeof(book),1,fp);
	  fclose(fp);
	  c=1;
	}
    }
    if(c==0)
	{
	   gotoxy(15,19);
	   printf("No record found");
	}
    gotoxy(15,21);
    c=0;
    printf("Modify another Record?(Y/N)");
    another=getch();
  }
   book_menu();
}
void list(void)   //function for list of data.
{
	char ch;   //variable declaration
	int i;
	clrscr();
	flushall();
	while(1)
	{
		box(25,5,60,22);
		box(2,2,79,24);
		lineHor(26,59,8);
		lineHor(26,59,20);
		gotoxy(32,6);
		printf("LIST MENU");
		gotoxy(32,7);
		printf("~~~~~~~~~~~~~");
		gotoxy(32,10);
		printf("1. STUDENT LIST.");
		gotoxy(32,12);
		printf("2. TEACHER LIST.");
		gotoxy(32,14);
		printf("3. BOOK LIST.");
		gotoxy(32,16);
		printf("0. EXIT.");
		gotoxy(32,21);
		printf("Enter Your Choice : ");
		ch=getche();
		if(ch==27)
			return;
		else if(ch=='1')
		{
			stud_list();
			break;
		}
		else if(ch=='2')
		{
			teacher_list();
			break;
		}
		else if(ch=='3')
		{
			book_list();
			break;
		}
		else if(ch=='0')
		{
			main_menu();
			break;
		}
		else
		{
		  gotoxy(10,23);
		  printf("\aWrong Entry!!Please re-entered correct option");
		  getch(); //holds the screen until a key is pressed
		}
	}
}

void stud_list(void)
{
    int j;
    FILE *fp;
    clrscr();
    flushall();

    gotoxy(1,1);
    printf("*********************************Student List*****************************");
    gotoxy(2,2);
    printf(" Member ID      NAME	         Gender    Course   Sem");
    j=4;
    fp=fopen("C:\STUDENT.dat","rb");
    while(fread(&stud,sizeof(stud),1,fp)==1)
    {
	flushall();
	gotoxy(3,j);
	printf("%d",stud.stud_id);
	gotoxy(16,j);
	printf("%s",stud.stud_name);
	gotoxy(40,j);
	printf("%s",stud.stud_gender);
	gotoxy(47,j);
	printf("%s",stud.stud_course);
	gotoxy(55,j);
	printf("%d",stud.stud_sem);
	printf("\n\n");
	j++;
    }
    gotoxy(1,25);
    printf("Press any Key to continue...");
    getch();
    fclose(fp);
    list();
 }

void teacher_list(void)
{
    int j;
    FILE *fp;
    clrscr();
    flushall();

    gotoxy(1,1);
    printf("*********************************Staff List*****************************");
    gotoxy(2,2);
    printf(" Member ID      NAME		Gender		Department ");
    j=4;
    fp=fopen("C:\TEACHER.dat","rb");
    while(fread(&teacher,sizeof(teacher),1,fp)==1)
    {
	flushall();
	gotoxy(3,j);
	printf("%d",teacher.teacher_id);
	gotoxy(16,j);
	printf("%s",teacher.teacher_name);
	gotoxy(40,j);
	printf("%s",teacher.teacher_gender);
	gotoxy(50,j);
	printf("%s",teacher.teacher_department);
	printf("\n\n");
	j++;
    }
    gotoxy(1,25);
    printf("Press any Key to continue...");
    getch();
    fclose(fp);
    list();
 }

void book_list(void)
{
    int j;
    FILE *fp;
    clrscr();
    flushall();

    gotoxy(1,1);
    printf("*********************************Book List*****************************");
    gotoxy(2,2);
    printf(" BOOK ID  NAME      Publiser   author      price  states Issue_to_User");
    j=4;
    fp=fopen("C:\BOOK.dat","rb");
    while(fread(&book,sizeof(book),1,fp)==1)
    {
	flushall();
	gotoxy(3,j);
	printf("%d",book.book_id);
	gotoxy(14,j);
	printf("%s",book.book_name);
	gotoxy(23,j);
	printf("%s",book.book_pub);
	gotoxy(33,j);
	printf("%s",book.book_auth);
	gotoxy(46,j);
	printf("%d",book.book_price);
	gotoxy(53,j);
	printf("%d",book.bk_sts);
	gotoxy(62,j);
	printf("%s",book.bk_user);
	gotoxy(70,j);
	printf("%d",book.m_id);
	printf("\n\n");
	j++;
    }
    gotoxy(1,25);
    printf("Press any Key to continue...");
    getch();
    fclose(fp);
    list();
 }

void transaction_menu(void)
{
	char ch;
	int i;
	flushall();
	clrscr();
	box1();
	box(25,5,60,23);
	lineHor(26,59,8);
	lineHor(26,59,21);
	while(1)
	{
		gotoxy(32,6);
		printf("TRANSACTION MENU");
		gotoxy(32,7);
		printf("~~~~~~~~~~~~~~~~");
		gotoxy(32,10);
		printf("1. STUDENT SECTION.");
		gotoxy(32,12);
		printf("2. TEACHER SECTION.");
		gotoxy(32,14);
		printf("0. EXIT.");
		gotoxy(32,22);
		printf("Enter Your Choice : ");
		ch=getche();
		if(ch==27)
			return;
		else if(ch=='1')
		{
			transactions_menu();
			break;
		}
		else if(ch=='2')
		{
			transactiont_menu();
			exit(1);
			break;
		}
		else if(ch=='0')
			main_menu();
			break;
	}
}

void transactions_menu(void)
{
	char ch;
	int i;
	flushall();
	clrscr();
	box1();
	box(25,5,60,23);
	lineHor(26,59,8);
	lineHor(26,59,21);
	while(1)
	{
		gotoxy(32,6);
		printf("STUDENT TRANSACTION MENU");
		gotoxy(32,7);
		printf("~~~~~~~~~~~~~~~~~~~~~~~~");
		gotoxy(32,10);
		printf("1. ISSUE.");
		gotoxy(32,12);
		printf("2. RETURN.");
		gotoxy(32,14);
		printf("0. EXIT.");
		gotoxy(32,22);
		printf("Enter Your Choice : ");
		ch=getche();
		if(ch==27)
			return;
		else if(ch=='1')
		{
			trans_issue();
			break;
		}
		else if(ch=='2')
		{
			trans_return();
			break;
		}
		else if(ch=='0')
			transaction_menu();
			break;
	}
}

void trans_issue(void)
{
	int mem_id,bk_id;
	int fnd_mem=0;
	int fnd_bk=0;
	int i=0;
	long size;
	FILE *fp_mem,*fp_bk;
	flushall();
	clrscr();
	fp_mem=fopen("C:\STUDENT.DAT","rb");
	if(fp_mem==NULL)
	{
		fclose(fp_mem);
		fp_mem=fopen("C:\STUDENT.DAT","wb");
		fclose(fp_mem);
		fp_mem=fopen("C:\STUDENT.DAT","rb");
	}
	fp_bk=fopen("C:\BOOK.DAT","rb+");
	if(fp_bk==NULL)
	{
		fclose(fp_bk);
		fp_bk=fopen("C:\BOOK.DAT","wb");
		fclose(fp_bk);
		fp_bk=fopen("C:\BOOK.DAT","rb+");
	}
	gotoxy(20,5);
	printf("BOOK ISSUE SCREEN");
	gotoxy(20,6);
	printf("-----------------");
	gotoxy(5,9);
	printf("Enter The Stud Id : ");
	scanf("%d",&mem_id);
	while(!feof(fp_mem))
	{
		fread(&stud,sizeof(stud),1,fp_mem);
		if(feof(fp_mem))
			break;
		if(stud.stud_id==mem_id)
		{
			fnd_mem=1;
			gotoxy(5,11);
			printf("Enter The Book Id : ");
			scanf("%d",&bk_id);
			while(!feof(fp_bk))
			{
				fread(&book,sizeof(book),1,fp_bk);
				if(feof(fp_bk))
					break;
				i++;
				if(book.book_id==bk_id&&book.bk_sts!=1)
				{
					gotoxy(5,13);
					fnd_bk=1;
					size=(i-1)*sizeof(book);
					book.bk_sts=1;
					book.m_id=mem_id;
					strcpy(book.bk_user,"student");
					gotoxy(5,13);
					printf("Book will issue to student %d.",mem_id);
					getch();
					fseek(fp_bk,size,SEEK_SET);
					fwrite(&book,sizeof(book),1,fp_bk);
				}
			}
		}
	}
	fclose(fp_mem);
	fclose(fp_bk);
	if(fnd_mem==0)
	{
		gotoxy(1,24);
		clreol();
		gotoxy(1,25);
		clreol();
		gotoxy(10,25);
		printf("Member Not Found.");
	}
	else if(fnd_bk==0)
	{
		gotoxy(1,24);
		clreol();
		gotoxy(1,25);
		clreol();
		gotoxy(10,25);
		printf("Book Is Already Isued or Not in Book list.");
	}
	getch();
	transactions_menu();
}

void trans_return()
{
	int bk_id,result;
	int fnd_bk=0,i=0;
	int fnd_tran=0;
	long size=0;
	FILE *fp_bk;
	flushall();
	clrscr();
	fp_bk=fopen("C:\BOOK.DAT","rb+");
	if(fp_bk==NULL)
	{
		fclose(fp_bk);
		fp_bk=fopen("C:\BOOK.DAT","wb");
		fclose(fp_bk);
		fp_bk=fopen("C:\BOOK.DAT","rb+");
	}
	gotoxy(20,5);
	printf("BOOK RETURN SCREEN");
	gotoxy(20,6);
	printf("-----------------");
	gotoxy(5,9);
	printf("Enter The Book Id : ");
	scanf("%d",&bk_id);
	while(!feof(fp_bk))
	{
		fread(&book,sizeof(book),1,fp_bk);
		if(feof(fp_bk))
			break;
		i++;
		if(book.book_id==bk_id&&book.bk_sts==1)
		{
			fnd_bk=1;
			fnd_tran=1;
			if(strcmp(book.bk_user,"student")==0)
			{
				size=(i-1)*sizeof(book);
				book.bk_sts=0;
				strcpy(book.bk_user,"null");
				book.m_id=0;
				fseek(fp_bk,size,SEEK_SET);
				fwrite(&book,sizeof(book),1,fp_bk);
				fclose(fp_bk);
			}
			else
			{
			   gotoxy(10,20);
			   printf("User is not a student");
			   getch();
			   break;
			}
		}
		else
		{
		  gotoxy(10,22);
		  printf("Check Book id and User type.");
		  getch();
		  break;
		}

	}
	if(fnd_bk==0||fnd_tran==0)
	{
		gotoxy(10,24);
		clreol();
		gotoxy(10,25);
		clreol();
		gotoxy(10,25);
		printf("This Is Book. which iz Not Issued Till.");
	}
transactions_menu();
}

void transactiont_menu(void)
{
	char ch;
	int i;
	flushall();
	clrscr();
	box1();
	box(25,5,60,23);
	lineHor(26,59,8);
	lineHor(26,59,21);
	while(1)
	{
		gotoxy(32,6);
		printf("TEACHER TRANSACTION MENU");
		gotoxy(32,7);
		printf("~~~~~~~~~~~~~~~~~~~~~~~~");
		gotoxy(32,10);
		printf("1. ISSUE.");
		gotoxy(32,12);
		printf("2. RETURN.");
		gotoxy(32,14);
		printf("0. EXIT.");
		gotoxy(32,22);
		printf("Enter Your Choice : ");
		ch=getche();
		if(ch==27)
			return;
		else if(ch=='1')
		{
			trant_issue();
			break;
		}
		else if(ch=='2')
		{
			trant_return();
			break;
		}
		else if(ch=='0')
			transaction_menu();
			break;
	}
}
void trant_issue(void)
{
	int mem_id,bk_id;
	int fnd_mem=0;
	int fnd_bk=0;
	int i=0;
	long size;
	FILE *fp_mem,*fp_bk;
	flushall();
	clrscr();
	fp_mem=fopen("C:\TEACHER.DAT","rb");
	if(fp_mem==NULL)
	{
		fclose(fp_mem);
		fp_mem=fopen("C:\TEACHER.DAT","wb");
		fclose(fp_mem);
		fp_mem=fopen("C:\TEACHER.DAT","rb");
	}
	fp_bk=fopen("C:\BOOK.DAT","rb+");
	if(fp_bk==NULL)
	{
		fclose(fp_bk);
		fp_bk=fopen("C:\BOOK.DAT","wb");
		fclose(fp_bk);
		fp_bk=fopen("C:\BOOK.DAT","rb+");
	}
	gotoxy(20,5);
	printf("BOOK ISSUE SCREEN");
	gotoxy(20,6);
	printf("-----------------");
	gotoxy(5,9);
	printf("Enter The Teacher Id : ");
	scanf("%d",&mem_id);
	while(!feof(fp_mem))
	{
		fread(&teacher,sizeof(teacher),1,fp_mem);
		if(feof(fp_mem))
			break;
		if(teacher.teacher_id==mem_id)
		{
			fnd_mem=1;
			gotoxy(5,11);
			printf("Enter The Book Id : ");
			scanf("%d",&bk_id);
			while(!feof(fp_bk))
			{
				fread(&book,sizeof(book),1,fp_bk);
				if(feof(fp_bk))
					break;
				i++;
				if(book.book_id==bk_id&&book.bk_sts!=1)
				{
					gotoxy(5,13);
					fnd_bk=1;
					size=(i-1)*sizeof(book);
					book.bk_sts=1;
					book.m_id=mem_id;
					strcpy(book.bk_user,"teacher");
					gotoxy(5,13);
					printf("Book will issue to teacher %d.",mem_id);
					getch();
					fseek(fp_bk,size,SEEK_SET);
					fwrite(&book,sizeof(book),1,fp_bk);
				}
			}
		}
	}
	fclose(fp_mem);
	fclose(fp_bk);
	if(fnd_mem==0)
	{
		gotoxy(1,24);
		clreol();
		gotoxy(1,25);
		clreol();
		gotoxy(10,25);
		printf("Member Not Found.");
	}
	else if(fnd_bk==0)
	{
		gotoxy(1,24);
		clreol();
		gotoxy(1,25);
		clreol();
		gotoxy(10,25);
		printf("Book Is Already Isued or Not in Book List.");
	}
	getch();
	transactiont_menu();
}

void trant_return()
{
	int bk_id,result;
	int fnd_bk=0,i=0;
	int fnd_tran=0;
	long size=0;
	FILE *fp_bk;
	flushall();
	clrscr();
	fp_bk=fopen("C:\BOOK.DAT","rb+");
	if(fp_bk==NULL)
	{
		fclose(fp_bk);
		fp_bk=fopen("C:\BOOK.DAT","wb");
		fclose(fp_bk);
		fp_bk=fopen("C:\BOOK.DAT","rb+");
	}
	gotoxy(20,5);
	printf("BOOK RETURN SCREEN");
	gotoxy(20,6);
	printf("-----------------");
	gotoxy(5,9);
	printf("Enter The Book Id : ");
	scanf("%d",&bk_id);
	while(!feof(fp_bk))
	{
		fread(&book,sizeof(book),1,fp_bk);
		if(feof(fp_bk))
			break;
		i++;
		if(book.book_id==bk_id&&book.bk_sts==1)
		{
			fnd_bk=1;
			fnd_tran=1;
			puts(book.bk_user);
			if(strcmp(book.bk_user,"teacher")==0)
			{
				size=(i-1)*sizeof(book);
				book.bk_sts=0;
				strcpy(book.bk_user,"null");
				book.m_id=0;
				fseek(fp_bk,size,SEEK_SET);
				fwrite(&book,sizeof(book),1,fp_bk);
				fclose(fp_bk);
			}
			else
			{
			   gotoxy(10,20);
			   printf("User is not a teacher");
			   getch();
			   break;
			}
		}
		else
		{
		  gotoxy(10,22);
		  printf("Check Book id and User type.");
		  break;
		}

	}
	if(fnd_bk==0||fnd_tran==0)
	{
		gotoxy(10,24);
		//clreol();
		gotoxy(10,25);
		//clreol();
		gotoxy(10,25);
		printf("This Is Book. which iz Not Issued Till or Not in BOOk list.");
	}
transactiont_menu();
}
