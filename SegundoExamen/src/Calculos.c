/*
 * Calculos.c
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

/** \brief Calcula el pasaje de centímetros a metros
 *
 * \param numeroEnCentimetros float Numero a ser convertido a metros
 * \return Retorna el valor en metros
 *
 */
float calculo_pasajeCentimetroMetro(float numeroEnCentimetros)
{
	float numeroEnMetros;

	numeroEnMetros = numeroEnCentimetros / 100;

	return numeroEnMetros;
}

/** \brief Calcula el precio marítimo
 *
 * \param barco Barco Estructura que contiene el precio y los metros cúbicos
 * \param altoMetros float El alto del producto en metros
 * \param anchoMetros float El ancho del producto en metros
 * \param profundoMetros float El profundo del producto en metros
 * \return Retorna el valor del precio marítimo en dólares
 *
 */
float calculo_precioMaritimo(Barco barco, float altoMetros, float anchoMetros, float profundoMetros)
{
	float precioTotalMaritimo;
	int flagError;
	float precioContenedor;
	float metrosCubicos;

	precioContenedor = barco_getPrecio(barco, &flagError);
	if(!flagError)
	{
		metrosCubicos = barco_getMetrosCubicos(barco, &flagError);
		if(!flagError)
		{
			precioTotalMaritimo = (precioContenedor / metrosCubicos) * (altoMetros * anchoMetros * profundoMetros);
		}
	}

	return precioTotalMaritimo;
}

/** \brief Calcula el peso real del artículo
 *
 * \param pListaArticulos LinkedList* Puntero a la lista
 * \param barco Barco Estructura que contiene el precio por Kg
 * \param indiceArticulo int Indice del artículo
 * \return Retorna el valor del precio marítimo en dólares
 *
 */
float calculo_pesoReal(LinkedList* pListaArticulos, Avion avion, int indiceArticulo)
{
	float pesoTotalReal;
	float pesoEnKg;
	float precioPorKg;
	int flagError;
	Articulo* pArticulo = NULL;

	pArticulo = (Articulo*)ll_get(pListaArticulos, indiceArticulo);

	pesoEnKg = articulo_getPesoKg(pArticulo, &flagError);
	if(!flagError)
	{
		precioPorKg = avion_getPrecioPorKg(avion, &flagError);
		if(!flagError)
		{
			pesoTotalReal = pesoEnKg * precioPorKg;
		}
	}

	return pesoTotalReal;
}

/** \brief Calcula el peso real del artículo
 *
 * \param pListaArticulos LinkedList* Puntero a la lista
 * \param barco Barco Estructura que contiene el precio por Kg
 * \param indiceArticulo int Indice del artículo
 * \return Retorna el valor del precio marítimo en dólares
 *
 */
float calculo_pesoVolumetrico(LinkedList* pListaArticulos, Avion avion, int indiceArticulo)
{
	float pesoTotalVolumetrico;
	float pesoEnKgVolumetricos;
	float precioPorKg;
	float altoCm;
	float anchoCm;
	float profundoCm;
	float constanteVolumetrica;
	int flagError;
	Articulo* pArticulo = NULL;

	pArticulo = (Articulo*)ll_get(pListaArticulos, indiceArticulo);

	altoCm = articulo_getAltoCm(pArticulo, &flagError);
	if(!flagError)
	{
		anchoCm = articulo_getAnchoCm(pArticulo, &flagError);
		if(!flagError)
		{
			profundoCm = articulo_getProfundoCm(pArticulo, &flagError);
			if(!flagError)
			{
				constanteVolumetrica = avion_getConstanteVolumetrica(avion, &flagError);
				if(!flagError)
				{
					precioPorKg = avion_getPrecioPorKg(avion, &flagError);
					if(!flagError)
					{
						pesoEnKgVolumetricos = (altoCm * anchoCm * profundoCm) / constanteVolumetrica;
						pesoTotalVolumetrico = pesoEnKgVolumetricos * precioPorKg;
					}
				}
			}
		}
	}

	return pesoTotalVolumetrico;
}

/** \brief Calcula el precio aéreo
 *
 * \param pListaArticulos LinkedList* Puntero a la lista
 * \param pListaAranceles LinkedList* Puntero a la lista
 * \param indiceArticulo int Indice del artículo
 * \return Retorna el valor del transporte aéreo en dólares
 *
 */
float calculo_precioAereo(LinkedList* pListaArticulos, Avion avion, int indiceArticulo)
{
	float precioTotalAereo;
	float pesoReal;
	float pesoVolumetrico;

	pesoReal = calculo_pesoReal(pListaArticulos, avion, indiceArticulo);
	pesoVolumetrico = calculo_pesoVolumetrico(pListaArticulos, avion, indiceArticulo);

	if(pesoReal > pesoVolumetrico)
	{
		precioTotalAereo = pesoReal;
	}
	else
	{
		precioTotalAereo = pesoVolumetrico;
	}

	return precioTotalAereo;
}

/** \brief Calcula el valor del seguro
 *
 * \param pListaArticulos LinkedList* Puntero a la lista
 * \param pListaAranceles LinkedList* Puntero a la lista
 * \param indiceArticulo int Indice del artículo
 * \return Retorna el valor del transporte aéreo en dólares
 *
 */
float calculo_valorSeguro(LinkedList* pListaArticulos, LinkedList* pListaAranceles, int indiceArticulo)
{
	float valorSeguro;
	float fob;
	float porcentajeSeguro;
	int idArticulo;
	int indiceArancel;
	int flagError;
	Articulo* pArticulo = NULL;
	Arancel* pArancel = NULL;

	pArticulo = (Articulo*)ll_get(pListaArticulos, indiceArticulo);

	idArticulo = articulo_getIdPosicionArancelaria(pArticulo, &flagError);
	if(!flagError)
	{
		indiceArancel = buscarIdArancel(pListaAranceles, idArticulo);
		pArancel = (Arancel*)ll_get(pListaAranceles, indiceArancel);

		fob = articulo_getFob(pArticulo, &flagError);
		if(!flagError)
		{
			porcentajeSeguro = arancel_getPorcentajeSeguro(pArancel, &flagError);
			if(!flagError)
			{
				valorSeguro = (fob * porcentajeSeguro) / 100;
			}
		}
	}

	return valorSeguro;
}

/** \brief Calcula la base imponible si el producto viaja en barco
 *
 * \param pListaArticulos LinkedList* Puntero a la lista
 * \param pListaAranceles LinkedList* Puntero a la lista
 * \param barco Barco Estructura que contiene los valores del barco
 * \param indiceArticulo int Indice del artículo
 * \return Retorna el valor de la base imponible en dólares
 *
 */
float calculo_baseImponibleMaritima(LinkedList* pListaArticulos, LinkedList* pListaAranceles, Barco barco, int indiceArticulo)
{
	float baseImponible;
	float valorSeguro;
	float fob;
	float altoM;
	float anchoM;
	float profundoM;
	float altoCm;
	float anchoCm;
	float profundoCm;
	float transporteMaritimo;
	int flagError;
	Articulo* pArticulo = NULL;

	pArticulo = (Articulo*)ll_get(pListaArticulos, indiceArticulo);

	fob = articulo_getFob(pArticulo, &flagError);
	if(!flagError)
	{
		altoCm = articulo_getAltoCm(pArticulo, &flagError);
		if(!flagError)
		{
			anchoCm = articulo_getAnchoCm(pArticulo, &flagError);
			if(!flagError)
			{
				profundoCm = articulo_getProfundoCm(pArticulo, &flagError);
				if(!flagError)
				{
					altoM = calculo_pasajeCentimetroMetro(altoCm);
					anchoM = calculo_pasajeCentimetroMetro(anchoCm);
					profundoM = calculo_pasajeCentimetroMetro(profundoCm);

					valorSeguro = calculo_valorSeguro(pListaArticulos, pListaAranceles, indiceArticulo);
					transporteMaritimo = calculo_precioMaritimo(barco, altoM, anchoM, profundoM);
					baseImponible = fob + valorSeguro + transporteMaritimo;
				}
			}
		}
	}

	return baseImponible;
}

/** \brief Calcula la base imponible si el producto viaja en avion
 *
 * \param pListaArticulos LinkedList* Puntero a la lista
 * \param pListaAranceles LinkedList* Puntero a la lista
 * \param avion Avion Estructura que contiene los valores del avion
 * \param indiceArticulo int Indice del artículo
 * \return Retorna el valor de la base imponible en dólares
 *
 */
float calculo_baseImponibleAerea(LinkedList* pListaArticulos, LinkedList* pListaAranceles, Avion avion, int indiceArticulo)
{
	float baseImponible;
	float valorSeguro;
	float fob;
	float transporteAereo;
	int flagError;
	Articulo* pArticulo = NULL;

	pArticulo = (Articulo*)ll_get(pListaArticulos, indiceArticulo);

	fob = articulo_getFob(pArticulo, &flagError);
	if(!flagError)
	{
		valorSeguro = calculo_valorSeguro(pListaArticulos, pListaAranceles, indiceArticulo);
		transporteAereo = calculo_precioAereo(pListaArticulos, avion, indiceArticulo);
		baseImponible = fob + valorSeguro + transporteAereo;
	}

	return baseImponible;
}

/** \brief Calcula el valor de importación marítima
 *
 * \param pListaArticulos LinkedList* Puntero a la lista
 * \param pListaAranceles LinkedList* Puntero a la lista
 * \param barco Barco Estructura que contiene los valores del barco
 * \param indiceArticulo int Indice del artículo
 * \return Retorna el valor de importación marítima
 *
 */
float calculo_valorImportacionMaritima(LinkedList* pListaArticulos, LinkedList* pListaAranceles, Barco barco, int indiceArticulo)
{
	float valorImportacion;
	float baseImponibleMaritima;
	float porcentajeImportacion;
	int idArticulo;
	int indiceArancel;
	int flagError;
	Articulo* pArticulo = NULL;
	Arancel* pArancel = NULL;

	pArticulo = (Articulo*)ll_get(pListaArticulos, indiceArticulo);

	idArticulo = articulo_getIdPosicionArancelaria(pArticulo, &flagError);
	if(!flagError)
	{
		indiceArancel = buscarIdArancel(pListaAranceles, idArticulo);
		pArancel = (Arancel*)ll_get(pListaAranceles, indiceArancel);

		porcentajeImportacion = arancel_getPorcentajeImportacion(pArancel, &flagError);
		if(!flagError)
		{
			baseImponibleMaritima = calculo_baseImponibleMaritima(pListaArticulos, pListaAranceles, barco, indiceArticulo);
			valorImportacion = (baseImponibleMaritima * porcentajeImportacion) / 100;
		}
	}

	return valorImportacion;
}

/** \brief Calcula el valor de importación aérea
 *
 * \param pListaArticulos LinkedList* Puntero a la lista
 * \param pListaAranceles LinkedList* Puntero a la lista
 * \param avion Avion Estructura que contiene los valores del avion
 * \param indiceArticulo int Indice del artículo
 * \return Retorna el valor de importación aérea
 *
 */
float calculo_valorImportacionAerea(LinkedList* pListaArticulos, LinkedList* pListaAranceles, Avion avion, int indiceArticulo)
{
	float valorImportacion;
	float baseImponibleAerea;
	float porcentajeImportacion;
	int flagError;
	int idArticulo;
	int indiceArancel;
	Articulo* pArticulo = NULL;
	Arancel* pArancel = NULL;

	pArticulo = (Articulo*)ll_get(pListaArticulos, indiceArticulo);

	idArticulo = articulo_getIdPosicionArancelaria(pArticulo, &flagError);
	if(!flagError)
	{
		indiceArancel = buscarIdArancel(pListaAranceles, idArticulo);
		pArancel = (Arancel*)ll_get(pListaAranceles, indiceArancel);

		porcentajeImportacion = arancel_getPorcentajeImportacion(pArancel, &flagError);
		if(!flagError)
		{
			baseImponibleAerea = calculo_baseImponibleAerea(pListaArticulos, pListaAranceles, avion, indiceArticulo);
			valorImportacion = (baseImponibleAerea * porcentajeImportacion) / 100;
		}
	}

	return valorImportacion;
}

/** \brief Calcula el valor de la tasa estadística marítima
 *
 * \param pListaArticulos LinkedList* Puntero a la lista
 * \param pListaAranceles LinkedList* Puntero a la lista
 * \param barco Barco Estructura que contiene los valores del barco
 * \param indiceArticulo int Indice del artículo
 * \return Retorna el valor de la tasa estadística marítima
 *
 */
float calculo_valorTasaEstadisticaMaritima(LinkedList* pListaArticulos, LinkedList* pListaAranceles, Barco barco, int indiceArticulo)
{
	float valorTasaEstadistica;
	float baseImponibleMaritima;
	float porcentajeTasaEstadistica;
	int flagError;
	int idArticulo;
	int indiceArancel;
	Articulo* pArticulo = NULL;
	Arancel* pArancel = NULL;

	pArticulo = (Articulo*)ll_get(pListaArticulos, indiceArticulo);

	idArticulo = articulo_getIdPosicionArancelaria(pArticulo, &flagError);
	if(!flagError)
	{
		indiceArancel = buscarIdArancel(pListaAranceles, idArticulo);
		pArancel = (Arancel*)ll_get(pListaAranceles, indiceArancel);

		porcentajeTasaEstadistica = arancel_getPorcentajeTasaEstadistica(pArancel, &flagError);
		if(!flagError)
		{
			baseImponibleMaritima = calculo_baseImponibleMaritima(pListaArticulos, pListaAranceles, barco, indiceArticulo);
			valorTasaEstadistica = (baseImponibleMaritima * porcentajeTasaEstadistica) / 100;
		}
	}

	return valorTasaEstadistica;
}

/** \brief Calcula el valor de la tasa estadística aérea
 *
 * \param pListaArticulos LinkedList* Puntero a la lista
 * \param pListaAranceles LinkedList* Puntero a la lista
 * \param avion Avion Estructura que contiene los valores del avion
 * \param indiceArticulo int Indice del artículo
 * \return Retorna el valor de la tasa estadística aérea
 *
 */
float calculo_valorTasaEstadisticaAerea(LinkedList* pListaArticulos, LinkedList* pListaAranceles, Avion avion, int indiceArticulo)
{
	float valorTasaEstadistica;
	float baseImponibleAerea;
	float porcentajeTasaEstadistica;
	int flagError;
	int idArticulo;
	int indiceArancel;
	Articulo* pArticulo = NULL;
	Arancel* pArancel = NULL;

	pArticulo = (Articulo*)ll_get(pListaArticulos, indiceArticulo);

	idArticulo = articulo_getIdPosicionArancelaria(pArticulo, &flagError);
	if(!flagError)
	{
		indiceArancel = buscarIdArancel(pListaAranceles, idArticulo);
		pArancel = (Arancel*)ll_get(pListaAranceles, indiceArancel);

		porcentajeTasaEstadistica = arancel_getPorcentajeTasaEstadistica(pArancel, &flagError);
		if(!flagError)
		{
			baseImponibleAerea = calculo_baseImponibleAerea(pListaArticulos, pListaAranceles, avion, indiceArticulo);
			valorTasaEstadistica = (baseImponibleAerea * porcentajeTasaEstadistica) / 100;
		}
	}

	return valorTasaEstadistica;
}

/** \brief Calcula el costo argentino marítimo
 *
 * \param pListaArticulos LinkedList* Puntero a la lista
 * \param pListaAranceles LinkedList* Puntero a la lista
 * \param barco Barco Estructura que contiene los valores del barco
 * \param indiceArticulo int Indice del artículo
 * \return Retorna el costo argentino marítimo
 *
 */
float calculo_costoArgentinoMaritimo(LinkedList* pListaArticulos, LinkedList* pListaAranceles, Barco barco, int indiceArticulo)
{
	float costoArgentinoMaritimo;
	float baseImponibleMaritima;
	float valorImportacion;
	float valorTasaEstadistica;

	baseImponibleMaritima = calculo_baseImponibleMaritima(pListaArticulos, pListaAranceles, barco, indiceArticulo);
	valorImportacion = calculo_valorImportacionMaritima(pListaArticulos, pListaAranceles, barco, indiceArticulo);
	valorTasaEstadistica = calculo_valorTasaEstadisticaMaritima(pListaArticulos, pListaAranceles, barco, indiceArticulo);

	costoArgentinoMaritimo = baseImponibleMaritima + valorImportacion + valorTasaEstadistica;

	return costoArgentinoMaritimo;
}

/** \brief Calcula el costo argentino aéreo
 *
 * \param pListaArticulos LinkedList* Puntero a la lista
 * \param pListaAranceles LinkedList* Puntero a la lista
 * \param avion Avion Estructura que contiene los valores del avion
 * \param indiceArticulo int Indice del artículo
 * \return Retorna el costo argentino aéreo
 *
 */
float calculo_costoArgentinoAereo(LinkedList* pListaArticulos, LinkedList* pListaAranceles, Avion avion, int indiceArticulo)
{
	float costoArgentinoAereo;
	float baseImponibleAereo;
	float valorImportacion;
	float valorTasaEstadistica;

	baseImponibleAereo = calculo_baseImponibleAerea(pListaArticulos, pListaAranceles, avion, indiceArticulo);
	valorImportacion = calculo_valorImportacionAerea(pListaArticulos, pListaAranceles, avion, indiceArticulo);
	valorTasaEstadistica = calculo_valorTasaEstadisticaAerea(pListaArticulos, pListaAranceles, avion, indiceArticulo);

	costoArgentinoAereo = baseImponibleAereo + valorImportacion + valorTasaEstadistica;

	return costoArgentinoAereo;
}
