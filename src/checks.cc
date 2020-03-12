#include <iostream>
#include "../include/checks.h"
#include "../include/utils.h"

/*
Check that numbers in the given row are consistent
*/
bool check_row_consistency(sudoku matrix, int row){
    bool found[SUDOKU_SIZE] = {false};
    for(int i = 0; i < SUDOKU_SIZE; i++)
        if(matrix[row][i] != 0 && found[matrix[row][i] - 1]) return false;
        else found[matrix[row][i] - 1] = true;
    return true;
}

/*
Check that numbers in the given column are consistent
*/
static bool check_col_consistency(sudoku matrix, int col){
    bool found[SUDOKU_SIZE] = {false};
    for(int i = 0; i < SUDOKU_SIZE; i++)
        if(matrix[i][col] != 0 && found[matrix[i][col] - 1]) return false;
        else found[matrix[i][col] - 1] = true;
    return true;
}

/*
Check that numbers in a given square are consistent
*/
static bool check_sqr_consistency(sudoku matrix, int row, int col){
    bool found[SUDOKU_SIZE] = {false};
    row = row * SUDOKU_DIV;
    col = col * SUDOKU_DIV;
    for(int i = 0; i < SUDOKU_DIV; i++) 
        for(int j = 0; j < SUDOKU_DIV; j++)
            if(matrix[row + i][col + j] != 0 && found[matrix[row + i][col + j] - 1]) return false;
            else found[matrix[row + i][col + j] - 1] = true;
    return true;
}

/*
Check that numbers in all rows are consistent
*/
static bool check_rows_consistency(sudoku matrix){
    for(int i = 0; i < SUDOKU_SIZE; i++)
        if(!check_row_consistency(matrix, i)) return false;
    return true;
}

/*
Check that numbers in all columns are consistent
*/
static bool check_cols_consistency(sudoku matrix){
    for(int i = 0; i < SUDOKU_SIZE; i++)
        if(!check_col_consistency(matrix, i)) return false;
    return true;
}

/*
Check that numbers in all squares are consistent
*/
static bool check_sqrs_consistency(sudoku matrix){
    for(int i = 0; i < SUDOKU_DIV; i++) 
        for(int j = 0; j < SUDOKU_DIV; j++)
            if(!check_sqr_consistency(matrix, i, j)) return false;
    return true;
}

/*
Check that sudoku is consistent
*/
bool check_consistency(sudoku matrix){
    return check_rows_consistency(matrix) &&
        check_cols_consistency(matrix) && check_sqrs_consistency(matrix);
}

/*
Check that sudoku has no missing numbers
*/
bool complete(sudoku matrix){
    for(int i = 0; i < SUDOKU_SIZE; i++) 
        for(int j = 0; j < SUDOKU_SIZE; j++)
            if(matrix[i][j] == 0) return false;
    return true;
}