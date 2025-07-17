#include <stdio.h>
#include "init.h" //funzioni per inizializzare la scacchiera
#include "const.h" // constanti


void printMatrice(int [SIZE][SIZE]);

int mossa(int [SIZE][SIZE],int,int,int,int);

/*
matrice pezzi da rappresentare su scacchiera

rossi cod ascii x 10
verdi cod ascii

mosse come creare un pattern?
*/ 

int main(int argc, char *argv[]){    

    int board[SIZE][SIZE];
    int tmp = 0 , x1,x2,y1,y2;
    int out[32];
    int i = 0;

    init( board );
    printMatrice(board);
    for(int x = 0 ; x < 5 ; x++){
        printf("inserisci pos iniziale (x,y)");
        scanf("%d %d",&x1,&y1);
        printf("inserisci pos finale (x,y)");
        scanf("%d %d",&x2,&y2);
        out[i] = mossa(board,x1,y1,x2,y2 );
        
        printMatrice(board);

        i = ( out[i] != 0 ) ? ++i :  i ;        
    }
/*
for (int y = 0 ; y < 5; y++){
    printf("%d-",out[y]);
};
*/
    int y = 0;
    int b;
    char *t;
    while( out[y] != 0 ){
         if (out[y]>126){

                b  = out[y] / 10 ;
                t = "\e[1;31m";

            }
            else {

                b = out[y];
                t = "\e[1;32m";
            }

            printf("%s %c\e[0m",t,b);
            y++;

    }
}


void printMatrice(int board[SIZE][SIZE]){

    int b = 0;
    char *t = "";

    for (int y = 0 ; y <= SIZE -1 ; y++){

        for (int x = 0 ; x <= SIZE -1 ; x++){

            if (board[x][y]>126){

                b  = board[x][y] / 10 ;
                t = "\e[1;31m";

            }
            else {

                b = board[x][y];
                t = "\e[1;32m";
            }

            if((x+y)%2==0){

                printf ("%s\e[40m %c \e[0m",t, b); //neroS biancoT

            }
            else{

                printf ("%s\e[47m %c \e[0m", t,b); //biancoS neroT

            }

        }

        printf("\n");
    }

};


int mossa(int board[SIZE][SIZE],int x1,int y1,int x2,int y2){

    int tmp = 0;

    if (board[x2][y2] != ' '){
        tmp = board[x2][y2];
    }

    printf("%d -%c-\n",tmp,' ');

    board[x2][y2] = board[x1][y1];
    board[x1][y1] = ' ';

    return tmp;

}

