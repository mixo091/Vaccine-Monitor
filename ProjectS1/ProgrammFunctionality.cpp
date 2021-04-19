#include <iostream>
#include<string.h>
#include "DataStructures.h"
#include "ProgrammFunctionality.h"



//--------------INSERT CITIZEN RECORD------------//
int  InsertCitizenRecord(LinkedList **list,RecordList ** Records,Countries** countries,int id , char* name ,char* surname,int age,char* country,char* virus,date _date,bool Vaccinated){
        CountryNode* Country =GetCountryNode(*countries,country);
        Record* dup=NULL;
        dup= GetRecord((*Records),id);
        if (dup!=NULL){
            if((strcmp(dup->name,name)!=0) || (strcmp(dup->surname,surname)!=0)){
                //cout<<"Sorry the id number "<<id<<" belongs to "<<dup->name<<" "<<dup->surname<<endl;
                return 1;
            }
        }

        if(Country==NULL){
            //The country of the Record doesnt exists at the list of Countries ,so add it.
            InsertCountry(countries,country);
        }
        //Check if this Specific Person exists at The system.
        /*The Record as it is impemented in this programm is an object that 
          depicts a person in the programm not an actual Record as it is in the files*/
        Record* record =GetRecord(*Records,id);
        if(record==NULL){
            //if not ,create it and add to the system.
            Record* newRecord=new Record(id,name,surname,age,Vaccinated);
            CountryNode* Country =GetCountryNode(*countries,country);
            if(Country==NULL){
            //it doesnt exists at the list ,so add it.
            //and link(with a pointer) the Country_node to The Record. 
                InsertCountry(countries,country);
                newRecord->SetCountry(GetCountryNode(*countries,country));
            }else{
                //dont add it  to the the list just link to the record.
                //and link(with a pointer) the Country_node to The Record. 
                newRecord->SetCountry(Country);
             }
           //Finally,add the Record to the Record_list and to the System.
           add_Record(Records,newRecord);
           record=newRecord;}
        //now ,No matter what the record pointer points to the record at The recordlist.
        //now add the Record  to the system .
        System_InsertRecord(list,record,virus,Vaccinated,_date);
       
    return 1;
}



void System_InsertRecord(LinkedList **list, Record* r,char* virus,bool Vaccinated,date _date){
    LinkedList* Lptr=(*list);
    //cout<<"Inserting a new Record at the System."<<endl;
    //get The virus of the Record.
    //Check if the virus exists at the system.
    if(SearchVirus(Lptr,virus)){
        //cout<<"The virus exists at the System Already."<<endl;
        //find the virus at the system and insert the record at the right skiplist .
         insert_record(list,r,virus, _date,Vaccinated);
    }else{
        /*if not, create the dataStructures for the new virus
        and insert the Record at the appropriate structures. */
        //cout<<"The virus does not exist at the system_initialazing data.."<<endl;
        //Initialize the virus at the system .
        Virus_Init(list,virus);
        /*as we justs initialized the virus will also be the fisrt Record 
        /of this specific virus. */
       // cout<<(*list)->head->virus_data.VirusName<<endl;
        //insert the virus at the right skiplist.
        insert_record(list,r,virus,_date,Vaccinated);
        //For now lets put them all at the vaccinated list.
    }
    return;
}




int insert_record(LinkedList **list,Record*r,char* virus,date _date,bool Vaccinated){
    //Find the position of the virus on the System.
    cout<<"Insert record with id ["<<r->id<<"] and virus["<<virus<<"] ."<<endl;
    Node* irritator = (*list)->head;
    int counter=(*list)->size;
    while(counter!=0){
        //cout<<"virus :"<<irritator->virus_data.VirusName<<endl;
        if(!strcmp(irritator->virus_data.VirusName,virus)){
            //if the record is vaccinated enter it to the bloom .
            //it doesnt matter if it is already in ,the same values will be 1.
            if(Vaccinated==true){
                //cout<<"The record is vaccinated enter it on  the bloom filter."<<endl;
                char buf[10] = {0};
                sprintf(buf, "%d", r->id);
                cout<<buf<<endl;
                BloomFilter_insert(irritator->virus_data.virusFilter,buf);
                //insert to the vaccinated list.
                if(SL_insert(&(irritator->virus_data.vaccinated),r->id,r,&_date)){
                   
                    return -1;  
            }
            }
            else{
            //insert the Record to the proper SkipList.(non_vaccinated)
            if(SL_insert(&(irritator->virus_data.non_vaccinated),r->id,r,&_date)){
               
                 return -1;  
            }
            }
            return 1;
        }
        irritator=irritator->next;
        counter--;
    }
    return -1;   
    }
//--------------------------------------------------------------//

void PrintList(LinkedList *list){
    Node* temp=list->head;
    int i=list->size;
    while(i!=0){
        cout<<"___Vaccinated____"<<endl;
        SL_print(&temp->virus_data.vaccinated);
        cout<<"___Not-Vaccinated____"<<endl;
        SL_print(&temp->virus_data.non_vaccinated);

        temp=temp->next;
        i--;
    }
    cout<<"NULL"<<endl;

}



//The function that implements the  "/vaccineStatus citizenID virusName" query.
void System_VaccineStatusV(int citizenID,char* VirusName,LinkedList* system){
    cout<<"VaccineStatus for Virus:";
    cout<<"citizenID ["<<citizenID<<"] "<<"- VirusName ["<<VirusName<<"] "<<endl;
    Node* temp=GetIndex(system,VirusName);
    if(temp!=NULL){
        cout<<"VaccineStatus "<<temp->virus_data.VirusName<<endl;
        SLnode* vaccinated=SL_searchR(&temp->virus_data.vaccinated,citizenID);
        SLnode* non_vaccinated=SL_searchR(&temp->virus_data.non_vaccinated,citizenID);
        //PrintVirusData(VirusName,system); 
        if(vaccinated!=NULL){
            cout<<"VACCINATED ON ";
            vaccinated->_date->printDate();
            cout<<endl;
            return ;  
        }
        if(non_vaccinated!=NULL){
            cout<<"NOT VACCINATED"<<endl;
            return ;
        }
    }
    cout<<" DOES NOT EXIST AT THE SYSTEM."<<endl;
    return ;
}



//----------------------------------------------------------------- //
//The function that implements the "/vaccineStatus citizenID " query.
void System_VaccineStatus(int citizenID,LinkedList* system){
    cout<<"VaccineStatus for ";
    cout<<"citizenID ["<<citizenID<<"] :"<<endl;
    Node* temp=system->head;
    int counter=system->size;
    while(counter>0){
        //---------------------------------------------------------------------
        if(temp!=NULL){
            SLnode* vaccinated=SL_searchR(&temp->virus_data.vaccinated,citizenID);
            SLnode* non_vaccinated=SL_searchR(&temp->virus_data.non_vaccinated,citizenID);
            //PrintVirusData(VirusName,system); 
            if(vaccinated!=NULL){
                cout<<temp->virus_data.VirusName<<" ";
                cout<<"YES ";
                vaccinated->_date->printDate();
                cout<<endl;  
        }
            if(non_vaccinated!=NULL){
                cout<<temp->virus_data.VirusName<<" ";
                cout<<"NO "<<endl;
        }
      }
        counter--;
        temp=temp->next;
    }

    return;
}

//-------------------------------------------------------------------------------------------------//
//NON VACCINATED FOR VIRUS X.

//Just prints the non-vaccinated SkipList for this Specific Virus.

 // implements"/list-nonVaccinated-Persons virusName" query.
void  getNonVaccinated(char* VirusName,LinkedList* system){
    cout<<"Non vaccinated citizens for virus ["<<VirusName<<"]"<<endl;
     Node* temp=GetIndex(system,VirusName);
     if(temp!=NULL){
     SL_printRecords((&temp->virus_data.non_vaccinated));}
     else{
         cout<<"Sorry there isn't a Record Vaccinated/Non-vaccinated for Virus ["<<VirusName<<"] ,try again!"<<endl;
     }
    return;
}

//----------------------------------------------------------------------------------------------------------//

//VACCINATE A NEW RECORD NOW.
void  VaccinateNow(int citizenID,char * firstName,char* lasName ,char * country,int age ,char * VirusName,LinkedList** system,RecordList* records){

    //first lets check if the record is already vaccinated.
    //the unique key for every Record in the system is the id and the virus name compined.
    cout<<"citizenID ["<<citizenID<<"] "<<"- VirusName ["<<VirusName<<"] "<<endl;
    Node* temp=GetIndex((*system),VirusName);
    if(temp!=NULL){
        cout<<"VaccineStatus "<<temp->virus_data.VirusName<<endl;
        SLnode* vaccinated=SL_searchR(&temp->virus_data.vaccinated,citizenID);
        SLnode* non_vaccinated=SL_searchR(&temp->virus_data.non_vaccinated,citizenID);
        //PrintVirusData(VirusName,system); 
        if(vaccinated!=NULL){
            cout<<"ERROR: CITIZEN "<<citizenID<< "ALREADY VACCINATED ON "; 
            vaccinated->_date->printDate();
            cout<<endl;
            return ;
        }else{
            char buf[10] = {0};
            Record* r=GetRecord(records,citizenID);
            if(r==NULL){
                cout<<"This Record does not exist at the system"<<endl;
                return;
            }else{
            sprintf(buf, "%d", citizenID);
            BloomFilter_insert(temp->virus_data.virusFilter,buf);
            time_t ttime = time(0);
            tm *local_time = localtime(&ttime);
            r->vaccinated=true;
            date today;
            today.exists-true;
            today.day=local_time->tm_mday;
            today.month=1+local_time->tm_mon;
            today.year=(1900+local_time->tm_year);
             //insert to the vaccinated list.
            SL_insert(&(temp->virus_data.vaccinated),citizenID,r,&today);    
            return;
            }
        }
    }
    return ;
}


int getPos(Countries *list,char* country){
    int pos=-1;
    CountryNode* irritator=list->head;
    int counter=0;
    while(counter<list->size){
       // cout<<irritator->country<<endl;
        if(strcmp(irritator->country,country)==0){
           // cout<<"dffggerw"<<endl;
            pos=counter;
            return pos;
        }
        irritator=irritator->next;
        counter++;
    }

return pos;    
}



void PrintByPos(int pos,Countries *list){
   CountryNode* irritator=list->head;
    int counter=0;
    while(counter<list->size){
        if(counter==pos){
            cout<<irritator->country;     

        }
        irritator=irritator->next;
        counter++;
    }
return ; 
}


//===========================================================================//

bool CompareDates(date* low ,date* high){
    if(low->year<high->year){
        return true;
    }
    if(low->year==high->year){
        if(low->month<high->month){
            return true;
        }
        if(low->month==high->month){
            if(low->day<high->day){
                return true ;
            }
        }
    }
    return false;
}


//=============================================================================================//

//GETTING THE STATS FOR A VIRUS FOR EACH COUNTRY.

void populationStatus(char* VirusName ,date* d1,date* d2,Countries* _Countries,LinkedList* system){
    //If d1 is given and d2 is not its an ERROR.
     if(d1!=NULL){
        if(d2==NULL){
             cout<<"ERROR!"<<endl;
             return;
         }
     }
    SLnode* p;
    Node* Virusdata=GetIndex(system,VirusName);
    cout<<"Virus ["<<Virusdata->virus_data.VirusName<<"] "<<endl;
    SLnode* _node1;
    SLnode* non_vaccinated;
    CountryNode* irritator=_Countries->head;
    int VaccinatedCounters[_Countries->size]={0};
    int nonVaccinatedCounters[_Countries->size]={0};
    int VaccinatedOverall[_Countries->size]={0};
    p=Virusdata->virus_data.vaccinated.bottomleft;
        for (_node1 = p; _node1 != NULL; _node1 = _node1->next) {
             if(_node1->data!=NULL){
                //cout<<"Country for searching "<<_node1->data->_country->country<<endl;
                int pos=getPos(_Countries,_node1->data->_country->country);
                if(pos!=-1){
                    //cout<<pos<<endl;
                    VaccinatedOverall[pos]++;
                }
                if( (CompareDates(d1,(_node1->_date)) && CompareDates((_node1->_date),d2)) || (d1==NULL && d2==NULL)){
                if(pos!=-1){
                   // cout<<pos<<endl;
                    VaccinatedCounters[pos]++;
                }
             }
             }
        }
    //now lets coutn the non vaccinated for each country.  
    p=Virusdata->virus_data.non_vaccinated.bottomleft;
        for (_node1 = p; _node1 != NULL; _node1 = _node1->next) {
             if(_node1->data!=NULL){
                int pos=getPos(_Countries,_node1->data->_country->country);
                if(pos!=-1){
                    nonVaccinatedCounters[pos]++;
                }
             }
        }
    int i=0;
    while(i<_Countries->size){
            if((VaccinatedOverall[i]+nonVaccinatedCounters[i])!=0){
                PrintByPos(i,_Countries);
                cout<<" ";
            
                cout<<"VaccinatedInRange:"<<VaccinatedCounters[i]<<" ";
                cout<<"VaccinatedOverral:"<<VaccinatedOverall[i]<<" ";
                cout<<"Non_vaccinated: "<<nonVaccinatedCounters[i]<<"  /";
               float per=(float)VaccinatedCounters[i]/((float)VaccinatedOverall[i]+(float)nonVaccinatedCounters[i]);
               per=per*((float)100);
               printf("%.2f", per);
               cout<<"%";
            }
          
            cout<<endl;

        i++;
    }

    return;
}

//NOW FOR A SPECIFIC COUNTRY.


void CountryPopulationStatus(char* VirusName,char* Country,date* d1,date* d2,Countries* _Countries,LinkedList* system){
       //If d1 is given and d2 is not its an ERROR.
     if(d1!=NULL){
        if(d2==NULL){
             cout<<"Date-ERROR!"<<endl;
             return;
         }
     }

   // d1->printDate();
    cout<<endl;
   // d2->printDate();
    cout<<endl;
    cout<<VirusName<<endl;

    SLnode* p;
    Node* Virusdata=NULL;
    Virusdata =GetIndex(system,VirusName);
    if(Virusdata!=NULL){
      //  cout<<Virusdata->virus_data.VirusName<<endl;
    }else{
      //  cout<<"NULL"<<endl;
    }
    cout<<Virusdata<<endl;
    cout<<"Virus ["<<Virusdata->virus_data.VirusName<<"] "<<endl;
    //cout<<"here"<<endl;
    SLnode* _node1;
    SLnode* non_vaccinated;
    int VaccinatedCounters=0;
    int nonVaccinatedCounters=0;
    int VaccinatedOverall=0;
        p=Virusdata->virus_data.vaccinated.bottomleft;
        for (_node1 = p; _node1 != NULL; _node1 = _node1->next) {
             if(_node1->data!=NULL){
                if(strcmp(Country,_node1->data->_country->country)==0){
                    cout<<" "<<_node1->data->id<<endl;
                    VaccinatedOverall++;
                    if( (CompareDates(d1,(_node1->_date)) && CompareDates((_node1->_date),d2)) || (d1==NULL && d2==NULL)){
                             VaccinatedCounters++;}
                }
             }
        }
        
        p=Virusdata->virus_data.non_vaccinated.bottomleft;
        for (_node1 = p; _node1 != NULL; _node1 = _node1->next) {
             if(_node1->data!=NULL){
                if(strcmp(Country,_node1->data->_country->country)==0){
                    nonVaccinatedCounters++;
                }
             }
        }
    if((VaccinatedOverall+nonVaccinatedCounters)!=0){
        cout<<Country;
        cout<<" ";
            
        cout<<"VaccinatedInRange:"<<VaccinatedCounters<<" ";
        cout<<"VaccinatedOverral:"<<VaccinatedOverall<<" ";
        cout<<"Non_vaccinated: "<<nonVaccinatedCounters<<"  /";
        float per=(float)VaccinatedCounters/((float)VaccinatedOverall+(float)nonVaccinatedCounters);
        per=per*((float)100);
        printf("%.2f", per);
        cout<<"%";
   }
    return;
}



//QUICK ANSWER IF A CITIZEN IS NOT VACCINATED FOR A SPECIFIC VIRUS.

void VaccineBloomStatus(LinkedList* system,char* VirusName,int id){
    //First we need the data of the virus to get the specific bloomFilter.
    Node*  Virus = NULL;
    Virus = GetIndex(system,VirusName);
    if(Virus !=NULL){
        char buf[10] = {0};
        sprintf(buf, "%d", id);
       // cout<<buf<<endl;
        bool Status=BloomFilter_check(Virus->virus_data.virusFilter,buf);
        if(Status==false){
            cout<<"NOT VACIINATED"<<endl;
        }else{
            cout<<"MAYBE"<<endl;
        }

    }else{
        cout<<"ERROR:The virus does not exist at the system."<<endl;
        return;
    }
    return;  
}


//POPPING STATS FOR A SPECIFIC VIRUS IN EVERY GROUP-AGE FOR A SPECIFIC COUNTRY.
//------------------------------------------------------------------------------

void CountryPopStatusByAge(char* VirusName,char* Country,date* d1,date* d2,Countries* _Countries,LinkedList* system){


        int age_groups=4;
       //If d1 is given and d2 is not its an ERROR.
     if(d1!=NULL){
        if(d2==NULL){
             cout<<"ERROR"<<endl;
             return;
         }
     }

 //   cout<<"in"<<endl;

    SLnode* p;
    Node* Virusdata=GetIndex(system,VirusName);
    cout<<"Virus ["<<Virusdata->virus_data.VirusName<<"] "<<endl;
    SLnode* _node1;
    SLnode* non_vaccinated;
    int VaccinatedCounters[age_groups]={0};
    int nonVaccinatedCounters[age_groups]={0};
    int VaccinatedOverall[age_groups]={0};
        p=Virusdata->virus_data.vaccinated.bottomleft;
        for (_node1 = p; _node1 != NULL; _node1 = _node1->next) {
             if(_node1->data!=NULL){
                if(strcmp(Country,_node1->data->_country->country)==0){
                    if(_node1->data->age<=20){VaccinatedOverall[0]++;}
                    else if(_node1->data->age>20 && _node1->data->age<=40){VaccinatedOverall[1]++;}
                    else if(_node1->data->age>40 && _node1->data->age<=60){VaccinatedOverall[2]++;}
                    else{VaccinatedOverall[3]++;}
                    if( (CompareDates(d1,_node1->_date) && CompareDates(_node1->_date,d2)) || (d1==NULL && d2==NULL)){
                        if(_node1->data->age<=20){VaccinatedCounters[0]++;}
                        else if(_node1->data->age>20 && _node1->data->age<=40){VaccinatedCounters[1]++;}
                        else if(_node1->data->age>40 && _node1->data->age<=60){VaccinatedCounters[2]++;}
                        else{VaccinatedCounters[3]++;}}                            
                }             
            }
        }
        
        p=Virusdata->virus_data.non_vaccinated.bottomleft;
        for (_node1 = p; _node1 != NULL; _node1 = _node1->next) {
             if(_node1->data!=NULL){
                if(strcmp(Country,_node1->data->_country->country)==0){
                       if(_node1->data->age<=20){nonVaccinatedCounters[0]++;}
                        else if(_node1->data->age>20 && _node1->data->age<=40){nonVaccinatedCounters[1]++;}
                        else if(_node1->data->age>40 && _node1->data->age<=60){nonVaccinatedCounters[2]++;}
                        else{nonVaccinatedCounters[3]++;}         
                }
             }
        }


    for(int i=0;i<age_groups;i++){
        if((VaccinatedOverall[i]+nonVaccinatedCounters[i])!=0){
        cout<<Country;
        cout<<" ";
        cout<<endl;
        if(i==0){cout<<"0-20: ";}
        else if(i==1){cout<<"20-40: ";}
        else if(i==2){cout<<"40-60: ";}
        else{cout<<"60+: " ;}
        cout<<endl;
        cout<<"VaccinatedInRange:"<<VaccinatedCounters[i]<<" ";
        cout<<"VaccinatedOverral:"<<VaccinatedOverall[i]<<" ";
        cout<<"Non_vaccinated: "<<nonVaccinatedCounters[i]<<"  /";
        cout<<endl;
        float per=(float)VaccinatedCounters[i]/((float)VaccinatedOverall[i]+(float)nonVaccinatedCounters[i]);
        per=per*((float)100);
        printf("%.2f", per);
        cout<<"%";
        }
    }

    return;
}



//POPPING STATS FOR A SPECIFIC VIRUS IN EVERY GROUP-AGE FOR  EACH COUNTRY.
//------------------------------------------------------------------------------



void popStatusByAge(char* VirusName,date* d1,date* d2,Countries* _Countries,LinkedList* system){
    CountryNode* temp= _Countries->head;
    int count = _Countries->size;
    while(count>0){
        CountryPopStatusByAge(VirusName,temp->country,d1,d2,_Countries, system);
        temp=temp->next;
        count--;
    }
    return;
}



//The menu of the VaccineMonitor that is taking the commands.

void TakeCommands(RecordList* Records, LinkedList*  DataSystem,Countries* countries){
    cout<<"Vaccine monitor is ready for your command!"<<endl;
    cout<<"Please enter a Command!"<<endl;
    char Command[512];
    cin.getline(Command,512);
    cout<<"The Command is :"<<Command<<endl;
    char * Commandtoken = strtok(Command, " ");
    cout<<"Command Token"<< Commandtoken<<endl;
    while(strcmp(Commandtoken,"/exit")){

        if(!strcmp(Commandtoken,"/vaccineStatus")){
            char* IdToken=NULL;
            IdToken=strtok(NULL," ");
            char* VirusToken=NULL;
            VirusToken=strtok(NULL," ");
            int id=atoi(IdToken);
            if(VirusToken!=NULL){
                cout<<"Vaccinate Status for Citizen Id ["<<IdToken<<"] Virus ["<<VirusToken<<"]."<<endl;
                System_VaccineStatusV(id,VirusToken,DataSystem);
                cout<<"_________________________________________________________________________________"<<endl;
            }else{
                cout<<"Vaccinate Status for Citizen Id ["<<IdToken<<"]."<<endl;
                System_VaccineStatus(id,DataSystem);
                cout<<"_________________________________________________________________________________"<<endl;

            }
        }
        else if(!strcmp(Commandtoken,"/vaccineStatusBloom")){
            char* IdToken=NULL;
            IdToken=strtok(NULL," ");
            char* VirusToken=NULL;
            VirusToken=strtok(NULL," ");
            VaccineBloomStatus(DataSystem,VirusToken,atoi(IdToken));
            cout<<"_________________________________________________________________________________"<<endl;}
        
        else if(!strcmp(Commandtoken,"/list-nonVaccinated-Persons")){
            char* VirusToken=strtok(NULL," ");
            cout<<"Non-Vaccinated for Virus "<<VirusToken<<endl;
            getNonVaccinated(VirusToken,DataSystem);
            cout<<"_________________________________________________________________________________"<<endl;
        }else if(!strcmp(Commandtoken,"/insertCitizenRecord")){
            date temp;
            const char * yes="YES";
            bool Vaccinated=false;
            char* ptr = strtok(NULL," ");
            char* id= (char*)malloc(sizeof(char)*(strlen(ptr)+1));
            strcpy(id,ptr);
            ptr = strtok(NULL," ");
            char* name = (char*)malloc(sizeof(char)*(strlen(ptr)+1));
            strcpy(name,ptr);
            ptr = strtok(NULL," ");
            char* lastName = (char*)malloc(sizeof(char)*(strlen(ptr)+1));
            strcpy(lastName,ptr);
            ptr = strtok(NULL," ");
            char* country = (char*)malloc(sizeof(char)*(strlen(ptr)+1));
            strcpy(country,ptr);
            ptr = strtok(NULL," ");
            char* age = (char*)malloc(sizeof(char)*(strlen(ptr)+1));
            strcpy(age,ptr);
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

            //cout<<"Inserting Record [ "<<id<<" "<<name<<" "<<lastName<<" "<<country<<" "<<age<<" "<<virus<<" "<<vaccinated<<" ] at the Vaccine_Monitor."<<endl;
            InsertCitizenRecord(&DataSystem,&Records,&countries,atoi(id),name,lastName,atoi(age),country,virus,temp,Vaccinated);
            cout<<"_________________________________________________________________________________"<<endl;  
        }else if(!strcmp(Commandtoken,"/vaccinateNow")){
            char* ptr = strtok(NULL," ");
            char* id= (char*)malloc(sizeof(char)*(strlen(ptr)+1));
            strcpy(id,ptr);
            ptr = strtok(NULL," ");
            char* name = (char*)malloc(sizeof(char)*(strlen(ptr)+1));
            strcpy(name,ptr);
            ptr = strtok(NULL," ");
            char* lastName = (char*)malloc(sizeof(char)*(strlen(ptr)+1));
            strcpy(lastName,ptr);
            ptr = strtok(NULL," ");
            char* country = (char*)malloc(sizeof(char)*(strlen(ptr)+1));
            strcpy(country,ptr);
            ptr = strtok(NULL," ");
            char* age = (char*)malloc(sizeof(char)*(strlen(ptr)+1));
            strcpy(age,ptr);
            ptr = strtok(NULL," ");
            char* virus = (char*)malloc(sizeof(char)*(strlen(ptr)+1));
            strcpy(virus,ptr);
            VaccinateNow(atoi(id),name,lastName,country,atoi(age),virus,&DataSystem,Records);
            ///vaccinateNow citizenID firstName lastName country age virusName
            cout<<"_________________________________________________________________________________"<<endl;
            
        }
        else if(!strcmp(Commandtoken,"/populationStatus")){
            cout<<"PopulationStatus!!"<<endl;
            char* word =Command;
            char* line =Command;
            date temp1,temp2;
            char* input1,*input2,*input3,*date2;
            int i;
            char* virus;
            for ( i = 0; word != NULL; i++) {
              
                if(i==1){
                     input1=word;
                }
                else if(i==2){
                     input2=word;
                }else if (i==3){
                     input3=word;
                     cout<<input3<<endl;
                }else if(i==4){
                    date2=word;
                    cout<<date2<<endl;

                }
                 word = strtok(NULL, " ");
            }
            
            if(i==4){
                char* day=strtok(input2,"-");
                cout<<atoi(day)<<endl;
                temp1.day=atoi(day);
                char* month=strtok(NULL,"-");
                cout<<atoi(month)<<endl;
                temp1.month=atoi(month);
                char* year=strtok(NULL," ");
                cout<<atoi(year)<<endl;
                temp1.year=atoi(year);
             
                day=strtok(input3,"-");
                temp2.day=atoi(day);
                month=strtok(NULL,"-");
                temp2.month=atoi(month);
                year=strtok(NULL," ");
                temp2.year=atoi(year);
               
                populationStatus(input1,&temp1,&temp2,countries,DataSystem);
            }else if(i==5){
               
                char* day=strtok(input3,"-");
                cout<<atoi(day)<<endl;
                temp1.day=atoi(day);
                char* month=strtok(NULL,"-");
                cout<<atoi(month)<<endl;
                temp1.month=atoi(month);
                char* year=strtok(NULL," ");
                cout<<atoi(year)<<endl;
                temp1.year=atoi(year);
             
                day=strtok(date2,"-");
                temp2.day=atoi(day);
                month=strtok(NULL,"-");
                temp2.month=atoi(month);
                year=strtok(NULL," ");
                temp2.year=atoi(year);
               
                CountryPopulationStatus(input1,input2,&temp1,&temp2,countries,DataSystem);
            }
        cout<<"_________________________________________________________________________________"<<endl;
        }else if(Commandtoken,"/popByAge"){
            char* word =Command;
            char* line =Command;
            date temp1,temp2;
            char* input1,*input2,*input3,*date2;
            int i;
            char* virus;
            for ( i = 0; word != NULL; i++) {
                printf("%d: \"%s\"\n", i, word);
                if(i==1){
                     input1=word;
                }
                else if(i==2){
                     input2=word;
                }else if (i==3){
                     input3=word;
                     cout<<input3<<endl;
                }else if(i==4){
                    date2=word;
                    cout<<date2<<endl;

                }
                 word = strtok(NULL, " ");
            }
          
            if(i==4){
                char* day=strtok(input2,"-");
                cout<<atoi(day)<<endl;
                temp1.day=atoi(day);
                char* month=strtok(NULL,"-");
                cout<<atoi(month)<<endl;
                temp1.month=atoi(month);
                char* year=strtok(NULL," ");
                cout<<atoi(year)<<endl;
                temp1.year=atoi(year);
              
                day=strtok(input3,"-");
                temp2.day=atoi(day);
                month=strtok(NULL,"-");
                temp2.month=atoi(month);
                year=strtok(NULL," ");
                temp2.year=atoi(year);
              
                popStatusByAge(input1,&temp1,&temp2,countries,DataSystem);
                cout<<"_________________________________________________________________________________"<<endl;
            }else if(i==5){
               
                char* day=strtok(input3,"-");
                cout<<atoi(day)<<endl;
                temp1.day=atoi(day);
                char* month=strtok(NULL,"-");
                cout<<atoi(month)<<endl;
                temp1.month=atoi(month);
                char* year=strtok(NULL," ");
                cout<<atoi(year)<<endl;
                temp1.year=atoi(year);
               
                day=strtok(date2,"-");
                temp2.day=atoi(day);
                month=strtok(NULL,"-");
                temp2.month=atoi(month);
                year=strtok(NULL," ");
                temp2.year=atoi(year);
               
                CountryPopStatusByAge(input1,input2,&temp1,&temp2,countries,DataSystem);
                cout<<"_________________________________________________________________________________"<<endl;
        
            }
        }
        
        else{
            cout<<"wrong input try again!"<<endl;
        }
        //Get the next Command;
        cout<<"Waiting for your Command..."<<endl;
        cin.getline(Command,512);
        cout<<"The Command is :"<<Command<<endl;
        
        char * Commandtoken = strtok(Command, " ");
        //cout<<strcmp(Commandtoken,"/vaccinateNow")<<endl;
        cout<<"Command Token"<< Commandtoken<<endl;
    }

    //freeSystem(DataSystem);
   // freeCountries(countries);
    //freeRecords(Records);
    return;
}



//====================================================================================================//