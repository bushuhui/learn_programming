#include "sudoku.h"
#include "time.h"
#include "tool_function.cpp"
#include "mainwindow.h"

Sudoku::Sudoku()
{

}

//this fun is  to create a random sudoku;
//use a interesting way: to change a sudoku with a random form
void Sudoku::RandomSudoku()
{
    // initialization of the numbers in the sudoku
    for(int i = 0;i < 9; i++){
        for(int j = 0; j < 9; j++){
            sudokuboard[i][j].value = in_number[i][j];
        }
    }

    //random  form
    int change_form [9];
    for(int i = 0;i < 9;i ++){
        change_form[i] = i+1;
    }
    RandomList(change_form,9);

    //use the form to change
    //meanwhile rondom the numbers which will not be shown
    for(int i = 0; i < 9; i ++){
        for(int j = 0;j < 9; j ++){
            sudokuboard[i][j].value = change_form[sudokuboard[i][j].value-1] ;
            sudokuboard[i][j].point_type = false;
            int temp = rand()%10;
            if(temp > game_mode){
                sudokuboard[i][j].value = 0;
                sudokuboard[i][j].point_type = true;
            }
        }
    }
    b_sign = false;
    location[0] = 0;
    location[1] = 0;
}

void Sudoku::Check_board()
{
    for(int i = 0;i < 9;i ++){
        for(int j = 0; j < 9;j ++){
            if(sudokuboard[i][j].point_type == true && sudokuboard[i][j].value != 0){
                Check_point_player(i*9+j,sudokuboard[i][j].value);
            }
        }
    }
}

void Sudoku::Check_point_player(int n, int key)
{
    // Is horizontal ok?
    for (int i = 0; i < 9; i++){
        // j = horizontal location
        int j = n / 9;
        if (sudokuboard[j][i].value == key && i != n%9 ){
            sudokuboard[n/9][n%9].point_Islegal = false;
            sudokuboard[j][i].point_Islegal = false;
        }
    }

    //Is vertical ok ?
    for (int i = 0; i < 9; i++){
        // j = vertical location
        int j = n % 9;
        if (sudokuboard[i][j].value == key && i != n/9 ){
            sudokuboard[n/9][n%9].point_Islegal = false;
            sudokuboard[i][j].point_Islegal = false;
        }
    }

    // is the small square OK ?
    //x,y is the square's location in the board
    int x = Which_square(n/9,n%9) / 10;
    int y = Which_square(n/9,n%9) % 10;
    for (int i = x; i < x + 3; i++){
        for (int j = y; j < y + 3; j++){
            if (sudokuboard[i][j].value == key && i != n/9 && j != n%9){
                sudokuboard[n/9][n%9].point_Islegal = false;
                sudokuboard[i][j].point_Islegal = false;
            }
        }
    }
}

bool Sudoku::Check_point_computer(int n, int key)
{

    // Is horizontal ok?
    for (int i = 0; i < 9; i++){
        // j = horizontal location
        int j = n / 9;
        if (sudokuboard[j][i].value == key){
            return false;
        }
    }

    //Is vertical ok ?
    for (int i = 0; i < 9; i++){
        // j = vertical location
        int j = n % 9;
        if (sudokuboard[i][j].value == key){
                 return false;
        }
    }

    // is the small square OK ?
    //x,y is the square's location in the board
    int x = Which_square(n/9,n%9) / 10;
    int y = Which_square(n/9,n%9) % 10;
    for (int i = x; i < x + 3; i++){
        for (int j = y; j < y + 3; j++){
            if (sudokuboard[i][j].value == key){
                  return false;
            }
        }
    }
    return true;
}

// deep find
int Sudoku::SolveSudoku(int n)
{
    int x = n/9;
    int y = n%9;
    if (n > 80){
        b_sign = true;
        return 0;
    }


    if (sudokuboard[x][y].point_type == false){
        SolveSudoku(n+1);
    }

    else{
        //enumerate
        for (int i = 1; i <= 9; i++){
            if (Check_point_computer(n, i) == true){
                sudokuboard[x][y].value = i;
                // find for next block ;
                SolveSudoku(n+1);
                //update_( new_game );
                if (b_sign == true){
                    return 0;
                    }
                // return for next number;
                sudokuboard[x][y].value = 0;
            }
        }
    }
}
