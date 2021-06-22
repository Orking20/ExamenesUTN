/*
 * Barco.h
 *
 *  Created on: 16 jun. 2021
 *      Author: mateo
 */

#ifndef BARCO_H_
#define BARCO_H_

typedef struct
{
	float metrosCubicos;
	float precio;
}Barco;

//----------------Setters----------------

int barco_setMetrosCubicos(Barco* barco, float metrosCubicos);
int barco_setPrecio(Barco* barco, float precio);

//----------------Getters----------------

float barco_getMetrosCubicos(Barco barco, int* flagError);
float barco_getPrecio(Barco barco, int* flagError);

#endif /* BARCO_H_ */
