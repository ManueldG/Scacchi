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
per ora mosse libere 

controllo casella di partenza e di arrivo se c'è un pezzo
caso d'errore -spostamento o cattura
*/ 

int main(int argc, char *argv[]){    

    int board[SIZE][SIZE];
    int tmp = 0 , x1,x2,y1,y2;
    int out[32];
    int i = 0;
    short int flag = 0;   

    init( board );
    initOut(out);
    printMatrice(board);

    for(int x = 0 ; x < 5 ; x++){
        
        do{
            flag = 0;
            printf("inserisci pos iniziale x y: ");
            scanf("%d %d",&x1,&y1);

            if(board[x1][y1] == ' '){
                printf("qui non c'%c nessun pezzo da muovere -%c- \n",138,board[x1][y1]);       
                flag = 1;       
            }

             if ( (x1 > 7) || (x1 < 0) || (y1 > 7) || (y1 < 0) ){
                printf("fuori dalla scacchiera \n",board[x1][y1]);    
                flag = 1;          
            }

        } while (flag ); 
       // } while ( board[x1][y1] == ' ' );              
       
       do{
           flag = 0;

           printf("inserisci pos finale x y: ");
           scanf("%d %d",&x2,&y2);
            
            if(board[x2][y2] != ' '){
                printf("pezzo catturato \n");       
            }

             if ( (x2 > 7) || (x2 < 0) || (y2 > 7) || (y2 < 0) ){
                printf("fuori dalla scacchiera \n",board[x2][y2]);    
                flag = 1;          
            }

        } while (flag ); 

        out[i] = mossa(board,x1,y1,x2,y2 );
        
        printMatrice(board);

        i = ( out[i] != 0 ) ? ++i :  i ;        
    }

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

    //printf("%d \n",tmp);

    board[x2][y2] = board[x1][y1];
    board[x1][y1] = ' ';

    return tmp;

}

