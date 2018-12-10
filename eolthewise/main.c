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

	/*if(CALBC1_1MHZ==0xFF || CALDCO_1MHZ==0xFF)
	    {
	        __bis_SR_register(LPM4_bits); // Low Power Mode #trap on Error
	    }
	    else
	    {
	       // Factory parameters
	       DCOCTL = 0;
	       BCSCTL1 = CALBC1_1MHZ;
	       DCOCTL = (0 | CALDCO_1MHZ);
	    }*/


	P1DIR &= ~(BIT3|BIT5|BIT6|BIT7);//capteurs
	ADC_init();
	ini_fonctions(&data_mesures);
	//ini_spi();
	InitUART();// for tests
	__bis_SR_register(GIE); // interrupts enabled

	statut_pwm= 1;
	pwm = 1500;



	while(1){


	    if(flag_trame_uart_recu == 1){
	        interpreteur_uart();
	        reset_uart();//une fois traitement fini reset
	    }else{
	        //reset_uart();
	        ;
	    }





















	    /*if(testmode ==0){
	        //update_valeurs(&data_mesures);
	        //simupwm(statut_pwm, pwm);//pin p2.4
           TXdata('a');
           TXdata(784+'0');
	    }*/

	    //delay(1000);
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



//test =  get_angle(&data_mesures);
//test = get_humi(&data_mesures);
//test = get_lum(&data_mesures);
//test =  get_temp(&data_mesures);

/*TXdata('a');
TXdata((char)get_angle(&data_mesures));
TXdata('\n');
TXdata('h');
TXdata((char)get_humi(&data_mesures));
TXdata('\n');
TXdata('l');
TXdata((char)get_lum(&data_mesures));
TXdata('\n');
TXdata('t');
TXdata((char)get_temp(&data_mesures));
TXdata('\n');*/
