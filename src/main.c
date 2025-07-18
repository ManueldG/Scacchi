#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "init.h" //funzioni per inizializzare la scacchiera
#include "const.h" // constanti


void printMatrice(int [SIZE][SIZE]);

int mossa(int [SIZE][SIZE],int,int,int,int);

int * identificaPezzo(int);

/*
TODO - matrice pezzi da rappresentare su scacchiera

rossi cod ascii x 10 (maggiori di 192)
verdi cod ascii

DONE creare funzione dei turni (tocca al rosso)
e impedire di mangiare i propri pezzi

DONE impedire di spostare i pezzi dell'avversario

TODO mosse come creare un pattern?per ora mosse libere 

TODO validazione mosse

TODO avere la possibillità di recuperare i pezzi mangiati(pedone in base  avversaria)

TODO arrocco (lungo corto)

TODO cronologia lista mosse

DONE controllo casella di partenza e di arrivo se c'è un pezzo
caso d'errore -spostamento o cattura
*/ 

int main(int argc, char *argv[]){    

    int board[SIZE][SIZE];
    int tmp = 0 , x1,x2,y1,y2;
    int out[MAX_OUT];
    int i = 0;
    short int flag = 0;   
    short int turno = 0;

    init( board ); //
    initOut(out); //  initialize board and out <init.c>
    printf( "\e[1;1H\e[2J"); //CLS
    printMatrice(board);

    for(int x = 0 ; x < TURNI ; x++){
        
        do{
            flag = 0;
            printf("%s inserisci pos iniziale x y: ",(turno ? PLR_TWO: PLR_ONE));
            scanf("%d %d",&x1,&y1);

            if(identificaPezzo(board[x1][y1])[1] != turno){
                printf("Usa un tuo pezzo \n");       
                flag = 1;       
            }

            if(board[x1][y1] == ' '){

                printf("qui non c'%c nessun pezzo da muovere \n",138);       
                flag = 1;     

            }

             if ( (x1 > 7) || (x1 < 0) || (y1 > 7) || (y1 < 0) ){

                printf("fuori dalla scacchiera \n");    
                flag = 1;          

            }

        } while (flag ); 
             
       do{
           flag = 0;

           printf("%s inserisci pos finale x y: ",(turno ? PLR_TWO : PLR_ONE));
           scanf("%d %d",&x2,&y2);
            
            if( (board[x2][y2] != ' ')  ){

                if( ( (turno == identificaPezzo(board[x2][y2])[1]) ) ){
                    printf("\n%c un tuo pezzo\n",138);
                    printf("\n%d %d\n",identificaPezzo(board[x2][y2])[1],turno);
                    flag = 1;

                }
                else{

                    // 192 > rosso - turno = 0  # 192 < verde - turno = 1 
                    printf("pezzo catturato %s %c  \n",(turno ? COLOR_TWO : COLOR_ONE ), identificaPezzo(board[x2][y2])[0] );  

                }
            }

             if ( (x2 > 7) || (x2 < 0) || (y2 > 7) || (y2 < 0) ){
                printf("fuori dalla scacchiera \n");    
                flag = 1;          
            }

        } while ( flag ); 

      // Converting time into milli_seconds
	int milli_seconds = 1000 * 2;

	// Storing start time
	clock_t start_time = clock();

	// looping till required time is not achieved
	while (clock() < start_time + milli_seconds)
		;
        
        printf( "\e[1;1H\e[2J"); //CLS

        out[i] = mossa(board,x1,y1,x2,y2 );
    
        printMatrice(board);

        i = ( out[i] != 0 ) ? ++i :  i ; 
        turno = !turno;       
    }

    int y = 0;
    int b;
    char *t;
    while( out[y] != 0 ){

        b = identificaPezzo(out[y])[0];
        t = (identificaPezzo(out[y])[1] ? COLOR_TWO : COLOR_ONE) ; // color green red



            printf("%s %c\e[0m",t,b); // reset color
            y++;

    }
}


void printMatrice(int board[SIZE][SIZE]){

    int b = 0;
    char *t = "";

    for (int y = 0 ; y <= SIZE -1 ; y++){

        for (int x = 0 ; x <= SIZE -1 ; x++){

            if (board[x][y]>126){

                b  = board[x][y] / 10 ; // identity piece
                t = COLOR_ONE; // identify color

            }
            else {

                b = board[x][y];
                t = COLOR_TWO;
            }

            if((x+y)%2==0){

                printf ("%s\e[40m %c \e[0m",t, b); //coloreTesto coloreSfondoNero 

            }
            else{

                printf ("%s\e[47m %c \e[0m", t,b); //coloreTesto coloreSfondoBianco 

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

    board[x2][y2] = board[x1][y1];
    board[x1][y1] = ' ';

    return tmp;

}

int * identificaPezzo(int pezzo){

    //0 rosso - 1 verde

   int* out = malloc( 2 * sizeof(int));


     if (pezzo>126){ // 126 cod last letter in ascii

                out[0]  = pezzo/ 10 ;
                out[1] = 0;

            }
            else {

                out[0] = pezzo;
                out[1] = 1;
            }

            return out;

}

