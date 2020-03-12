#include <iostream>
#include "../include/utils.h"
using namespace std;

/*
Print a line as +---+---+...+---+
*/
static void line(){
    cout << "+";
    for (int i = 1; i <= SUDOKU_SIZE; i++) cout << "---+";
    cout << endl;
}

/*
Print the sudoku in an pretty way
*/
void print_sudoku(sudoku array){
    line();
    for(int i = 0; i < SUDOKU_SIZE; i++){
        cout << "|";
        for(int j = 0; j < SUDOKU_SIZE; j++) cout << " " << array[i][j] << " |";
        cout << endl;
        line();
    }
}
