#include <iostream>
#include <cmath>

#include "functions.h"
using namespace std;

int main(){
    
    machineList ml;

    string mac = "Machineno";
    string choice;

    int noOfMachines,sizeOfIdSpace;
    cout<<endl<<"Enter size of identifier space (2,3,4,5): ";
    cin>>sizeOfIdSpace;
    // sizeOfIdSpace=5;cout<<endl;
    ml.bits=sizeOfIdSpace;

    cout<<"Enter number of machines: ";
    cin>>noOfMachines;
    // noOfMachines=8;cout<<endl;
    while ((noOfMachines)<0 || (noOfMachines)>=pow(2,sizeOfIdSpace))
    {
        cout<<endl<<"Wrong number of Machines"<<endl;
        cout<<"Error: no of Machines cannot be less than 0"<<endl;
        cout<<"       or greater than size of Identifier space"<<endl<<endl;
        cout<<"Enter noOfMachines again : ";
        cin>>noOfMachines;
    }
    int* machineArr = new int[noOfMachines];
    cout<<endl<<"Do you want to manually assign Machine IDs ( Yes/No ) : ";
    cin>>choice;
    // choice="No";cout<<endl;
    if (choice=="Yes"  || choice=="yes" || choice=="Y" || choice=="y")
    {
        cout<<endl<<"Enter information for Machibe below"<<endl;
        for (int i = 0; i < noOfMachines; i++)
        {
            cout<<"Enter node for this machine : ";
            cin>>choice;
            while (stoi(choice)<0 || stoi(choice)>pow(2,sizeOfIdSpace)-1)
            {
                cout<<endl<<"Wrong Choice!!!"<<endl;
                cout<<"Enter legal node for machine (0 - "<<pow(2,sizeOfIdSpace)-1<<") : ";
                cin>>choice;
            }
            machineArr[i] = stoi(choice);
            cout<<"Here"<<endl;
        }
    }else if (choice=="No"  || choice=="no" || choice=="N" || choice=="n")
    {
        //Auto assigning machine id
        for (int i = 0; i < noOfMachines; i++)
        {
            machineArr[i]=-1;
        }
        machineArr = completeArray(machineArr,noOfMachines,pow(2,sizeOfIdSpace)-1);

    }else
    {
        cout<<endl<<"Wrong Choice !!! "<<endl;
        cout<<"Exiting program... "<<endl;
        exit(0);
    }
        
    selectionSort(machineArr,noOfMachines);
    cout<<endl<<"Machine Nodes are -> {";
    for (int i = 0; i < noOfMachines; i++)
    {
        cout<<" "<<machineArr[i];
    }
    cout<<" }"<<endl;
    
    ml.insert(machineArr[0]);
    int option;
    string end;
    option=1;
    int k=0,currentMachine=0;
    cout<<endl<<"Do you want to manually assign Node IDs and Values ( Yes/No ) : ";
    cin>>choice;
    if (choice=="Yes"  || choice=="yes" || choice=="Y" || choice=="y")
    {
        while (option==1 && k<pow(2,sizeOfIdSpace))
        {
            cout<<"# 1)      Insert Data in any existing machine    #"<<endl;
            cout<<"# 2)      Do you want to stop entering values    #"<<endl;
            cout<<"Enter your desire option:";
            cin>>option;
            if (option==2)
            {
                break;
            }
            
            while (option==0 || option > 1)
            {
                cout<<"Wrong input!!!"<<endl;
                cout<<"Enter again option : ";
                cin>>option;
            }
            int key;
            string data;
            cout<<"Enter key of that node:";
            cin>>key;
            while (key<0 || key >pow(2,sizeOfIdSpace))
            {
                cout<<"Wrong input!!!"<<endl;
                cout<<"Enter again key : ";
                cin>>key;
            }
            if (key>machineArr[currentMachine] && currentMachine<noOfMachines-1)
            {
                ml.insert(machineArr[++currentMachine]);
                ml.makingRoutingTable();
            }
            
            cout<<"Enter data you want to enter on that node:";
            getline(cin>>ws,data);
            ml.insert(key,data);
            k++;
        }
    }else if (choice=="No"  || choice=="no" || choice=="N" || choice=="n")
    {
        int i=0;
        while (i<pow(2,sizeOfIdSpace))
        {
            string data="Node-> ";
            data.append(to_string(i));
            
            if (i>machineArr[currentMachine] && currentMachine<noOfMachines-1)
            {
                ml.insert(machineArr[++currentMachine]);
                ml.makingRoutingTable();
            }
            cout<<"Generating node ID..."<<endl;
			sleep(0.5);
			cout<<"nodeID => "<<i<<" Value =>"<<data<<endl;
            cout<<"Enter data you want to enter on that node:";
            ml.insert(i,data);
            i++;
        }
    }
    
    while (currentMachine<noOfMachines-1)
    {
        ml.insert(machineArr[++currentMachine]);
    }

    ml.makingRoutingTable();
    
    while(option!=10){
        if(option==10){
            break;
        }
   // ml.makingRoutingTable();
    cout<<"##################################################"<<endl;
    cout<<"                       MENU                       "<<endl;
    cout<<"##################################################"<<endl;
    cout<<"# 1)      Insert Data in any existing machine    #"<<endl;
    cout<<"# 2)      Remove Node                            #"<<endl;
    cout<<"# 3)      Print routing table of any machine     #"<<endl;
    cout<<"# 4)      Print any avl tree of any machine      #"<<endl;
    cout<<"# 5)      Add another machine                    #"<<endl;
    cout<<"# 6)      Remove machine any existing machine    #"<<endl;
    cout<<"# 7)      Display All machines                   #"<<endl;
    cout<<"# 8)      Display All FtTables                   #"<<endl;
    cout<<"# 9)      Use lookup                             #"<<endl;
    cout<<"#10)      Do you want to end program             #"<<endl;
    cout<<"##################################################"<<endl<<endl;
    cout<<"Enter your desire option:";
    cin>>option;
    


    if(option==1){
        int key;
        string data;
        cout<<"Enter key of that node:";
        cin>>key;
        cout<<"Enter data you want to enter on that node:";
        getline(cin>>ws,data);
        ml.insert(key,data);    
    }


     //################         POINT 5         ################"
    else if(option==2){
        
        int node;
        cout<<"Enter the Node you want to remove:";
        cin>>node;
        ml.removeNode(node);
        ml.makingRoutingTable();
        sleep(2.5);
    
    }

     //################         POINT 6         ################"
   else if (option==3){
        ml.makingRoutingTable();
        int machineId;
        cout<<"Which machine? :";
        cin>>machineId;
        ml.displayFTable(machineId);
        sleep(2.5);
       // ml.makingRoutingTable();
        
   }

     //"################         POINT 7        ################"
    else if(option==4){   
        ml.makingRoutingTable();
        int machineId;
        cout<<"Which machine? :";
        cin>>machineId;
         ml.displayAVL(machineId);
        // ml.makingRoutingTable();
    }
    else if(option==5){
         //ml.makingRoutingTable();
        int no_machine;
        cout<<"Enter the no of machine you want to insert:";
        cin>>no_machine;
        ml.insert(no_machine);
        //ml.makingRoutingTable();
    
    }
     //"################         POINT 9        ################"
    else if(option==6){
         
        int no_machine;
        cout<<"Enter the no of machine you want to remove:";
        cin>>no_machine;
        ml.remove(no_machine);
        //ml.makingRoutingTable();

    }
    else if(option==7){
        ml.makingRoutingTable();
    ml.displayAllMachine();sleep(6);
    
    cout<<endl;
    }
    else if(option==8){
        ml.makingRoutingTable();
        ml.displayAllFTable();
        cout<<endl;sleep(6);
       // ml.makingRoutingTable();
    }
    else if (option==9){
        ml.makingRoutingTable();
        int machineId,key;
        cout<<"Enter machine ID  :";
        cin>>machineId;
        cout<<"Enter starting ID :";
        cin>>key;
        ml.lookup(machineId,key);
        sleep(1);
    }
}
}
