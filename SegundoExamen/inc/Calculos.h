/*
 * Calculos.h
 *
 *  Created on: 19 jun. 2021
 *      Author: mateo
 */

#ifndef CALCULOS_H_
#define CALCULOS_H_

float calculo_pasajeCentimetroMetro(float numeroEnCentimetros);
float calculo_precioMaritimo(Barco barco, float altoMetros, float anchoMetros, float profundoMetros);
float calculo_pesoReal(LinkedList* pListaArticulos, Avion avion, int indice);
float calculo_pesoVolumetrico(LinkedList* pListaArticulos, Avion avion, int indice);
float calculo_precioAereo(LinkedList* pListaArticulos, Avion avion, int indice);
float calculo_valorSeguro(LinkedList* pListaArticulos, LinkedList* pListaAranceles, int indice);
float calculo_baseImponibleMaritima(LinkedList* pListaArticulos, LinkedList* pListaAranceles, Barco barco, int indice);
float calculo_baseImponibleAerea(LinkedList* pListaArticulos, LinkedList* pListaAranceles, Avion avion, int indice);
float calculo_valorImportacionMaritima(LinkedList* pListaArticulos, LinkedList* pListaAranceles, Barco barco, int indice);
float calculo_valorImportacionAerea(LinkedList* pListaArticulos, LinkedList* pListaAranceles, Avion avion, int indice);
float calculo_valorTasaEstadisticaMaritima(LinkedList* pListaArticulos, LinkedList* pListaAranceles, Barco barco, int indice);
float calculo_valorTasaEstadisticaAerea(LinkedList* pListaArticulos, LinkedList* pListaAranceles, Avion avion, int indice);
float calculo_costoArgentinoMaritimo(LinkedList* pListaArticulos, LinkedList* pListaAranceles, Barco barco, int indice);
float calculo_costoArgentinoAereo(LinkedList* pListaArticulos, LinkedList* pListaAranceles, Avion avion, int indice);

#endif /* CALCULOS_H_ */
