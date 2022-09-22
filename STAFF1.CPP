#include<fstream.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<iomanip.h>
#include<dos.h>
int n=0;
class group
{
    protected:
    struct staff
    {
     char flag;
     char stfid[50];
     char stfname[50];
     char degsin[50];
     char phone[10];
     int exp;
    }b;
     fstream file;
    public:
    group();
    void insert();
    void display();
    void update();
    void search();
    void deletion();
    void exit();
}; struct primary
    {
    char key[10];
    int offset;
    };
primary index[10];
void main()
{
    int choice;
    char pass[20];
    clrscr();
    group g;
y:      clrscr();
    gotoxy(12,12);
    cout<<"ENTER THE PASSWORD  :";
    cin>>pass;
    if(strcmp(pass,"mohan")==0)
    goto z;
    else
    {
	gotoxy(12,12);
	cout<<"INCORRECT PASSWORD";
	sound(1000);
	delay(1000);
	nosound();
	clrscr();
	goto y;
    }
    //group g;
z:      do
    {
      clrscr();
      gotoxy(30,4);
      cout<<"*********************";
      gotoxy(30,5);
      cout<<"  STAFF MANAGEMENT";
      gotoxy(30,6);
      cout<<"*********************";
      gotoxy(30,10);
      cout<<"1.insert record";
      gotoxy(30,11);
      cout<<"2.display";
      gotoxy(30,12);
      cout<<"3.update";
      gotoxy(30,13);
      cout<<"4.search by primarykey";
      gotoxy(30,14);
      cout<<"5.delete";
      gotoxy(30,15);
      cout<<"6.exit";
      gotoxy(30,20);
      cout<<"enter your choice  :";
      cin>>choice;
      clrscr();
      switch(choice)
      {
	case 1:
	     g.insert();
	     break;
	case 2:
	     g.display();
	     break;
	case 3:
	     g.update();
	     break;
	case 4:
	     g.search();
	     break;
	case 5:
	     g.deletion();
	     break;
	case 6:
	     g.exit();
	     exit(1);
    }
      }while(choice != 0);
}

void group::group() //zero argument constructor
{
 file.open("staff1.txt",ios::binary|ios::in|ios::out);
 if(!file)
    {
      cout<<endl<<"unable to open the file";
       exit();
    }
}


//adds record to the file
void group::insert()
{
    char ch;
    file.seekp(0L,ios::end);
    do
    {
     cout<<endl<<"enter staff id :";
     gets(b.stfid);
     cout<<endl<<"enter staff name :";
     gets(b.stfname);
     cout<<endl<<"enter desgination :";
     gets(b.degsin);
     cout<<endl<<"enter the phone number :";
     gets(b.phone);
     cout<<endl<<"enter the experience :";
     cin>>b.exp;
     b.flag=' ';
     file.write((char*)&b,sizeof(b));
     cout<<endl<<endl<<"add another record?(y/n)";
     cin>>ch;
     n++;
     strcpy(index[n].key,b.stfid);
     index[n].offset=file.tellg();

    }while(ch=='y' || ch=='Y');
}

//displays all the staff
void group::display()
{
int j=1;
file.seekg(0L,ios::beg);

while (file.read((char*)&b,sizeof(b)))
{
if(b.flag != '*')
{
    cout<<endl<<"RECORD NO :"<<j++<<endl<<"*************"<<endl<<"STAFF ID      :"<<b.stfid<<endl<<"STAFF NAME    :"<<b.stfname
	<<endl<<"DESGINATION   :"<<b.degsin<<endl<<"PHONENUMBER   :"<<b.phone
	<<endl<<"EXPERIENCE    :"<<b.exp<<endl<<endl<<endl;

    getch();
}
}
cout<<"*************PRIMARY KEY**********"<<endl;
cout<<"key\t";
cout<<"offset\n";
for(int i=1;i<=n;i++)
{
 cout<<index[i].key<<"\t";
 cout<<index[i].offset<<"\n";
 }
file.clear();
a:cout<<endl<<endl<<endl<<"press any key ....";
getch();
}

//update the staff
void group::update()
{
    char code[20];
    int count=0;
    long int pos;
    cout<<endl<<"enter the staffid :";
    gets(code);

    file.seekg(0L,ios::beg);

    while(file.read((char*)&b,sizeof(b)))
    {
      if(strcmp(b.stfid,code)==0)
       {
	cout<<endl<<"enter the new staffid :";
	gets(b.stfid);
	cout<<endl<<"enter the staff name  :";
	gets(b.stfname);
	cout<<endl<<"enter the desgination  :";
	gets(b.degsin);
	cout<<endl<<"enter the phone number :";
	gets(b.phone);
	cout<<endl<<"enter the experience   :";
	cin>>b.exp;
	b.flag=' ';

	pos=count*sizeof(b);
	file.seekp(pos,ios::beg);
	file.write((char*)&b,sizeof(b));
	return;
       }
    count++;
    }
    cout<<endl<<"no staff available with this id  :"<<code;
    cout<<endl<<"press any key ....";
    getch();

    file.clear();
}

//search for a given staff
 void group::search()
{
    char staffid[20],staffname[20];
    int opt;
    cout<<endl<<"search by          :";
    cout<<endl<<endl<<"1.staff id ";
   // cout<<endl<<endl<<"2.staff name ";
   // cout<<endl<<endl<<"enter your option  :";
    //cin>>opt;
    //if(opt==1)
    {
	cout<<endl<<endl<<"enter staff id   :";
	gets(staffid);
	file.seekg(0l,ios::beg);
	while(file.read((char*)&b,sizeof(b)))
	{
	    if(strcmp(b.stfid,staffid)==0)
	    {
			    cout<<endl<<setw(20)<<b.stfid<<setw(20)<<b.stfname<<setw(10)<<b.degsin<<setw(10)<<b.phone<<setw(10)<<b.exp;
	    }
	}  n--;
	file.clear();
    }
   // else
   // {
       //	cout<<endl<<endl<<"enter staff name   :";
       //	gets(staffname);
       //	file.seekg(0l,ios::beg);
       //	while(file.read((char*)&b,sizeof(b)))
     //	{
	   // if(strcmp(b.stfname,staffname)==0)
	    //{
	   //   cout<<endl<<setw(20)<<b.stfid<<setw(20)<<b.stfname<<setw(10)<<b.degsin<<setw(10)<<b.phone<<setw(10)<<b.exp;

	 //   }
       //	}
     //	file.clear();
   // }
    cout<<endl<<"press any key ...";
    getch();
}

//deletes the record
void group::deletion()
{
    char staffid[20],staffname[20],publ[20];
    int pos;
    int count=0;
    cout<<endl<<"enter  staff id :";
    gets(staffid);
    file.seekg(0l,ios::beg);
    while(file.read((char*)&b,sizeof(b)))
    {
	if(strcmp(b.stfid,staffid)==0)
	{
	    b.flag='*';
	    pos=count*sizeof(b);
	    file.seekp(pos,ios::beg);
	    file.write((char*)&b,sizeof(b));
	    cout<<endl<<"record deleted successfully";
	    goto v;
	}
	count++;
    }
    cout<<endl<<"the staff id is :"<<staffid<<" "<<"with name "<<staffname;
    v:cout<<endl<<"press any key.....";
    getch();
    file.clear();
}


void group::exit()
{
    file.close();
}
