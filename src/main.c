#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "init.h" //funzioni per inizializzare la scacchiera
#include "const.h" // constanti


void printMatrice(int [SIZE][SIZE]);

int mossa(int [SIZE][SIZE],int,int,int,int);

int * identificaPezzo(int);

void stampaOut(int *);

void delay(int);

int checkTorre(int [SIZE][SIZE], int ,int ,int ,int );

int checkAlfiere(int [SIZE][SIZE], int ,int ,int ,int );

int checkCavallo(int [SIZE][SIZE],int ,int ,int ,int );

int checkRe(int [SIZE][SIZE],int ,int ,int ,int );

int checkPedone(int [SIZE][SIZE],int ,int ,int ,int );

 typedef struct i
    {
        int x;
        int y;
    } iniziale_type;

    typedef struct f
    {
        int x;
        int y;
    } finale_type;


typedef struct crn
{
    char pezzo;
    int player;
    iniziale_type iniziale;
    finale_type finale;
   
    
} crono;

crono cron[TURNI];


/*
TODO - matrice pezzi da rappresentare su scacchiera

rossi cod ascii x 10 (maggiori di 192)
verdi cod ascii

DONE creare funzione dei turni (tocca al rosso)
e impedire di mangiare i propri pezzi

DONE impedire di spostare i pezzi dell'avversario

DONE controllo casella di partenza e di arrivo se c'è un pezzo
caso d'errore -spostamento o cattura

DONE cronologia lista mosse (salvare in array)

IN PROGRESS validazione mosse  (torre alfiere cavallo regina Re)( pedone da fare) quasi fatto 

IN PROGRESS errori appaiono tutti insieme da sistemare


TODO avere la possibillità di recuperare i pezzi mangiati(pedone in base  avversaria)

TODO arrocco (lungo corto)



*/ 

int main(int argc, char *argv[]){    

    int board[SIZE][SIZE];
    int out[MAX_OUT];

    int tmp = 0 , x1,x2,y1,y2;
    int i = 0;
    short int flag = 0;   
    short int turno = 0;

    init( board ); //
    initOut(out); //  initialize board and out <init.c>

    //printf( "\e[1;1H\e[2J"); //CLS
    printMatrice(board);

    for(int x = 0 ; x < TURNI ; x++){
        
        do{
            flag = 0;
            
            printf("%s inserisci pos iniziale x y: ",(turno ? PLR_TWO: PLR_ONE));
            scanf("%c %d",&x1,&y1);
            fflush(stdin);

            x1 = (char) x1 - 65;
            y1 = y1 - 1;

            printf("-%d %d-\n",(char)x1,y1);
            
            

             if ( (x1 > 7) || (x1 < 0) || (y1 > 7) || (y1 < 0) ){

                printf("fuori dalla scacchiera \n");    
                flag = 1;          

            }
            else{

                if( (identificaPezzo(board[x1][y1])[1] != turno) && (board[x1][y1] != ' ')){
                printf("Usa un tuo pezzo \n");       
                flag = 1;       
            }else if(board[x1][y1] == ' '){

                printf("qui non c'%c nessun pezzo da muovere \n",138);       
                flag = 1;     

            }

            }

        } while (flag ); 
             
       do{
           flag = 0;

           printf("%s inserisci pos finale x y: ",(turno ? PLR_TWO : PLR_ONE));
           scanf("%c %d",&x2,&y2);
           fflush(stdin);

            x2 =(char) x2 - 65;
            y2 = y2 - 1;     
            
           
            if ( (x2 > 7) || (x2 < 0) || (y2 > 7) || (y2 < 0) ){

                printf("fuori dalla scacchiera \n");    
                flag = 1;          

            }
            else{

                 if( (board[x2][y2] != ' ')  ){

                if( ( (turno == identificaPezzo(board[x2][y2])[1]) ) ){
                    printf("\n%c un tuo pezzo\n",138);
                    printf("\n pezzo %d  turno %d\n",identificaPezzo(board[x2][y2])[1],turno);
                    flag = 1;

                }
                else{

                    // 192 > rosso - turno = 0  # 192 < verde - turno = 1 
                    printf("pezzo catturato %s %c  \n",(turno ? COLOR_ONE : COLOR_TWO ), identificaPezzo(board[x2][y2])[0] );  

                }
            }

            }

            switch ( identificaPezzo(board[x1][y1])[0] ) {
                case 'T':
                    printf("Torre");
                      if(!checkTorre(board,x1,x2,y1,y2)){

                            printf(" \e[0m mossa non valida \n"); 
                            flag = 1;
                    }

                    break;
                case 'C':
                    printf("Cavallo");
                    
                    if(!checkCavallo(board,x1,x2,y1,y2)){
                        flag = 1;
                        printf("\e[0m mossa non valida %d \n",flag);
                    }
                    break;
                case 'A':
                    printf("Alfiere");
                     if(!checkAlfiere(board,x1,x2,y1,y2)){

                        flag = 1;
                        printf(" \e[0m mossa non valida \n");  

                    }
                    break;
                case 'R':
                    printf("Re");
                    if( !checkRe(board,x1,x2,y1,y2) ){

                        flag = 1;
                        printf(" \e[0m mossa non valida \n");  

                    }
                    break;
                case 'D':
                    printf("Regina");
                    //printf(" \e[0m check %d %d \n", checkAlfiere(board,x1,x2,y1,y2)  , checkTorre(board,x1,x2,y1,y2)  ); //DEBUG

                    if( !( ( !checkAlfiere(board,x1,x2,y1,y2) && checkTorre(board,x1,x2,y1,y2) ) || ( checkAlfiere(board,x1,x2,y1,y2) && !checkTorre(board,x1,x2,y1,y2) ) )){

                        printf(" \e[0m mossa non valida \n"); 

                        flag = 1;

                    }
                    break;
                case 'p':
                    printf("pedone");
                    if( !checkPedone(board,x1,x2,y1,y2) ){

                        flag = 1;
                        printf(" \e[0m mossa non valida\n");  

                    }

                    break;
                default:
                    printf("sconosciuto");
            }  

            cron[x].pezzo = identificaPezzo(board[x1][y1])[0];
            cron[x].player = identificaPezzo(board[x1][y1])[1];
            cron[x].iniziale.x = x1;
            cron[x].iniziale.y = y1;

            cron[x].finale.x = x2;
            cron[x].finale.y = y2;
            
            
            if (flag==1){
                turno = !turno;
                break;
            }

        } while ( flag ); 

        delay(5);
   
        //printf( "\e[1;1H\e[2J"); //DEBUG CLS 

        //printf("# flag = %d#\n",flag); //DEBUG

        if(!flag){

            out[i] = mossa(board,x1,y1,x2,y2 );        
            
            stampaOut(out);

        }

        printMatrice(board);

        i = ( out[i] != 0 ) ? ++i :  i ; 
        
        turno = !turno;       
        
    }  //check  

    for( int j = 0 ; j < TURNI ; j++ ){
            
            printf("%s %c \e[0m( %c , %d ) -> ( %c , %d )\n", cron[j].player ? COLOR_ONE: COLOR_TWO, cron[j].pezzo, cron[j].iniziale.x + 65 , cron[j].iniziale.y + 1, cron[j].finale.x + 65 , cron[j].finale.y + 1 );
    }
   
}


void printMatrice(int board[SIZE][SIZE]){

    int b = 0;
    char *t ;

    for (int y = 0 ; y < SIZE ; y++){

        for (int x = 0 ; x < SIZE ; x++){

            if (board[x][y]>126){

                b  = board[x][y] / 10 ; // identity piece
                t = COLOR_ONE; // identify color

            }
            else {

                b = board[x][y];
                t = COLOR_TWO;
            }

            if((x+y)%2==0){

                printf ("%s\e[40m %c \e[0m",t,b); // coloreTesto coloreSfondoNero 

            }
            else{

                printf ("%s\e[47m %c \e[0m", t,b); // coloreTesto coloreSfondoBianco 

            }
            

        }
        printf ("\e[0m %c \e[0m",y+49);
        printf("\n");
        
        
    }
    printf(" A  B  C  D  E  F  G  H  \n");

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

void stampaOut(int out[]){

    int b = 0;
    char *t = "";
    int y = 0;
    while( out[y] != 0 ){

        b = identificaPezzo(out[y])[0];
        t = (identificaPezzo(out[y])[1] ? COLOR_TWO : COLOR_ONE) ; // color green red

            printf("%s %c\e[0m\n",t,b); // reset color
            y++;

    }
}

void delay(int sec){

    // Converting time into milli_seconds
    int milli_seconds = 1000 * sec;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
    ;
        

}

int checkTorre(int board[SIZE][SIZE], int x1,int x2,int y1,int y2){
     //controllo mosse torre

     /*devo verificare anche il caso dove un qualunque pezzo sia in mezzo al percorso 
      provare se pos != ' ' count++ 
      inutile restituire se il pezzo è dell'avverario
      restituisco 1 se la mossa è valida 0 in caso contrario
     */
            int cx = x2 - x1;
            int cy = y2 - y1;
            int out = 0;

            //la torre si muove orizzontalmente o verticalmente deve risultare o cx = 0 o cy = 0 altrimenti non è una mossa valida
            // poi controllare se in mezzo al percorso ci sono dei pezzi non importa quali [x1,y2] o [y1,y2] estremi esclusi

            
            if( (!(cx == 0) && (cy == 0)) || ( (cx == 0) && !( cy == 0 ) )  ){
                out = 1;
            }

            if( cx == 0 ){
                if( y1 < y2 )
                    for(int k = y1 + 1 ; k < y2 ; k++){

                        if( board[x1][k] != ' ' ){

                            out = 0;
                            break;

                        }
                    }
                else
                    for(int k = y2 ; k <= y1 - 1 ; k++){

                        if( board[x1][k] != ' ' ){

                            out = 0;
                            break;
                        }
                    }                     
            }
            else if( cy == 0 ){
                if( x1 < x2 )
                    for(int k = x1 + 1 ; k < x2 ; k++){
                        
                        if( board[k][y1] != ' ' ){
                            out = 0;
                            break;

                        }
                    }
                else{
                    for(int k = x2 ; k < x1 - 1; k++){

                        if( board[k][y1] != ' ' ){

                            out = 0;                   
                            break;

                        }
                    }

                }

            } // fine torre


            return out;
}

int checkAlfiere(int board[SIZE][SIZE], int x1,int x2,int y1,int y2){
     //controllo mosse alfiere

            int cx = x2 - x1;
            int cy = y2 - y1;

            int out = 0;            
            //controllo movimento giusto

            //printf("| %d|", abs(cx/cy));   //DEBUG
            
            if( abs(cx/cy) == 1){

                out = 1;

                if(x1 < x2){
                    for(int k = 1 ; k < abs(cx) ; k++)  
                        if( board[x1 + k][y1 - k ] != ' ' ){ 

                            out = 0;
                        }
                }
                else{
                    for(int k = 1; k < abs(cx)  ; k++)   
                        if( board[x2 +k][y2 + k] != ' ' ){  

                            out = 0;

                        }
                }
            }
            else{
                out = 0;
            }
            

            return out;
}

int checkCavallo(int board[SIZE][SIZE],int x1,int x2,int y1,int y2){

    int pattern[5][5] = {   {0,1,0,1,0},
                            {1,0,0,0,1},
                            {0,0,0,0,0},
                            {1,0,0,0,1},
                            {0,1,0,1,0} };

    int dx = x2 - x1;
    int dy = y2 - y1;

    int out = pattern[2+dx][2+dy];

    printf("%d",out);

    return out;
}


int checkRe(int board[SIZE][SIZE],int x1,int x2,int y1,int y2){

    int pattern[3][3] = {   {1,1,1},
                            {1,0,1},
                            {1,1,1} };

    int dx = x2 - x1; //DEBUG 0 -1 -> 1,0
    int dy = y2 - y1;

    int out = pattern[1+dx][1+dy];

    //printf("%d",out); //DEBUG 0 -1 -> 1,0

    return out;
}


int checkPedone(int board[SIZE][SIZE],int x1,int x2,int y1,int y2){
    //da fare
    int pattern[3][3] = {   {1,0,1},
                            {1,1,1},
                            {0,1,0}
                        };

    int dx = x2 - x1;
    int dy = y2 - y1;

    int out = pattern[1+dx][abs(dy)];

    printf("%d",out);

    return out;
}

/*
int checkAlfiere(int board[SIZE][SIZE], int x1,int x2,int y1,int y2){}

posizione iniziale x1 y1 5 5
x2 = x1++ 6 6 -> 7 7
-> x2, x2 6 6 -> 7 7
-> x2, x1 -  2*x1 -x2 -> 6 4 - 7 3
-> 2*x1 - x2 -> 4 4 
-> 2*x1 - x2, x -> 4 6 -> 3 7 
*/ 


