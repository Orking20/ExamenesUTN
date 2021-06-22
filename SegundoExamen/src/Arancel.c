/*
 * Arancel.c
 *
 *  Created on: 16 jun. 2021
 *      Author: mateo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/utn.h"
#include "../inc/Arancel.h"

static int isValidIdArancel(int id);
static int isValidNomenclatura(char* nomenclatura);
static int isValidPorcentajeSeguro(float porcentajeSeguro);
static int isValidPorcentajeImportacion(float porcentajeImportacion);
static int isValidPorcentajeTasaEstadistica(float porcentajeTasaEstadistica);
static int isValidTipoLicencia(char* tipoLicencia);

/** \brief Asigna espacio en la memoria heap para un Arancel
 *
 * \return Retora el espacio de memoria obtenido o si no lo pudo conseguir NULL
 *
 */
Arancel* arancel_new(void)
{
	return (Arancel*)malloc(sizeof(Arancel));
}

/** \brief Asigna espacio en la memoria para un nuevo Arancel y asigna valores a sus campos
 *
 * \param char* idStr Asigna un valor a idStr
 * \param char* codigoStr Asigna un valor a nomenclaturaStr
 * \param char* descripcionStr Asigna un valor a porcentajeSeguroStr
 * \param char* nomenclaturaStr Asigna un valor a porcentajeImportacionStr
 * \param char* fobStr Asigna un valor a porcentajeTasaEstadisticaStr
 * \return Arancel* Retora el espacio de memoria con valores cargados o NULL
 *
 */
Arancel* arancel_newParametros(char* idStr, char* nomenclaturaStr, char* porcentajeSeguroStr, char* porcentajeImportacionStr, char* porcentajeTasaEstadisticaStr, char* tipoLicenciaStr)
{
	Arancel* auxArancel = arancel_new();

	if(auxArancel != NULL)
	{
		if(arancel_setIdArancel(auxArancel, atoi(idStr)) < 0 ||
		   arancel_setNomenclatura(auxArancel, nomenclaturaStr) < 0 ||
		   arancel_setPorcentajeSeguro(auxArancel, atof(porcentajeSeguroStr)) < 0 ||
		   arancel_setPorcentajeImportacion(auxArancel, atof(porcentajeImportacionStr)) < 0 ||
		   arancel_setPorcentajeTasaEstadistica(auxArancel, atof(porcentajeTasaEstadisticaStr)) < 0 ||
		   arancel_setTipoLicencia(auxArancel, tipoLicenciaStr) < 0)
		{
			arancel_delete(auxArancel);
			auxArancel = NULL;
		}
	}

	return auxArancel;
}

/** \brief Libera el espacio de memoria entregado por parametro
 *
 * \param Arancel* this Puntero que va a ser liberado
 * \return Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int arancel_delete(Arancel* this)
{
	int retorno = -1;

	if(this != NULL)
	{
		free(this);
		retorno = 0;
	}

	return retorno;
}

//----------------Setters----------------

/** \brief Comprueba que el id sea válido y lo asigna a la estructura
 *
 * \param Arancel* this Donde se guardará el dato obtenido
 * \param id int Dato que se evaluará y guardará en la estructura
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int arancel_setIdArancel(Arancel* this, int id)
{
	int retorno = -1;

	if(this != NULL && isValidIdArancel(id) == 1)
	{
		this->idArancel = id;
		retorno = 0;
	}

	return retorno;
}

/** \brief Comprueba que la nomenclatura sea válida y la asigna a la estructura
 *
 * \param this Arancel* Donde se guardará el dato obtenido
 * \param nomenclatura char* Dato que se evaluará y guardará en la estructura
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int arancel_setNomenclatura(Arancel* this, char* nomenclatura)
{
	int retorno = -1;

	if(this != NULL && isValidNomenclatura(nomenclatura) == 1)
	{
		strncpy(this->nomenclatura, nomenclatura, sizeof(this->nomenclatura));
		retorno = 0;
	}

	return retorno;
}

/** \brief Comprueba que el porcentaje del seguro sea válido y lo asigna a la estructura
 *
 * \param Arancel* this Donde se guardará el dato obtenido
 * \param porcentajeSeguro float Dato que se evaluará y guardará en la estructura
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int arancel_setPorcentajeSeguro(Arancel* this, float porcentajeSeguro)
{
	int retorno = -1;

	if(this != NULL && isValidPorcentajeSeguro(porcentajeSeguro) == 1)
	{
		this->porcentajeSeguro = porcentajeSeguro;
		retorno = 0;
	}

	return retorno;
}

/** \brief Comprueba que el porcentaje de la importación sea válido y lo asigna a la estructura
 *
 * \param Arancel* this Donde se guardará el dato obtenido
 * \param porcentajeImportacion float Dato que se evaluará y guardará en la estructura
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int arancel_setPorcentajeImportacion(Arancel* this, float porcentajeImportacion)
{
	int retorno = -1;

	if(this != NULL && isValidPorcentajeImportacion(porcentajeImportacion) == 1)
	{
		this->porcentajeImportacion = porcentajeImportacion;
		retorno = 0;
	}

	return retorno;
}

/** \brief Comprueba que el porcentaje de tasa estadística sea válido y lo asigna a la estructura
 *
 * \param Arancel* this Donde se guardará el dato obtenido
 * \param porcentajeTasaEstadistica float Dato que se evaluará y guardará en la estructura
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int arancel_setPorcentajeTasaEstadistica(Arancel* this, float porcentajeTasaEstadistica)
{
	int retorno = -1;

	if(this != NULL && isValidPorcentajeTasaEstadistica(porcentajeTasaEstadistica) == 1)
	{
		this->porcentajeTasaEstadistica = porcentajeTasaEstadistica;
		retorno = 0;
	}

	return retorno;
}

/** \brief Comprueba que el tipo de licencia sea válido y lo asigna a la estructura
 *
 * \param Arancel* this Donde se guardará el dato obtenido
 * \param tipoLicencia char* Dato que se evaluará y guardará en la estructura
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int arancel_setTipoLicencia(Arancel* this, char* tipoLicencia)
{
	int retorno = -1;

	if(this != NULL && isValidTipoLicencia(tipoLicencia) == 1)
	{
		strncpy(this->tipoLicencia, tipoLicencia, sizeof(this->tipoLicencia));
		retorno = 0;
	}

	return retorno;
}

//----------------Getters----------------

/** \brief Obtiene el valor de id
 *
 * \param this Arancel* Dato que queremos obtener
 * \param flagError int* Nos avisa si hay algún error
 * \return int Retora el valor dentro de id o NULL
 *
 */
int arancel_getIdArancel(Arancel* this, int* flagError)
{
	*flagError = -1;
	int auxId = -1;

	if(this != NULL && flagError != NULL)
	{
		auxId = this->idArancel;
		*flagError = 0;
	}

	return auxId;
}

/** \brief Obtiene el valor de nomenclatura
 *
 * \param this Arancel* Dato que queremos obtener
 * \param flagError int* Nos avisa si hay algún error
 * \return char* Retora el valor dentro de nomenclatura o NULL
 *
 */
char* arancel_getNomenclatura(Arancel* this, int* flagError)
{
	*flagError = -1;
	char* auxNomenclatura = NULL;

	if(this != NULL && flagError != NULL)
	{
		auxNomenclatura = this->nomenclatura;
		*flagError = 0;
	}

	return auxNomenclatura;
}

/** \brief Obtiene el valor de porcentajeSeguro
 *
 * \param this Arancel* Dato que queremos obtener
 * \param flagError int* Nos avisa si hay algún error
 * \return float Retora el valor dentro de porcentajeSeguro o NULL
 *
 */
float arancel_getPorcentajeSeguro(Arancel* this, int* flagError)
{
	*flagError = -1;
	float auxPorcentajeSeguro = -1;

	if(this != NULL && flagError != NULL)
	{
		auxPorcentajeSeguro = this->porcentajeSeguro;
		*flagError = 0;
	}

	return auxPorcentajeSeguro;
}

/** \brief Obtiene el valor de porcentajeImportacion
 *
 * \param this Arancel* Dato que queremos obtener
 * \param flagError int* Nos avisa si hay algún error
 * \return float Retora el valor dentro de porcentajeImportacion o NULL
 *
 */
float arancel_getPorcentajeImportacion(Arancel* this, int* flagError)
{
	*flagError = -1;
	float auxPorcentajeImportacion = -1;

	if(this != NULL && flagError != NULL)
	{
		auxPorcentajeImportacion = this->porcentajeImportacion;
		*flagError = 0;
	}

	return auxPorcentajeImportacion;
}

/** \brief Obtiene el valor de porcentajeTasaEstadistica
 *
 * \param this Arancel* Dato que queremos obtener
 * \param flagError int* Nos avisa si hay algún error
 * \return float Retora el valor dentro de porcentajeTasaEstadistica o NULL
 *
 */
float arancel_getPorcentajeTasaEstadistica(Arancel* this, int* flagError)
{
	*flagError = -1;
	float auxPorcentajeTasaEstadistica = -1;

	if(this != NULL && flagError != NULL)
	{
		auxPorcentajeTasaEstadistica = this->porcentajeTasaEstadistica;
		*flagError = 0;
	}

	return auxPorcentajeTasaEstadistica;
}

/** \brief Obtiene el valor de tipoLicencia
 *
 * \param this Arancel* Dato que queremos obtener
 * \param flagError int* Nos avisa si hay algún error
 * \return char* Retora el valor dentro de tipoLicencia o NULL
 *
 */
char* arancel_getTipoLicencia(Arancel* this, int* flagError)
{
	*flagError = -1;
	char* auxTipoLicencia = NULL;

	if(this != NULL && flagError != NULL)
	{
		auxTipoLicencia = this->tipoLicencia;
		*flagError = 0;
	}

	return auxTipoLicencia;
}
//----------------Validaciones----------------

/** \brief Comprueba que el ID sea válido
 *
 * \param int id El dato a comprobar que sea válido
 * \return int Retora 1 si es válido, 0 si no es válido o -1 (ERROR)
 *
 */
static int isValidIdArancel(int id)
{
	int retorno = -1;

	if(id > 0)
	{
		retorno = 1;
	}
	else
	{
		retorno = 0;
	}

	return retorno;
}

/** \brief Comprueba que la nomenclatura sea válida
 *
 * \param nomenclatura char* El dato a comprobar que sea válido
 * \return Retora 1 si es válido, 0 si no es válido o -1 (ERROR)
 *
 */
static int isValidNomenclatura(char* nomenclatura)
{
	int retorno = -1;

	retorno = 1;

	return retorno;
}

/** \brief Comprueba que el porcentaje de seguro sea válido
 *
 * \param porcentajeSeguro float El dato a comprobar que sea válido
 * \return Retora 1 si es válido, 0 si no es válido o -1 (ERROR)
 *
 */
static int isValidPorcentajeSeguro(float porcentajeSeguro)
{
	int retorno = -1;

	retorno = 1;

	return retorno;
}

/** \brief Comprueba que el porcentaje de la importacion sea válido
 *
 * \param porcentajeImportacion float El dato a comprobar que sea válido
 * \return Retora 1 si es válido, 0 si no es válido o -1 (ERROR)
 *
 */
static int isValidPorcentajeImportacion(float porcentajeImportacion)
{
	int retorno = -1;

	retorno = 1;

	return retorno;
}

/** \brief Comprueba que el porcentaje tasa estadística sea válido
 *
 * \param porcentajeTasaEstadistica float El dato a comprobar que sea válido
 * \return Retora 1 si es válido, 0 si no es válido o -1 (ERROR)
 *
 */
static int isValidPorcentajeTasaEstadistica(float porcentajeTasaEstadistica)
{
	int retorno = -1;

	retorno = 1;

	return retorno;
}

/** \brief Comprueba que la licencia sea válida
 *
 * \param tipoLicencia char* El dato a comprobar que sea válido
 * \return Retora 1 si es válido, 0 si no es válido o -1 (ERROR)
 *
 */
static int isValidTipoLicencia(char* tipoLicencia)
{
	int retorno = -1;

	retorno = 1;

	return retorno;
}

