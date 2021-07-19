#include "machineNode.h"
#include <unistd.h>

using namespace std;

machineList* autoAssignID(int noMachines,int IDbits){
    machineList* ml = new machineList;

    for (int i = 0; i < noMachines; i++)
    {
        machineNode* node = new machineNode;
        node->filename="";
        node->headAvlTree=NULL;
        node->next=NULL;
        node->id=((IDbits-i-1)/(noMachines-i)+(i));
        ml->insert(node);

        
    }
    
    return ml;
}
void selectionSort(int* a, int n) {
   int i, j, min, temp;
   for (i = 0; i < n - 1; i++) {
      min = i;
      for (j = i + 1; j < n; j++)
      if (a[j] < a[min])
      min = j;
      temp = a[i];
      a[i] = a[min];
      a[min] = temp;
   }
}
unsigned int SHF(string input, unsigned int bits) {
	unsigned int init = 123451535;
	unsigned int mul = 7654321;
	unsigned int hash, bits_size = 2;

	for (int i = 0; i < input.length(); i++) {
		hash = hash ^ (input[i]);
		hash *=  mul;
	}

	for (int i = 0; i <= bits; i++, bits_size *= bits_size);

	while (hash > bits_size) {
		hash /= 10;
	}

	return hash;
}

int* completeArray(int* array, int size,int tnodes) {
	int value, j;
	bool check = true;
    srand(time(NULL)); 
	for (int i = 0; i < size; i++) {
		if (array[i] <= 0) {
			check = true;
			while (check) {
				value = rand() % tnodes;
				//cout << value;

				for (j = 0; j < size; j++) {

					if (array[j] == value) {
						break;
					}
				}

				if (j == size) {
					
					cout<<"Generating new machine ID..."<<endl;
					sleep(1);
					cout<<"New Machine ID-> "<<value<<endl;
					sleep(0.5);
					array[i] = value;
					check = false;
				}
			}
		}
	}

	return array;
}
