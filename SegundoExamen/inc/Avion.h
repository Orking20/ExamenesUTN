/*
 * Avion.h
 *
 *  Created on: 16 jun. 2021
 *      Author: mateo
 */

#ifndef AVION_H_
#define AVION_H_

typedef struct
{
	float constanteVolumetrica;
	float precioPorKg;
}Avion;

//----------------Setters----------------

int avion_setConstanteVolumetrica(Avion* pAvion, float constanteVolumetrica);
int avion_setPrecioPorKg(Avion* pAvion, float precioPorKg);

//----------------Getters----------------

float avion_getConstanteVolumetrica(Avion avion, int* flagError);
float avion_getPrecioPorKg(Avion avion, int* flagError);

#endif /* AVION_H_ */
