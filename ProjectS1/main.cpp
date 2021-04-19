#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <string.h>
#include <stdio.h>
#include "DataStructures.h"
#include "ProgrammFunctionality.h"

using namespace std;
int main(int argc, char const *argv[]){
    //Take and check my command line arguments.
    int bloomSize;
    char* TestFile;
    cout<<"Number of Arguments: "<<argc<<endl;
    if(argc<5 || argc>5){
        cout<<"ERROR:wrong usage::Wrong number of arguments."<<endl;
        cout<<"ERROR:wrong input format"<<endl;
        cout<<"InputFormat: ./vaccineMonitor -c citizenRecordsFile -b bloomSize"<<endl;
        return -1;

    }
    if (! strcmp(argv[1], "-c")) {
		TestFile = strdup(argv[2]);
        cout<<"FileName :"<<TestFile<<endl;
	} else {
        cout<<"ERROR:wrong input format"<<endl;
        cout<<"InputFormat: ./vaccineMonitor -c citizenRecordsFile âb bloomSize"<<endl;
		return -1;
	}
	if (! strcmp(argv[3], "-b")) {
		bloomSize = atoi(argv[4]);
	} else {
        cout<<"ERROR:wrong input format"<<endl;
        cout<<"InputFormat: ./vaccineMonitor -c citizenRecordsFile -b bloomSize"<<endl;
		return -1;
	}
    //Lets initialiaze the Data Structures.
    RecordList* Records=InitializeRecordList();
    LinkedList*  DataSystem= InitializeList(bloomSize);
    Countries* countries=InitializeCountries();
    //-------------------------------------------------------------------------
    const char * yes="YES";
    //Lets collect the iniatial data from the file and insert at the system.
    char * Recordfile =(char*) malloc( sizeof(char) * ( strlen(TestFile) + 1 ) );
    strcpy(Recordfile,TestFile);
    cout<<"file :"<<Recordfile<<endl;
    //Open the Records file.
    fstream RecordFile;
    RecordFile.open(Recordfile,std::fstream::in);
    if(!RecordFile.is_open()){
        cerr<<"ERROR::Error Opening the given file."<<endl;
        return -1;
    }
    //-----------------------------------------------
    char buffer[512];
    char* ptr;
    date temp;
    //lets check the input of the file .
    
    std::string line;
    std::ifstream myfile(TestFile);

    //Lets count the number of lines at the file.
	int numLines = 0;
    ifstream in(TestFile);
    std::string unused;
    while ( std::getline(in, unused) )
        ++numLines;
    cout<<"number of lines at the file "<<numLines<<endl;
    //----------------------------------------------------------------------
    //----------------------------------------------------------------------
    cout<<"Initial Record Insertion at the VaccineMonitor."<<endl;

     while(RecordFile.getline(buffer,512)){
       if (numLines==0){
           break;
       }

        //temp.exists=false;
        bool Vaccinated=false;
       //get id .
        ptr = strtok(buffer," ");
        char* id= (char*)malloc(sizeof(char)*(strlen(ptr)+1));
        strcpy(id,ptr);
       //get name 
        ptr = strtok(NULL," ");
        char* name = (char*)malloc(sizeof(char)*(strlen(ptr)+1));
        strcpy(name,ptr);
       //get last name 
        ptr = strtok(NULL," ");
        char* lastName = (char*)malloc(sizeof(char)*(strlen(ptr)+1));
        strcpy(lastName,ptr);
       //get country 
        ptr = strtok(NULL," ");
        char* country = (char*)malloc(sizeof(char)*(strlen(ptr)+1));
        strcpy(country,ptr);
       //get age 
        ptr = strtok(NULL," ");
        char* age = (char*)malloc(sizeof(char)*(strlen(ptr)+1));
        strcpy(age,ptr);
        //get virus
        ptr = strtok(NULL," ");
        char* virus = (char*)malloc(sizeof(char)*(strlen(ptr)+1));
        strcpy(virus,ptr);
        ptr = strtok(NULL," ");
        char* vaccinated = (char*)malloc(sizeof(char)*(strlen(ptr)+1));
        strcpy(vaccinated,ptr);
        if(!strcmp(vaccinated,yes)){
            Vaccinated=true;
            temp.exists=true;
            ptr = strtok(NULL," ");
            char* date =(char*)malloc(sizeof(char)*(strlen(ptr)+1));
            strcpy(date,ptr);
            temp.day=atoi(date);
            char * day = strtok(date,"-");
            temp.day=atoi(day);
            char * month = strtok(NULL,"-");
            temp.month=atoi(month);
            char * year = strtok(NULL,"-");
            temp.year=atoi(year);   
        }
       numLines--;
        //Insert the Record.
       InsertCitizenRecord(&DataSystem,&Records,&countries,atoi(id),name,lastName,atoi(age),country,virus,temp,Vaccinated);
     }

    cout<<"__________________Initial Insertion of Records:FINISHED ___________________"<<endl;
    cout<<"__________________ VACCINE_MONITOR is ready for your Commands!________________"<<endl;
    TakeCommands(Records,DataSystem,countries);
    cout<<"Exiting..."<<endl;
    cout<<"Vaccine Monitor is turned off!";
return 1;}