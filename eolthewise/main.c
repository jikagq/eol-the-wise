/**
 * main.c
 */

#include <msp430.h> 

//#include "spi.h"
#include "fonctions.h"
#include "uart.h"

/*pins capteurs
 *p1.3     (a3)    ->girouette
 *p1.5        (a5)    ->temperature
 *p1.6(led2)  (a6)    ->humidité
 *p1.7        (a7)    ->lum
 */


/*pins spi
 *
 *p1.0(led1)    (a0)    ->cs
 *p1.1(uart)  (a1)    ->miso
 *p1.2(uart)  (a2)    ->mosi
 *p1.4      (a4)    ->clk
 */

mesures data_mesures;
int statut_pwm; //0= pas de pwm 1=pwm en sortie
int pwm; //valeur de la pwm

int testmode=0;


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR &= ~(BIT3|BIT5|BIT6|BIT7);//capteurs
	ADC_init();
	ini_fonctions(&data_mesures);
	//ini_spi();
	InitUART();// utilisation de l'uart via usb pour transmission
	__bis_SR_register(GIE); // interrupts enabled

	while(1){
	    if(flag_trame_uart_recu == 1){//check si une trame valide a été reçu
	        interpreteur_uart();
	        reset_uart();//une fois traitement fini reset
	    }else{
	        //reset_uart();
	        ;
	    }
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

