/*
 * Arancel.h
 *
 *  Created on: 16 jun. 2021
 *      Author: mateo
 */

#ifndef ARANCEL_H_
#define ARANCEL_H_

#define TAM_NOMENCLATURA 128
#define TAM_TIPO_LICENCIA 24

typedef struct
{
	int idArancel;
	char nomenclatura[TAM_NOMENCLATURA];
	float porcentajeSeguro;
	float porcentajeImportacion;
	float porcentajeTasaEstadistica;
	char tipoLicencia[TAM_TIPO_LICENCIA];
}Arancel;

//----------------Memoria dinámica----------------

Arancel* arancel_new(void);
Arancel* arancel_newParametros(char* idStr, char* nomenclaturaStr, char* porcentajeSeguroStr, char* porcentajeImportacionStr, char* porcentajeTasaEstadisticaStr, char* tipoLicenciaStr);
int arancel_delete(Arancel* this);

//----------------Setters----------------

int arancel_setIdArancel(Arancel* this, int id);
int arancel_setNomenclatura(Arancel* this, char* nomenclatura);
int arancel_setPorcentajeSeguro(Arancel* this, float porcentajeSeguro);
int arancel_setPorcentajeImportacion(Arancel* this, float porcentajeImportacion);
int arancel_setPorcentajeTasaEstadistica(Arancel* this, float porcentajeTasaEstadistica);
int arancel_setTipoLicencia(Arancel* this, char* tipoLicencia);

//----------------Getters----------------

int arancel_getIdArancel(Arancel* this, int* flagError);
char* arancel_getNomenclatura(Arancel* this, int* flagError);
float arancel_getPorcentajeSeguro(Arancel* this, int* flagError);
float arancel_getPorcentajeImportacion(Arancel* this, int* flagError);
float arancel_getPorcentajeTasaEstadistica(Arancel* this, int* flagError);
char* arancel_getTipoLicencia(Arancel* this, int* flagError);

#endif /* ARANCEL_H_ */
