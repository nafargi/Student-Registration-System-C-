//========================================================================================
// Name        : student regstration system
// Author      : Nafargi
// Copyright   : Your copyright notice
//========================================================================================

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <cstdlib>



using namespace std;
struct Student{
  int id;
  char name[50];
  float gpa ;
};

const int SIZE=3;
Student si[SIZE];
char tempFileName[50]="temp_file.txt";
char fileName[50]="student_info.txt";
fstream file;

void menu(){

cout << "--------- MENU --------- \n";
cout << "1.Register Studenet \n";
cout << "2.Show All Studenet \n";
cout << "3.Update Studenet Info \n";
cout << "4.Search Studenet \n";
cout << "5.Delet Studenet \n";
cout << "6.Exit The Program \n";
cout << " Enter your choice \n";
cout<<"PRESS ANY KEY TO GET STARTED!"<<endl;
    cin.get();

}

void registerStudent(char fileName[]){
 int j;
  file.open(fileName, ios :: app | ios :: binary);

  if(!file){
    cerr<< "Error opening the file . ";
    return;
  }


  for( j=0;j<SIZE;j++)
 {
     cout<<" Enter  Name Of The Student \n";
     cin.ignore();
     cin.getline(si[j].name,50) ;

     cout<<" Enter Id Of The Student \n";
     cin>>si[j].id ;

     cout<<" Enter GPA Of The Student \n";
     cin>>si[j].gpa;

     file.write((char *) (&si [j]), sizeof(Student));

  }
 file.close();
}

void showStudentInfo(char fileName[]){

     file.open(fileName, ios :: in | ios :: binary);
  if(!file){
    cerr<< "Error opening the file for writing. ";
    exit(1);
  }

     cout<<"--------------------------------------------------------------------------------"<<endl;
     cout<<"---------------------------Student record Table---------------------------------"<<endl;
     cout<<"--------------------------------------------------------------------------------"<<endl;
     cout<< setw (22) << " Name " << setw(22) << " Id " << setw(22) << "  GPA \n";
     cout<<"--------------------------------------------------------------------------------"<<endl;

 for( int j=0;j<SIZE;j++) {

     file.read((char *) (&si [j]), sizeof(Student));

     cout << setw(22) << si[j].name << setw(22) << si[j].id << setw(22) << si[j].gpa <<endl;
  }
     cout<<"--------------------------------------------------------------------------------"<<endl;
 file.close();
}

void updateStudentInfo(char fileName[],int id){

    file.open(fileName, ios :: in | ios :: out | ios :: binary);
  if(!file){

    cerr<< "Error opening the file for writing. ";
    exit(1);
  }

    for(int j=0;j<SIZE;j++){

           file.read((char *) (&si [j]), sizeof(Student));

            if(si[j].id == id){
                cout <<"Enter update info  \n" ;
                cout <<"Name : \n" ;

                cin.ignore();
                cin.getline(si[j].name,50) ;

               cout<<" Enter Id Of The Student \n";
               cin>>si[j].id ;

               cout<<" Enter GPA Of The Student \n";
               cin>>si[j].gpa;

        cout << " Sutdent updated successfully " <<endl ;

     file.seekp(0);
     file.write((char *) (&si [j]), sizeof(Student));
     file.close();

             return;
            }
    }
 cout << " Sutdent not found with  ID " << id <<endl ;
 file.close();
}

void searchStudent(char fileName[],int id){

    file.open(fileName, ios :: in | ios :: binary);
  if(!file){

    cerr<< "Error opening the file for writing. ";
    exit(1);
  }

   for(int j=0;j<SIZE;j++){
            file.read((char *) (&si [j]), sizeof(Student));

            if(si[j].id == id){

                cout <<"Student found \n" ;
                cout << "Name : "<< si[j].name<< ", ID : "<< si[j].id<< ", GPA  : "<<si[j].gpa<<endl;
                file.close();
                return;
            }
    }

 cout << " Sutdent not found with  ID " << id <<endl ;
 file.close();

}


void deleteStudent(char fileName[] , int id){

    if (file.is_open()){
    file.close();
    }

  file.open(fileName, ios :: in | ios :: binary);
  if(!file){
    cerr<< "Error opening the file for writing. ";
    exit(1);
  }
  ofstream tempFile(tempFileName, ios :: out | ios :: binary);
  if(!tempFile){
    cerr<< "Error opening the file for writing. ";
    file.close();
    exit(1);
  }


  bool studentfound = false;
     for(int j=0;j<SIZE;j++) {

   file.read((char *) (&si [j]), sizeof(Student));
   if(si[j].id == id){

     cout << " Sutdent with  ID " << id <<" deleted successfully. " << endl ;

     studentfound = true;
     continue;
   }
  tempFile.write((char *) (&si [j]), sizeof(Student));
  }

 file.close();
 tempFile.close();

  remove(fileName);
  rename (tempFileName , fileName);

 if(!studentfound){
      cout << " Deletion Is Failed " <<endl ;
      cout << " Sutdent not found with  ID " << id <<endl ;
    return;
  }

}
int main(){


   system( "color 60" );

   int choice =0;

   while ( choice != 6){

     menu();
     cin>>choice;
     system("cls");


        switch (choice){

    case 1:
        registerStudent (fileName);
        break;

    case 2:
        showStudentInfo (fileName);
        break;

    case 3: {
        int id;
        cout << "Enter Student Id to Update \n";
        cin >> id;
        updateStudentInfo (fileName, id);
        break;
        }

    case 4: {
        int id;
        cout << "Enter Student Id to Search \n";
        cin >> id;
        searchStudent (fileName,id);
        break;
        }

    case 5: {
        int Id;
        cout << "Enter Student Id to Delete \n";
        cin >> Id;
        deleteStudent (fileName,Id);
        break;
        }

    case 6:
         cout << " Exite The Program \n";
         break;
         default:
         cout << " Invalide Input Try Again \n";

      }

   }



return 0;
}
