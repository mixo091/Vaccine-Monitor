#include <iostream>
#include <stdlib.h>
#include <cstdlib> 
#include <strings.h>
#include<stdint.h>
#include<inttypes.h>
#include "DataStructures.h"


using namespace std;

//SkipList_Imlementation.

//Function to create a new node of The SkipList.
SLnode *SLnew_node(int id,Record* data){
    SLnode* _node = (SLnode*)malloc(sizeof(SLnode));
    _node->id = id;
    _node->_date=NULL;
    //points to a peson.
    _node->data = data;
    if(data!=NULL){
        //-----------------
    }
    _node->next =NULL;
    _node->prev =NULL;
    _node->up = NULL;
    _node->down = NULL;
    return _node;
}
SLnode* SetDate(SLnode* x,date* Date){
    if(Date!=NULL){
        x->_date=(date*)malloc(sizeof(date));
        x->_date->day=Date->day;
        x->_date->month=Date->month;
        x->_date->year =Date->year;
        x->_date->exists=true;
    }
    return x;
}



//Initilization of the SkipList.
void SkipList_init(SkipList* list,char* virusName,bool VaccinatedSL){
   // cout<<"SkipList Initalazation!"<<endl;
    //creaitng the "edges" fo the skip list.
    SLnode *_node1 = SLnew_node(LOWEST_KEY, NULL);
    SLnode *_node2 = SLnew_node(HIGHEST_KEY, NULL);
    //initizalize pointer values of the nodes.
    _node1->next = _node2;
    _node2->prev = _node1;
    // cout<<_node1->next->id<<endl;
    //SkipList name based on the virus.
    list->Virus=(char*)malloc(sizeof(char)*strlen(virusName)+1);
    strcpy(list->Virus,virusName);
    list->vaccinatedList=VaccinatedSL;
    list->topleft=_node1;
    list->bottomleft = _node1;
    list->topright = _node2;
    list->bottomright = _node2;
    //cout<<list->topleft<<""<<_node1<<endl;
    //initialize height ands length.
    list->height = 0;
    list->len = 2;  
    //cout<<"CheckPoint:SkipList_init for virus " <<list->Virus<<":PASS"<<endl;
    return;
}

int CoinFlip(int height) {
    int times;
    int coin;
    times = 0;
    while(1) {
        coin = random() & 0x1;
        //coin==1 or coin==0
        if (coin == 0) {
            break;
        }
        ++times;
        if (times == height + 1) {
            break;
        }
    };
    return times;
}



//Function to Insert a new Record to the SkipList.(Link the Record pointer ot the Record Object). 
int SL_insert(SkipList*list, int id, Record* data,date* _date){
    //The implementation of insertion.
    //cout<<"The Record to be inserted in the skip list"<<endl;
    //data->Print_Record();
    SLnode* temp;
    int RandomLvl;
    int insertionHeight;
    int j;
    int level;
    SLnode **update;
    int res;
    //-----------------------------------------------------------//
    if (id == LOWEST_KEY || id == HIGHEST_KEY) {
        return -1;
    }
    //------------------------------------------------------------//
    RandomLvl= CoinFlip(list->height);
    if (RandomLvl >= list->height) {
        //if the Rardom level of insertiom is greater than the current height 
        //we need to construct a new higher level on the SkipList.
        //-----Construct Higher level-----//
        SLnode *_node1 = SLnew_node(LOWEST_KEY, NULL);
        SLnode *_node2 = SLnew_node(HIGHEST_KEY, NULL);
        _node1->next = _node2;
        _node2->prev = _node1;
        _node1->down = list->topleft;
        _node2->down = list->topright;
        list->topleft->up = _node1;
        list->topright->up = _node2;
        list->topleft = _node1;
        list->topright = _node2;
        list->height=list->height+1;
    }
    //----------------------------------------------//
    update = (SLnode **) malloc(sizeof(SLnode *) * (list->height + 1));
    bzero(update, sizeof(SLnode *) * (list->height + 1));
    level = list->height;
    temp = list->topleft;
    //Search pos of the new insertion.
    while (1) {
        while (id >= temp->next->id) {
            temp = temp->next;
        }
        if (temp->down== NULL) {
            break;
        }
        update[level--] = temp;
        temp = temp->down;
    }
    update[level] = temp;
  //-----------------------------------------//
   for (j = 0; j <= list->height; ++j) {
        if (update[j] != 0) {
           // printf("%d\n", update[j]->id);
        }
    }
    //Link the Record* p->Record .
    if (temp->id == id) {
        res = 0;
        do {
            temp->data = data;
            temp = temp->up;
        } while (temp != NULL);
    } else {
        res = 1;
        while (level <= RandomLvl) {
           SLnode * _node1 = SLnew_node(id, data);
           if(_date!=NULL){
           _node1 =SetDate(_node1,_date);}
          // _node1->data->Print_Record();
            _node1->next = update[level]->next;
            update[level]->next->prev = _node1;
            _node1->prev = update[level];
            update[level]->next = _node1;
            if (level > 0) {
                _node1->down = update[level - 1]->next;
                update[level - 1]->next->up = _node1;
            }
            ++level;
        }
        ++list->len;
    }
    //----------------------------------------------------------//
    SLnode *foo;
    for (foo = list->topleft; foo->down != NULL;) {
        if (foo->next->id == LOWEST_KEY && foo->down->next->id == HIGHEST_KEY) {
            list->topleft = foo->down;
            list->topright = foo->down->next;
            list->topleft->up = NULL;
            list->topright->up = NULL;
            --list->height;
            free(foo->data);
            free(foo->next);
            free(foo);
            foo = list->topleft;
        } else {
            break;
        }
    }

    free(update);
    return res;
  //--------------------------------------------
}

//-------------------------------------------------//
//Function to print The SkipList.
//with the structure that it depicts.
void SL_print(const SkipList* list){
    SLnode* p;
    SLnode* _node1;
    int  CurrentLvl = list->height;
    cout<<list->height<<endl;
    int i;
    cout<<"|+++++_____ SkipList of [ "<<list->Virus<<" ] _____+++++|";
    cout<<endl;
    cout<<list->height<<endl;
    //----------------------------------------------------------------
    for (p = list->topleft; p != NULL; p= p->down, --CurrentLvl) {
        printf("Level %d: ", CurrentLvl);
        for (_node1 = p; _node1 != NULL; _node1 = _node1->next) {
             printf(" -> %d ", _node1->id);
             if(_node1->data!=NULL){
             cout<<_node1->data->name<<" "<<_node1->data->surname<<" "<<_node1->data->_country->country;
             if (list->vaccinatedList==true && _node1->_date!=NULL){
                 cout<<" ->";
                 _node1->_date->printDate();
             }}
        }
        cout<<endl;
    }
    cout<<"_________________________________________________________________________________________________________"<<endl;
    return;
}


//Search a node which points on a Citizen with a specific Id.
SLnode* SL_searchR(SkipList* list,int id){
    SLnode* irritator;
    irritator=list->topleft;
    while(1){
        while(id>=irritator->next->id){
            irritator=irritator->next;
        }
        if (irritator->down== NULL){
            break;
        }
         irritator = irritator->down;

    }
        if (irritator->id != id) {
            irritator = NULL;
        }
         return irritator;
}
//Functions to Print Just th Record in the Skiplist.
//without the structure of the data(just the Record inside it.)
void SL_printRecords( SkipList* list){
    SLnode* p;
    SLnode* _node1;
    int numberOfRecords=0;
    p = list->bottomleft;
        for (_node1 = p; _node1 != NULL; _node1 = _node1->next) {
             if(_node1->data!=NULL){
                 _node1->data->Print_Record();
                 cout<<endl;
                 numberOfRecords++;
             }
        }
    cout<<"No OF RECORDS:"<<numberOfRecords<<endl;
    return;
}
void  SL_free(SkipList *list){
    SLnode *temp;
    SLnode *_node1;
    SLnode *_node2;
    for (temp = list->bottomleft;temp != NULL;) {
    _node1 = temp;
        temp  = temp->next;
        while (_node1 != NULL) {
            _node2= _node1;
            _node1 = _node1->up;
            free(_node2->data);
            free(_node2);
        }
    }
}


//--------------------------------------------------------//
//==================================================================================================================//
//BloomFilter_Implementation.

//Hash function Generator.
unsigned long db2(unsigned char *str) {
	unsigned long hash = 5381;
	int c; 
	while (c = *str++) {
		hash = ((hash << 5) + hash) + c; // hash * 33 + c 
	}
	return hash;
}
unsigned long sbm(unsigned char *str) {
	unsigned long hash = 0;
	int c;

	while (c = *str++) {
		hash = c + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}
unsigned long hashi(unsigned char *str, unsigned int i) {
	return db2(str) + i*sbm(str) + i*i;
}

//-------------------------------------------------------//

BloomFilter* BloomFilter_init(size_t size){
    BloomFilter* filter = (BloomFilter*)calloc(1,sizeof(BloomFilter));
    filter->size = size;
    filter->bits = malloc(size); 
    return filter;
}


void BloomFilter_insert(BloomFilter* filter,  const void *id) {

	uint8_t* bits = (uint8_t*) filter->bits;
    //irritate hash functions and get values.
    int i=K;
	while (i>0) {
      
		unsigned int hash = hashi((unsigned char *)id, i);
		hash %= filter->size * 8;
		bits[hash / 8] |= 1 << hash % 8;
		i--;
	}
}


bool BloomFilter_check(BloomFilter* filter, const void * id) {
	
	uint8_t *bits =(uint8_t *) filter->bits;
    int i=K;
	while (i>0) {
		unsigned int hash = hashi((unsigned char *)id, i);
		hash %= filter->size * 8;
		if (!(bits[hash / 8] & 1 << hash % 8)) {
			return false;
		}
		i--;
	}
	return true;

}

void FreeFilter(BloomFilter* filter){
    free(filter->bits);
	free(filter);
}



Node* CreateNode(char* virus,int bloomSize, Node *next)
{
    Node *node =(Node*) malloc(sizeof(Node));
  //  cout<<"ok"<<endl;
    node->virus_data.VirusData_init(virus,bloomSize);
   // cout<<node->virus_data.VirusName<<endl;
    node->next = next;
  //  cout<<"ok"<<endl;
    return node;
}

LinkedList *InitializeList(int bloomSize)
{
    LinkedList *list =(LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->size = 0;
    list->Bloomsize=bloomSize;

   // cout<<"CkeckPoint:DataSystem initialazation//PASSED"<<endl;;
    return list;
}

bool SearchVirus(LinkedList *list,char* virus){
    Node* irritator = list->head;
    int counter=list->size;
    while(counter!=0){
      //  cout<<"virus :"<<irritator->virus_data.VirusName<<endl;
        if(!strcmp(irritator->virus_data.VirusName,virus)){
            return true;
        }
        irritator=irritator->next;
        counter--;
        
    }
    return false;
}


//Get Index of the Virus At the System.
Node* GetIndex(LinkedList *list,char* virus){
    Node* irritator = list->head;
    int counter=list->size;
    while(counter!=0){
       // cout<<irritator->virus_data.VirusName<<endl;
        if(!strcmp(irritator->virus_data.VirusName,virus)){
            cout<<"here"<<endl;
            return irritator;
        }
        irritator=irritator->next;
        counter--;    
    }
    return NULL;
}

//initialazation of the virus at the system.
void Virus_Init(LinkedList **list,char* virus){
   // cout<<"Virus: "<<virus<<" is going to be inserted"<<endl;
    Node * newNode = CreateNode(virus,(*list)->Bloomsize, NULL);
    newNode->next=(*list)->head;
    (*list)->head=newNode;
    (*list)->size++;
    return ;
}


void freeSystem(LinkedList* list){
    Node* irritator = list->head;
    int counter=list->size;
    while(counter!=0){
    if(irritator!=NULL){
        SL_free(&irritator->virus_data.non_vaccinated);
        SL_free(&irritator->virus_data.vaccinated);
        FreeFilter(irritator->virus_data.virusFilter);
        free(irritator);
        }  
        irritator=irritator->next;
        counter--;        
    }
    free(list);
    return ;
}