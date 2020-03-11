#include <iostream>
#include "read_csv.h"
using namespace std;

int main(int argc, char** argv) {
    if(argc != 2){
        cout << "Usage is ./executable <csv_file>" << endl;
        exit(1);
    }
    
    read(argv[1]);
    
    return 0;
}

