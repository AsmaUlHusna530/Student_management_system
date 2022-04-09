#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>




void add(FILE * fp); //to add to list
FILE * del(FILE * fp);//to delete from list
void edit(FILE * fp);//to edit a record
void displayList(FILE * fp);//display whole list
void searchRecord(FILE *fp);//find a particular record
void printChar(char ch,int n);//printing a character ch n times
void printHead();//printing head line for each screen

struct Stud
{
    char name[100];
    char dept[50];
    char sem[50];
    int ID;
    float cgpa;
}s;


int main()
{
 FILE * fp;

int option;
char another;

if((fp=fopen("studentInfo.txt","rb+"))==NULL)
{
    if((fp=fopen("studentInfo.txt","wb+"))==NULL)
       {
           printf("can't open file");
           return 0;
       }
}

printHead();

while(1)
{
    printHead();
    printf("\n\t");

    printf("\n\n\t\t\t1. INSERT Student");
    printf("\n\n\t\t\t2. DELETE Student");
    printf("\n\n\t\t\t3. EDIT Student LIST");
    printf("\n\n\t\t\t4. DISPLAY Student LIST");
    printf("\n\n\t\t\t5. SEARCH Record");
    printf("\n\n\t\t\t0. EXIT");

    printf("\n\n\t\tEnter Your Option :  ");
    scanf("%d",&option);

    switch(option)
    {
        case 0: return 1;
                break;
        case 1: add(fp);
                break;
        case 2: fp=del(fp);
                break;
        case 3: edit(fp);
                break;
        case 4: displayList(fp);
                break;
        case 5: searchRecord(fp);
                break;
        default: printf("\n\t\tYou Pressed wrong key");
                  exit(0);

    }
}
return 1;

}

//----printing character ch at n times ------

void printChar(char ch,int n)
{int i;
    for(i=0;i<=n;i++)
    {
        putchar(ch);
    }
}

//-----Printing Head Line of the program -----

void printHead()
{ system("cls");

printf("\n\n\t");
printChar('=',16);
printf(" [STUDENT  INFORMATION  SYSTEM] ");
printChar('=',16);
printf("\n");
}


// ==========ADDING NEW RECORD==========================

void add(FILE * fp)
{
printHead();

char another='y';




fseek(fp,0,SEEK_END);
while(another=='y'||another=='Y')
{

    printf("\n\n\t\tEnter Full Name of Student:\t");
    fflush(stdin);
    fgets(s.name,100,stdin); //fgets takes an extra \n character as input
    s.name[strlen(s.name)-1]='\0';

    printf("\n\n\t\tEnter Department:\t");
    fflush(stdin);
    fgets(s.dept,50,stdin);
    s.dept[strlen(s.dept)-1]='\0';

    printf("\n\n\t\tEnter Semester: \t");
    fflush(stdin);
    fgets(s.sem,50,stdin);
    s.sem[strlen(s.sem)-1]='\0';



    printf("\n\n\t\tEnter ID: \t");
    scanf("%d",&s.ID);


    printf("\n\n\t\tEnter CGPA: \t");
    scanf("%f",&s.cgpa);


    fwrite(&s,sizeof(s),1,fp);

    printf("\n\n\t\tWant to enter another student info (Y/N)\t");
    fflush(stdin);
    another=getchar();
}
}


//===================DELETING A RECORD FROM LIST ============
FILE * del(FILE * fp)
{
 printHead();


int flag=0,tempID,siz=sizeof(s);
FILE *ft;

if((ft=fopen("temp.txt","wb+"))==NULL)
{
    printf("\n\n\t\t\t\\t!!! ERROR !!!\n\t\t");
    system("pause");
     return fp;
}

printf("\n\n\tEnter ID of Student to Delete the Record");
printf("\n\n\t\t\tID No. : ");
scanf("%d",&tempID);

rewind(fp);


while((fread(&s,siz,1,fp))==1)
{
    if(s.ID==tempID)
    { flag=1;
    printf("\n\tRecord Deleted for");
    printf("\n\n\t\t%s\n\n\t\t%s\n\n\t\t%s\n\n\t\t%d\n\t\n\n\t\t%f",s.name,s.dept,s.sem,s.ID,s.cgpa);

    }

    fwrite(&s,siz,1,ft);
}


fclose(fp);
fclose(ft);

remove("studentInfo.txt");
rename("temp.txt","studentInfo.txt");

if((fp=fopen("studentInfo.txt","rb+"))==NULL)
{
    printf("ERROR");
    return  NULL;
}

if(flag==0)
printf("\n\n\t\t**** RECORD NOT FOUND**** \n\t");

printChar('-',65);
printf("\n\t");
system("pause");
return fp;
}


//===========MODIFY A RECORD ===========================

void edit(FILE * fp)
{
printHead();


int i,flag=0,tempID,siz=sizeof(s);


printf("\n\n\tEnter ID  of Student to EDIT the Record : ");
scanf("%d",&tempID);

rewind(fp);

while((fread(&s,siz,1,fp))==1)
{
    if(s.ID==tempID)
        {flag=1;
        break;
        }
}

if(flag==1)
    {
    fseek(fp,-siz,SEEK_CUR);
    printf("\n\n\t\tRECORD FOUND");
    printf("\n\n\t\tEnter New Data for the Record");

     printf("\n\n\t\tEnter Full Name of Student\t");
    fflush(stdin);
    fgets(s.name,100,stdin); //fgets takes an extra \n character as input
    s.name[strlen(s.name)-1]='\0';

    printf("\n\n\t\tEnter Department\t");
    fflush(stdin);
    fgets(s.dept,50,stdin);
    s.dept[strlen(s.dept)-1]='\0';

    printf("\n\n\t\tEnter Semester\t");
    fflush(stdin);
    fgets(s.sem,50,stdin);
    s.sem[strlen(s.sem)-1]='\0';



    printf("\n\n\t\tEnter ID \t");
    scanf("%d",&s.ID);

    printf("\n\n\t\tEnter CGPA \t");
    scanf("%f",&s.cgpa);


    fwrite(&s,sizeof(s),1,fp);
}

else printf("\n\n\t!!!! ERROR !!!! RECORD NOT FOUND");

printf("\n\n\t");
system("pause");

}

//====================DISPLAY THE LIST =================
void displayList(FILE * fp)
{   printHead();

    int i,siz=sizeof(s);

    rewind(fp);

    while((fread(&s,siz,1,fp))==1)
    {
        printf("\n\t\tNAME : %s",s.name);
        printf("\n\n\t\tDEPARTMENT : %s",s.dept);
        printf("\n\n\t\tSEMESTER : %s",s.sem);
        printf("\n\n\t\tID : %d",s.ID);
        printf("\n\n\t\tCGPA: %f",s.cgpa);


    }
    printf("\n\n\n\t");
     printChar('*',65);
    printf("\n\n\t");
    system("pause");
}

void searchRecord(FILE *fp)
{printHead();

int tempID,flag,siz;

char another='y';

siz=sizeof(s);

while(another=='y'||another=='Y')
{
printf("\n\n\tEnter ID Number of Student to search the record : ");
scanf("%d",&tempID);

rewind(fp);

while((fread(&s,siz,1,fp))==1)
{
    if(s.ID==tempID)
        {flag=1;
        break;
        }
}

if(flag==1)
    {
        printf("\n\t\tNAME : %s",s.name);
        printf("\n\n\t\tDEPARTMENT : %s",s.dept);
        printf("\n\n\t\tSEMESTER : %s",s.sem);
        printf("\n\n\t\tID : %d",s.ID);
        printf("\n\n\t\tCGPA: %f",s.cgpa);


        printChar('-',65);

}
else printf("\n\n\t\t!!!! ERROR RECORD NOT FOUND !!!!");


printf("\n\n\t\tWant to enter another search (Y/N)");
fflush(stdin);
another=getchar();
}
}

