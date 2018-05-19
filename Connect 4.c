/*Name: Program of a game called connect 4
File Name: Connect 4.c
Date: Oct, 2016 - Dec, 2016
Author: Zhenghang Zhong(Klaus)
Description: A program which designs a game of strategy for 2 players and it has three functions: 1. player 1 choose to play with another player or computer 
2. Players choose the size of grid and the connection numbers 3. whenever one player cennects counters to the connection numbers, program declares the winner.
*/ 
#include<stdio.h>                                                                    /*include information about standard buffered input&output stdio.h*/
#include<conio.h>                                                                    /*include function getch() conio.h*/                               
#include<stdlib.h>                                                                   /*include function to clear screen(system("cls"), rand(), malloc(), free() stdlib.h*/
#include<time.h>                                                                     /*include function of time() time.h*/

void _initial(char **Grid,int,int);                                                  /*define a _initial function to initialize the Grid with '-'*/
int _playing(char **Grid,int,int,int,int);                                           /*define a function to put counters in the grid as players expect*/
int _rightNumber(int,int);                                                           /*define a function to judge if the number entered is satisfactory*/
void _counters (int);                                                                 /*define a function to see the times players have input*/
int JUDGE(char **Grid,int,int,int);                                                  /*define a JUDGE function to see if anyone has connected specified counters and wins the game*/

int main(){
	int State;                                                                       /*declare a variable to decide whether restart the game*/
	State = 0;
	
	while(State != 1){                                        
	
	int i,k,P2,ROWS,COLS,CON;                                                        /*declare 6 variable of the type of int, i is used in for loop, k stores value entered bu players, P2 decides is player2 man or computer, and ROWS,COLS and CON decide row, col and connecting numbers */
	int Turn=0;                                                                        /*declare a variable of the type of int which means the total turns of players*/
	char **Grid;                                                                     /*declare a 2D array with ** */
	
	
	printf("\t\t\tGame of Connect 4\n");                                             /*rules*/
	printf("Rules:\n1.two players, player 1 VS player player2 or player 1 vs computer\n2.The Grid is typically 6X7. But you change change the size if you like.\n3.The game is won when either player is able to create a line of 4 counters, players can change connection numbers\n");
	printf("Press any button to start.\n");
	getch();
	system("cls");
	printf("1. Player1 VS Player2,    press 'A'\n2. Plyaer1 VS Compuer,    press any other buttons\n");  /*choose playing mode*/
	if(getch()=='A') P2 = 1;
	else P2 =0;
	system("cls");
	
	printf("Press 'B': Classic mode (6X7 grid and connect 4)\n");                                       /*choose classic mode or change the size*/
	printf("Press any other button: Change the rules!\n\n");
	if(getch()=='B'){                                                                                   /*classic mode*/
	    ROWS = 6;
	    COLS = 7;
	    CON = 4;
    }
    else{
    	printf("Design your Grid!\n\n1. Enter number of Rows, Cols and Connecting numbers seperately with blanks!\n\nE.g.(6 7 4)\n\nHint:Connecting numbers should be less than Rows and Cols!\n");
    	k=scanf("%d %d %d",&ROWS,&COLS,&CON);
		while(k!=3){                                                                                      /*in case player enters in a wrong way, increase robustness*/
		printf("Error, please enter numbers like (6 7 4)!\n");
		fflush(stdin);
		k=scanf("%d %d %d",&ROWS,&COLS,&CON);
	               }
	}
	
	Grid = (char **)malloc(ROWS * sizeof(char **));                                                      /*creates a block of memory space with a size of ROWS * the byte size of a pointer to a char pointer*/
	for(i=0;i<ROWS; i++)
		{
		Grid[i] = (char *)malloc(COLS * sizeof(char *));                                                 /*creates a block of memory space with a size of COLS * the byte size of a pointer to a char variable*/
		}
	
	system("cls");
	_initial(Grid,ROWS,COLS);                                                                            /*innitialize the grid according to ROWS and COLS*/
    
	while(1){                                                                                            /*infinite while loop until some conditions are achieved*/
		Turn++;                                                                                           /*total inputing times*/
		if(Turn % 2==1) {                                      /*player 1 inpurs*/
		scanf("%d",&k);
		k=_rightNumber(k,COLS);
	                    }
	    else if(Turn % 2 ==0){
	                           if(P2 == 0){                    /*computer inpurs*/
	    		                    srand(time(NULL));         /*create a srand according to time function*/
			                        k= rand()%COLS+1;		   /*k is in the interval [1,COLS]*/	                   
			                            }
			                   else if (P2 == 1) {                                /*player 2 inpurs*/
			                        scanf("%d",&k);
			                        k = _rightNumber(k,COLS);
		                                        }
		}

		while(_playing(Grid,ROWS,COLS,k,Turn)==1 && JUDGE(Grid,ROWS,COLS,CON)!=2){                        /*when asked to place counter in a already filled col*/
			if(P2==1 || Turn % 2 ==1){
			printf("\nNo more space, change the COL!\n");
		    scanf("%d",&k);
		    k = _rightNumber(k,COLS);
		            }
		    else if(P2==0){                                 /*when computer inputs counter in a filled column*/
		    	k= rand()%COLS+1;
		    	k = _rightNumber(k,COLS);
			}
		}
		
		_counters(Turn);                                 /*print on the screen the times of inputing*/
        if(JUDGE(Grid,ROWS,COLS,CON) == 1) {             /*it happens when someone wins*/
            if(Turn%2 ==1) printf("\nCongratulations!!!Player 1, you win!!! \n");
		    else if(P2==1) printf("\nCongratulations!!!Player 2, you win!!! \n");
		        else       printf("\nSorry! The computer wins!!!\n");
		    break;
	            }
	    else if (JUDGE(Grid,ROWS,COLS,CON) == 2){          /*it happens when no one wins with grid filled*/
	    	printf("\nGrid has been filled, no winner!!!\n");
	    	break;
		                         }                     
            }
    printf("\nGame over!! Press 'N' to start again!\n\nPress any other buttons to end the game!\n");  
	if('N'==getch()) {                                  /*choose whether to restart game*/
		system("cls");
	    State = 0;
	                 }
	else State = 1;     
	for(i = 0;i<ROWS;i++) {
  	        free(Grid[i]);                              /*free the block of memory space created before*/
  	        free(Grid);                             
        }     
    }
  return 0;
}

int _playing(char **Grid,int ROWS,int COLS,int k,int Turn){                        
	int i,j;
	if(*((*Grid)+(k-1)) !='-'){                                       /*the condition satisfies when the column is filled*/
		return 1;
	}
	for(i =ROWS-1;i>=0;i--){                                         /*serach from the botton of the col and place counter in first playce which is blank '-'*/
			if(*(*(Grid+i)+(k-1))=='-') {
				if(Turn%2 == 1) *(*(Grid+i)+k-1)= 'O';               /*player 1 places 'O'*/
				else *(*(Grid+i)+k-1) = 'X';                         /*player 2 places 'X'*/
				break;
			                       }                       
		                      }
	system("cls");
	
	for(j = 0;j<COLS;j++) printf("\t%d",j+1);                        /*print the number of columns on the screen*/
	printf("\n\n");
	for(i = 0;i<ROWS;i++){                                          /*print the Grid*/
	for(j = 0;j<COLS;j++){
		printf("\t%c",Grid[i][j]);
	                     }
	printf("\n\n\n");
}
}

void _initial(char **Grid,int ROWS,int COLS){

	int i,j;
	for(i = 0;i<ROWS;i++)                                             /*initialization*/
	for(j = 0;j<COLS;j++)
		Grid[i][j] = '-';
		
	for(j = 0;j<COLS;j++) printf("\t%d",j+1);                         /*print the number of columns on the screen*/
	printf("\n\n");	
	for(i = 0;i<ROWS;i++){                                            /*print the Grid*/
	for(j = 0;j<COLS;j++){
		printf("\t%c",*(*(Grid+i)+j));
	                     }
	printf("\n\n\n");
    }
}
	
int JUDGE(char **Grid,int ROWS,int COLS,int CON) {
	int found = 0;
	int i,j,c;                                                    /*i, j and c control rows, cols and counters need to be judged whether connect enough numbers*/
	
	for(i = 0;i<ROWS;i++){                                        /*judge in rows, if same counters in number CONS has been connected*/
	for(j = 0;j<(COLS-CON+1);j++) {
		for(c = 0;c<(CON-1);c++) if (*(*(Grid+i)+j+c)==*(*(Grid+i)+j+c+1)) {
			found++;
		}
	    if(*(*(Grid+i)+j)!='-'&&found==CON-1) {                   /*only when CON counters are same and not '-', it returns 1*/ 
	    	return 1;
		}
	    else found =0;                                            /*initialize the variable found*/ 
	}
}
		
		 
	for(j = 0;j<COLS;j++){                                        /*judge in columns, if same counters in number CONS has been connected*/
	for(i = 0;i<(ROWS-CON+1);i++){
	    for(c = 0;c<(CON-1);c++) if ( *(*(Grid+i+c)+j)==*(*(Grid+i+c+1)+j) ) {
	    	found++;
		}
	    if(*(*(Grid+i)+j)!='-'&&found==CON-1) return 1;
	    else found =0;
   }
}

	for(i = 0;i<(ROWS-CON+1);i++){                                /*judge in direction of slash, if same counters in number CONS has been connected*/
	for(j = 0;j<(COLS-CON+1);j++){
	    for(c = 0;c<(CON-1);c++) if (*(*(Grid+i+c)+j+c)==*(*(Grid+i+c+1)+j+c+1)) {
	    	found++;
		}
	    if(*(*(Grid+i)+j)!='-'&&found==CON-1) return 1;      
	    else found =0;                                                     
	}
}
	
	for(i = 0;i<(ROWS-CON+1);i++){                               /*judge in direction of backslash, if same counters in number CONS has been connected*/
	for(j = (COLS-CON);j<COLS;j++){
	    for(c = 0;c<CON-1;c++) if ( *(*(Grid+i+c)+j-c)==*(*(Grid+i+c+1)+j-(c+1)) ) {
	    	found++;
		}
	    if(*(*(Grid+i)+j)!='-'&&found==CON-1) return 1;
	    else found =0;
	}
}

	for(j = 0;j<COLS;j++){                                      /* judge if the top row is filled (the grid is filled) */
		if(*(*(Grid+0)+j)!='-') found++; 
	    if(found==COLS) return 2;   
	} 	
	found = 0;
	}

int _rightNumber(int k,int COLS){                                /*judge if palyers enter a right number*/
	if(k>0&&k<=COLS) return k;                                   /* k is satisfied*/
	else {
	       while(k<=0||k>COLS){                                  /*k is not satisfied */
	           printf("Error!Please enter an integer in [1,%d] !!!\n",COLS);
	           fflush(stdin);
	           scanf("%d",&k);
	                       }
	     }
	system("cls");
    return k;
} 

void _counters (int Turn){                                        /* print on the screen the times of inputing*/       
	int i,m,n;
	m=0,n=0;
	for(i = 0;i<=Turn;i++){
		if(i%2==1) m=m+1;
		if(i%2==0) n=n+1;
	}
	printf("\nPl inputs %d times!\n",m);
	printf("\nP2 inputs %d times!\n",n-1);
}

