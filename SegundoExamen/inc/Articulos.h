/*
 * Articulos.h
 *
 *  Created on: 16 jun. 2021
 *      Author: mateo
 */

#ifndef ARTICULOS_H_
#define ARTICULOS_H_

#define TAM_CODIGO 128
#define TAM_DESCRIPCION 4096
#define TAM_PAIS_FABRICACION 256
#define TAM_NOMBRE 128

typedef struct
{
	int idArticulo;
	char codigo[TAM_CODIGO];
	char descripcion[TAM_DESCRIPCION];
	char paisFabricacion[TAM_PAIS_FABRICACION];
	float fob;
	float pesoKg;
	float altoCm;
	float anchoCm;
	float profundoCm;
	int idPosicionArancelaria;
}Articulo;

//----------------Memoria dinámica----------------

Articulo* articulo_new(void);
Articulo* articulo_newParametros(char* idStr, char* codigoStr, char* descripcionStr, char* paisFabricacionStr, char* fobStr, char* pesoKgStr, char* altoCmStr, char* anchoCmStr, char* profundoCmStr, char* idPosicionArancelariaStr, char* nomenclaturaStr);
int articulo_delete(Articulo* this);

//----------------Setters----------------

int articulo_setId(Articulo* this, int id);
int articulo_setNombre(Articulo* this, char* nombre);
int articulo_setCodigo(Articulo* this, char* codigo);
int articulo_setDescripcion(Articulo* this, char* descripcion);
int articulo_setPaisFabricacion(Articulo* this, char* paisFabricacion);
int articulo_setFob(Articulo* this, float fob);
int articulo_setPesoKg(Articulo* this, float pesoKg);
int articulo_setAltoCm(Articulo* this, float altoCm);
int articulo_setAnchoCm(Articulo* this, float anchoCm);
int articulo_setProfundoCm(Articulo* this, float profundoCm);
int articulo_setIdPosicionArancelaria(Articulo* this, int idPosicionArancelaria);

//----------------Getters----------------

int articulo_getId(Articulo* this, int* flagError);
char* articulo_getNombre(Articulo* this, int* flagError);
char* articulo_getCodigo(Articulo* this, int* flagError);
char* articulo_getDescripcion(Articulo* this, int* flagError);
char* articulo_getPaisFabricacion(Articulo* this, int* flagError);
float articulo_getFob(Articulo* this, int* flagError);
float articulo_getPesoKg(Articulo* this, int* flagError);
float articulo_getAltoCm(Articulo* this, int* flagError);
float articulo_getAnchoCm(Articulo* this, int* flagError);
float articulo_getProfundoCm(Articulo* this, int* flagError);
int articulo_getIdPosicionArancelaria(Articulo* this, int* flagError);

#endif /* ARTICULOS_H_ */
