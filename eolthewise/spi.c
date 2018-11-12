/*
 * spi.c
 *
 *  Created on: 12 nov. 2018
 *      Author: theo-
 */
#include <msp430.h>
#include "fonctions.h"
#include "spi.h"
/*pins spi
 *
 *p1.0(led1)    (a0)    ->cs
 *p1.1(uart)  (a1)    ->mosi
 *p1.2(uart)  (a2)    ->miso
 *p1.4      (a4)    ->clk
 */

mesures data_mesures;

void ini_spi(void){
    while (!(P1IN & BIT4));                   // If clock sig from mstr stays low,
                                                // it is not yet in SPI mode

      P1SEL = BIT1 + BIT2 + BIT4;
      P1SEL2 = BIT1 + BIT2 + BIT4;
      UCA0CTL1 = UCSWRST;                       // **Put state machine in reset**
      UCA0CTL0 |= UCCKPL + UCMSB + UCSYNC;      // 3-pin, 8-bit SPI master
      UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
      IE2 |= UCA0RXIE;                          // Enable USCI0 RX interrupt

      __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4, enable interrupts
}






#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR (void)
{
  while (!(IFG2 & UCA0TXIFG));              // USCI_A0 TX buffer ready?
  //UCA0TXBUF = UCA0RXBUF;

  char c = ' ';
  c = UCA0RXBUF;
  if(c == 'a'){
      update_valeurs(&data_mesures);
  }

}
