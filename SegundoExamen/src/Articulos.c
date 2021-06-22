/*
 * Articulos.c
 *
 *  Created on: 16 jun. 2021
 *      Author: mateo
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/utn.h"
#include "../inc/Arancel.h"
#include "../inc/Articulos.h"

static int isValidId(int id);
static int isValidCodigo(char* nombre);
static int isValidDescripcion(char* descripcion);
static int isValidPaisFabricacion(char* paisFabricacion);
static int isValidFob(float fob);
static int isValidPesoKg(float pesoKg);
static int isValidAltoCm(float altoCm);
static int isValidAnchoCm(float anchoCm);
static int isValidProfundoCm(float profundoCm);
static int isValidIdPosicionArancelaria(int idPosicionArancelaria);

/** \brief Asigna espacio en la memoria heap para un Articulo
 *
 * \return Retora el espacio de memoria obtenido o si no lo pudo conseguir NULL
 *
 */
Articulo* articulo_new(void)
{
	return (Articulo*)malloc(sizeof(Articulo));
}

/** \brief Asigna espacio en la memoria para un nuevo articulo y asigna valores a sus campos
 *
 * \param char* idStr Asigna un valor a idStr
 * \param char* nombreStr Asigna un valor a nombreStr
 * \param char* codigoStr Asigna un valor a codigoStr
 * \param char* descripcionStr Asigna un valor a descripcionStr
 * \param char* paisFabricacionStr Asigna un valor a paisFabricacionStr
 * \param char* fobStr Asigna un valor a fobStr
 * \param char* pesoKgStr Asigna un valor a pesoKgStr
 * \param char* altoCmStr Asigna un valor a altoCmStr
 * \param char* anchoCmStr Asigna un valor a anchoCmStr
 * \param char* profundoCmStr Asigna un valor a profundoCmStr
 * \param char* posicionArancelariaStr Asigna un valor a posicionArancelariaStr
 * \return Articulo* Retora el espacio de memoria con valores cargados o NULL
 *
 */
Articulo* articulo_newParametros(char* idStr, char* codigoStr, char* descripcionStr, char* paisFabricacionStr,
								 char* fobStr, char* pesoKgStr, char* altoCmStr, char* anchoCmStr,
								 char* profundoCmStr, char* idPosicionArancelariaStr, char* nomenclaturaStr)
{
	Articulo* auxArticulo = articulo_new();
	Arancel* auxArancel = arancel_new();

	if(auxArticulo != NULL)
	{
		if(articulo_setId(auxArticulo, atoi(idStr)) < 0 ||
		   articulo_setCodigo(auxArticulo, codigoStr) < 0 ||
		   articulo_setDescripcion(auxArticulo, descripcionStr) < 0 ||
		   articulo_setPaisFabricacion(auxArticulo, paisFabricacionStr) < 0 ||
		   articulo_setFob(auxArticulo, atof(fobStr)) < 0 ||
		   articulo_setPesoKg(auxArticulo, atof(pesoKgStr)) < 0 ||
		   articulo_setAltoCm(auxArticulo, atof(altoCmStr)) < 0 ||
		   articulo_setAnchoCm(auxArticulo, atof(anchoCmStr)) < 0 ||
		   articulo_setProfundoCm(auxArticulo, atof(profundoCmStr)) < 0 ||
		   articulo_setIdPosicionArancelaria(auxArticulo, atoi(idPosicionArancelariaStr)) < 0 ||
		   arancel_setNomenclatura(auxArancel, nomenclaturaStr) < 0)
		{
			articulo_delete(auxArticulo);
			arancel_delete(auxArancel);
			auxArticulo = NULL;
		}
	}

	return auxArticulo;
}

/** \brief Libera el espacio de memoria entregado por parametro
 *
 * \param Articulo* this Puntero que va a ser liberado
 * \return Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int articulo_delete(Articulo* this)
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
 * \param Articulo* this Donde se guardará el dato obtenido
 * \param id int Dato que se evaluará y guardará en la estructura
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int articulo_setId(Articulo* this, int id)
{
	int retorno = -1;

	if(this != NULL && isValidId(id) == 1)
	{
		this->idArticulo = id;
		retorno = 0;
	}

	return retorno;
}

/** \brief Comprueba que el codigo sea válido y lo asigna a la estructura
 *
 * \param this Articulo* Donde se guardará el dato obtenido
 * \param codigo char* Dato que se evaluará y guardará en la estructura
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int articulo_setCodigo(Articulo* this, char* codigo)
{
	int retorno = -1;

	if(this != NULL && isValidCodigo(codigo) == 1)
	{
		strncpy(this->codigo, codigo, sizeof(this->codigo));
		retorno = 0;
	}

	return retorno;
}

/** \brief Comprueba que la descripcion sea válida y la asigna a la estructura
 *
 * \param this Articulo* Donde se guardará el dato obtenido
 * \param descripcion char* Dato que se evaluará y guardará en la estructura
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int articulo_setDescripcion(Articulo* this, char* descripcion)
{
	int retorno = -1;

	if(this != NULL && isValidDescripcion(descripcion) == 1)
	{
		strncpy(this->descripcion, descripcion, sizeof(this->descripcion));
		retorno = 0;
	}

	return retorno;
}

/** \brief Comprueba que el pais de fabricacion sea válido y lo asigna a la estructura
 *
 * \param this Articulo* Donde se guardará el dato obtenido
 * \param paisFabricacion char* Dato que se evaluará y guardará en la estructura
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int articulo_setPaisFabricacion(Articulo* this, char* paisFabricacion)
{
	int retorno = -1;

	if(this != NULL && isValidPaisFabricacion(paisFabricacion) == 1)
	{
		strncpy(this->paisFabricacion, paisFabricacion, sizeof(this->paisFabricacion));
		retorno = 0;
	}

	return retorno;
}

/** \brief Comprueba que el fob sea válido y lo asigna a la estructura
 *
 * \param Articulo* this Donde se guardará el dato obtenido
 * \param fob float Dato que se evaluará y guardará en la estructura
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int articulo_setFob(Articulo* this, float fob)
{
	int retorno = -1;

	if(this != NULL && isValidFob(fob) == 1)
	{
		this->fob = fob;
		retorno = 0;
	}

	return retorno;
}

/** \brief Comprueba que el peso sea válido y lo asigna a la estructura
 *
 * \param Articulo* this Donde se guardará el dato obtenido
 * \param pesoKg float Dato que se evaluará y guardará en la estructura
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int articulo_setPesoKg(Articulo* this, float pesoKg)
{
	int retorno = -1;

	if(this != NULL && isValidPesoKg(pesoKg) == 1)
	{
		this->pesoKg = pesoKg;
		retorno = 0;
	}

	return retorno;
}

/** \brief Comprueba que el alto sea válido y lo asigna a la estructura
 *
 * \param Articulo* this Donde se guardará el dato obtenido
 * \param altoCm float Dato que se evaluará y guardará en la estructura
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int articulo_setAltoCm(Articulo* this, float altoCm)
{
	int retorno = -1;

	if(this != NULL && isValidAltoCm(altoCm) == 1)
	{
		this->altoCm = altoCm;
		retorno = 0;
	}

	return retorno;
}

/** \brief Comprueba que el ancho sea válido y lo asigna a la estructura
 *
 * \param Articulo* this Donde se guardará el dato obtenido
 * \param anchoCm float Dato que se evaluará y guardará en la estructura
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int articulo_setAnchoCm(Articulo* this, float anchoCm)
{
	int retorno = -1;

	if(this != NULL && isValidAnchoCm(anchoCm) == 1)
	{
		this->anchoCm = anchoCm;
		retorno = 0;
	}

	return retorno;
}

/** \brief Comprueba que el profundo sea válido y lo asigna a la estructura
 *
 * \param Articulo* this Donde se guardará el dato obtenido
 * \param profundoCm float Dato que se evaluará y guardará en la estructura
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int articulo_setProfundoCm(Articulo* this, float profundoCm)
{
	int retorno = -1;

	if(this != NULL && isValidProfundoCm(profundoCm) == 1)
	{
		this->profundoCm = profundoCm;
		retorno = 0;
	}

	return retorno;
}

/** \brief Comprueba que la posicion arancelaria sea válida y la asigna a la estructura
 *
 * \param Articulo* this Donde se guardará el dato obtenido
 * \param posicionArancelaria float Dato que se evaluará y guardará en la estructura
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int articulo_setIdPosicionArancelaria(Articulo* this, int idPosicionArancelaria)
{
	int retorno = -1;

	if(this != NULL && isValidIdPosicionArancelaria(idPosicionArancelaria) == 1)
	{
		this->idPosicionArancelaria = idPosicionArancelaria;
		retorno = 0;
	}

	return retorno;
}

//----------------Getters----------------

/** \brief Obtiene el valor de id
 *
 * \param this Articulo* Dato que queremos obtener
 * \param flagError int* Nos avisa si hay algún error
 * \return int Retora el valor dentro de id o NULL
 *
 */
int articulo_getId(Articulo* this, int* flagError)
{
	*flagError = -1;
	int auxId = -1;

	if(this != NULL && flagError != NULL)
	{
		auxId = this->idArticulo;
		*flagError = 0;
	}

	return auxId;
}

/** \brief Obtiene el valor de codigo
 *
 * \param this Articulo* Dato que queremos obtener
 * \param flagError int* Nos avisa si hay algún error
 * \return char* Retora el valor dentro de codigo o NULL
 *
 */
char* articulo_getCodigo(Articulo* this, int* flagError)
{
	*flagError = -1;
	char* auxCodigo = NULL;

	if(this != NULL && flagError != NULL)
	{
		auxCodigo = this->codigo;
		*flagError = 0;
	}

	return auxCodigo;
}

/** \brief Obtiene el valor de descripcion
 *
 * \param this Articulo* Dato que queremos obtener
 * \param flagError int* Nos avisa si hay algún error
 * \return char* Retora el valor dentro de descripcion o NULL
 *
 */
char* articulo_getDescripcion(Articulo* this, int* flagError)
{
	*flagError = -1;
	char* auxDescripcion = NULL;

	if(this != NULL && flagError != NULL)
	{
		auxDescripcion = this->descripcion;
		*flagError = 0;
	}

	return auxDescripcion;
}

/** \brief Obtiene el valor de paisFabricacion
 *
 * \param this Articulo* Dato que queremos obtener
 * \param flagError int* Nos avisa si hay algún error
 * \return char* Retora el valor dentro de paisFabricacion o NULL
 *
 */
char* articulo_getPaisFabricacion(Articulo* this, int* flagError)
{
	*flagError = -1;
	char* auxPaisFabricacion = NULL;

	if(this != NULL && flagError != NULL)
	{
		auxPaisFabricacion = this->paisFabricacion;
		*flagError = 0;
	}

	return auxPaisFabricacion;
}

/** \brief Obtiene el valor de fob
 *
 * \param this Articulo* Dato que queremos obtener
 * \param flagError int* Nos avisa si hay algún error
 * \return float Retora el valor dentro de fob o NULL
 *
 */
float articulo_getFob(Articulo* this, int* flagError)
{
	*flagError = -1;
	float auxFob = -1;

	if(this != NULL && flagError != NULL)
	{
		auxFob = this->fob;
		*flagError = 0;
	}

	return auxFob;
}

/** \brief Obtiene el valor de pesoKg
 *
 * \param this Articulo* Dato que queremos obtener
 * \param flagError int* Nos avisa si hay algún error
 * \return float Retora el valor dentro de pesoKg o NULL
 *
 */
float articulo_getPesoKg(Articulo* this, int* flagError)
{
	*flagError = -1;
	float auxPesoKg = -1;

	if(this != NULL && flagError != NULL)
	{
		auxPesoKg = this->pesoKg;
		*flagError = 0;
	}

	return auxPesoKg;
}

/** \brief Obtiene el valor de altoCm
 *
 * \param this Articulo* Dato que queremos obtener
 * \param flagError int* Nos avisa si hay algún error
 * \return float Retora el valor dentro de altoCm o NULL
 *
 */
float articulo_getAltoCm(Articulo* this, int* flagError)
{
	*flagError = -1;
	float auxAltoCm = -1;

	if(this != NULL && flagError != NULL)
	{
		auxAltoCm = this->altoCm;
		*flagError = 0;
	}

	return auxAltoCm;
}

/** \brief Obtiene el valor de anchoCm
 *
 * \param this Articulo* Dato que queremos obtener
 * \param flagError int* Nos avisa si hay algún error
 * \return float Retora el valor dentro de anchoCm o NULL
 *
 */
float articulo_getAnchoCm(Articulo* this, int* flagError)
{
	*flagError = -1;
	float auxAnchoCm = -1;

	if(this != NULL && flagError != NULL)
	{
		auxAnchoCm = this->anchoCm;
		*flagError = 0;
	}

	return auxAnchoCm;
}

/** \brief Obtiene el valor de profundoCm
 *
 * \param this Articulo* Dato que queremos obtener
 * \param flagError int* Nos avisa si hay algún error
 * \return float Retora el valor dentro de profundoCm o NULL
 *
 */
float articulo_getProfundoCm(Articulo* this, int* flagError)
{
	*flagError = -1;
	float auxProfundoCm = -1;

	if(this != NULL && flagError != NULL)
	{
		auxProfundoCm = this->profundoCm;
		*flagError = 0;
	}

	return auxProfundoCm;
}

/** \brief Obtiene el valor de posicionArancelaria
 *
 * \param this Articulo* Dato que queremos obtener
 * \param flagError int* Nos avisa si hay algún error
 * \return float Retora el valor dentro de posicionArancelaria o NULL
 *
 */
int articulo_getIdPosicionArancelaria(Articulo* this, int* flagError)
{
	*flagError = -1;
	int auxIdPosicionArancelaria = -1;

	if(this != NULL && flagError != NULL)
	{
		auxIdPosicionArancelaria = this->idPosicionArancelaria;
		*flagError = 0;
	}

	return auxIdPosicionArancelaria;
}

//----------------Validaciones----------------

/** \brief Comprueba que el ID sea válido
 *
 * \param int id El dato a comprobar que sea válido
 * \return int Retora 1 si es válido, 0 si no es válido o -1 (ERROR)
 *
 */
static int isValidId(int id)
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

/** \brief Comprueba que el codigo sea válido
 *
 * \param codigo char* El dato a comprobar que sea válido
 * \return Retora 1 si es válido, 0 si no es válido o -1 (ERROR)
 *
 */
static int isValidCodigo(char* codigo)
{
	int retorno = -1;

	retorno = 1;

	return retorno;
}

/** \brief Comprueba que la descripcion sea válida
 *
 * \param descripcion char* El dato a comprobar que sea válido
 * \return Retora 1 si es válido, 0 si no es válido o -1 (ERROR)
 *
 */
static int isValidDescripcion(char* descripcion)
{
	int retorno = -1;

	retorno = 1;

	return retorno;
}

/** \brief Comprueba que el pais de fabricacion sea válido
 *
 * \param paisFabricacion char* El dato a comprobar que sea válido
 * \return Retora 1 si es válido, 0 si no es válido o -1 (ERROR)
 *
 */
static int isValidPaisFabricacion(char* paisFabricacion)
{
	int retorno = -1;

	retorno = 1;

	return retorno;
}

/** \brief Comprueba que el fob sea válido
 *
 * \param fob float El dato a comprobar que sea válido
 * \return Retora 1 si es válido, 0 si no es válido o -1 (ERROR)
 *
 */
static int isValidFob(float fob)
{
	int retorno = -1;

	if(fob > 0)
	{
		retorno = 1;
	}

	return retorno;
}

/** \brief Comprueba que el peso sea válido
 *
 * \param pesoKg float El dato a comprobar que sea válido
 * \return Retora 1 si es válido, 0 si no es válido o -1 (ERROR)
 *
 */
static int isValidPesoKg(float pesoKg)
{
	int retorno = -1;

	if(pesoKg > 0)
	{
		retorno = 1;
	}

	return retorno;
}

/** \brief Comprueba que el alto sea válido
 *
 * \param altoCm float El dato a comprobar que sea válido
 * \return Retora 1 si es válido, 0 si no es válido o -1 (ERROR)
 *
 */
static int isValidAltoCm(float altoCm)
{
	int retorno = -1;

	if(altoCm > 0)
	{
		retorno = 1;
	}

	return retorno;
}

/** \brief Comprueba que el ancho sea válido
 *
 * \param anchoCm float El dato a comprobar que sea válido
 * \return Retora 1 si es válido, 0 si no es válido o -1 (ERROR)
 *
 */
static int isValidAnchoCm(float anchoCm)
{
	int retorno = -1;

	if(anchoCm > 0)
	{
		retorno = 1;
	}

	return retorno;
}

/** \brief Comprueba que el profundo sea válido
 *
 * \param profundoCm float El dato a comprobar que sea válido
 * \return Retora 1 si es válido, 0 si no es válido o -1 (ERROR)
 *
 */
static int isValidProfundoCm(float profundoCm)
{
	int retorno = -1;

	if(profundoCm > 0)
	{
		retorno = 1;
	}

	return retorno;
}

/** \brief Comprueba que idPosicionArancelaria sea válido
 *
 * \param idPosicionArancelaria int El dato a comprobar que sea válido
 * \return Retora 1 si es válido, 0 si no es válido o -1 (ERROR)
 *
 */
static int isValidIdPosicionArancelaria(int idPosicionArancelaria)
{
	int retorno = -1;

	if(idPosicionArancelaria > 0)
	{
		retorno = 1;
	}
	else
	{
		retorno = 0;
	}

	return retorno;
}
