
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <string.h>
#include <stdio.h>
#include<stdint.h>
#include<inttypes.h>

using namespace std;
//Functionality of the list whick keeps the Countries.
//List of countries at the system.
typedef struct CountryNode {
    struct CountryNode *next;
    char* country;
} CountryNode;

typedef struct Countries {
    CountryNode *head;
    int size;
} Countries;

CountryNode* CreateCountryNode(char* Country, CountryNode *next);
Countries *InitializeCountries(void);
CountryNode* GetCountryNode(Countries *list,char* Country);
void InsertCountry(Countries **list,char* Country);
void PrintCountries(Countries *list);
void freeCountries(Countries* list);


//Data Srructure Which Represents a Date.
typedef struct date{
    bool exists;
    int day;
    int month;
    int year;

    void printDate(){
        if(exists){
            cout<<day<<"-"<<month<<"-"<<year;
        }
    }
}date;

//Data Structure which represents a Citizen.
class Record{
    public:
        char* name;
        char* surname;
        int id;
        int age;
        bool vaccinated;
        CountryNode* _country;
        Record(int Id,char* Name,char* Surname,int Age,bool Vaccinated){
            this->id=Id;
            this->name = (char*)malloc(sizeof(char)*(strlen(Name)+1));
            this->surname = (char*)malloc(sizeof(char)*(strlen(Surname)+1));
            this->age=Age;
            this->vaccinated=Vaccinated;
            strcpy(name,Name);
            strcpy(surname,Surname);      
            _country=NULL;
        }

        //Function to print The info of the Record.
        void Print_Record(){
            cout<<"Id:"<<this->id<<",";
            cout<<"Name:"<<this->name<<",";
            cout<<"Surname:"<<this->surname<<",";
            cout<<"Country: "<<this->_country->country<<",";
            cout<<" ";
            cout<<endl;
        }
       void SetCountry(CountryNode* Country){
           if(_country==NULL){
               _country=Country;
           }
           return;
       }
};


//-----------------------------------------------------------------------------------------------------------
typedef struct RecordNode {
    struct RecordNode *next;
    Record* r;
} RecordNode;

typedef struct RecordList {
    RecordNode *head;
    RecordList *tail;
    int size;
} RecordList;

RecordNode* CreateRecordNode(Record* rptr, RecordNode *next);
RecordList *InitializeRecordList(void);
Record* GetRecord(RecordList *list,int id );
void add_Record(RecordList **list,Record*r);
void PrintRecordList(RecordList *list);
void freeRecords(RecordList* list);


//-----------------------------------------------------------------------------------------------------------------


#define LOWEST_KEY -1000000
#define HIGHEST_KEY 1000000

//The skipList node.
typedef struct SLnode {
    int id;
    Record* data;
    date* _date;
    struct SLnode *next;
    struct SLnode *prev;
    struct SLnode *down;
    struct SLnode *up;
} SLnode;


//Skip list as an object.
typedef struct SkipList {

    char* Virus;
    bool vaccinatedList;

    SLnode* topleft;
    SLnode *bottomleft;
    SLnode *topright;
    SLnode *bottomright;
    //max height.
    int height;
    int len;
   
} SkipList;

//Functionality.
//initialization of the SkipList.
void SkipList_init(SkipList* list,char* virus_name,bool vaccinatedSL);
//Insert in the SkipLlist.
int SL_insert(SkipList*list, int id, Record* data,date* _date);
//Search Record at the SkipList.
SLnode* SL_searchR(SkipList* list,int id);
//Print SkipList.
void SL_print(const SkipList* list);
//Print just the Record of the SkipList.
void SL_printRecords(SkipList* list);
void  SL_free(SkipList *list);

#define K 16
typedef struct BloomFilter   BloomFilter;

//BloomFilter implementations.
struct BloomFilter {
    void* bits;
    size_t size;
};

BloomFilter* BloomFilter_init(size_t size);
void FreeFilter(BloomFilter* filter);
void BloomFilter_insert(BloomFilter* filter, const void * id);
bool BloomFilter_check(BloomFilter* filter, const void *id);

//============================================================================================//


//simple structure to keep all the info of a virus.
typedef struct VirusData{
    char*  VirusName;
    SkipList vaccinated;
    SkipList non_vaccinated;
    BloomFilter* virusFilter;
    //Initialize the virus and its structures at the system.
    void VirusData_init(char*  virus,int bloomSize){
    VirusName=(char*)malloc(sizeof(char)*(strlen(virus)+1));
    strcpy(VirusName,virus);
    //cout<<VirusName<<endl;
    //initialize SkipList of the Virus.
    SkipList_init(&vaccinated,VirusName,true);
    SkipList_init(&non_vaccinated,VirusName,false);
    virusFilter= BloomFilter_init(bloomSize);
    return;
}
}VirusData;



//structure initialazation.
//simple LinkedList implentation to Keep the VirusData;
typedef struct Node {
    struct Node *next;
    VirusData virus_data;
} Node;

typedef struct LinkedList {
    Node *head;
    int Bloomsize;
    int size;
} LinkedList;


Node* CreateNode(char* virus,int bloomSize, Node *next);
LinkedList *InitializeList(int bloomSize);
bool SearchVirus(LinkedList *list,char* virus);
//Get Index of the Virus At the System.
Node* GetIndex(LinkedList *list,char* virus);

//initialazation of the virus at the system.
void Virus_Init(LinkedList **list,char* virus);
void freeSystem(LinkedList* list);
 
//------------------------------------------------------------------------//
//------------------------------------------------------------------------//












