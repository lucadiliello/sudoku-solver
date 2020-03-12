#include <iostream>
#include <list>
#include <algorithm>
#include "../include/solver.h"
#include "../include/utils.h"
#include "../include/checks.h"
using namespace std;

/*
Get all values present on a row
*/
static lis get_row(sudoku matrix, int index){
    lis res;
    for(int i = 0; i < SUDOKU_SIZE; i++)
        if(matrix[index][i] != 0)
            res.push_back(matrix[index][i]);
    return res;
}

/*
Get all values present on a column
*/
static lis get_col(sudoku matrix, int index){
    lis res;
    for(int i = 0; i < SUDOKU_SIZE; i++) 
        if(matrix[i][index] != 0)
            res.push_back(matrix[i][index]);
    return res;
}

/*
Get all values present on a square
*/
static lis get_square(sudoku matrix, int row, int col){
    lis res;
    for(int i = row * SUDOKU_DIV; i < (row + 1) * SUDOKU_DIV; i++) 
        for(int j = col * SUDOKU_DIV; j < (col + 1) * SUDOKU_DIV; j++)
            if(matrix[i][j] != 0) res.push_back(matrix[i][j]);
    return res;
}

/*
Check if a list contains an element
*/
static bool contains(lis a, int el){
    for(lis::iterator it = a.begin(); it != a.end(); it++){
        if(*it == el) return true;
    }
    return false;
}

/*
Get list of possible values for a location.
This function checks only for values on the same row/col or in the same square. It does not make any inference.
*/
static lis ** get_initial_possibilities(sudoku matrix){
    lis ** res = new lis*[SUDOKU_SIZE];
    for(int i = 0; i < SUDOKU_SIZE; i++) res[i] = new lis[SUDOKU_SIZE];

    // rows
    lis rows[SUDOKU_SIZE];
    for(int r = 0; r < SUDOKU_SIZE; r++) rows[r] = get_row(matrix, r);
    // cols
    lis cols[SUDOKU_SIZE];
    for(int c = 0; c < SUDOKU_SIZE; c++) cols[c] = get_col(matrix, c);
    // sqr
    lis sqr[SUDOKU_DIV][SUDOKU_DIV];
    for(int s = 0; s < SUDOKU_DIV; s++)
        for(int q = 0; q < SUDOKU_DIV; q++) 
            sqr[s][q] = get_square(matrix, s, q);
    
    // create list of allowed elements
    for(int i = 0; i < SUDOKU_SIZE; i++){
        for(int j = 0; j < SUDOKU_SIZE; j++){
            if(matrix[i][j] == 0){
                for(int k = 1; k <= SUDOKU_SIZE; k++) {
                    if(
                        !contains(rows[i], k) &&
                        !contains(cols[j], k) &&
                        !contains(sqr[i / SUDOKU_DIV][j / SUDOKU_DIV], k)
                    ) res[i][j].push_back(k);
                }
            }
        }
    }    
    return res;
}

/*
Get list of possible values for a location
*/
static void free_possibilities(lis ** possibilities){
    for(int i = 0; i < SUDOKU_SIZE; i++) delete[] possibilities[i];   
    delete[] possibilities; 
}

/*
Update an entry of the sudoku and update the list of possible value of neighbours
*/
static void update_possibilities_and_matrix(sudoku matrix, lis ** possibilities, int i, int j, int new_value){
    int last_value = matrix[i][j];
    matrix[i][j] = new_value;
    
    //only not known values have a list of possibilities
    for(int r = 0; r < SUDOKU_SIZE; r++){
        // update on same row
        if(matrix[i][r] == 0 && r != j){
            if(new_value == 0){
                lis::iterator pos = find(possibilities[i][r].begin(), possibilities[i][r].end(), last_value);
                if(pos == possibilities[i][r].end()) possibilities[i][r].push_back(last_value);
            }
            else{
                lis::iterator pos = find(possibilities[i][r].begin(), possibilities[i][r].end(), new_value);
                if(pos != possibilities[i][r].end()) possibilities[i][r].erase(pos);
            }
        }
        
        // update on same column
        if(matrix[r][j] == 0 && r != i){
            if(new_value == 0){
                lis::iterator pos = find(possibilities[r][j].begin(), possibilities[r][j].end(), last_value);
                if(pos == possibilities[r][j].end()) possibilities[r][j].push_back(last_value);
            }
            else{
                lis::iterator pos = find(possibilities[r][j].begin(), possibilities[r][j].end(), new_value);
                if(pos != possibilities[r][j].end()) possibilities[r][j].erase(pos);
            }
        }
    }
    // update in same square
    int base_i = (i / SUDOKU_DIV) * SUDOKU_DIV;
    int base_j = (j / SUDOKU_DIV) * SUDOKU_DIV;
    for(int it_i = base_i; it_i < base_i + SUDOKU_DIV; it_i++)
        for(int it_j = base_j; it_j < base_j + SUDOKU_DIV; it_j++)
            if(matrix[it_i][it_j] == 0 && it_i != i && it_j != j){
                if(new_value == 0){
                    lis::iterator pos = find(possibilities[it_i][it_j].begin(), possibilities[it_i][it_j].end(), last_value);
                    if(pos == possibilities[it_i][it_j].end()) possibilities[it_i][it_j].push_back(last_value);
                }
                else {
                    lis::iterator pos = find(possibilities[it_i][it_j].begin(), possibilities[it_i][it_j].end(), new_value);
                    if(pos != possibilities[it_i][it_j].end()) possibilities[it_i][it_j].erase(pos);
                }
            }
}

/*
Solve the sudoku by backtracking
*/
bool _solve(sudoku matrix, lis ** possibilities){

    if(!check_consistency(matrix)) return false;
    if(complete(matrix)) return true;

    // find empty cell (can be improved)
    int i, j;
    bool found = false;
    for(int it_i = 0; it_i < SUDOKU_SIZE; it_i++){
        for(int it_j = 0; it_j < SUDOKU_SIZE; it_j++){
            if(matrix[it_i][it_j] == 0){
                i = it_i;
                j = it_j;
                found = true;
            }
            if(found) break;
        }
        if(found) break;
    }

    for(lis::iterator it = possibilities[i][j].begin(); it != possibilities[i][j].end(); it++){
        update_possibilities_and_matrix(matrix, possibilities, i, j, *it);
        if(_solve(matrix, possibilities)) return true;
        update_possibilities_and_matrix(matrix, possibilities, i, j, 0);
    }
    return false;
}

/*
Wrapper for _solve
*/
void solve(sudoku matrix){
    // get list of possibilities for each cell
    lis ** possibilities = get_initial_possibilities(matrix);
    // call solve with backtrack
    _solve(matrix, possibilities);
    // free memory
    free_possibilities(possibilities);    
}

