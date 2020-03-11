// reading a text file
#include "read_csv.h"
#include <iostream>
#include <fstream>
#include <sstream>

#define SUDOKU_SIZE 9
using namespace std;

static void print_line(){
    cout << string(SUDOKU_SIZE * 2 + 1, '-') << endl;
}

static void print_sudoku(int ** array){
    print_line();
    for (int i = 0; i < SUDOKU_SIZE; i++){
        cout << "|";
        for (int j = 0; j < SUDOKU_SIZE; j++) cout << array[i][j] << "|";
        cout << endl;
        print_line();
    }
}


static int * split_line(string line) {

    int * res = new int[SUDOKU_SIZE];
    stringstream ss(line);
    string number;
    int i = 0;
    
    while(getline(ss, number, ',' )) {
        if(i >= SUDOKU_SIZE) return NULL;
        if(number == "X") res[i] = 0;
        else res[i] = stoi(number);
        i++;
    }    
    return res;
}



int** read(char * filename){ 
    // define sudoku matrix
    int** res = new int*[SUDOKU_SIZE];

    // open input file
    ifstream input_file(filename);
    //support variable
    string line;
    int i = 0;

    if(input_file.is_open()){
        while (getline(input_file, line)){
            if(i >= SUDOKU_SIZE){
                cout << "File error, exiting" << endl;
                exit(1);
            }
            res[i] = split_line(line);
            if(res[i] == NULL){
                cout << "File error, exiting" << endl;
                exit(1);
            }
            i++;
        }
        input_file.close();

    } else {
        cout << "Unable to open file, exiting" << endl;
        exit(1);
    }
    cout << "Input csv sudoku is:" << endl;
    print_sudoku(res);

    return res;
}