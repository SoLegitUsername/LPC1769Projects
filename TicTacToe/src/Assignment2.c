/*
===============================================================================
 Name        : Assignment3.c
 Authors      : $Raymond Atkinson
 Version     :
 Copyright   : $(copyright)
 Description : A simple game of TicTacToe made for the LPC1769 Rev-D.
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>

#define FIO0DIR (*(volatile unsigned int *)0x2009c000)
#define FIO0PIN (*(volatile unsigned int *)0x2009c014)
#define FIO1DIR (*(volatile unsigned int *)0x2009c020)
#define FIO1PIN (*(volatile unsigned int *)0x2009c034)
#define FIO2DIR (*(volatile unsigned int *)0x2009c040)
#define FIO2PIN (*(volatile unsigned int *)0x2009c054)
#define PINMODE4 (*(volatile unsigned int *)0x4002c050)

#define sw1 ((FIO2PIN >> 3) & 1) //Top left button
#define sw2 ((FIO2PIN >> 4) & 1) //Top middle button
#define sw3 ((FIO2PIN >> 5) & 1) //Top right button
#define sw4 ((FIO2PIN >> 6) & 1) //Right top button
#define sw5 ((FIO2PIN >> 7) & 1) //Right middle button
#define sw6 ((FIO2PIN >> 8) & 1) //Right bottom button
#define sw7 ((FIO2PIN >> 2) & 1) //RESET BUTTON

int moves[9] = {0};	//Initialize to keep track of player moves so we can check for win conditions later

int main(void) {
	while(1){
		int i = 0;	//Reset index so we start on player one's move
		for(int k = 0; k<9; k++){	//Set moves back to 0 so a new game may begin
			moves[k] = 0;
		}
		ResetBoardState();	//Reset all LEDs and Switches to their LOW state
		for(i; i<10; i++) {	//Loops 9 times and on the 9th time, if no winners, end in stalemate
			if(i == 9){
				Stalemate();	//Blinks between yellow and green meaning a stalemate
				wait_ticks(500000);
			}
			if(i%2 == 0){	//If index counter is even, we let the yellow player move
				PlayerTwoMove();
				CheckWinCondition();	//Check all possible win conditions (if found, will call either PlayerOneWin() or PlayerTwoWin())
				wait_ticks(500000);
			}
			if(i%2 == 1){	//If index counter is odd, we let the green player move
				PlayerOneMove();
				CheckWinCondition();
				wait_ticks(500000);
			}
		}
	}
}

void wait_ticks(ticks){	//Increment index a given amount of times in order to waste time.
	for(int i = 0; i < ticks; i++){
	}
}

void PlayerOneMove(){
	while(1){
		if(sw1==1){
			while(1){
				if(sw4==1){
					if(moves[0] != 0) PlayerOneMove();
					FIO0PIN |= (1<<25);	//Turn ON top left
					moves[0] = 1;
					return;
				}
				if(sw5==1){
					if(moves[3] != 0) PlayerOneMove();
					FIO0PIN |= (1<<18); //Turn ON Middle left
					moves[3] = 1;
					return;
				}
				if(sw6==1){
					if(moves[6] != 0) PlayerOneMove();
					FIO0PIN |= (1<<9); //Turn ON Bottom left
					moves[6] = 1;
					return;
				}
			}
		}
		else if(sw2==1){
			while(1){
				if(sw4==1){
					if(moves[1] != 0) PlayerOneMove();
					FIO1PIN |= (1<<30);	//Turn ON Top middle
					moves[1] = 1;
					return;
				}
				if(sw5==1){
					if(moves[4] != 0) PlayerOneMove();
					FIO0PIN |= (1<<15); //Turn ON Middle middle
					moves[4] = 1;
					return;
				}
				if(sw6==1){
					if(moves[7] != 0) PlayerOneMove();
					FIO0PIN |= (1<<7); //Turn ON Bottom middle
					moves[7] = 1;
					return;
				}
			}
		}
		else if(sw3==1){
			while(1){
				if(sw4==1){
					if(moves[2] != 0) PlayerOneMove();
					FIO0PIN |= (1<<2);	//Turn ON Top right
					moves[2] = 1;
					return;
				}
				if(sw5==1){
					if(moves[5] != 0) PlayerOneMove();
					FIO0PIN |= (1<<23); //Turn ON Middle right
					moves[5] = 1;
					return;
				}
				if(sw6==1){
					if(moves[8] != 0) PlayerOneMove();
					FIO0PIN |= (1<<0); //Turn ON Bottom right
					moves[8] = 1;
					return;
				}
			}
		}
	}
}

void PlayerTwoMove(){
	while(1){
		if(sw1==1){
			while(1){
				if(sw4==1){
					if(moves[0] != 0) PlayerTwoMove();
					FIO0PIN |= (1<<26);	//Turn ON Top left
					moves[0] = 2;
					return;
				}
				if(sw5==1){
					if(moves[3] != 0) PlayerTwoMove();
					FIO0PIN |= (1<<17); //Turn ON Middle left
					moves[3] = 2;
					return;
				}
				if(sw6==1){
					if(moves[6] != 0) PlayerTwoMove();
					FIO0PIN |= (1<<8); //Turn ON Bottom left
					moves[6] = 2;
					return;
				}
			}
		}
		else if(sw2==1){
			while(1){
				if(sw4==1){
					if(moves[1] != 0) PlayerTwoMove();
					FIO1PIN |= (1<<31);	//Turn ON Top middle
					moves[1] = 2;
					return;
				}
				if(sw5==1){
					if(moves[4] != 0) PlayerTwoMove();
					FIO0PIN |= (1<<16); //Turn ON Middle middle
					moves[4] = 2;
					return;
				}
				if(sw6==1){
					if(moves[7] != 0) PlayerTwoMove();
					FIO0PIN |= (1<<6); //Turn ON Bottom middle
					moves[7] = 2;
					return;
				}
			}
		}
		else if(sw3==1){
			while(1){
				if(sw4==1){
					if(moves[2] != 0) PlayerTwoMove();
					FIO0PIN |= (1<<3);	//Turn ON Top right
					moves[2] = 2;
					return;
				}
				if(sw5==1){
					if(moves[5] != 0) PlayerTwoMove();
					FIO0PIN |= (1<<24); //Turn ON Middle right
					moves[5] = 2;
					return;
				}
				if(sw6==1){
					if(moves[8] != 0) PlayerTwoMove();
					FIO0PIN |= (1<<1); //Turn ON Bottom right
					moves[8] = 2;
					return;
				}
			}
		}
	}
}

void CheckWinCondition(){
	//HORIZONTAL VICTORIES
	if(moves[0] == 1 && moves[1] == 1 && moves[2] == 1){
		PlayerOneWin();
	}
	else if(moves[0] == 2 && moves[1] == 2 && moves[2] == 2){
		PlayerTwoWin();
	}
	else if(moves[3] == 1 && moves[4] == 1 && moves[5] == 1){
		PlayerOneWin();
	}
	else if(moves[3] == 2 && moves[4] == 2 && moves[5] == 2){
		PlayerTwoWin();
	}
	else if(moves[6] == 1 && moves[7] == 1 && moves[8] == 1){
		PlayerOneWin();
	}
	else if(moves[6] == 2 && moves[7] == 2 && moves[8] == 2){
		PlayerTwoWin();
	}

	//VERTICAL VICTORIES
	else if(moves[0] == 1 && moves[3] == 1 && moves[6] == 1){
		PlayerOneWin();
	}
	else if(moves[0] == 2 && moves[3] == 2 && moves[6] == 2){
		PlayerTwoWin();
	}
	else if(moves[1] == 1 && moves[4] == 1 && moves[7] == 1){
		PlayerOneWin();
	}
	else if(moves[1] == 2 && moves[4] == 2 && moves[7] == 2){
		PlayerTwoWin();
	}
	else if(moves[2] == 1 && moves[5] == 1 && moves[8] == 1){
		PlayerOneWin();
	}
	else if(moves[2] == 2 && moves[5] == 2 && moves[8] == 2){
		PlayerTwoWin();
	}

	//DIAGONAL VICTORIES
	else if(moves[0] == 1 && moves[4] == 1 && moves[8] == 1){
		PlayerOneWin();
	}
	else if(moves[0] == 2 && moves[4] == 2 && moves[8] == 2){
		PlayerTwoWin();
	}
	else if(moves[2] == 1 && moves[4] == 1 && moves[6] == 1){
		PlayerOneWin();
	}
	else if(moves[2] == 2 && moves[4] == 2 && moves[6] == 2){
		PlayerTwoWin();
	}
}

void PlayerOneWin(){	//Will make all LEDs blink green to indicate a green win

	//Set all GREEN LEDs to low (off)
	FIO0PIN &= ~(1<<25);	//Top left
	FIO1PIN &= ~(1<<30);	//Top middle
	FIO0PIN &= ~(1<<2);		//Top right
	FIO0PIN &= ~(1<<18);	//Middle left
	FIO0PIN &= ~(1<<15);	//Middle middle
	FIO0PIN &= ~(1<<23);	//Middle right
	FIO0PIN &= ~(1<<9);		//Bottom left
	FIO0PIN &= ~(1<<7);		//Bottom middle
	FIO0PIN &= ~(1<<0);		//Bottom right

	//Set all YELLOW LEDs to low (off)
	FIO0PIN &= ~(1<<26);	//Top left
	FIO1PIN &= ~(1<<31);	//Top middle
	FIO0PIN &= ~(1<<3);		//Top right
	FIO0PIN &= ~(1<<17);	//Middle left
	FIO0PIN &= ~(1<<16);	//Middle middle
	FIO0PIN &= ~(1<<24);	//Middle right
	FIO0PIN &= ~(1<<8);		//Bottom left
	FIO0PIN &= ~(1<<6);		//Bottom middle
	FIO0PIN &= ~(1<<1);		//Bottom right

	for(int j = 0; j<5; j++){

		wait_ticks(250000);

		//Set all GREEN LEDs to high (on)
		FIO0PIN |= (1<<25);	//Top left
		FIO1PIN |= (1<<30);	//Top middle
		FIO0PIN |= (1<<2);	//Top right
		FIO0PIN |= (1<<18);	//Middle left
		FIO0PIN |= (1<<15);	//Middle middle
		FIO0PIN |= (1<<23);	//Middle right
		FIO0PIN |= (1<<9);	//Bottom left
		FIO0PIN |= (1<<7);	//Bottom middle
		FIO0PIN |= (1<<0);	//Bottom right

		wait_ticks(250000);

		//Set all GREEN LEDs to low (off)
		FIO0PIN &= ~(1<<25);	//Top left
		FIO1PIN &= ~(1<<30);	//Top middle
		FIO0PIN &= ~(1<<2);		//Top right
		FIO0PIN &= ~(1<<18);	//Middle left
		FIO0PIN &= ~(1<<15);	//Middle middle
		FIO0PIN &= ~(1<<23);	//Middle right
		FIO0PIN &= ~(1<<9);		//Bottom left
		FIO0PIN &= ~(1<<7);		//Bottom middle
		FIO0PIN &= ~(1<<0);		//Bottom right
	}
	main(); //Call beginning of main and start game over again
}

void PlayerTwoWin(){	//Will make all LEDs blink yellow to indicate a yellow win

	//Set all GREEN LEDs to low (off)
	FIO0PIN &= ~(1<<25);	//Top left
	FIO1PIN &= ~(1<<30);	//Top middle
	FIO0PIN &= ~(1<<2);		//Top right
	FIO0PIN &= ~(1<<18);	//Middle left
	FIO0PIN &= ~(1<<15);	//Middle middle
	FIO0PIN &= ~(1<<23);	//Middle right
	FIO0PIN &= ~(1<<9);		//Bottom left
	FIO0PIN &= ~(1<<7);		//Bottom middle
	FIO0PIN &= ~(1<<0);		//Bottom right

	//Set all YELLOW LEDs to low (off)
	FIO0PIN &= ~(1<<26);	//Top left
	FIO1PIN &= ~(1<<31);	//Top middle
	FIO0PIN &= ~(1<<3);		//Top right
	FIO0PIN &= ~(1<<17);	//Middle left
	FIO0PIN &= ~(1<<16);	//Middle middle
	FIO0PIN &= ~(1<<24);	//Middle right
	FIO0PIN &= ~(1<<8);		//Bottom left
	FIO0PIN &= ~(1<<6);		//Bottom middle
	FIO0PIN &= ~(1<<1);		//Bottom right

	for(int j = 0; j<5; j++){

		wait_ticks(250000);

		//Set all YELLOW LEDs to high (on)
		FIO0PIN |= (1<<26);	//Top left
		FIO1PIN |= (1<<31);	//Top middle
		FIO0PIN |= (1<<3);	//Top right
		FIO0PIN |= (1<<17);	//Middle left
		FIO0PIN |= (1<<16);	//Middle middle
		FIO0PIN |= (1<<24);	//Middle right
		FIO0PIN |= (1<<8);	//Bottom left
		FIO0PIN |= (1<<6);	//Bottom middle
		FIO0PIN |= (1<<1);	//Bottom right

		wait_ticks(250000);

		//Set all YELLOW LEDs to low (off)
		FIO0PIN &= ~(1<<26);	//Top left
		FIO1PIN &= ~(1<<31);	//Top middle
		FIO0PIN &= ~(1<<3);		//Top right
		FIO0PIN &= ~(1<<17);	//Middle left
		FIO0PIN &= ~(1<<16);	//Middle middle
		FIO0PIN &= ~(1<<24);	//Middle right
		FIO0PIN &= ~(1<<8);		//Bottom left
		FIO0PIN &= ~(1<<6);		//Bottom middle
		FIO0PIN &= ~(1<<1);		//Bottom right
	}
	main();
}

void Stalemate(){ ///Blinks between green and yellow to indicate a stalemate

	//Set all GREEN LEDs to low (off)
	FIO0PIN &= ~(1<<25);	//Top left
	FIO1PIN &= ~(1<<30);	//Top middle
	FIO0PIN &= ~(1<<2);		//Top right
	FIO0PIN &= ~(1<<18);	//Middle left
	FIO0PIN &= ~(1<<15);	//Middle middle
	FIO0PIN &= ~(1<<23);	//Middle right
	FIO0PIN &= ~(1<<9);		//Bottom left
	FIO0PIN &= ~(1<<7);		//Bottom middle
	FIO0PIN &= ~(1<<0);		//Bottom right

	//Set all YELLOW LEDs to low (off)
	FIO0PIN &= ~(1<<26);	//Top left
	FIO1PIN &= ~(1<<31);	//Top middle
	FIO0PIN &= ~(1<<3);		//Top right
	FIO0PIN &= ~(1<<17);	//Middle left
	FIO0PIN &= ~(1<<16);	//Middle middle
	FIO0PIN &= ~(1<<24);	//Middle right
	FIO0PIN &= ~(1<<8);		//Bottom left
	FIO0PIN &= ~(1<<6);		//Bottom middle
	FIO0PIN &= ~(1<<1);		//Bottom right

	for(int j = 0; j<5; j++){

			//Set all YELLOW LEDs to high (on)
			FIO0PIN |= (1<<26);	//Top left
			FIO1PIN |= (1<<31);	//Top middle
			FIO0PIN |= (1<<3);	//Top right
			FIO0PIN |= (1<<17);	//Middle left
			FIO0PIN |= (1<<16);	//Middle middle
			FIO0PIN |= (1<<24);	//Middle right
			FIO0PIN |= (1<<8);	//Bottom left
			FIO0PIN |= (1<<6);	//Bottom middle
			FIO0PIN |= (1<<1);	//Bottom right

			wait_ticks(250000);

			//Set all YELLOW LEDs to low (off)
			FIO0PIN &= ~(1<<26);	//Top left
			FIO1PIN &= ~(1<<31);	//Top middle
			FIO0PIN &= ~(1<<3);		//Top right
			FIO0PIN &= ~(1<<17);	//Middle left
			FIO0PIN &= ~(1<<16);	//Middle middle
			FIO0PIN &= ~(1<<24);	//Middle right
			FIO0PIN &= ~(1<<8);		//Bottom left
			FIO0PIN &= ~(1<<6);		//Bottom middle
			FIO0PIN &= ~(1<<1);		//Bottom right

			//Set all GREEN LEDs to high (on)
			FIO0PIN |= (1<<25);	//Top left
			FIO1PIN |= (1<<30);	//Top middle
			FIO0PIN |= (1<<2);	//Top right
			FIO0PIN |= (1<<18);	//Middle left
			FIO0PIN |= (1<<15);	//Middle middle
			FIO0PIN |= (1<<23);	//Middle right
			FIO0PIN |= (1<<9);	//Bottom left
			FIO0PIN |= (1<<7);	//Bottom middle
			FIO0PIN |= (1<<0);	//Bottom right

			wait_ticks(250000);

			//Set all GREEN LEDs to low (off)
			FIO0PIN &= ~(1<<25);	//Top left
			FIO1PIN &= ~(1<<30);	//Top middle
			FIO0PIN &= ~(1<<2);		//Top right
			FIO0PIN &= ~(1<<18);	//Middle left
			FIO0PIN &= ~(1<<15);	//Middle middle
			FIO0PIN &= ~(1<<23);	//Middle right
			FIO0PIN &= ~(1<<9);		//Bottom left
			FIO0PIN &= ~(1<<7);		//Bottom middle
			FIO0PIN &= ~(1<<0);		//Bottom right
	}
	main();
}

void ResetBoardState(){	//Set all pins to their initial values and thus reset the game
	//Set all GREEN LEDs as outputs
		FIO0DIR |= (1<<25);	//Top left
		FIO1DIR |= (1<<30);	//Top middle
		FIO0DIR |= (1<<2);	//Top right
		FIO0DIR |= (1<<18);	//Middle left
		FIO0DIR |= (1<<15);	//Middle middle
		FIO0DIR |= (1<<23);	//Middle right
		FIO0DIR |= (1<<9);	//Bottom left
		FIO0DIR |= (1<<7);	//Bottom middle
		FIO0DIR |= (1<<0);	//Bottom right

		//Set all YELLOW LEDs as outputs
		FIO0DIR |= (1<<26);	//Top left
		FIO1DIR |= (1<<31);	//Top middle
		FIO0DIR |= (1<<3);	//Top right
		FIO0DIR |= (1<<17);	//Middle left
		FIO0DIR |= (1<<16);	//Middle middle
		FIO0DIR |= (1<<24);	//Middle right
		FIO0DIR |= (1<<8);	//Bottom left
		FIO0DIR |= (1<<6);	//Bottom middle
		FIO0DIR |= (1<<1);	//Bottom right

		//Set all GREEN LEDs to low (off)
		FIO0PIN &= ~(1<<25);	//Top left
		FIO1PIN &= ~(1<<30);	//Top middle
		FIO0PIN &= ~(1<<2);		//Top right
		FIO0PIN &= ~(1<<18);	//Middle left
		FIO0PIN &= ~(1<<15);	//Middle middle
		FIO0PIN &= ~(1<<23);	//Middle right
		FIO0PIN &= ~(1<<9);		//Bottom left
		FIO0PIN &= ~(1<<7);		//Bottom middle
		FIO0PIN &= ~(1<<0);		//Bottom right

		//Set all YELLOW LEDs to low (off)
		FIO0PIN &= ~(1<<26);	//Top left
		FIO1PIN &= ~(1<<31);	//Top middle
		FIO0PIN &= ~(1<<3);		//Top right
		FIO0PIN &= ~(1<<17);	//Middle left
		FIO0PIN &= ~(1<<16);	//Middle middle
		FIO0PIN &= ~(1<<24);	//Middle right
		FIO0PIN &= ~(1<<8);		//Bottom left
		FIO0PIN &= ~(1<<6);		//Bottom middle
		FIO0PIN &= ~(1<<1);		//Bottom right

		//Set all buttons to be pull down (11)
		PINMODE4 |= (1<<7) | (1<<6);	//Top left (sw1)
		PINMODE4 |= (1<<9) | (1<<8);	//Top middle (sw2)
		PINMODE4 |= (1<<11) | (1<<10);	//Top right (sw3)
		PINMODE4 |= (1<<13) | (1<<12);	//Right top (sw4)
		PINMODE4 |= (1<<15) | (1<<14);	//Right middle (sw5)
		PINMODE4 |= (1<<17) | (1<<16);	//Right middle (sw6)

		//Set all button ports to read low
		FIO2DIR &= ~(1<<3); //Set sw1 port to read low
		FIO2DIR &= ~(1<<4);	//Set sw2 port to read low
		FIO2DIR &= ~(1<<5);	//Set sw3 port to read low
		FIO2DIR &= ~(1<<6);	//Set sw4 port to read low
		FIO2DIR &= ~(1<<7);	//Set sw5 port to read low
		FIO2DIR &= ~(1<<8);	//Set sw6 port to read low
}
