/*
 * Controller.h
 *
 *  Created on: 17 jun. 2021
 *      Author: mateo
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include "../inc/Barco.h"
#include "../inc/Avion.h"

//----------------Articulo----------------
int controller_cargarArticulos(LinkedList* pListaArticulos);
int controller_altaArticulo(LinkedList* pListaArticulos, LinkedList* pListaAranceles);
int controller_modificarArticulo(LinkedList* pListaArticulos, LinkedList* pListaAranceles);
int controller_bajaArticulo(LinkedList* pListaArticulos, LinkedList* pListaAranceles);
int controller_listarArticulo(LinkedList* pListaArticulos, LinkedList* pListaAranceles);
int controller_listarArticuloConId(LinkedList* pListaArticulos, LinkedList* pListaAranceles);
int controller_listarArticulosFobAltos(LinkedList* pListaArticulos);
int controller_ordenarArticulos(LinkedList* pListaArticulos, LinkedList* pListaAranceles);
int controller_guardarArticulos(LinkedList* pListaArticulos, LinkedList* pListaAranceles);

//----------------Arancel----------------
int controller_cargarArancel(LinkedList* pListaAranceles);
int controller_altaArancel(LinkedList* pListaArancel);
int controller_modificarArancel(LinkedList* pListaArancel);
int controller_bajaArancel(LinkedList* pListaArancel, LinkedList* pListaArticulo);
int controller_listarArancel(LinkedList* pListaAranceles);
int controller_listarArancelConId(LinkedList* pListaAranceles);
int controller_ordenarAranceles(LinkedList* pListaAranceles);
int controller_guardarArancel(LinkedList* pListaAranceles);

//----------------Barco----------------

int controller_cargarBarco(Barco* pBarco);
int controller_altaBarco(Barco* pBarco);
int controller_modificarBarco(Barco* pBarco);
int controller_listarBarco(Barco barco);
int controller_guardarBarco(Barco* pBarco);

//----------------Avion----------------

int controller_cargarAvion(Avion* pAvion);
int controller_altaAvion(Avion* pAvion);
int controller_modificarAvion(Avion* pAvion);
int controller_listarAvion(Avion avion);
int controller_guardarAvion(Avion* pAvion);

//----------------ID----------------

void setearValorMaximoId(int id);
int generarId(void);
int buscarIdArancel(LinkedList* pListaAranceles, int articuloIdPosicionArancelaria);
int buscarIdPosArancelaria(LinkedList* pListaArticulos, int idArancel);

//----------------Filtrar----------------

LinkedList* filtrar(LinkedList* listaOriginal, int (*funcionCriterio)(void*));
int listarArticulosCaros(LinkedList* listaFiltrada);
int funcionCriterioFiltrarFob(void* pElemento);

#endif /* CONTROLLER_H_ */
