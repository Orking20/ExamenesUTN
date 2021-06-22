/*
 * parser.c
 *
 *  Created on: 17 jun. 2021
 *      Author: mateo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"
#include "../inc/Articulos.h"
#include "../inc/Arancel.h"
#include "../inc/Barco.h"
#include "../inc/Avion.h"

/** \brief Parsea los datos de los articulos desde el archivo Articulos.csv
 *
 * \param pFile FILE* Archivo
 * \param pListaArticulo LinkedList* Puntero a la lista
 * \return int Retorna 0 (EXITO) o -1 (ERROR)
 *
 */
int parser_articulo(FILE* pFile, LinkedList* pListaArticulo)
{
	int retorno = -1;
	char bufferId[64];
	char bufferCodigo[TAM_CODIGO];
	char bufferDescripcion[TAM_DESCRIPCION];
	char bufferPaisFabricacion[TAM_PAIS_FABRICACION];
	char bufferFob[64];
	char bufferPesoKg[64];
	char bufferAltoCm[64];
	char bufferAnchoCm[64];
	char bufferProfundoCm[64];
	char bufferNomenclatura[64];
	char bufferIdPosicionArancelaria[64];
	Articulo* auxiliarArticulo = NULL;

	if(pFile != NULL && pListaArticulo != NULL)
	{
		do
		{
			if(fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
			   bufferId, bufferCodigo, bufferDescripcion, bufferPaisFabricacion, bufferFob, bufferPesoKg, bufferAltoCm, bufferAnchoCm, bufferProfundoCm, bufferIdPosicionArancelaria, bufferNomenclatura) == 11)
			{
				auxiliarArticulo = articulo_newParametros(bufferId, bufferCodigo, bufferDescripcion, bufferPaisFabricacion, bufferFob, bufferPesoKg, bufferAltoCm, bufferAnchoCm, bufferProfundoCm, bufferIdPosicionArancelaria, bufferNomenclatura);
				if(auxiliarArticulo != NULL)
				{
					if(!ll_add(pListaArticulo, auxiliarArticulo))
					{//TODO
						retorno = 0;
					}
				}
			}
		}while(!feof(pFile));
	}

	return retorno;
}

/** \brief Parsea los datos de las posiciones aranceladas desde el archivo PosicionesAranceladas.csv
 *
 * \param pFile FILE* Archivo
 * \param pListaArticulo LinkedList* Puntero a la lista
 * \return int Retorna 0 (EXITO) o -1 (ERROR)
 *
 */
int parser_arancel(FILE* pFile, LinkedList* pListaArancel)
{
	int retorno = -1;
	char bufferId[64];
	char bufferNomenclatura[TAM_NOMENCLATURA];
	char bufferPorcentajeSeguro[64];
	char bufferPorcentajeImportacion[64];
	char bufferPorcentajeTasaEstadistica[64];
	char bufferTipoLicencia[TAM_TIPO_LICENCIA];
	Arancel* auxiliarArancel = NULL;

	if(pFile != NULL && pListaArancel != NULL)
	{
		do
		{
			if(fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", bufferId, bufferNomenclatura, bufferPorcentajeSeguro, bufferPorcentajeImportacion, bufferPorcentajeTasaEstadistica, bufferTipoLicencia) == 6)
			{
				auxiliarArancel = arancel_newParametros(bufferId, bufferNomenclatura, bufferPorcentajeSeguro, bufferPorcentajeImportacion, bufferPorcentajeTasaEstadistica, bufferTipoLicencia);
				if(auxiliarArancel != NULL)
				{
					if(!ll_add(pListaArancel, auxiliarArancel))
					{//TODO
						retorno = 0;
					}
				}
			}
		}while(!feof(pFile));
	}

	return retorno;
}

/** \brief Parsea los datos del transporte marítimo desde el archivo Barco.bin
 *
 * \param pFile FILE* Archivo
 * \param pBarco Barco* Estructura donde se cargarán los datos
 * \return int Retorna 0 (EXITO) o -1 (ERROR)
 *
 */
int parser_barco(FILE* pFile, Barco* pBarco)
{
	int retorno = -1;

	if(pFile != NULL && pBarco != NULL)
	{
		if(fread(pBarco,sizeof(Barco), 1, pFile) == 1)
		{
			retorno = 0;
		}
	}

	return retorno;
}

/** \brief Parsea los datos del transporte aéreo desde el archivo Avion.bin
 *
 * \param pFile FILE* Archivo
 * \param pAvion Avion* Estructura donde se cargarán los datos
 * \return int Retorna 0 (EXITO) o -1 (ERROR)
 *
 */
int parser_avion(FILE* pFile, Avion* pAvion)
{
	int retorno = -1;

	if(pFile != NULL && pAvion != NULL)
	{
		if(fread(pAvion,sizeof(Barco), 1, pFile) == 1)
		{
			retorno = 0;
		}
	}

	return retorno;
}
