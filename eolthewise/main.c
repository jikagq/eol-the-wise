/**
 * main.c
 */

#include <msp430.h> 

#include "spi.h"
#include "fonctions.h"

/*pins capteurs
 *p1.4     (a4)    ->girouette
 *p1.5        (a5)    ->temperature
 *p1.6(led2)  (a6)    ->humidité
 *p1.7        (a7)    ->lum
 */


/*pins spi
 *
 *
 *
 *
 *
 */

mesures data_mesures;


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//P1DIR |= 0x01; // met ligne P1.0 en sortie
	//P1DIR &= ~(0x08); // met ligne P1.3 en entrée

	P1DIR &= ~(BIT4|BIT5|BIT6|BIT7);//capteurs

	P1DIR |= BIT0;//led1

	//P2DIR bits spi

	ADC_init();
	ini_spi();
	ini_fonctions(&data_mesures);


	/*
	 * probleme port spi
	 * traitement dans le msp ? ou envoi des valeurs brute au raspi ?
	 *
	 *
	 */



	while(1){

	    //attendre la requette





	}


	return 0;
}

/**delai du pauvre*/
void delay (unsigned int ms)
{
    volatile unsigned int i, z;
    i=100;
    while (i--) {
        z=ms;
        while(z--);
    }
}
