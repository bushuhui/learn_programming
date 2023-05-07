#include "tool_function.h"

int in_number[9][9] = {{1,2,3,4,5,6,7,8,9},
                      {4,5,6,7,8,9,1,2,3},
                      {7,8,9,1,2,3,4,5,6},
                      {8,9,1,2,3,4,5,6,7},
                      {2,3,4,5,6,7,8,9,1},
                      {5,6,7,8,9,1,2,3,4},
                      {6,7,8,9,1,2,3,4,5},
                      {9,1,2,3,4,5,6,7,8},
                      {3,4,5,6,7,8,9,1,2}};

// make a list random
void RandomList(int a[], int n)
{
   int index, tmp, i;
   srand(time(NULL));
   for (i = 0; i <n; i++)
    {
       index = rand() % (n - i) + i;
       if (index != i)
         {
            tmp = a[i];
            a[i] = a[index];
            a[index] = tmp;
         }
    }
 }

int Which_square(int x,int y)
{

    if(x<=2){
        if(y<=2) return 00;
        else if(y<=5) return 03;
        else return 06;
    }
    else if(x<=5){
        if(y<=2) return 30;
        else if(y<=5) return 33;
        else return 36;
    }
    else {
        if(y<=2) return 60;
        else if(y<=5) return 63;
        else return 66;
    }
}

void get_time(int time[],int times)
{
    for(int i = 0; i < 3 ;i++){
         time[2-i] = times % 100;
         times /= 100;
    }
}
