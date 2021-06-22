/*
 * menu.h
 *
 *  Created on: 16 jun. 2021
 *      Author: mateo
 */

#ifndef MENU_H_
#define MENU_H_

#include "../inc/Barco.h"
#include "../inc/Avion.h"

void opcionArticulos(LinkedList* pListaArticulos, LinkedList* pListaAranceles);
void opcionPosicionArancelaria(LinkedList* pListaArancel, LinkedList* pListaArticulo);
void opcionTransporteMaritimo(Barco barco);
void opcionTransporteAereo(Avion avion);
void opcionInformes(LinkedList* pListaArticulos, LinkedList* pListaAranceles, Barco barco, Avion avion);

#endif /* MENU_H_ */
