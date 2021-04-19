#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <string.h>
#include <stdio.h>
#include "DataStructures.h"

using namespace std;
//Implementation of Country_list.
CountryNode* CreateCountryNode(char* Country, CountryNode *next)
{
    CountryNode *node =(CountryNode*) malloc(sizeof(CountryNode));
    node->country=(char*)malloc(sizeof(char)*strlen(Country+1));
    strcpy(node->country,Country);
    node->next = next;
    return node;
}

Countries *InitializeCountries(void)
{
    Countries *list =(Countries*)malloc(sizeof(Countries));
    list->head = NULL;
    list->size = 0;
    //cout<<"Country List initialized Successfully."<<endl;;
    return list;
}
CountryNode* GetCountryNode(Countries *list,char* Country ){
    CountryNode* irritator = list->head;
    int counter=list->size;
    while(counter!=0){
        if(irritator!=NULL){
            if(strcmp(irritator->country,Country)==0){
                return irritator;
            }
        }  
        irritator=irritator->next;
        counter--;
    }
    return NULL;
}

void InsertCountry(Countries **list,char* Country){
    CountryNode * newNode = CreateCountryNode(Country, NULL);
    newNode->next=(*list)->head;
    (*list)->head=newNode;
    (*list)->size++;
    return ;
}

void PrintCountries(Countries *list){
    CountryNode* irritator = list->head;
    int counter=list->size;
    cout<<"Size:"<<list->size<<endl;
    int lineChanger=0;
    while(counter!=0){
    if(irritator!=NULL){
        cout<<irritator->country<<" -> ";
        lineChanger++;
        }  
        if(lineChanger==5){
            lineChanger=0;
            cout<<endl;
        }
        irritator=irritator->next;
        counter--;        
    }
    return ;
}

void freeCountries(Countries* list){
    CountryNode* irritator = list->head;
    int counter=list->size;
    while(counter!=0){
    if(irritator!=NULL){
        free(irritator);
        }  
        irritator=irritator->next;
        counter--;        
    }
    free(list);
    return ;
}
//-------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------//
//Implementation of The Record List.


//-----------------------------------------------------------------------------------------------------------



RecordNode* CreateRecordNode(Record* rptr, RecordNode *next)
{
    RecordNode *node =(RecordNode*) malloc(sizeof(RecordNode));
    //cout<<"ok"<<endl;
    node->r=rptr;
    node->next = next;
    return node;
}
RecordList *InitializeRecordList(void)
{
    RecordList *list =(RecordList*)malloc(sizeof(RecordList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    cout<<"Record list initialazation//PASSED"<<endl;;
    return list;
}


Record* GetRecord(RecordList *list,int id ){
    RecordNode* irritator = list->head;
    int counter=list->size;
    while(counter!=0){


        if(irritator!=NULL){
            if(irritator->r->id==id){
                return irritator->r;

            }
        }  
        irritator=irritator->next;
        counter--;
        
    }
    return NULL;
}

void add_Record(RecordList **list,Record*r)
{  //cout<<(*list)->size<<endl;
    RecordNode * newNode = CreateRecordNode(r, NULL);
   // cout<<"edw"<<endl;
    newNode->next=(*list)->head;
    (*list)->head=newNode;
    (*list)->size++;
    //cout<<"done"<<endl;
    return ;
}


void freeRecords(RecordList* list){
    RecordNode* irritator = list->head;
    int counter=list->size;
    while(counter!=0){
    if(irritator!=NULL){
        free(irritator);
        }  
        irritator=irritator->next;
        counter--;        
    }
    free(list);
    return ;
}