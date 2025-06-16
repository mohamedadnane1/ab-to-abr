#include <iostream>
#include <fstream>
#include <stack>
#include <stdlib.h>

using namespace std;

#include "AVL.h"

int main(int argc,char** argv)
{
	 if (argc != 2) {
        cout << argv[0] << " <filename>" << endl;
        return 1;
    }
    char* filename = argv[1];

    bool option = true; 
    AVL arbre1(filename, option);

    cout<<endl<<endl;  
    cout<<"______ARBRE AVANT EQUILIBRE______"<<endl<<endl;
    arbre1.prefixe();

    cout<<endl<<endl<<endl<<endl;

    cout<<"______ARBRE APRES EQUILIBRE______"<<endl<<endl;

    arbre1.equilibre();    
    arbre1.prefixe();

    return 0;
}