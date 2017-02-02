
/*
 File name: exerc_2_8.c
 
 Date: 2017-02-01
 
 Group Number:  #nr 4
 
 Members of students contributed:
 
 Rafael Antonino Sauleo
 
 Filip Isakovski
 
 Maria-Bianca Cindroi
 
 Demonstration code: [<Examen code> <10707>]
 
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>     


#define MAX_COINS 13

const int HUMAN = 0;
const int COMPUTER = 1;

/* ------------- IO --------------- */

/*
 * human_choice
 * Get human choce as an int from stdin.
 * Clears stdin.
 * in: pile
 * out: int-value in range 1-3 (and also less than pile)
 */
int human_choice(int pile);

/*
 * write_winner
 * Write winner as a string on stdout.
 * in: Values HUMAN or COMPUTER.
 * out:
 */
void write_winner( int player );

/*
 * play_again
 * Ask human if he/she wants to play
 * another round. If 'n' or 'N' selected
 * (single char) return false else true.
 * Clears stdin.
 * in: 
 * out: true or false
 */
int play_again();

/* ---------------- Logic ----------------*/

/*
 * computer_choice 
 * Get computers choice (including some AI,
 * if 4 coins or less left, function makes a 
 * smart choice else random).
 * in: pile
 * out: int-value in range 1-3 (and also less than pile)
 */
int computer_choice(int pile);

/*
 * toggle
 * Switches player, if HUMAN in COMPUTER out
 * etc.
 * in:  actual player
 * out: next player
 */
int toggle( int player );

/* --------------------- Utilities -------------*/
void clear_stdin();

/***************************************************
 *
 *    MAIN
 *
 ***************************************************/
int main()
{
  int pile,			/* This is how many coins we have */
    player,			/* Who is playing? */
    play_again_val = true,
    n_coins;			/* Number of coins taken */
  
  srand( time(0) );		/* Setup random */

  printf("Welcome to NIM by Group 4!\n\n");
 
 
  
  pile = MAX_COINS;		/* Set start values (= init) */
  player = HUMAN;

  /* 
   *  Program main loop 
   */
  while( play_again_val ) {	

    printf("There are %d coins in the pile.\n", pile );
    
    if( player == HUMAN ){
      n_coins = human_choice(pile);      
    }else{
      n_coins = computer_choice(pile);
      printf("- I took %d\n", n_coins);      
    }
    pile -= n_coins;
      
    if( pile <= 1 ){
      pile = MAX_COINS;
      write_winner( player );  
      play_again_val = play_again();
      player = HUMAN;
      if(play_again_val==false)
	  	break;
    }
    else{
    	player = toggle( player );
	}
  }
  /*
   * end main loop
   */
 
  printf("Exitted!\n");

  return 0;
}

/******************************************************
 *
 *  DEFINITIONS
 * 
 ******************************************************/


void clear_stdin()
{
  while( getchar() != '\n' ){
    ;
  }
}

int human_choice(int pile)
{
	int choice;
	int trigger = 0;
	while(trigger==0)
	{
		printf("Enter a number between 1-3, that is less than the pile:\n");
		scanf("%d", &choice);
		if((choice == 1 || choice == 2 || choice == 3) && choice <= pile)
		{
			trigger = 1;
			return choice;
		}
	}
	
	return choice;	
}

/*
 * computer_choice 
 * Get computers choice (including some AI,
 * if 4 coins or less left, function makes a 
 * smart choice else random).
 * in: pile
 * out: int-value in range 1-3 (and also less than pile)
 */
int computer_choice(int pile)
{
	int r = (rand() % 3) + 1;
	if(pile <= 4){
		if(pile == 4){
			return 3;
		}
		if(pile == 3){
			return 2;
		}
		if(pile == 2){
			return 1;
		}
	}
	else
	{
		return r;
	}
}

void write_winner(int player )
{
	if(player == HUMAN)
		printf("Winner: HUMAN!\n");
	else
		printf("Winner: COMPUTER!\n");
}

int play_again()
{
	char c;
	printf("Play again? (Y\\N)\n");
	clear_stdin();
	while (c = getchar()){
		printf("Please input (Y\\N)!\n");
		if(c=='Y' || c=='y'){
			return true;
		}
		else if(c=='N' || c=='n'){
			return false;
		}
		else{
			continue;
		}
	}
}

/*
 * toggle
 * Switches player, if HUMAN in COMPUTER out
 * etc.
 * in:  actual player
 * out: next player
 */
int toggle( int player )
{
	if(player == HUMAN)
		return COMPUTER;
	else
		return HUMAN;
}
