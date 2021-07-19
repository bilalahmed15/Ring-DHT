
#include <iostream>
#include <fstream>
using namespace std;

struct avlNode {
    int key;
    int line;
    string value;
    string filename;
    avlNode* left;
    avlNode* right;
};
class avlTree{
    int height;
    int difference;
    
    public:
    avlNode* treeHead;
    avlTree(){
        treeHead=NULL;
    }
    int getHeight(avlNode* n){
        int cHeight=0;
        if (n!=NULL){
            int left_height=getHeight(n->left);
            int right_height=getHeight(n->right);
            int max=0;
            if (left_height>right_height)
            {
                max=left_height;
            }else 
                max=right_height;
            cHeight=max+1;
        }
        return cHeight;
    }
    int heightDifference(avlNode* n){
        int left_height=getHeight(n->left);
        int right_height=getHeight(n->right);
        int diff=left_height-right_height;
        // cout<<" diff: "<<diff<<n->key<<endl;
        return diff;
    }
    avlNode* insert(avlNode* c_head,int key,string value,string filename,int fileline){

        if (c_head==NULL)
        {
            c_head=new avlNode;
            c_head->key=key;
            c_head->value=value;
            c_head->filename=filename;
            c_head->line=fileline;
            ofstream outfile;

            outfile.open(filename, std::ios_base::app); // append instead of overwrite
            outfile << value <<'\n'; 

            c_head->left=NULL;
            c_head->right=NULL;
            if (treeHead==NULL)
                treeHead=c_head;
                
            return c_head;    
        }else if (key < (c_head->key))
        {
            c_head->left=insert(c_head->left,key,value,filename,fileline);
            c_head=balance(c_head);
        }else if (key>(c_head->key))
        {
            c_head->right=insert(c_head->right,key,value,filename,fileline);
            c_head=balance(c_head);
        }
        return c_head;        
    }

    avlNode* rotateRight(avlNode* currentHead,char ch){
        avlNode* temp;
        temp=currentHead->right;
        if (ch=='r')
        {
            currentHead->right=temp->left;
            temp->left=currentHead;
            return temp;
        }else if (ch=='l')
        {
            currentHead->right=rotateLeft(temp,'l');
            return rotateRight(currentHead,'r');
        }   
    }
    avlNode* rotateLeft(avlNode* currentHead,char ch){
        avlNode* temp;
        temp=currentHead->left;
        if (ch=='l')
        {
            currentHead->left=temp->right;
            temp->right=currentHead;
            return temp;
        }else if (ch=='r')
        {
            currentHead->left=rotateRight(temp,'r');
            return rotateLeft(currentHead,'l');
        }   
    }
    avlNode* balance(avlNode* n){
        int diff=heightDifference(n);
        // cout<<diff<<" here "<<n->key<<endl;
        if (diff>1){
            if (heightDifference(n->left)>0)
            {
                n=rotateLeft(n,'l');    
            }else
            {
                n=rotateLeft(n,'r');
            }
        }else if (diff<-1)
        {
            if (heightDifference(n->right)>0)
            {
                n=rotateRight(n,'l');
            }else
            {
                n=rotateRight(n,'r');
            }
        }
        return n;
    }

    avlNode* Remove(avlNode* c_head,int key){
        if (c_head==NULL){
            return c_head;
        }
        if (key<c_head->key)
        {
            c_head->left=Remove(c_head->left,key);
        }
        else if (key>c_head->key)
        {
            c_head->right=Remove(c_head->right,key);
        }
        else //If Equal
        {
            if (c_head->left==NULL || c_head->right==NULL)
            {
                avlNode* temp;
                if (c_head->left!=NULL)
                {
                    temp=c_head->left;
                }else
                {
                    temp=c_head->right;
                }
                if (temp==NULL)
                {
                    temp=c_head;
                    c_head=NULL;
                }
                else
                {
                    *c_head=*temp;
                }
                delete temp;   
            }else
            {
                
                avlNode* temp;
                avlNode* temp2=c_head->right;
                while (temp2->left!=NULL)
                {
                    temp2=temp2->left;
                }
                temp=temp2;
                c_head->key=temp->key;
                c_head->right=Remove(c_head->right,temp->key);
            }
            
            
        }
        if (c_head==NULL)
        {
            return c_head;
        }
        balance(c_head);
        
    }
    
    string currenttemp="Null";
    int currentkey;
    int fileL;
    void getValue( avlNode* n,int key ){
        
        if (n->key == key )
                {
                    currenttemp=n->value;
                    currentkey=key;
                    fileL=n->line;
                    return;
                }
        if(n != NULL)
        {
            // cout<<"Node: " << n->key  ;
            if(n->left != NULL)
            {
                getValue(n->left,key);
            }
            if(n->right != NULL)
            {
                getValue(n->right,key);
                
            }
           
        }
        
    }

    void Print(avlNode *n)
    {
        if(n != NULL)
        {
            cout<<"Node: " << n->key  ;
            if(n->left != NULL)
            {
                cout<<endl<<"\t moving left\n";
                Print(n->left);
                cout<<"Returning to Node " << n->key << " from its' left subtree\n";
            }
            else
            {
                cout<<endl<<"\t left subtree is empty\n";
            }
            cout<<"     "  ;
            if(n->right != NULL)
            {
                cout<<"\t moving right\n";
                Print(n->right);
                cout<<"Returning to Node " << n->key << " from its' right subtree\n";
            }
            else
            {
                cout<<"\t right subtree is empty\n";
            }
        }
    }
};
