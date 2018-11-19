/**
 * main.c
 */

#include <msp430.h> 

#include "spi.h"
#include "fonctions.h"

/*pins capteurs
 *p1.3     (a3)    ->girouette
 *p1.5        (a5)    ->temperature
 *p1.6(led2)  (a6)    ->humidité
 *p1.7        (a7)    ->lum
 */


/*pins spi
 *
 *p1.0(led1)    (a0)    ->cs
 *p1.1(uart)  (a1)    ->mosi
 *p1.2(uart)  (a2)    ->miso
 *p1.4      (a4)    ->clk
 */

mesures data_mesures;


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	if(CALBC1_1MHZ==0xFF || CALDCO_1MHZ==0xFF)
	    {
	        __bis_SR_register(LPM4_bits); // Low Power Mode #trap on Error
	    }
	    else
	    {
	       // Factory parameters
	       DCOCTL = 0;
	       BCSCTL1 = CALBC1_1MHZ;
	       DCOCTL = (0 | CALDCO_1MHZ);
	    }




	//P1DIR |= 0x01; // met ligne P1.0 en sortie
	//P1DIR &= ~(0x08); // met ligne P1.3 en entrée

	P1DIR &= ~(BIT3|BIT5|BIT6|BIT7);//capteurs



	//P2DIR bits spi

	ADC_init();
	ini_fonctions(&data_mesures);
	ini_spi();

	/*
	 * probleme port spi
	 * traitement dans le msp ? ou envoi des valeurs brute au raspi ?
	 * pas sur que le msp ai le tps de renvoyer toutes les valeurs lorsque il en reçoi la demande
	 * ajouter des led sur le port2
	 */



	while(1){
	    //attendre la requette
	    update_valeurs(&data_mesures);
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
