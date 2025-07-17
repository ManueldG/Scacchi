 #include <stdio.h> 
 #include "const.h"

 //inizializza la scacchiera 

 void init(int board[SIZE][SIZE]){
        for (int y = 0 ; y <= SIZE -1 ; y++)
            for (int x = 0 ; x <= SIZE -1 ; x++)
                board[x][y] = (char) ' '; // 176 : 219;

         int k = 1;

    for( int x = 0 ; x <= SIZE - 1 ; x++)
    {

        board[x][1] =  piece[1]*10; //red
        board[x][6] =  piece[1]; //white
        k++;
        if (k<=6){

            board[x][0] = piece[k]*10; //red
            board[7-x][0] = piece[k]*10;

            board[x][7] = (char) piece[k]; // white
            board[7-x][7] = (char) piece[k];

        }
    }
    board[3][0] = piece[5]*10; // red
    board[3][7] = piece[5]; // white
    };

    void initOut(int out[32]){

        for (int i = 0 ; i < 32 ; i++)
            out[i] = 0;

    };
