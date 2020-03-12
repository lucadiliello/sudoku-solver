#include <iostream>
#include "../include/read_csv.h"
#include "../include/solver.h"
#include "../include/utils.h"
using namespace std;

int main(int argc, char** argv) {
    if(argc != 2){
        cout << "Usage is ./executable <csv_file>" << endl;
        exit(1);
    }
    // read csv from file
    sudoku s = read(argv[1]);

    // print input, solve sudoku and print solution (first found if there are more than one)
    cout << "input sudoku is:" << endl;
    print_sudoku(s);
    cout << "solving..." << endl;
    solve(s);
    cout << "solved sudoku is:" << endl;
    print_sudoku(s);

    return 0;
}

