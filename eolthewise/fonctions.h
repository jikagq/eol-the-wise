/*
 * fonctions.h
 *
 *  Created on: 12 nov. 2018
 *      Author: theo-
 */

#ifndef FONCTIONS_H_
#define FONCTIONS_H_



typedef struct
{
    int angle;
    int temp;
    int humi;
    int lum;
} mesures;

extern mesures data_mesures;//variable position de type pos
extern int statut_pwm;
extern int pwm;

void ini_fonctions(mesures *p);
void update_valeurs(mesures *p);

int get_girouette(void);
int get_temperature(void);
int get_humidite(void);
int get_luminosite(void);

int get_angle(mesures *p);
int get_humi(mesures *p);
int get_lum(mesures *p);
int get_temp(mesures *p);

void simupwm(int actif, int angle);

#endif /* FONCTIONS_H_ */
