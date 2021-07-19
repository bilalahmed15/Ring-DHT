#include <iostream>
#include <cmath>
#include <fstream>
#include "avlTree.h"
using namespace std;


struct machineNode{
    int id;
    int* ftTable;
    int lineCounter;
    machineNode* ftarray;
    string filename;
    avlTree headAVL;
    avlNode* headAvlTree;
    machineNode* next;
};
class machineList{
    machineNode* head;
    machineNode* tail;
    
public:
    int bits;
    int largestMachineID;
    int smallestMachineID;
    int count=0;
    int totalNodes=0;
        machineList();
        void insert(machineNode* new1);
        void insert(int machineID);
        //########################     insulting key value pair   #################################
        void insert(int key, string value);
        void removeNode(int key);               // To remove a Node
        void remove(int key,int machineID);     // To remove Node present at mentioned machine ID
        void remove(int val);                   // To remove Machine at Value 
        void displayAllFTable();                // To display all FT table
        void displayFTable(int machineID);      // To display mentioned machine's FT Table
        void displayAVL(int machineID);         // To display AVL Tree of mentioned machine ID
        void displayAllMachine();               // To display all machines
        int calculateFT(int val,int machine);   // To calculate FT of certain node in machine
        void makingRoutingTable();              // To make routing Table of all Machines
        int lookup(int key,int startMachineID); // To lookup for a certain node in startMachine
};
machineList::machineList(){
        head=NULL;
        tail=NULL;
        largestMachineID=0;
        smallestMachineID=100000;
    }
void machineList::insert(machineNode* new1){
    machineNode* temp=new machineNode;
    machineNode* start=new machineNode;
    new1->filename="./files/machine";
    new1->filename.append(to_string(new1->id));
    new1->filename.append(".txt");
    new1->lineCounter=0;
        ofstream myfile(new1->filename);

    myfile.close();
    count++;
    start=head;
    if(head==NULL){
        head=new1;
        new1->next=head;
    }
    else{
        machineNode * ptr = head;
        while (ptr->next != head) {
            ptr = ptr->next;
        }
        ptr ->next = new1;
        new1->next = head;
        // cout<<endl<<"Head Value: "<<head->id<<" currentValue: "<<new1->id<<endl; 
    }
    new1->ftTable=new int[bits];
    new1->ftarray=new machineNode[bits];
    if (new1->id > largestMachineID)
    {
        largestMachineID=new1->id;
    }
    if (new1->id < smallestMachineID)
    {
        smallestMachineID=new1->id;
    }
    new1->headAvlTree=NULL;
}
void machineList::insert(int machineID){
    machineNode* machine=new machineNode;
    machine->filename="./files/machine";
    machine->filename.append(to_string(machineID));
    machine->filename.append(".txt");
    machine->lineCounter=0;
    machine->headAvlTree=NULL;
    machine->next=NULL;
    machine->id=machineID;
    ofstream myfile(machine->filename);

    myfile.close();

    if (head==NULL ) //|| head->id > machineID)
    {
        
        insert(machine);
    }else if (machineID>largestMachineID){
            largestMachineID=machineID;
            machineNode* current= new machineNode;
            machineNode* prev= new machineNode;
            prev->id=0;
            current=head->next;
            count++;
            while (current->next!=head )
            {
                prev=current;
                current=current->next;
            }
            prev=current;
            current=current->next;
            for (int i = machineID; i!=prev->id; i--)
            {
                (current->headAVL.getValue(current->headAvlTree,i));
                //  cout<<current->headAVL.currenttemp<<endl;
                if (current->headAVL.currenttemp!="Null")
                {
                   
                    machine->headAvlTree = machine->headAVL.insert(machine->headAvlTree,i,current->headAVL.currenttemp,machine->filename,++machine->lineCounter);
                    current->headAVL.getValue(current->headAvlTree,i);
                    current->headAvlTree = current->headAVL.Remove(current->headAvlTree,i);                        
                    fstream nfile;   
                    nfile.open(current->filename,ios::in);
                    if (nfile.is_open()){   //checking whether the file is open
                        string tp;int k=0;
                        string fileNew="";
                        
                        while(getline(nfile, tp)){ //read data from file object and put it into string.
                            k++;
                            if (k!=current->headAVL.fileL)
                            {
                                fileNew.append(tp);
                                fileNew.append("\n");
                            }else
                            {
                                fileNew.append("\n");
                            }
                            
                        }
                        nfile.close();
                        nfile.open(current->filename,ios::out);
                        nfile<<fileNew;
                        nfile.close();
                    }
                }
                if(i==0)
                    i=totalNodes;
            }
            machine->ftTable=new int[bits];
            machine->ftarray=new machineNode[bits];
            prev->next=machine;
            machine->next=current;                   
            
            return;
    }else if(head->id > machineID){
        machineNode* current= new machineNode;
        machineNode* prev= new machineNode;
        prev->id=0;
        current=head->next;
        count++;
        while (current->next!=head )
        {
            prev=current;
            current=current->next;
        }
        prev=current;
        current=current->next;
        for (int i = machineID; i!=prev->id; i--)
        {
            (current->headAVL.getValue(current->headAvlTree,i));
            //  cout<<current->headAVL.currenttemp<<endl;
            if (current->headAVL.currenttemp!="Null")
                {
                   
                machine->headAvlTree = machine->headAVL.insert(machine->headAvlTree,i,current->headAVL.currenttemp,machine->filename,++machine->lineCounter);
                current->headAVL.getValue(current->headAvlTree,i);
                current->headAvlTree = current->headAVL.Remove(current->headAvlTree,i);
                
                fstream nfile;   
                nfile.open(current->filename,ios::in);
                if (nfile.is_open()){   //checking whether the file is open
                    string tp;int k=0;
                    string fileNew="";
                    
                    while(getline(nfile, tp)){ //read data from file object and put it into string.
                        k++;
                        if (k!=current->headAVL.fileL)
                        {
                            fileNew.append(tp);
                            fileNew.append("\n");
                        }else
                        {
                            fileNew.append("\n");
                        }
                        
                    }
                    nfile.close();
                    nfile.open(current->filename,ios::out);
                    nfile<<fileNew;
                    nfile.close();
                }
                }
            if (i==0)
                i=totalNodes;
            
        }
        machine->ftTable=new int[bits];
        machine->ftarray=new machineNode[bits];
        prev->next=machine;
        head=machine;
        machine->next=current;

    }else
    {
        machineNode* prev = new machineNode;
        machineNode* current= new machineNode;
        current=head;
        prev->id=0;
        count++;
        while (!(prev->id < machineID && machineID < current->id) )
        {
            prev=current;
            current=current->next;
            // cout<<"Prev: "<<prev->id<<" Current: "<<current->id<<endl;
        }
        if (prev->id < machineID && machineID < current->id)
        {
            for (int i = machineID; i!=prev->id; i--)
            {
                (current->headAVL.getValue(current->headAvlTree,i));
                //  cout<<current->headAVL.currenttemp<<endl;
                if (current->headAVL.currenttemp!="Null")
                {
                   
                    machine->headAvlTree = machine->headAVL.insert(machine->headAvlTree,i,current->headAVL.currenttemp,machine->filename,++machine->lineCounter);
                    current->headAVL.getValue(current->headAvlTree,i);
                    current->headAvlTree = current->headAVL.Remove(current->headAvlTree,i);
                    
                    fstream nfile;   
                    nfile.open(current->filename,ios::in);
                    if (nfile.is_open()){   //checking whether the file is open
                        string tp;int k=0;
                        string fileNew="";
                        
                        while(getline(nfile, tp)){ //read data from file object and put it into string.
                            k++;
                            if (k!=current->headAVL.fileL)
                            {
                                fileNew.append(tp);
                                fileNew.append("\n");
                            }else
                            {
                                fileNew.append("\n");
                            }
                            
                        }
                        nfile.close();
                        nfile.open(current->filename,ios::out);
                        nfile<<fileNew;
                        nfile.close();
                    }
                }
            }
            machine->ftTable=new int[bits];
            machine->ftarray=new machineNode[bits];
            prev->next=machine;
            machine->next=current;
        }        
    }   
}
void machineList::insert(int key, string value){
            machineNode* temp=new machineNode;
            totalNodes++;
            temp=head;
            int currentCount=0;
            while (currentCount<count)
            {

                if (temp->id >= key)
                {
                    temp->headAvlTree=temp->headAVL.insert(temp->headAvlTree,key,value,temp->filename,++temp->lineCounter);
                    if (temp->headAvlTree == NULL)
                    {
                        cout<<" NULL Machine "<<endl;
                    }
                    return;
                }                
                temp=temp->next;
                currentCount+=1;
            }
            temp=head;
            while (temp!=NULL)// || currentCount==0)
            {
            if (key>largestMachineID && temp->id == smallestMachineID)
                {
                    temp->headAvlTree=temp->headAVL.insert(temp->headAvlTree,key,value,temp->filename,++temp->lineCounter);
                    if (temp->headAvlTree == NULL)
                    {
                        cout<<" NULL Tree";
                    }
                    return;
                }
                temp=temp->next;
                currentCount+=1;
            }
            return;
        }
void machineList::removeNode(int key){
            
            machineNode* temp=head;
            cout<<"Starting from machine "<<temp->id<<endl;
            int countt=0;
            if (key>largestMachineID)
            {
                cout<<"Removing "<<key<<" From AVLTree"<<endl;
                cout<<"From Machine ID "<<temp->id<<endl;
                temp->headAVL.getValue(temp->headAvlTree,key);
                temp->headAvlTree= temp->headAVL.Remove(temp->headAvlTree,key);

                
                fstream nfile;   
                nfile.open(temp->filename,ios::in);
                if (nfile.is_open()){   //checking whether the file is open
                    string tp;int k=0;
                    string fileNew="";
                    
                    while(getline(nfile, tp)){ //read data from file object and put it into string.
                        k++;
                        if (k!=temp->headAVL.fileL)
                        {
                            fileNew.append(tp);
                            fileNew.append("\n");
                        }else
                        {
                            fileNew.append("\n");
                        }
                        
                    }
                    nfile.close();
                    nfile.open(temp->filename,ios::out);
                    nfile<<fileNew;
                    nfile.close();
                }
                return;
            }
            
            while (temp!=NULL )//&& (temp!=head || countt==0))
            {
                int i=0;
                if (key<=temp->id)
                {
                    cout<<"Going to machine "<<temp->id<<endl;
                    cout<<"Removing "<<key<<" From AVLTree"<<endl;
                    cout<<"From Machine ID "<<temp->id<<endl;
                    temp->headAVL.getValue(temp->headAvlTree,key);
                    temp->headAvlTree= temp->headAVL.Remove(temp->headAvlTree,key);
                    fstream nfile;   
                    nfile.open(temp->filename,ios::in);
                    if (nfile.is_open()){   //checking whether the file is open
                        string tp;int k=0;
                        string fileNew="";
                        
                        while(getline(nfile, tp)){ //read data from file object and put it into string.
                            k++;
                            if (k!=temp->headAVL.fileL)
                            {
                                fileNew.append(tp);
                                fileNew.append("\n");
                            }else
                            {
                                fileNew.append("\n");
                            }
                            
                        }
                        nfile.close();
                        nfile.open(temp->filename,ios::out);
                        nfile<<fileNew;
                        nfile.close();
                    }
                    if (temp->headAvlTree == NULL)
                    {
                        cout<<endl<<"Machine "<<temp->id<<" is Empty "<<endl;
                        cout<<"Removing Machine "<<temp->id<<endl;
                        // remove(temp->id,temp->next->id);
                        remove(temp->id);
                    }
                    return;
                }
                countt++;
                bool smallbool=false;
                while (i<bits && key>temp->ftTable[i])
                {
                    if(temp->id==temp->ftTable[i] && i==bits-1){
                        i--;temp=temp->next;smallbool=true;break;}
                    if(temp->id==temp->ftTable[i]){
                        i--;temp=temp->next;smallbool=true;break;}
                    i++;
                    
                }
                if(smallbool==true && key>temp->id){
                    cout<<"Going to machine "<<temp->id<<endl;
                    continue;}
                if (i>=bits)
                {
                    cout<<"Going to machine "<<temp->ftTable[i-1]<<endl;
                    
                    temp = &temp->ftarray[i-1];
                    continue;
                }
                if (!(key>temp->ftTable[i]) && i<bits)
                {
                    if (i==0)
                    {
                        temp=temp->next;
                        continue;
                    }

                    cout<<"Going to machine "<<temp->ftTable[i-1]<<endl;
                    
                    temp = &temp->ftarray[i-1];
                    continue;
                }
            }
            cout<<"Cannot find this MachineID "<<endl;
        }
void machineList::remove(int key,int machineID){
            machineNode* temp=head;
            int countt=0;
            while (temp!=NULL && (temp!=head || countt==0))
            {
                if (temp->id == machineID)
                {
                    cout<<endl<<"Removing "<<key<<" From AVLTree"<<endl;
                    cout<<endl<<"From Machine ID "<<temp->id<<endl;
                    temp->headAVL.getValue(temp->headAvlTree,key);
                    temp->headAvlTree= temp->headAVL.Remove(temp->headAvlTree,key);
                    fstream nfile;   
                    nfile.open(temp->filename,ios::in);
                    if (nfile.is_open()){   //checking whether the file is open
                        string tp;int k=0;
                        string fileNew="";
                        
                        while(getline(nfile, tp)){ //read data from file object and put it into string.
                            k++;
                            if (k!=temp->headAVL.fileL)
                            {
                                fileNew.append(tp);
                                fileNew.append("\n");
                            }else
                            {
                                fileNew.append("\n");
                            }
                            
                        }
                        nfile.close();
                        nfile.open(temp->filename,ios::out);
                        nfile<<fileNew;
                        nfile.close();
                    }
                    if (temp->headAvlTree == NULL)
                    {
                        cout<<" NULL "<<endl;
                    }
                    return;
                }
                countt++;
                temp=temp->next;
            }
            cout<<"Cannot find this MachineID "<<endl;
        }
void machineList::remove(int val){
            
            machineNode* pre=new machineNode;
            machineNode* current=new machineNode;
            current=head;
            count--;
            if (val==smallestMachineID)
            {
                while(current->next!=head ){
                    pre=current;
                    current=current->next;
                }
                pre=current;
                current=current->next;            
            }else
            {
                while(current->next!=head && current->id!=val){
                    pre=current;
                    current=current->next;
                }
            }
            
            
            // current->headAVL.treeHead=current->headAvlTree;
            if(current->id==val && current->headAvlTree!=NULL){
                pre->next=current->next;
                if (current->id==smallestMachineID)
                {
                    for (int i = current->id; i!=pre->id; i--)
                    {
                        if (current->headAvlTree!=NULL)
                            {
                                (current->headAVL.getValue(current->headAvlTree,i));
                            }
                            
                            
                            //  cout<<current->headAVL.currenttemp<<endl;
                            if(current->headAVL.currentkey==i){
                                current->next->headAvlTree = current->next->headAVL.insert(current->next->headAvlTree,i,current->headAVL.currenttemp,current->next->filename,++current->next->lineCounter);
                                current->headAVL.getValue(current->headAvlTree,i);
                                current->headAvlTree = current->headAVL.Remove(current->headAvlTree,i);
                                
                                fstream nfile;   
                                nfile.open(current->filename,ios::in);
                                if (nfile.is_open()){   //checking whether the file is open
                                    string tp;int k=0;
                                    string fileNew="";
                                    
                                    while(getline(nfile, tp)){ //read data from file object and put it into string.
                                        k++;
                                        if (k!=current->headAVL.fileL)
                                        {
                                            fileNew.append(tp);
                                            fileNew.append("\n");
                                        }else
                                        {
                                            fileNew.append("\n");
                                        }
                                        
                                    }
                                    nfile.close();
                                    nfile.open(current->filename,ios::out);
                                    nfile<<fileNew;
                                    nfile.close();
                                }
                            }
                        if(i==0)
                            i=totalNodes;
                            // cout<<i<<" ";
                    }
                }
                else{
                    for (int i = current->id; i!=pre->id; i--)
                        {
                            if (current->headAvlTree!=NULL)
                            {
                                (current->headAVL.getValue(current->headAvlTree,i));
                            }
                            
                            
                            //  cout<<current->headAVL.currenttemp<<endl;
                            if(current->headAVL.currentkey==i){
                               current->next->headAvlTree = current->next->headAVL.insert(current->next->headAvlTree,i,current->headAVL.currenttemp,current->next->filename,++current->next->lineCounter);
                                current->headAVL.getValue(current->headAvlTree,i);
                                current->headAvlTree = current->headAVL.Remove(current->headAvlTree,i);
                                
                                fstream nfile;   
                                nfile.open(current->filename,ios::in);
                                if (nfile.is_open()){   //checking whether the file is open
                                    string tp;int k=0;
                                    string fileNew="";
                                    
                                    while(getline(nfile, tp)){ //read data from file object and put it into string.
                                        k++;
                                        if (k!=current->headAVL.fileL)
                                        {
                                            fileNew.append(tp);
                                            fileNew.append("\n");
                                        }else
                                        {
                                            fileNew.append("\n");
                                        }
                                        
                                    }
                                    nfile.close();
                                    nfile.open(current->filename,ios::out);
                                    nfile<<fileNew;
                                    nfile.close();
                                }
                            }
                            
                        }
                    }
                count--;
                if (val==largestMachineID)
                {
                    largestMachineID = pre->id;
                }
                if (val==smallestMachineID)
                {
                    smallestMachineID = pre->next->id;
                    head=head->next;
                }
                
                return;
            }
            else{
                 pre->next=current->next;
                 return;
                cout<<"nothing removed"<<endl;
            }
        }
void machineList::displayAllFTable(){
    machineNode* temp=head;
    int count=0;
    while (temp!=NULL && (temp!=head || count==0))
    {
        cout<<endl<<"For Machine ID "<<temp->id<<endl;
        cout<<"FT Table "<<endl; 
        for (int i = 0; i < bits; i++)
        {
            cout<<" "<<i+1<<" | "<<temp->ftTable[i]<<endl;
        }
        count++;
        temp=temp->next;
    }
}
void machineList::displayFTable(int machineID){
    machineNode* temp=head;
    int count=0;
    while (temp!=NULL && (temp!=head || count==0))
    {
        if (temp->id == machineID)
        {
            cout<<endl<<"For Machine ID "<<temp->id<<endl;
            cout<<"FT Table "<<endl; 
            for (int i = 0; i < bits; i++)
            {
                cout<<" "<<i+1<<" | "<<temp->ftTable[i]<<endl;
            }
            return;
        }
        count++;
        temp=temp->next;
    }
    cout<<endl<<"Cannot find this MachineID "<<endl;
}
void machineList::displayAVL(int machineID){
    machineNode* temp=head;
    int count=0;
    while (temp!=NULL && (temp!=head || count==0))
    {
        if (temp->id == machineID)
        {
            cout<<endl<<"Printing AVL Tree";
            cout<<endl<<"For Machine ID "<<temp->id<<endl;
            temp->headAVL.Print(temp->headAvlTree);
            if (temp->headAvlTree == NULL)
            {
                cout<<" NULL "<<endl;
            }
            return;
        }
        count++;
        temp=temp->next;
    }
    cout<<endl<<"Cannot find this MachineID "<<endl;
}
void machineList::displayAllMachine(){
    machineNode* temp=head;
    int count=0;
    while (temp!=NULL && (temp!=head || count==0))
    {
        count++;
        cout<<endl<<"For Machine ID "<<temp->id<<endl;
        cout<<"FT Table "<<endl; 
        for (int i = 0; i < bits; i++)
        {
            cout<<" "<<i+1<<" | "<<temp->ftTable[i]<<endl;
        }
        temp->headAVL.Print(temp->headAvlTree);
        if (temp->headAvlTree == NULL)
        {
            cout<<" NULL ";
        }
        temp=temp->next;
    }
    
}
int machineList::calculateFT(int val,int machine){
    int v;
    v=machine+(pow(2,val-1));
    return v;
}
void machineList::makingRoutingTable(){
            machineNode* temp=new machineNode;
            temp=head->next;
            int counter=0;
            while (temp !=(head->next) || counter ==0)
                {
                    
                    for (int i = 0; i < bits; i++)
                    {
                        int value = calculateFT(i+1,temp->id); 
                        if (value>totalNodes-1)
                        {
                            value=value-totalNodes;
                        }
                        if (value>largestMachineID && value<totalNodes)
                        {
                            value=0;
                        }
                        
                        machineNode* temp2=new machineNode;
                        temp2=head;
                        int ctr=0;
                        while (temp2 !=(head) || ctr ==0)
                        {
                            if (temp2->id >= value)
                            {
                                temp->ftTable[i]=temp2->id;
                                temp->ftarray[i]=(*temp2);
                                break;
                            }                    
                            temp2=temp2->next;
                            ctr++;
                        }
                        
                    }
                    temp=temp->next;
                    counter++;
                }
        }
int machineList::lookup(int key,int startMachineID){
    cout<<"Starting from machine "<<startMachineID<<endl;
    machineNode* temp=head;
    machineNode* prev;
    if (temp->id==startMachineID)
    {
        while (temp->next!=head)
        {
            prev=temp;
            temp=temp->next;
        }
        
    }
    else{
    while (temp->id!=startMachineID)
    {
        prev=temp;
        temp=temp->next;
    }
    }
    bool found = false;
    int st=startMachineID;
    int countt=0;
    if ((key<temp->id && key>prev->id) || (temp->id==smallestMachineID && key>largestMachineID))
    {
        if (temp->headAvlTree!=NULL)
        {
            
            temp->headAVL.getValue(temp->headAvlTree,key);
            if (temp->headAVL.currentkey == key){
                found=true;
            }
        }
    }
    while (key<temp->id && found!=true)
    {
                int i =0;    
        if(key==temp->ftTable[i])
            {    
                cout<<"Going to machine "<<temp->ftTable[i]<<endl;
                found=true;
                continue;
            }    
        
        while (i<bits && key<temp->ftTable[i])
            {
                if(key==temp->ftTable[i])
            {    
                cout<<"Going to machine "<<temp->ftTable[i]<<endl;
                found=true;
                break;
            }    
                if (temp->ftTable[i]==smallestMachineID && key<smallestMachineID)
                {
                    // cout<<temp->id;displayFTable(temp->id);
                    cout<<"Going to machine "<<temp->ftTable[i]<<endl;
                    found=true;
                    break;
                }
                i++;//cout<<i<<" ";
            }
        if (found==true)    
            continue;
        if (i==bits)
            {
                // cout<<i<<" "<<temp->ftTable[i-1]<<": ";
                if (temp->ftTable[i-1]==smallestMachineID && key<smallestMachineID)
                {
                    cout<<temp->id;displayFTable(temp->id);
                    cout<<"Going to machine "<<temp->ftTable[i-1]<<endl;
                    found=true;
                    continue;
                }
                
                if (temp->ftTable[i-1] == startMachineID)
                {
                    cout<<"Going to machine "<<temp->ftTable[i-2]<<endl;
                    st=temp->ftTable[i-2];
                    temp = &temp->ftarray[i-2];
                    continue;
                }
                
                cout<<"Going to machine "<<temp->ftTable[i-1]<<endl;
                st=temp->ftTable[i-1];
                temp = &temp->ftarray[i-1];
                // cout<<"Temp: "<<temp->id<<" "<<i<<endl;
                continue;
            }
        if (!(key<temp->ftTable[i]) && i<bits )
            {
                if(key==temp->ftTable[i])
            {    
                cout<<"Going to machine "<<temp->ftTable[i]<<endl;
                found=true;
                continue;
            }    
                // cout<<temp->id<<"<id"<<i<<"<i :";
                cout<<"Going to machine "<<temp->ftTable[i]<<endl;
                st=temp->ftTable[i];
                temp = &temp->ftarray[i];
                continue;
            }
    }

        while (found!=true)
        {
            int i=0;
            if(key<=temp->ftTable[i])
            {    
                cout<<"Going to machine "<<temp->ftTable[i]<<endl;
                found=true;
                continue;
            }    
            while (i<bits && key>temp->ftTable[i])
            {
                i++;
                if (key>largestMachineID)
                {
                    if (temp->ftTable[i]==smallestMachineID)
                    {
                        cout<<"Going to machine "<<temp->ftTable[i]<<endl;
                        found=true;
                        break;
                    }
                    
                }
            }
            
            
            if (i>=bits)
            {
                // cout<<i<<" <-";
                if (key>largestMachineID)
                {
                    // cout<<i<<" <-";
                        cout<<"Going to machine "<<temp->ftTable[i-1]<<endl;
                    st=temp->ftTable[i-1];
                    temp = &temp->ftarray[i-1];
                    continue;
                }
                cout<<"Going to machine "<<temp->ftTable[i-1]<<endl;
                st=temp->ftTable[i-1];
                temp = &temp->ftarray[i-1];
                continue;
            }
            
            if (!(key>temp->ftTable[i]) && i<bits )
            {
                cout<<"Going to machine "<<temp->ftTable[i-1]<<endl;
                st=temp->ftTable[i-1];
                temp = &temp->ftarray[i-1];
                continue;
            }
        }
    
    if(found == true);
        cout<<"Found "<<endl;
}


