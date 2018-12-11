/*
 * fonctions.c
 *
 *  Created on: 12 nov. 2018
 *      Author: theo-
 */
#include <msp430.h>
#include "fonctions.h"
#include "ADC.h"


#define pin_girouette 3
#define pin_temp 5
#define pin_humi 6
#define pin_lum 7

mesures data_mesures; //variables des capteurs
int statut_pwm; //0= pas de pwm 1=pwm en sortie
int pwm; //valeur de la pwm
int testvar = 123;

/*initialise la structure*/
void ini_fonctions(mesures *p){
    p->angle = 1234;
    p->humi = 600;
    p->lum = 10;
    p->temp = 64;


    statut_pwm = 0;
    pwm = 0;

    /*ini pwm*/

    P2DIR |= BIT4;
    P2SEL |= BIT4;
    P2SEL2 &= ~BIT4;
    TA1CTL=TASSEL_2 | MC_1;

    TA1CCTL2|= OUTMOD_7;

    TA1CCR0 = 20000;
    TA1CCR2 = 0;

}

/*met à jour la structure*/
void update_valeurs(mesures *p){
    p->angle = get_girouette();
    p-> temp = get_temperature();
    p->humi = get_humidite();
    p-> lum = get_luminosite();
}

/*lit l'adc*/
int get_girouette(void){
    ADC_Demarrer_conversion(pin_girouette);
    return ADC_Lire_resultat();
}
int get_temperature(void){
    ADC_Demarrer_conversion(pin_temp);
    return ADC_Lire_resultat();
}
int get_humidite(void){
    ADC_Demarrer_conversion(pin_humi);
    return ADC_Lire_resultat();
}
int get_luminosite(void){
    ADC_Demarrer_conversion(pin_lum);
    return ADC_Lire_resultat();
}





/*accede aux valeurs de la structures*/
int get_angle(mesures *p){
    return p->angle;
}
int get_humi(mesures *p){
    return p->humi ;
}
int get_lum(mesures *p){
    return p->lum ;
}
int get_temp(mesures *p){
    return p->temp ;
}




void simupwm(int actif, int pwm){
    if(actif == 0){
        TA1CCR2 = 0;
    }else{
        TA1CCR2 = pwm;
    }
}
