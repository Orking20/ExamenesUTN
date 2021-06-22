/*
 * Avion.c
 *
 *  Created on: 16 jun. 2021
 *      Author: mateo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/utn.h"
#include "../inc/Avion.h"

static int isValidConstanteVolumetrica(float constanteVolumetrica);
static int isValidPrecioPorKg(float precioPorKg);

//----------------Setters----------------

/** \brief Comprueba que la constante volumetrica sea válida y la asigna a la estructura
 *
 * \param pAvion Avion* Donde se guardará el dato obtenido
 * \param constanteVolumetrica float Dato que se evaluará y guardará en la estructura
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int avion_setConstanteVolumetrica(Avion* pAvion, float constanteVolumetrica)
{
	int retorno = -1;

	if(pAvion != NULL && isValidConstanteVolumetrica(constanteVolumetrica) == 1)
	{
		pAvion->constanteVolumetrica = constanteVolumetrica;
		retorno = 0;
	}

	return retorno;
}

/** \brief Comprueba que el precio por Kg sea válido y lo asigna a la estructura
 *
 * \param pAvion Avion* Donde se guardará el dato obtenido
 * \param precioPorKg float Dato que se evaluará y guardará en la estructura
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int avion_setPrecioPorKg(Avion* pAvion, float precioPorKg)
{
	int retorno = -1;

	if(pAvion != NULL && isValidPrecioPorKg(precioPorKg) == 1)
	{
		pAvion->precioPorKg = precioPorKg;
		retorno = 0;
	}

	return retorno;
}

//----------------Getters----------------

/** \brief Obtiene el valor de constanteVolumetrica
 *
 * \param avion Avion Dato que queremos obtener
 * \param flagError int* Nos avisa si hay algún error
 * \return float Retora el valor dentro de constanteVolumetrica o NULL
 *
 */
float avion_getConstanteVolumetrica(Avion avion, int* flagError)
{
	*flagError = -1;
	float auxConstanteVolumetrica = -1;

	if(flagError != NULL)
	{
		auxConstanteVolumetrica = avion.constanteVolumetrica;
		*flagError = 0;
	}

	return auxConstanteVolumetrica;
}

/** \brief Obtiene el valor de precioPorKg
 *
 * \param avion Avion Dato que queremos obtener
 * \param flagError int* Nos avisa si hay algún error
 * \return float Retora el valor dentro de precioPorKg o NULL
 *
 */
float avion_getPrecioPorKg(Avion avion, int* flagError)
{
	*flagError = -1;
	float auxPrecioPorKg = -1;

	if(flagError != NULL)
	{
		auxPrecioPorKg = avion.precioPorKg;
		*flagError = 0;
	}

	return auxPrecioPorKg;
}

//----------------Validaciones----------------

/** \brief Comprueba que la constante volumetrica sea válida
 *
 * \param constanteVolumetrica float El dato a comprobar que sea válido
 * \return Retora 1 si es válido, 0 si no es válido o -1 (ERROR)
 *
 */
static int isValidConstanteVolumetrica(float constanteVolumetrica)
{
	int retorno = -1;

	if(constanteVolumetrica > 0)
	{
		retorno = 1;
	}

	return retorno;
}

/** \brief Comprueba que el precio por Kg sea válido
 *
 * \param precio float El dato a comprobar que sea válido
 * \return Retora 1 si es válido, 0 si no es válido o -1 (ERROR)
 *
 */
static int isValidPrecioPorKg(float precioPorKg)
{
	int retorno = -1;

	if(precioPorKg > 0)
	{
		retorno = 1;
	}

	return retorno;
}
