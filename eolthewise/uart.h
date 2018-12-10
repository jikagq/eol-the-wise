/*
 * uart.h
 *
 *  Created on: 3 mars 2018
 *      Author: theo-
 */

#include <msp430g2553.h>
#include <msp430.h>

#ifndef UART_H_
#define UART_H_



extern volatile char Trame_uart_rx[8];
extern volatile char Trame_uart_tx[8];
extern volatile int unsigned index_uart_rx_buffer;
extern volatile int flag_trame_uart_recu;

void InitUART(void);
void TXdata( unsigned char c );
void pong(void);
void ack(void);
void nak(void);
void itoad(long unsigned int value, char *result, int base);
void reset_uart(void);
void interpreteur_uart(void);

#endif /* UART_H_ */
