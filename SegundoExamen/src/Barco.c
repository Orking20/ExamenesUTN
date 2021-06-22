/*
 * Barco.c
 *
 *  Created on: 16 jun. 2021
 *      Author: mateo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/utn.h"
#include "../inc/Barco.h"

static int isValidMetrosCubicos(float metrosCubicos);
static int isValidPrecio(float precio);

//----------------Setters----------------

/** \brief Comprueba que los metros cubicos sean válidos y los asigna a la estructura
 *
 * \param barco Barco* Donde se guardará el dato obtenido
 * \param metrosCubicos float Dato que se evaluará y guardará en la estructura
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int barco_setMetrosCubicos(Barco* barco, float metrosCubicos)
{
	int retorno = -1;

	if(isValidMetrosCubicos(metrosCubicos) == 1)
	{
		barco->metrosCubicos = metrosCubicos;
		retorno = 0;
	}

	return retorno;
}

/** \brief Comprueba que el precio sea válido y lo asigna a la estructura
 *
 * \param barco Barco* Donde se guardará el dato obtenido
 * \param precio float Dato que se evaluará y guardará en la estructura
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int barco_setPrecio(Barco* barco, float precio)
{
	int retorno = -1;

	if(isValidPrecio(precio) == 1)
	{
		barco->precio = precio;
		retorno = 0;
	}

	return retorno;
}

//----------------Getters----------------

/** \brief Obtiene el valor de metrosCubicos
 *
 * \param barco Barco Dato que queremos obtener
 * \param flagError int* Nos avisa si hay algún error
 * \return float Retora el valor dentro de metrosCubicos o NULL
 *
 */
float barco_getMetrosCubicos(Barco barco, int* flagError)
{
	*flagError = -1;
	float auxMetrosCubicos = -1;

	if(flagError != NULL)
	{
		auxMetrosCubicos = barco.metrosCubicos;

		*flagError = 0;
	}

	return auxMetrosCubicos;
}

/** \brief Obtiene el valor de precio
 *
 * \param barco Barco Dato que queremos obtener
 * \param flagError int* Nos avisa si hay algún error
 * \return float Retora el valor dentro de precio o NULL
 *
 */
float barco_getPrecio(Barco barco, int* flagError)
{
	*flagError = -1;
	float auxPrecio = -1;

	if(flagError != NULL)
	{
		auxPrecio = barco.precio;
		*flagError = 0;
	}

	return auxPrecio;
}

//----------------Validaciones----------------

/** \brief Comprueba que los metros cubicos sean válidos
 *
 * \param metrosCubicos float El dato a comprobar que sea válido
 * \return Retora 1 si es válido, 0 si no es válido o -1 (ERROR)
 *
 */
static int isValidMetrosCubicos(float metrosCubicos)
{
	int retorno = -1;

	if(metrosCubicos > 0)
	{
		retorno = 1;
	}

	return retorno;
}

/** \brief Comprueba que el precio sea válido
 *
 * \param precio float El dato a comprobar que sea válido
 * \return Retora 1 si es válido, 0 si no es válido o -1 (ERROR)
 *
 */
static int isValidPrecio(float precio)
{
	int retorno = -1;

	if(precio > 0)
	{
		retorno = 1;
	}

	return retorno;
}
