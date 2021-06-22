/*
 * Informes.c
 *
 *  Created on: 19 jun. 2021
 *      Author: mateo
 */

#include <stdio.h>
#include <stdlib.h>
#include "../inc/Articulos.h"
#include "../inc/Arancel.h"
#include "../inc/Barco.h"
#include "../inc/Avion.h"
#include "../inc/LinkedList.h"
#include "../inc/Controller.h"
#include "../inc/Calculos.h"
#include "../inc/Informes.h"

static int buscarElemento(LinkedList* pLista);

/** brief Muestra todos los artículos con su valor argentino marítimo y aéreo

 * \param pListaArticulos LinkedList* Puntero a la lista
 * \param pListaAranceles LinkedList* Puntero a la lista
 * \param barco Barco*  Estructura que contiene los valores del barco
 * \param avion Avion*  Estructura que contiene los valores del avion
 * \return int Retora 1 si hay por lo menos un elemento, 0 si no hay ninguno o -1 si hay un error
 *
 */
int informe_listarCostoArgentino(LinkedList* pListaArticulos, LinkedList* pListaAranceles, Barco barco, Avion avion)
{
	int retorno = -1;
	int limite = ll_len(pListaArticulos);
	int flagError;
	//int indice;
	Articulo* pArticulo = NULL;
	//Arancel* pArancel = NULL;

	if(pListaArticulos != NULL)
	{
		if(buscarElemento(pListaArticulos) == 1)
		{
			printf("\nDescripción\t\t\t\t\t\tValor argentino marítimo\tValor argentino aéreo\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			for(int i = 0; i < limite; i++)
			{
				pArticulo = (Articulo*)ll_get(pListaArticulos, i);
				//indice = buscarIdArancel(pListaAranceles, articulo_getIdPosicionArancelaria(pArticulo, &flagError)); // Por si es necesario listar la nomenclatura
				//pArancel = (Arancel*)ll_get(pListaAranceles, indice);
				printf("\n%-53s | %-29.2f | %-12.2f", articulo_getDescripcion(pArticulo, &flagError),
						calculo_costoArgentinoMaritimo(pListaArticulos, pListaAranceles, barco, i), calculo_costoArgentinoAereo(pListaArticulos, pListaAranceles, avion, i));
			}

			retorno = 0;
		}
		else
		{
			printf("\nNo hay artículos para mostrar. Cargalos en la opción 1 del menú de artículos\n");
		}
	}

	return retorno;
}



/** brief Busca si hay elementos cargados en una lista

 * \param pLista LinkedList* Puntero a la lista
 * \return int Retora 1 si hay por lo menos un elemento, 0 si no hay ninguno o -1 si hay un error
 *
 */
static int buscarElemento(LinkedList* pLista)
{
	int retorno = -1;

	if(pLista != NULL)
	{
		retorno = 0;
		for(int i = 0; i < ll_len(pLista); i++)
		{
			retorno = 1;
			break;
		}
	}

	return retorno;
}
