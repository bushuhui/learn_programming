#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>

/*
struct POINT:
    value :the number in the block of the sudoku
            0: wait for player to input number
            1-9 : number in the block
   point_type :
            true :the number can be changed;
            False : the number can't be changed;
    point_Islegal :
            true : the number can stay;
            false : the number is illegal;
*/
struct POINT{
    int value;
    bool point_type  ;
    bool point_Islegal = true;
};

//Sudoku is the main class(include numbers; input ;output;solve)
class Sudoku
{
public:
    bool b_sign = false;  // true: the sudoke is solved
    POINT sudokuboard[9][9];  // 9*9 points
    int location[2];  // the mouse chose which number to change
    int game_mode = 3;
    int game_time;

    Sudoku();
    bool Check_point_computer(int n, int key);  //check the point's number
    void Check_point_player(int n,int key);
    int SolveSudoku(int n);  // solve the sudoku
    void Check_board();  //use fun:check_point to check every point
    void Input_number();
    void RandomSudoku();  // build a sudoku
};

#endif // SUDOKU_H
