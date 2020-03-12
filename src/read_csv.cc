#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/read_csv.h"
#include "../include/utils.h"
using namespace std;

/*
Split a line on the character "," and return the list of numbers with 0 as "empty"
*/
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

/*
Read the csv file and return the sudoku matrix as a 2D array of integers
*/
sudoku read(char * filename){ 
    // define sudoku matrix
    sudoku res = new int*[SUDOKU_SIZE];

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
    return res;
}