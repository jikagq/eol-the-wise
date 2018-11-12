/**
 * main.c
 */

#include <msp430.h> 

#include "ADC.h"
#include "spi.h"
#include "fonctions.h"

/*pins capteurs
 *p1.4     (a4)    ->girouette
 *p1.5        (a5)    ->temperature
 *p1.6(led2)  (a6)    ->humidité
 *p1.7        (a7)    ->lum
 */
#define pin_girouette 4
#define pin_temp 5
#define pin_humi 6
#define pin_lum 7

/*pins spi
 *
 *
 *
 *
 *
 */

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	

	ADC_init();
	ini_spi();
	ini_fonctions();






	while(1){

	    //attendre la requette





	}


	return 0;
}
