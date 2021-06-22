/*
 * Controller.c
 *
 *  Created on: 17 jun. 2021
 *      Author: mateo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/utn.h"
#include "../inc/LinkedList.h"
#include "../inc/Controller.h"
#include "../inc/Articulos.h"
#include "../inc/Arancel.h"
#include "../inc/Barco.h"
#include "../inc/Avion.h"
#include "../inc/parser.h"

static int contador = 0;
static int buscarElemento(LinkedList* pLista);
static int buscarIdMaximo(LinkedList* pListaArticulos, int* idMaximo);
static int articulo_buscarPorId(LinkedList* pListaArancel, int id);
static int arancel_buscarPorId(LinkedList* pListaArancel, int id);
static int ordenarPorCodigo(void* elemento1, void* elemento2);
static int ordenarPorDescripcion(void* elemento1, void* elemento2);
static int ordenarPorPais(void* elemento1, void* elemento2);
static int ordenarPorFob(void* elemento1, void* elemento2);
static int ordenarPorPesoKg(void* elemento1, void* elemento2);
static int ordenarPorAltoCm(void* elemento1, void* elemento2);
static int ordenarPorAnchoCm(void* elemento1, void* elemento2);
static int ordenarPorProfundoCm(void* elemento1, void* elemento2);
static int ordenarPorNomenclatura(void* elemento1, void* elemento2);
static int ordenarPorSeguro(void* elemento1, void* elemento2);
static int ordenarPorImportacion(void* elemento1, void* elemento2);
static int ordenarPorTasaEstadistica(void* elemento1, void* elemento2);
static int ordenarPorLicencia(void* elemento1, void* elemento2);

//----------------Articulo----------------

/** \brief Carga los datos de los articulos desde el archivo "Articulos.csv"
 *
 * \param pListaArticulos LinkedList* Puntero a la lista
 * \return int Retorna 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_cargarArticulos(LinkedList* pListaArticulos)
{
	int retorno = -1;
	FILE* pFile = NULL;

	pFile = fopen("articulo.csv", "r");

	if(pListaArticulos != NULL && pFile != NULL)
	{
		if(!parser_articulo(pFile, pListaArticulos))
		{
			fclose(pFile);
			printf("\nSe ha cargado exitosamente!");
			retorno = 0;
		}
		else
		{
			printf("\nError. El archivo no pudo abrirse");
		}
	}

    return retorno;
}

/** \brief Alta de Articulos
 *
 * \param pListaArticulos LinkedList* Puntero a la lista
 * \param pListaAranceles LinkedList* Puntero a la lista
 * \return int Retorna 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_altaArticulo(LinkedList* pListaArticulos, LinkedList* pListaAranceles)
{
	int retorno = -2;
	int idArticulo;
	char bufferCodigo[TAM_CODIGO];
	char bufferDescripcion[TAM_DESCRIPCION];
	char bufferPaisFabricacion[TAM_PAIS_FABRICACION];
	float bufferFob;
	float bufferPesoKg;
	float bufferAltoCm;
	float bufferAnchoCm;
	float bufferProfundoCm;
	int bufferIdPosicionArancelaria;
	int idArancel;
	int flagError;
	Arancel* auxiliarArancel = NULL;
	Articulo* auxiliarArticulo = NULL;

	if(pListaArticulos != NULL)
	{
		controller_listarArancelConId(pListaAranceles);
		if(!utn_getNumero(&bufferIdPosicionArancelaria, "\nIngrese el ID de la posición arancelaria a la que va a pertenecer este artículo: ", "\nError. Ese ID es inválido", 1, 100000))
		{
			for(int i = 0; i < ll_len(pListaAranceles); i++)
			{
				auxiliarArancel = (Arancel*)ll_get(pListaAranceles, i);
				if(auxiliarArancel != NULL)
				{
					idArancel = arancel_getIdArancel(auxiliarArancel, &flagError);
					if(bufferIdPosicionArancelaria == idArancel)
					{
						retorno = -1;

						if(!utn_getTexto(bufferCodigo, TAM_CODIGO, "Ingrese el código: ", "\nError. Ese código no es válido\n") &&
						   !utn_getTexto(bufferDescripcion, TAM_DESCRIPCION, "Ingrese la descripción: ", "\nError. Esa descripción no es válida\n") &&
						   !utn_getTexto(bufferPaisFabricacion, TAM_PAIS_FABRICACION, "Ingrese el país de fabricación: ", "\nError. Ese país no es válido\n") &&
						   !utn_getDecimal(&bufferFob, "Ingrese el valor FOB: ", "\nError. Ese número no es válido\n", 0, 900000000) &&
						   !utn_getDecimal(&bufferPesoKg, "Ingrese el peso en Kg: ", "\nError. Ese peso no es válido\n", 0, 1000000) &&
						   !utn_getDecimal(&bufferAltoCm, "Ingrese la altura del paquete en cm: ", "\nError. Esa altura no es válida\n", 0, 1000000) &&
						   !utn_getDecimal(&bufferAnchoCm, "Ingrese la anchura del paquete en cm: ", "\nError. Esa anchura no es válida\n", 0, 1000000) &&
						   !utn_getDecimal(&bufferProfundoCm, "Ingrese la profundidad del paquete en cm: ", "\nError. Esa profundidad no es válida\n", 0, 1000000))
						{
							auxiliarArticulo = articulo_new();

							buscarIdMaximo(pListaArticulos, &idArticulo);
							setearValorMaximoId(idArticulo);

							idArticulo = generarId();
							if(!articulo_setId(auxiliarArticulo, idArticulo) &&
							   !articulo_setCodigo(auxiliarArticulo, bufferCodigo) &&
							   !articulo_setDescripcion(auxiliarArticulo, bufferDescripcion) &&
							   !articulo_setPaisFabricacion(auxiliarArticulo, bufferPaisFabricacion) &&
							   !articulo_setFob(auxiliarArticulo, bufferFob) &&
							   !articulo_setPesoKg(auxiliarArticulo, bufferPesoKg) &&
							   !articulo_setAltoCm(auxiliarArticulo, bufferAltoCm) &&
							   !articulo_setAnchoCm(auxiliarArticulo, bufferAnchoCm) &&
							   !articulo_setProfundoCm(auxiliarArticulo, bufferProfundoCm) &&
							   !articulo_setIdPosicionArancelaria(auxiliarArticulo, bufferIdPosicionArancelaria))
							{
								if(!ll_add(pListaArticulos, auxiliarArticulo))
								{
									retorno = 0;
									break;
								}
							}
							else if(!articulo_delete(auxiliarArticulo))
							{
								retorno = -1;
							}
						}
					}
				}
			}
		}
		if(retorno == -2)
		{
			printf("\nEse ID no coincide con ningún otro");
		}
	}

    return retorno;
}

/** \brief Modificar datos de articulos
 *
 * \param pListaArticulos LinkedList* Puntero a la lista
 * \param pListaAranceles LinkedList* Puntero a la lista
 * \return int Retorna 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_modificarArticulo(LinkedList* pListaArticulos, LinkedList* pListaAranceles)
{
	int retorno = -1;
	int indice;
	int opcionMenu;
	int auxiliarId;
	char bufferCodigo[TAM_CODIGO];
	char bufferDescripcion[TAM_DESCRIPCION];
	char bufferPaisFabricacion[TAM_PAIS_FABRICACION];
	float bufferFob;
	float bufferPesoKg;
	float bufferAltoCm;
	float bufferAnchoCm;
	float bufferProfundoCm;
	int bufferIdPosicionArancelaria;
	int idArancel;
	int flagError;
	Articulo* auxiliarArticulo = NULL;
	Arancel* auxiliarArancel = NULL;

	if(pListaArticulos != NULL)
	{
		if(buscarElemento(pListaArticulos) == 1)
		{
			controller_listarArticuloConId(pListaArticulos, pListaAranceles);
			utn_getNumero(&auxiliarId, "\nIngrese el ID del artículo que desea modificar: ", "\nError. Ese ID no es válido", 1, 100000);
			indice = articulo_buscarPorId(pListaArticulos, auxiliarId);
			if(indice >= 0)
			{
				auxiliarArticulo = (Articulo*)ll_get(pListaArticulos, indice);
				if(auxiliarArticulo != NULL)
				{
					utn_getNumero(&opcionMenu, "\n¿Que desea modificar?\n1) Código\n2) Descripción\n3) Origen\n4) FOB\n5) Peso\n6) Altura paquete\n7) Anchura paquete\n8) Profundidad paquete\n9) Nomenclatura\n0) Cancelar\n", "\nError. Elija una de las opciones del menú\n", 0, 9);
					switch(opcionMenu)
					{
						case 1:
						{
							if(!utn_getTexto(bufferCodigo, TAM_CODIGO, "\nIngrese el nuevo código: ", "\nError. Ese código no es válido\n"))
							{
								articulo_setCodigo(auxiliarArticulo, bufferCodigo);
							}
							break;
						}
						case 2:
						{
							if(!utn_getTexto(bufferDescripcion, TAM_DESCRIPCION, "Ingrese la nueva descripción: ", "\nError. Esa descripción no es válida\n"))
							{
								articulo_setDescripcion(auxiliarArticulo, bufferDescripcion);
							}
							break;
						}
						case 3:
						{
							if(!utn_getTexto(bufferPaisFabricacion, TAM_PAIS_FABRICACION, "Ingrese el nuevo país de fabricación: ", "\nError. Ese país no es válido\n"))
							{
								articulo_setPaisFabricacion(auxiliarArticulo, bufferPaisFabricacion);
							}
							break;
						}
						case 4:
						{
							if(!utn_getDecimal(&bufferFob, "Ingrese el nuevo valor FOB: ", "\nError. Ese número no es válido\n", 0, 900000000))
							{
								articulo_setFob(auxiliarArticulo, bufferFob);
							}
							break;
						}
						case 5:
						{
							if(!utn_getDecimal(&bufferPesoKg, "Ingrese el nuevo peso en Kg: ", "\nError. Ese peso no es válido\n", 0, 1000000))
							{
								articulo_setPesoKg(auxiliarArticulo, bufferPesoKg);
							}
							break;
						}
						case 6:
						{
							if(!utn_getDecimal(&bufferAltoCm, "Ingrese la nueva altura del paquete en cm: ", "\nError. Esa altura no es válida\n", 0, 1000000))
							{
								articulo_setAltoCm(auxiliarArticulo, bufferAltoCm);
							}
							break;
						}
						case 7:
						{
							if(!utn_getDecimal(&bufferAnchoCm, "Ingrese la nueva anchura del paquete en cm: ", "\nError. Esa anchura no es válida\n", 0, 1000000))
							{
								articulo_setAnchoCm(auxiliarArticulo, bufferAnchoCm);
							}
							break;
						}
						case 8:
						{
							if(!utn_getDecimal(&bufferProfundoCm, "Ingrese la nueva profundidad del paquete en cm: ", "\nError. Esa profundidad no es válida\n", 0, 1000000))
							{
								articulo_setProfundoCm(auxiliarArticulo, bufferProfundoCm);
							}
							break;
						}
						case 9:
						{
							controller_listarArancelConId(pListaAranceles);
							if(!utn_getNumero(&bufferIdPosicionArancelaria, "\nIngrese el ID de la nueva posición arancelaria a la que va a pertenecer este artículo: ", "\nError. Ese ID es inválido", 1, 100000))
							{
								for(int i = 0; i < ll_len(pListaAranceles); i++)
								{
									auxiliarArancel = (Arancel*)ll_get(pListaAranceles, i);
									if(auxiliarArancel != NULL)
									{
										idArancel = arancel_getIdArancel(auxiliarArancel, &flagError);
										if(bufferIdPosicionArancelaria == idArancel)
										{
											articulo_setIdPosicionArancelaria(auxiliarArticulo, bufferIdPosicionArancelaria);
											retorno = 0;
											break;
										}
									}
								}
							}
							if(retorno == -1)
							{
								printf("\nEse ID no coincide con ningún otro");
							}
							break;
						}
					}
					retorno = 0;
				}
			}
			else
			{
				printf("\nEse ID no coincide con ningún otro");
			}
		}
		else
		{
			printf("\nAntes de editar un artículo tienes que cargar al menos un artículo en la opción 1 del menú de artículos\n");
		}
	}

    return retorno;
}

/** \brief Baja de articulo
 *
 * \param pListaArticulos LinkedList* Puntero a la lista
 * \param pListaAranceles LinkedList* Puntero a la lista
 * \return int Retorna 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_bajaArticulo(LinkedList* pListaArticulos, LinkedList* pListaAranceles)
{
	int retorno = -1;
	int auxiliarId;
	int indice;
	char confirmacion[24];
	Articulo* auxiliarArticulo = NULL;

	if(pListaArticulos != NULL)
	{
		if(buscarElemento(pListaArticulos) == 1)
		{
			controller_listarArticuloConId(pListaArticulos, pListaAranceles);
			if(!utn_getNumero(&auxiliarId, "\nIngrese el ID del Articulo que desea eliminar: ", "\nError. Ese ID no es válido", 1, 100000))
			{
				indice = articulo_buscarPorId(pListaArticulos, auxiliarId);
				if(indice >= 0)
				{
					auxiliarArticulo = (Articulo*)ll_get(pListaArticulos, indice);
					if(auxiliarArticulo != NULL &&
					   !utn_getRespuestaSiNo(confirmacion, "\nEstas seguro que quieres eliminar este Articulo? (si/no)", "\nError. Solo puedes ingresar 'si' o 'no'") &&
					   strncmp(confirmacion, "si", 24) == 0)
					{
						if(!ll_remove(pListaArticulos, indice) && !articulo_delete(auxiliarArticulo))
						{
							printf("\nSe ha eliminado con éxito\n");
							retorno = 0;
						}
					}
				}
			}
			else
			{
				printf("\nEse ID no coincide con ningún otro");
			}
		}
		else
		{
			printf("\nAntes de eliminar un artículo tienes que cargar al menos un artículo en la opción 1 del menú de artículos\n");
		}
	}

    return retorno;
}

/** \brief Listar articulos
 *
 * \param pListaArticulos LinkedList* Puntero a la lista
 * \param pListaAranceles LinkedList* Puntero a la lista
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_listarArticulo(LinkedList* pListaArticulos, LinkedList* pListaAranceles)
{
	int retorno = -1;
	int limite = ll_len(pListaArticulos);
	Articulo* pArticulo = NULL;
	Arancel* pArancel = NULL;
	int flagError;
	int indice;

	if(pListaArticulos != NULL)
	{
		if(buscarElemento(pListaArticulos) == 1)
		{
			printf("Código\t  Item\t\t\tOrigen\t\tFOB\t\tPeso Kg\t\tAlto cm\t\tAncho cm\tProfundidad cm\t\tNomenclatura\n"
				   "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			for(int i = 0; i < limite; i++)
			{
				pArticulo = (Articulo*)ll_get(pListaArticulos, i);
				indice = buscarIdArancel(pListaAranceles, articulo_getIdPosicionArancelaria(pArticulo, &flagError));
				pArancel = (Arancel*)ll_get(pListaAranceles, indice);
				printf("\n%-6s | %-20s | %-13s | %-13.2f | %-13.2f | %-13.2f | %-13.2f | %-21.2f | %s",
						   articulo_getCodigo(pArticulo, &flagError), articulo_getDescripcion(pArticulo, &flagError), articulo_getPaisFabricacion(pArticulo, &flagError),
						   articulo_getFob(pArticulo, &flagError), articulo_getPesoKg(pArticulo, &flagError), articulo_getAltoCm(pArticulo, &flagError),
						   articulo_getAnchoCm(pArticulo, &flagError), articulo_getProfundoCm(pArticulo, &flagError), arancel_getNomenclatura(pArancel, &flagError));
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

/** \brief Listar articulos
 *
 * \param pListaArticulos LinkedList* Puntero a la lista
 * \param pListaAranceles LinkedList* Puntero a la lista
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_listarArticuloConId(LinkedList* pListaArticulos, LinkedList* pListaAranceles)
{
	int retorno = -1;
	int limite = ll_len(pListaArticulos);
	Articulo* pArticulo = NULL;
	Arancel* pArancel = NULL;
	int flagError;
	int indice;

	if(pListaArticulos != NULL)
	{
		printf("ID\tCódigo\t  Descripción\t\t\t\t\tPais\t\tFOB\t\tPeso Kg\t\tAlto cm\t\tAncho cm\tProfundidad cm\t\tNomenclatura\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		for(int i = 0; i < limite; i++)
		{
			pArticulo = (Articulo*)ll_get(pListaArticulos, i);
			indice = buscarIdArancel(pListaAranceles, articulo_getIdPosicionArancelaria(pArticulo, &flagError));
			pArancel = (Arancel*)ll_get(pListaAranceles, indice);
			printf("\n%-6d | %-6s | %-44s | %-13s | %-13.2f | %-13.2f | %-13.2f | %-13.2f | %-21.2f | %s", articulo_getId(pArticulo, &flagError),
				   articulo_getCodigo(pArticulo, &flagError), articulo_getDescripcion(pArticulo, &flagError), articulo_getPaisFabricacion(pArticulo, &flagError),
				   articulo_getFob(pArticulo, &flagError), articulo_getPesoKg(pArticulo, &flagError), articulo_getAltoCm(pArticulo, &flagError),
				   articulo_getAnchoCm(pArticulo, &flagError), articulo_getProfundoCm(pArticulo, &flagError), arancel_getNomenclatura(pArancel, &flagError));
		}

		retorno = 0;
	}

    return retorno;
}

/** \brief Listar articulos con FOB superiores a 200
 *
 * \param pListaArticulos LinkedList* Puntero a la lista
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_listarArticulosFobAltos(LinkedList* pListaArticulos)
{
	int retorno = -1;
	LinkedList* listaFiltrada = NULL;

	if(pListaArticulos != NULL)
	{
		listaFiltrada = filtrar(pListaArticulos, funcionCriterioFiltrarFob);
		if(listaFiltrada != NULL)
		{
			listarArticulosCaros(listaFiltrada);
		}
		ll_deleteLinkedList(listaFiltrada);

		retorno = 0;
	}

    return retorno;
}

/** \brief Ordena los articulos por el criterio que el usuario quiera
 *
 * \param pListaArticulos LinkedList* Puntero a la lista
 * \param pListaAranceles LinkedList* Puntero a la lista
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_ordenarArticulos(LinkedList* pListaArticulos, LinkedList* pListaAranceles)
{
	int retorno = -1;
	int opcion;
	int orden;

	if(pListaArticulos != NULL)
	{
		if(!utn_getNumeroConIntentos(&opcion, "\n¿Por que categoría quiere ordenar?\n1) Código\n2) Descripción\n3) Origen\n4) FOB\n5) Peso en Kg\n6) Alto en Cm\n7) Ancho en Cm\n8) Profundidad en Cm\n", "\nError. Elija una de las opciones del menú\n", 1, 8, 3) &&
		   !utn_getNumeroConIntentos(&orden, "\nIngrese el orden (1-Ascendente | 0-Descendente): ", "\nError. Solo puedes ingresar 1 o 0", 0, 1, 3))
		{
			switch(opcion)
			{
				case 1:
				{
					if(!ll_sort(pListaArticulos, ordenarPorCodigo, orden))
					{
						retorno = 0;
					}
					break;
				}
				case 2:
				{
					if(!ll_sort(pListaArticulos, ordenarPorDescripcion, orden))
					{
						retorno = 0;
					}
					break;
				}
				case 3:
				{
					if(!ll_sort(pListaArticulos, ordenarPorPais, orden))
					{
						retorno = 0;
					}
					break;
				}
				case 4:
				{
					if(!ll_sort(pListaArticulos, ordenarPorFob, orden))
					{
						retorno = 0;
					}
					break;
				}
				case 5:
				{
					if(!ll_sort(pListaArticulos, ordenarPorPesoKg, orden))
					{
						retorno = 0;
					}
					break;
				}
				case 6:
				{
					if(!ll_sort(pListaArticulos, ordenarPorAltoCm, orden))
					{
						retorno = 0;
					}
					break;
				}
				case 7:
				{
					if(!ll_sort(pListaArticulos, ordenarPorAnchoCm, orden))
					{
						retorno = 0;
					}
					break;
				}
				case 8:
				{
					if(!ll_sort(pListaArticulos, ordenarPorProfundoCm, orden))
					{
						retorno = 0;
					}
					break;
				}
			}
			controller_listarArticulo(pListaArticulos, pListaAranceles);
		}
	}

	return retorno;
}

/** \brief Guarda los datos de los articulos en el archivo "Articulos.csv"
 *
 * \param pListaArticulos LinkedList* Puntero a la lista
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_guardarArticulos(LinkedList* pListaArticulos, LinkedList* pListaAranceles)
{
	int retorno = -1;
	Articulo* pArticulo = NULL;
	Arancel* pArancel;
	FILE* pFile;
	int flagError;
	int indice;

	pFile = fopen("articulo.csv", "w");

	if(pListaArticulos != NULL && pFile != NULL)
	{
		for(int i = 0; i < ll_len(pListaArticulos); i++)
		{
			pArticulo = (Articulo*)ll_get(pListaArticulos, i);
			indice = buscarIdArancel(pListaAranceles, articulo_getIdPosicionArancelaria(pArticulo, &flagError));
			pArancel = (Arancel*)ll_get(pListaAranceles, indice);
			fprintf(pFile, "%d,%s,%s,%s,%f,%f,%f,%f,%f,%d,%s\n", articulo_getId(pArticulo, &flagError), articulo_getCodigo(pArticulo, &flagError),
					articulo_getDescripcion(pArticulo, &flagError), articulo_getPaisFabricacion(pArticulo, &flagError), articulo_getFob(pArticulo, &flagError),
					articulo_getPesoKg(pArticulo, &flagError), articulo_getAltoCm(pArticulo, &flagError), articulo_getAnchoCm(pArticulo, &flagError),
					articulo_getProfundoCm(pArticulo, &flagError), articulo_getIdPosicionArancelaria(pArticulo, &flagError), arancel_getNomenclatura(pArancel, &flagError));
		}

		fclose(pFile);
		//printf("\nSe ha guardado correctamente!");
		retorno = 0;
	}

    return retorno;
}

//----------------Arancel----------------

/** \brief Carga los datos de las posiciones aranceladas desde el archivo "PosicionesAranceladas.csv"
 *
 * \param pListaAranceles LinkedList* Puntero a la lista
 * \return int Retorna 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_cargarArancel(LinkedList* pListaAranceles)
{
	int retorno = -1;
	FILE* pFile = NULL;

	pFile = fopen("posicion.csv", "r");

	if(pListaAranceles != NULL && pFile != NULL)
	{
		if(!parser_arancel(pFile, pListaAranceles))
		{
			fclose(pFile);
			printf("\nSe ha cargado exitosamente!");
			retorno = 0;
		}
		else
		{
			printf("\nError. El archivo no pudo abrirse");
		}
	}

    return retorno;
}

/** \brief Alta de Aranceles
 *
 * \param pListaArancel LinkedList* Puntero a la lista
 * \return int Retorna 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_altaArancel(LinkedList* pListaArancel)
{
	int retorno = -1;
	int idArancel;
	char bufferNomenclatura[TAM_NOMENCLATURA];
	float bufferPorcentajeSeguro;
	float bufferPorcentajeImportacion;
	float bufferPorcentajeTasaEstadistica;
	char bufferTipoLicencia[TAM_TIPO_LICENCIA];
	int auxIntTipoLicencia;
	Arancel* auxiliarArancel = NULL;

	if(pListaArancel != NULL)
	{
		if(!utn_getTexto(bufferNomenclatura, TAM_CODIGO, "\nIngrese la nomenclatura: ", "\nError. Esa nomenclatura no es válida\n") &&
		   !utn_getDecimal(&bufferPorcentajeSeguro, "Ingrese el porcentaje del seguro: ", "\nError. Ese número no es válido\n", 0, 10000) &&
		   !utn_getDecimal(&bufferPorcentajeImportacion, "Ingrese el porcentaje de importación: ", "\nError. Ese número no es válido\n", 0, 10000) &&
		   !utn_getDecimal(&bufferPorcentajeTasaEstadistica, "Ingrese el porcentaje de la tasa estadística: ", "\nError. Ese número no es válido\n", 0, 10000) &&
		   !utn_getNumero(&auxIntTipoLicencia, "Ingrese el tipo de licencia [1]Automatica - [2]No automatica: ", "\nError. Solo puedes ingresar [1] para automatica o [2] para no automatica", 1, 2))
		{
			auxiliarArancel = arancel_new();

			buscarIdMaximo(pListaArancel, &idArancel);
			setearValorMaximoId(idArancel);

			idArancel = generarId();
			if(auxIntTipoLicencia == 1)
			{
				strncpy(bufferTipoLicencia, "Automatica", sizeof(bufferTipoLicencia));
			}
			else
			{
				strncpy(bufferTipoLicencia, "No automatica", sizeof(bufferTipoLicencia));
			}

			if(!arancel_setIdArancel(auxiliarArancel, idArancel) &&
			   !arancel_setNomenclatura(auxiliarArancel, bufferNomenclatura) &&
			   !arancel_setPorcentajeSeguro(auxiliarArancel, bufferPorcentajeSeguro) &&
			   !arancel_setPorcentajeImportacion(auxiliarArancel, bufferPorcentajeImportacion) &&
			   !arancel_setPorcentajeTasaEstadistica(auxiliarArancel, bufferPorcentajeTasaEstadistica) &&
			   !arancel_setTipoLicencia(auxiliarArancel, bufferTipoLicencia))
			{
				if(!ll_add(pListaArancel, auxiliarArancel))
				{
					retorno = 0;
				}
			}
			else if(!arancel_delete(auxiliarArancel))
			{
				retorno = -1;
			}
		}
	}

    return retorno;
}

/** \brief Modificar datos de aranceles
 *
 * \param pListaAranceles LinkedList* Puntero a la lista
 * \return int Retorna 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_modificarArancel(LinkedList* pListaAranceles)
{
	int retorno = -1;
	int indice;
	int opcionMenu;
	int auxiliarId;
	char bufferNomenclatura[TAM_NOMENCLATURA];
	float bufferPorcentajeSeguro;
	float bufferPorcentajeImportacion;
	float bufferPorcentajeTasaEstadistica;
	char bufferTipoLicencia[TAM_TIPO_LICENCIA];
	int auxIntTipoLicencia;
	Arancel* auxiliarArancel = NULL;

	if(pListaAranceles != NULL)
	{
		if(buscarElemento(pListaAranceles) == 1)
		{
			controller_listarArancelConId(pListaAranceles);
			utn_getNumero(&auxiliarId, "\nIngrese el ID de la posición arancelaria que desea modificar: ", "\nError. Ese ID no es válido", 1, 100000);
			indice = arancel_buscarPorId(pListaAranceles, auxiliarId);
			if(indice >= 0)
			{
				auxiliarArancel = (Arancel*)ll_get(pListaAranceles, indice);
				if(auxiliarArancel != NULL)
				{
					utn_getNumero(&opcionMenu, "\n¿Que desea modificar?\n1) Nomenclatura\n2) Porcentaje del seguro\n3) Porcentaje de la importación\n4) Porcentaje de la tasa estadística\n5) Tipo de licencia\n0) Cancelar\n", "\nError. Elija una de las opciones del menú\n", 0, 5);
					switch(opcionMenu)
					{
						case 1:
						{
							if(!utn_getTexto(bufferNomenclatura, TAM_CODIGO, "\nIngrese la nueva nomenclatura: ", "\nError. Esa nomenclatura no es válida\n"))
							{
								arancel_setNomenclatura(auxiliarArancel, bufferNomenclatura);
							}
							break;
						}
						case 2:
						{
							if(!utn_getDecimal(&bufferPorcentajeSeguro, "Ingrese el nuevo porcentaje del seguro: ", "\nError. Ese número no es válido\n", 0, 10000))
							{
								arancel_setPorcentajeSeguro(auxiliarArancel, bufferPorcentajeSeguro);
							}
							break;
						}
						case 3:
						{
							if(!utn_getDecimal(&bufferPorcentajeImportacion, "Ingrese el nuevo porcentaje de la importación: ", "\nError. Ese número no es válido\n", 0, 10000))
							{
								arancel_setPorcentajeImportacion(auxiliarArancel, bufferPorcentajeImportacion);
							}
							break;
						}
						case 4:
						{
							if(!utn_getDecimal(&bufferPorcentajeTasaEstadistica, "Ingrese el nuevo porcentaje de la tasa estadística: ", "\nError. Ese número no es válido\n", 0, 10000))
							{
								arancel_setPorcentajeTasaEstadistica(auxiliarArancel, bufferPorcentajeTasaEstadistica);
							}
							break;
						}
						case 5:
						{
							if(!utn_getNumero(&auxIntTipoLicencia, "Ingrese el tipo de licencia [1]Automatica - [2]No automatica: ", "\nError. Solo puedes ingresar [1] para automatica o [2] para no automatica", 1, 2))
							{
								if(auxIntTipoLicencia == 1)
								{
									strncpy(bufferTipoLicencia, "Automatica", sizeof(bufferTipoLicencia));
								}
								else
								{
									strncpy(bufferTipoLicencia, "No automatica", sizeof(bufferTipoLicencia));
								}
								arancel_setTipoLicencia(auxiliarArancel, bufferTipoLicencia);
							}
							break;
						}
					}
					retorno = 0;
				}
			}
			else
			{
				printf("\nEse ID no coincide con ningún otro");
			}
		}
		else
		{
			printf("\nAntes de editar un artículo tienes que cargar al menos un artículo en la opción 1 del menú de artículos\n");
		}
	}

    return retorno;
}

/** \brief Baja de arancel
 *
 * \param pListaArancel LinkedList* Puntero a la lista
 * \return int Retorna 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_bajaArancel(LinkedList* pListaArancel, LinkedList* pListaArticulo)
{
	int retorno = -1;
	int auxiliarId;
	int indice;
	int indiceArticuloPos;
	int indiceArticulo;
	int idArticulo;
	int flagError;
	char confirmacion[24];
	Arancel* auxiliarArancel = NULL;
	Articulo* auxiliarArticulo = NULL;

	if(pListaArancel != NULL)
	{
		if(buscarElemento(pListaArancel) == 1)
		{
			controller_listarArancelConId(pListaArancel);
			if(!utn_getNumero(&auxiliarId, "\nIngrese el ID de la posición arancelaria que desea eliminar: ", "\nError. Ese ID no es válido", 1, 100000))
			{
				if(!utn_getRespuestaSiNo(confirmacion, "\nAl eliminar la posición arancelaria eliminarás todos los artículos que contengan la misma nomenclatura"
													   "\n¿Estas seguro que quieres eliminar esta posición arancelaria? (si/no)", "\nError. Solo puedes ingresar 'si' o 'no'") &&
				   strncmp(confirmacion, "si", 24) == 0)
				for(int i = 0; i < ll_len(pListaArticulo); i++)
				{
					indiceArticuloPos = buscarIdPosArancelaria(pListaArticulo, auxiliarId);

					if(indiceArticuloPos >= 0)
					{
						auxiliarArticulo = (Articulo*)ll_get(pListaArticulo, indiceArticuloPos);
						if(auxiliarArticulo != NULL)
						{
							idArticulo = articulo_getId(auxiliarArticulo, &flagError);
							indiceArticulo = articulo_buscarPorId(pListaArticulo, idArticulo);

							ll_remove(pListaArticulo, indiceArticulo);
						}
						articulo_delete(auxiliarArticulo);
					}
				}

				indice = arancel_buscarPorId(pListaArancel, auxiliarId);
				if(indice >= 0)
				{
					auxiliarArancel = (Arancel*)ll_get(pListaArancel, indice);
					if(auxiliarArancel != NULL)
					{
						if(!ll_remove(pListaArancel, indice) && !arancel_delete(auxiliarArancel))
						{
							printf("\nSe ha eliminado con éxito\n");
							retorno = 0;
						}
					}
				}
			}
			else
			{
				printf("\nEse ID no coincide con ningún otro");
			}
		}
		else
		{
			printf("\nAntes de eliminar una posición arancelaria tienes que cargar al menos una en la opción 1 del menú de posiciones arancelarias\n");
		}
	}

    return retorno;
}

/** \brief Listar posiciones arancelarias
 *
 * \param pListaAranceles LinkedList* Puntero a la lista
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_listarArancel(LinkedList* pListaAranceles)
{
	int retorno = -1;
	int limite = ll_len(pListaAranceles);
	Arancel* pArancel = NULL;
	int flagError;

	if(pListaAranceles != NULL)
	{
		if(buscarElemento(pListaAranceles) == 1)
		{
			printf("\nNomenclatura\t\t\tPorcentaje del seguro\tPorcentaje de la importación\tPorcentaje de la tasa estadística\tTipo de licencia\n---------------------------------------------------------------------------------------------------------------------------------------------------\n");
			for(int i = 0; i < limite; i++)
			{
				pArancel = (Arancel*)ll_get(pListaAranceles, i);
				printf("\n%-30s | %-21.2f | %-29.2f | %-37.2f | %s", arancel_getNomenclatura(pArancel, &flagError), arancel_getPorcentajeSeguro(pArancel, &flagError),
					   arancel_getPorcentajeImportacion(pArancel, &flagError), arancel_getPorcentajeTasaEstadistica(pArancel, &flagError), arancel_getTipoLicencia(pArancel, &flagError));
			}

			retorno = 0;
		}
		else
		{
			printf("\nNo hay posiciones aranceladas para mostrar. Cargalas en la opción 1 del menú de posiciones aranceladas\n");
		}
	}

    return retorno;
}

/** \brief Listar posiciones arancelarias
 *
 * \param pListaAranceles LinkedList* Puntero a la lista
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_listarArancelConId(LinkedList* pListaAranceles)
{
	int retorno = -1;
	int limite = ll_len(pListaAranceles);
	Arancel* pArancel = NULL;
	int flagError;

	if(pListaAranceles != NULL)
	{
		printf("ID\tNomenclatura\t\t\tPorcentaje del seguro\tPorcentaje de la importación\tPorcentaje de la tasa estadística\tTipo de licencia\n-------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		for(int i = 0; i < limite; i++)
		{
			pArancel = (Arancel*)ll_get(pListaAranceles, i);
			printf("\n%-6d | %-30s | %-21.2f | %-29.2f | %-37.2f | %s", arancel_getIdArancel(pArancel, &flagError), arancel_getNomenclatura(pArancel, &flagError), arancel_getPorcentajeSeguro(pArancel, &flagError),
					   arancel_getPorcentajeImportacion(pArancel, &flagError), arancel_getPorcentajeTasaEstadistica(pArancel, &flagError), arancel_getTipoLicencia(pArancel, &flagError));
		}

		retorno = 0;
	}

    return retorno;
}

/** \brief Ordena las posiciones arancelarias por el criterio que el usuario quiera
 *
 * \param pListaAranceles LinkedList* Puntero a la lista
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_ordenarAranceles(LinkedList* pListaAranceles)
{
	int retorno = -1;
	int opcion;
	int orden;

	if(pListaAranceles != NULL)
	{
		if(!utn_getNumeroConIntentos(&opcion, "\n¿Por que categoría quiere ordenar?\n1) Nomenclatura\n2) Porcentaje seguro\n3) Porcentaje importación\n4) Porcentaje tasa estadística\n5) Licencia\n", "\nError. Elija una de las opciones del menú\n", 1, 5, 3) &&
		   !utn_getNumeroConIntentos(&orden, "\nIngrese el orden (1-Ascendente | 0-Descendente): ", "\nError. Solo puedes ingresar 1 o 0", 0, 1, 3))
		{
			switch(opcion)
			{
				case 1:
				{
					if(!ll_sort(pListaAranceles, ordenarPorNomenclatura, orden))
					{
						retorno = 0;
					}
					break;
				}
				case 2:
				{
					if(!ll_sort(pListaAranceles, ordenarPorSeguro, orden))
					{
						retorno = 0;
					}
					break;
				}
				case 3:
				{
					if(!ll_sort(pListaAranceles, ordenarPorImportacion, orden))
					{
						retorno = 0;
					}
					break;
				}
				case 4:
				{
					if(!ll_sort(pListaAranceles, ordenarPorTasaEstadistica, orden))
					{
						retorno = 0;
					}
					break;
				}
				case 5:
				{
					if(!ll_sort(pListaAranceles, ordenarPorLicencia, orden))
					{
						retorno = 0;
					}
					break;
				}
			}
			controller_listarArancel(pListaAranceles);
		}
	}

	return retorno;
}

/** \brief Guarda los datos de las posiciones aranceladas en el archivo "PosicionesAranceladas.csv"
 *
 * \param pListaAranceles LinkedList* Puntero a la lista
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_guardarArancel(LinkedList* pListaAranceles)
{
	int retorno = -1;
	Arancel* pArancel = NULL;
	FILE* pFile;
	int flagError;

	pFile = fopen("posicion.csv", "w");

	if(pListaAranceles != NULL && pFile != NULL)
	{
		for(int i = 0; i < ll_len(pListaAranceles); i++)
		{
			pArancel = (Arancel*)ll_get(pListaAranceles, i);
			fprintf(pFile, "%d,%s,%f,%f,%f,%s\n", arancel_getIdArancel(pArancel, &flagError), arancel_getNomenclatura(pArancel, &flagError),
					arancel_getPorcentajeSeguro(pArancel, &flagError), arancel_getPorcentajeImportacion(pArancel, &flagError),
					arancel_getPorcentajeTasaEstadistica(pArancel, &flagError), arancel_getTipoLicencia(pArancel, &flagError));
		}

		fclose(pFile);
		//printf("\nSe ha guardado correctamente!");
		retorno = 0;
	}

    return retorno;
}

//----------------Barco----------------

/** \brief Carga los datos de el transporte marítimo desde el archivo "Barco.bin"
 *
 * \param pBarco Barco* Estructura donde se cargarán los datos
 * \return int Retorna 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_cargarBarco(Barco* pBarco)
{
	int retorno = -1;
	FILE* pFile = NULL;

	pFile = fopen("Barco.bin", "rb");

	if(pBarco != NULL && pFile != NULL)
	{
		if(!parser_barco(pFile, pBarco))
		{
			fclose(pFile);
			//printf("\nSe ha cargado exitosamente!");
			retorno = 0;
		}
		/*else
		{
			printf("\nError. El archivo no pudo abrirse");
		}*/
	}

    return retorno;
}

/** \brief Alta del barco
 *
 * \param pBarco Barco* Estructura donde se cargarán los datos
 * \return int Retorna 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_altaBarco(Barco* pBarco)
{
	int retorno = -1;
	float bufferMetrosCubicos;
	float bufferPrecio;

	if(pBarco != NULL)
	{
		if(!utn_getDecimal(&bufferMetrosCubicos, "Ingrese los metros cúbicos del contenedor del barco: ", "\nError. La medida del contenedor tiene que ser mayor a 0 y menor a 100 metros cúbicos\n", 1, 100) &&
		   !utn_getDecimal(&bufferPrecio, "Ingrese el precio total del contenedor: ", "\nError. Ese número no es válido\n", 0, 1000000))
		{
			if(!barco_setMetrosCubicos(pBarco, bufferMetrosCubicos) &&
			   !barco_setPrecio(pBarco, bufferPrecio))
			{
				retorno = 0;
			}
		}
	}

    return retorno;
}

/** \brief Modificar datos del barco
 *
 * \param pBarco Barco* Estructura donde se cargarán los datos
 * \return int Retorna 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_modificarBarco(Barco* pBarco)
{
	int retorno = -1;
	float bufferMetrosCubicos;
	float bufferPrecio;
	int opcionMenu;

	if(pBarco != NULL)
	{
		utn_getNumero(&opcionMenu, "\n¿Que valor desea modificar?\n1) Metros cúbicos\n2) Precio\n0) Cancelar", "\nError. Elija una de las opciones del menú\n", 0, 2);
		switch(opcionMenu)
		{
			case 1:
			{
				if(!utn_getDecimal(&bufferMetrosCubicos, "Ingrese los metros cúbicos del contenedor del barco: ", "\nError. La medida del contenedor tiene que ser mayor a 0 y menor o igual a 100 metros cúbicos\n", 1, 100))
				{
					barco_setMetrosCubicos(pBarco, bufferMetrosCubicos);
				}
				break;
			}
			case 2:
			{
				if(!utn_getDecimal(&bufferPrecio, "Ingrese el precio total del contenedor: ", "\nError. El precio tiene que ser mayor o igual a 0 y menor o igual a 1000000\n", 0, 1000000))
				{
					barco_setPrecio(pBarco, bufferPrecio);
				}
				break;
			}
			retorno = 0;
		}
	}

    return retorno;
}

/** \brief Listar los valores de la estructura Barco
 *
 * \param barco Barco Estructura que contiene los datos
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_listarBarco(Barco barco)
{
	int retorno = -1;
	int flagError;

	printf("Metros cúbicos\tPrecio del contenedor\n--------------------------------------\n");
	printf("\n%-14.4f | %.4f", barco_getMetrosCubicos(barco, &flagError), barco_getPrecio(barco, &flagError));
	retorno = 0;

    return retorno;
}

/** \brief Guarda los datos del transporte marítimo en el archivo "Barco.bin"
 *
 * \param pBarco Barco* Estructura donde se cargarán los datos
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_guardarBarco(Barco* pBarco)
{
	int retorno = -1;
	FILE* pFile;

	pFile = fopen("Barco.bin", "w+");

	if(pBarco != NULL && pFile != NULL)
	{
		fwrite(pBarco, sizeof(Barco), 1, pFile);

		fclose(pFile);
		printf("\nSe ha guardado correctamente!");
		retorno = 0;
	}

    return retorno;
}

//----------------Avion----------------

/** \brief Carga los datos de el transporte aéreo desde el archivo "Avion.bin"
 *
 * \param pAvion Avion* Estructura donde se cargarán los datos
 * \return int Retorna 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_cargarAvion(Avion* pAvion)
{
	int retorno = -1;
	FILE* pFile = NULL;

	pFile = fopen("Avion.bin", "rb");

	if(pAvion != NULL && pFile != NULL)
	{
		if(!parser_avion(pFile, pAvion))
		{
			fclose(pFile);
			//printf("\nSe ha cargado exitosamente!");
			retorno = 0;
		}
		/*else
		{
			printf("\nError. El archivo no pudo abrirse");
		}*/
	}

    return retorno;
}

/** \brief Alta del avion
 *
 * \param pAvion Avion* Estructura donde se cargarán los datos
 * \return int Retorna 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_altaAvion(Avion* pAvion)
{
	int retorno = -1;
	float bufferConstanteVolumetrica;
	float bufferPrecioPorKg;

	if(pAvion != NULL)
	{
		if(!utn_getDecimal(&bufferConstanteVolumetrica, "Ingrese el valor de la constante volumétrica: ", "\nError. La constante volumétrica tiene que ser mayor a 0 y menor a 1000000 metros cúbicos\n", 1, 1000000) &&
		   !utn_getDecimal(&bufferPrecioPorKg, "Ingrese el valor por Kg: ", "\nError. Ese número no es válido\n", 0, 1000000))
		{
			if(!avion_setConstanteVolumetrica(pAvion, bufferConstanteVolumetrica) &&
			   !avion_setPrecioPorKg(pAvion, bufferPrecioPorKg))
			{
				retorno = 0;
			}
		}
	}

    return retorno;
}

/** \brief Modificar datos del avion
 *
 * \param pAvion Avion* Estructura donde se cargarán los datos
 * \return int Retorna 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_modificarAvion(Avion* pAvion)
{
	int retorno = -1;
	float bufferConstanteVolumetrica;
	float bufferPrecioPorKg;
	int opcionMenu;

	if(pAvion != NULL)
	{
		utn_getNumero(&opcionMenu, "\n¿Que valor desea modificar?\n1) Constante volumétrica\n2) Precio por Kg\n0) Cancelar", "\nError. Elija una de las opciones del menú\n", 0, 2);
		switch(opcionMenu)
		{
			case 1:
			{
				if(!utn_getDecimal(&bufferConstanteVolumetrica, "Ingrese el valor de la nueva constante volumétrica: ", "\nError. La constante volumétrica tiene que ser mayor o igual a 0 y menor o igual a 100000\n", 0, 100000))
				{
					avion_setConstanteVolumetrica(pAvion, bufferConstanteVolumetrica);
				}
				break;
			}
			case 2:
			{
				if(!utn_getDecimal(&bufferPrecioPorKg, "Ingrese el precio por Kg: ", "\nError. El precio por Kg tiene que ser mayor o igual a 0 y menor o igual a 100000\n", 0, 100000))
				{
					avion_setPrecioPorKg(pAvion, bufferPrecioPorKg);
				}
				break;
			}
			retorno = 0;
		}
	}

    return retorno;
}

/** \brief Listar los valores de la estructura Avion
 *
 * \param avion Avion Estructura donde se cargarán los datos
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_listarAvion(Avion avion)
{
	int retorno = -1;
	int flagError;

	printf("Constante volumétrica\tPrecio por Kg\n--------------------------------------\n");
	printf("\n%-14.4f | %.4f", avion_getConstanteVolumetrica(avion, &flagError), avion_getPrecioPorKg(avion, &flagError));
	retorno = 0;

    return retorno;
}

/** \brief Guarda los datos del transporte aéreo en el archivo "Avion.bin"
 *
 * \param pAvion Avion* Estructura donde se cargarán los datos
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_guardarAvion(Avion* pAvion)
{
	int retorno = -1;
	FILE* pFile;

	pFile = fopen("Avion.bin", "w+");

	if(pAvion != NULL && pFile != NULL)
	{
		fwrite(pAvion, sizeof(Avion), 1, pFile);

		fclose(pFile);
		//printf("\nSe ha guardado correctamente!");
		retorno = 0;
	}

    return retorno;
}

//----------------ID----------------

void setearValorMaximoId(int id)
{
	contador = id;
}

int generarId(void)
{
	contador++;
	return contador;
}

/** \brief Busca la posición donde los IDs son iguales
 *
 * \param pListaAranceles LinkedList* Puntero a la lista
 * \param articuloIdPosicionArancelaria int ID del artículo que va a ser comparado
 * \return Retora la posición donde los IDs son iguales o -1 (ERROR) si no hay IDs iguales
 *
 */
int buscarIdArancel(LinkedList* pListaAranceles, int articuloIdPosicionArancelaria)
{
	int retorno = -1;
	Arancel* auxiliarArancel = NULL;

	if(pListaAranceles != NULL)
	{
		for(int i = 0; i < ll_len(pListaAranceles); i++)
		{
			auxiliarArancel = (Arancel*)ll_get(pListaAranceles, i);
			if(auxiliarArancel != NULL)
			{
				if(auxiliarArancel->idArancel == articuloIdPosicionArancelaria)
				{
					retorno = i;
					break;
				}
			}
		}
	}

	return retorno;
}

/** \brief Busca la posición donde los IDs son iguales
 *
 * \param pListaArticulos LinkedList* Puntero a la lista
 * \param idArancel int ID del arancel
 * \return Retora la posición donde los IDs son iguales o -1 (ERROR) si no hay IDs iguales
 *
 */
int buscarIdPosArancelaria(LinkedList* pListaArticulos, int idArancel)
{
	int retorno = -1;
	Articulo* auxiliarArticulo = NULL;

	if(pListaArticulos != NULL)
	{
		for(int i = 0; i < ll_len(pListaArticulos); i++)
		{
			auxiliarArticulo = (Articulo*)ll_get(pListaArticulos, i);
			if(auxiliarArticulo != NULL)
			{
				if(auxiliarArticulo->idPosicionArancelaria == idArancel)
				{
					retorno = i;
					break;
				}
			}
		}
	}

	return retorno;
}

//----------------Filtrar----------------

/** \brief Crea una lista filtrada según un criterio
 *
 * \param listaOriginal LinkedList* Puntero a la lista
 * \param funcionCriterio (*funcionCriterio) Puntero a la funcion criterio
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
LinkedList* filtrar(LinkedList* listaOriginal, int (*funcionCriterio)(void*))
{
	int limite;
	LinkedList* listaFiltrada = NULL;
	void* pElemento;

	if(listaOriginal != NULL)
	{
		listaFiltrada = ll_newLinkedList();
		limite = ll_len(listaOriginal);
		for(int i = 0; i < limite; i++)
		{
			pElemento = ll_get(listaOriginal, i);
			if(funcionCriterio(pElemento) == 1)
			{
				ll_add(listaFiltrada, pElemento);
			}
		}
	}

	return listaFiltrada;
}

/** \brief Itera la lista y utiliza a la funcion criterio en cada iteracion
 *
 * \param this LinkedList* Puntero a la lista
 * \param pFuncion (*pFuncion) Puntero a la funcion criterio
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int map(LinkedList* this, int(pFuncion)(void* pElemento))
{
	int retorno = -1;
	void* pElemento;

	if(this != NULL && pFuncion != NULL)
	{
		for(int i = 0; i<ll_len(this); i++)
		{
			pElemento = ll_get(this, i);
			pFuncion(pElemento);
		}
		retorno = 0;
	}

	return retorno;
}

/** \brief Muestra una lista de los articulos con FOB superiores a 200
 *
 * \param listaFiltrada LinkedList* Puntero a la lista
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int listarArticulosCaros(LinkedList* listaFiltrada)
{
	int retorno = -1;
	int limite;
	int flagError;
	Articulo* pArticulo = NULL;

	if(buscarElemento(listaFiltrada) == 1)
	{
		limite = ll_len(listaFiltrada);
		printf("\nCódigo\tDescripción\t\t\t\t\tPais\t\tFOB\t\tPeso Kg\t\tAlto cm\t\tAncho cm\tProfundidad cm\n"
			   "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		for(int i = 0; i < limite; i++)
		{
			pArticulo = (Articulo*)ll_get(listaFiltrada, i);
			printf("\n%-6s | %-44s | %-13s | %-13.2f | %-13.2f | %-13.2f | %-13.2f | %-21.2f",
					   articulo_getCodigo(pArticulo, &flagError), articulo_getDescripcion(pArticulo, &flagError), articulo_getPaisFabricacion(pArticulo, &flagError),
					   articulo_getFob(pArticulo, &flagError), articulo_getPesoKg(pArticulo, &flagError), articulo_getAltoCm(pArticulo, &flagError),
					   articulo_getAnchoCm(pArticulo, &flagError), articulo_getProfundoCm(pArticulo, &flagError));
		}

		retorno = 0;
	}
	else
	{
		printf("\nNo hay artículos para mostrar. Cargalos en la opción 1 del menú de artículos\n");
	}

	return retorno;
}

/** \brief Filtra articulos con FOB superiores a 200
 *
 * \param pElemento void* Puntero al elemento generico
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int funcionCriterioFiltrarFob(void* pElemento)
{
	int retorno = -1;
	Articulo* pArticulo;
	float fob;
	int flagError;

	pArticulo = (Articulo*)pElemento;

	fob = articulo_getFob(pArticulo, &flagError);
	if(!flagError)
	{
		retorno = 0;
		if(fob > 20)
		{
			retorno = 1;
		}
	}

	return retorno;
}

//----------------Funciones privadas----------------

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

/** \brief Busca el ID máximo
 *
 * \param pListaArticulos LinkedList* Puntero a la lista
 * \param idMaximo int*
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
static int buscarIdMaximo(LinkedList* pListaArticulos, int* idMaximo)
{
	int retorno = -1;
	int i;
	Articulo* auxiliarArticulo = NULL;
	int flagError;
	int auxiliarId;
	int auxiliarMaxId;

	if(pListaArticulos != NULL && idMaximo != NULL)
	{
		for(i = 0; i < ll_len(pListaArticulos); i++)
		{
			auxiliarArticulo = (Articulo*)ll_get(pListaArticulos, i);
			auxiliarId = articulo_getId(auxiliarArticulo, &flagError);
			if(!flagError && (i == 0 || auxiliarId > auxiliarMaxId))
			{
				auxiliarMaxId = auxiliarId;
			}
		}
		if(i == 0)
		{
			auxiliarMaxId = 0;
		}
		*idMaximo = auxiliarMaxId;
		retorno = 0;
	}

	return retorno;
}

/** \brief Busca la posición donde los IDs son iguales
 *
 * \param pListaArticulo LinkedList* Puntero a la lista
 * \param id int ID que se va a comparar con todos los IDs de los Articulos
 * \return Retora la posición donde los IDs son iguales o -1 (ERROR) si no hay IDs iguales
 *
 */
static int articulo_buscarPorId(LinkedList* pListaArticulo, int id)
{
	int respuesta = -1;
	int flagError;
	Articulo* auxiliarArticulo = NULL;

	if(pListaArticulo != NULL)
	{
		for(int i = 0; i < ll_len(pListaArticulo); i++)
		{
			auxiliarArticulo = ll_get(pListaArticulo, i);
			if(articulo_getId(auxiliarArticulo, &flagError) == id && !flagError)
			{
				respuesta = i;
				break;
			}
		}
	}

	return respuesta;
}

/** \brief Busca la posición donde los IDs son iguales
 *
 * \param pListaArancel LinkedList* Puntero a la lista
 * \param id int ID que se va a comparar con todos los IDs de los Articulos
 * \return Retora la posición donde los IDs son iguales o -1 (ERROR) si no hay IDs iguales
 *
 */
static int arancel_buscarPorId(LinkedList* pListaArancel, int id)
{
	int respuesta = -1;
	int flagError;
	Arancel* auxiliarArancel = NULL;

	if(pListaArancel != NULL)
	{
		for(int i = 0; i < ll_len(pListaArancel); i++)
		{
			auxiliarArancel = ll_get(pListaArancel, i);
			if(arancel_getIdArancel(auxiliarArancel, &flagError) == id && !flagError)
			{
				respuesta = i;
				break;
			}
		}
	}

	return respuesta;
}

/** \brief Ordena los artículos por el codigo
 *
 * \param elemento1 void* Puntero al primer elemento a comparar
 * \param elemento2 void* Puntero al segundo elemento a comparar
 * \return int Retora -1 si el código del primer elemento es menor o 1 si es mayor
 *
 */
static int ordenarPorCodigo(void* elemento1, void* elemento2)
{
	int retorno;
	Articulo* pArticulo1 = NULL;
	Articulo* pArticulo2 = NULL;
	char* codigo1;
	char* codigo2;
	int flagError;

	pArticulo1 = (Articulo*)elemento1;
	pArticulo2 = (Articulo*)elemento2;

	if(pArticulo1 != NULL && pArticulo2 != NULL)
	{
		codigo1 = articulo_getCodigo(pArticulo1, &flagError);
		codigo2 = articulo_getCodigo(pArticulo2, &flagError);

		if(strncmp(codigo1, codigo2, 128) < 0)
		{
			retorno = -1;
		}
		else if(strncmp(codigo1, codigo2, 128) > 0)
		{
			retorno = 1;
		}
	}

	return retorno;
}

/** \brief Ordena los artículos por descripcion
 *
 * \param elemento1 void* Puntero al primer elemento a comparar
 * \param elemento2 void* Puntero al segundo elemento a comparar
 * \return int Retora -1 si la descripción del primer elemento es menor o 1 si es mayor
 *
 */
static int ordenarPorDescripcion(void* elemento1, void* elemento2)
{
	int retorno;
	Articulo* pArticulo1 = NULL;
	Articulo* pArticulo2 = NULL;
	char* descripcion1;
	char* descripcion2;
	int flagError;

	pArticulo1 = (Articulo*)elemento1;
	pArticulo2 = (Articulo*)elemento2;

	if(pArticulo1 != NULL && pArticulo2 != NULL)
	{
		descripcion1 = articulo_getDescripcion(pArticulo1, &flagError);
		descripcion2 = articulo_getDescripcion(pArticulo2, &flagError);

		if(strncmp(descripcion1, descripcion2, 128) < 0)
		{
			retorno = -1;
		}
		else if(strncmp(descripcion1, descripcion2, 128) > 0)
		{
			retorno = 1;
		}
	}

	return retorno;
}

/** \brief Ordena los artículos por país
 *
 * \param elemento1 void* Puntero al primer elemento a comparar
 * \param elemento2 void* Puntero al segundo elemento a comparar
 * \return int Retora -1 si la país del primer elemento es menor o 1 si es mayor
 *
 */
static int ordenarPorPais(void* elemento1, void* elemento2)
{
	int retorno;
	Articulo* pArticulo1 = NULL;
	Articulo* pArticulo2 = NULL;
	char* pais1;
	char* pais2;
	int flagError;

	pArticulo1 = (Articulo*)elemento1;
	pArticulo2 = (Articulo*)elemento2;

	if(pArticulo1 != NULL && pArticulo2 != NULL)
	{
		pais1 = articulo_getPaisFabricacion(pArticulo1, &flagError);
		pais2 = articulo_getPaisFabricacion(pArticulo2, &flagError);

		if(strncmp(pais1, pais2, 128) < 0)
		{
			retorno = -1;
		}
		else if(strncmp(pais1, pais2, 128) > 0)
		{
			retorno = 1;
		}
	}

	return retorno;
}

/** \brief Ordena los artículos por el valor FOB
 *
 * \param elemento1 void* Puntero al primer elemento a comparar
 * \param elemento2 void* Puntero al segundo elemento a comparar
 * \return int Retora -1 si el valor FOB del primer elemento es menor o 1 si es mayor
 *
 */
static int ordenarPorFob(void* elemento1, void* elemento2)
{
	int retorno;
	Articulo* pArticulo1 = NULL;
	Articulo* pArticulo2 = NULL;
	float fob1;
	float fob2;
	int flagError;

	pArticulo1 = (Articulo*)elemento1;
	pArticulo2 = (Articulo*)elemento2;

	if(pArticulo1 != NULL && pArticulo2 != NULL)
	{
		fob1 = articulo_getFob(pArticulo1, &flagError);
		fob2 = articulo_getFob(pArticulo2, &flagError);

		if(fob1 < fob2)
		{
			retorno = -1;
		}
		else if(fob1 > fob2)
		{
			retorno = 1;
		}
	}

	return retorno;
}

/** \brief Ordena los artículos por el peso en Kg
 *
 * \param elemento1 void* Puntero al primer elemento a comparar
 * \param elemento2 void* Puntero al segundo elemento a comparar
 * \return int Retora -1 si el peso en Kg del primer elemento es menor o 1 si es mayor
 *
 */
static int ordenarPorPesoKg(void* elemento1, void* elemento2)
{
	int retorno;
	Articulo* pArticulo1 = NULL;
	Articulo* pArticulo2 = NULL;
	float peso1;
	float peso2;
	int flagError;

	pArticulo1 = (Articulo*)elemento1;
	pArticulo2 = (Articulo*)elemento2;

	if(pArticulo1 != NULL && pArticulo2 != NULL)
	{
		peso1 = articulo_getPesoKg(pArticulo1, &flagError);
		peso2 = articulo_getPesoKg(pArticulo2, &flagError);

		if(peso1 < peso2)
		{
			retorno = -1;
		}
		else if(peso1 > peso2)
		{
			retorno = 1;
		}
	}

	return retorno;
}

/** \brief Ordena los artículos por el alto en cm
 *
 * \param elemento1 void* Puntero al primer elemento a comparar
 * \param elemento2 void* Puntero al segundo elemento a comparar
 * \return int Retora -1 si el alto en cm del primer elemento es menor o 1 si es mayor
 *
 */
static int ordenarPorAltoCm(void* elemento1, void* elemento2)
{
	int retorno;
	Articulo* pArticulo1 = NULL;
	Articulo* pArticulo2 = NULL;
	float alto1;
	float alto2;
	int flagError;

	pArticulo1 = (Articulo*)elemento1;
	pArticulo2 = (Articulo*)elemento2;

	if(pArticulo1 != NULL && pArticulo2 != NULL)
	{
		alto1 = articulo_getAltoCm(pArticulo1, &flagError);
		alto2 = articulo_getAltoCm(pArticulo2, &flagError);

		if(alto1 < alto2)
		{
			retorno = -1;
		}
		else if(alto1 > alto2)
		{
			retorno = 1;
		}
	}

	return retorno;
}

/** \brief Ordena los artículos por el ancho en cm
 *
 * \param elemento1 void* Puntero al primer elemento a comparar
 * \param elemento2 void* Puntero al segundo elemento a comparar
 * \return int Retora -1 si el ancho en cm del primer elemento es menor o 1 si es mayor
 *
 */
static int ordenarPorAnchoCm(void* elemento1, void* elemento2)
{
	int retorno;
	Articulo* pArticulo1 = NULL;
	Articulo* pArticulo2 = NULL;
	float ancho1;
	float ancho2;
	int flagError;

	pArticulo1 = (Articulo*)elemento1;
	pArticulo2 = (Articulo*)elemento2;

	if(pArticulo1 != NULL && pArticulo2 != NULL)
	{
		ancho1 = articulo_getAnchoCm(pArticulo1, &flagError);
		ancho2 = articulo_getAnchoCm(pArticulo2, &flagError);

		if(ancho1 < ancho2)
		{
			retorno = -1;
		}
		else if(ancho1 > ancho2)
		{
			retorno = 1;
		}
	}

	return retorno;
}

/** \brief Ordena los artículos por el profundo en cm
 *
 * \param elemento1 void* Puntero al primer elemento a comparar
 * \param elemento2 void* Puntero al segundo elemento a comparar
 * \return int Retora -1 si el profundo en cm del primer elemento es menor o 1 si es mayor
 *
 */
static int ordenarPorProfundoCm(void* elemento1, void* elemento2)
{
	int retorno;
	Articulo* pArticulo1 = NULL;
	Articulo* pArticulo2 = NULL;
	float profundo1;
	float profundo2;
	int flagError;

	pArticulo1 = (Articulo*)elemento1;
	pArticulo2 = (Articulo*)elemento2;

	if(pArticulo1 != NULL && pArticulo2 != NULL)
	{
		profundo1 = articulo_getProfundoCm(pArticulo1, &flagError);
		profundo2 = articulo_getProfundoCm(pArticulo2, &flagError);

		if(profundo1 < profundo2)
		{
			retorno = -1;
		}
		else if(profundo1 > profundo2)
		{
			retorno = 1;
		}
	}

	return retorno;
}

/** \brief Ordena los aranceles por nomenclatura
 *
 * \param elemento1 void* Puntero al primer elemento a comparar
 * \param elemento2 void* Puntero al segundo elemento a comparar
 * \return int Retora -1 si la nomenclatura del primer elemento es menor o 1 si es mayor
 *
 */
static int ordenarPorNomenclatura(void* elemento1, void* elemento2)
{
	int retorno;
	Arancel* pArancel1 = NULL;
	Arancel* pArancel2 = NULL;
	char* nomenclatura1;
	char* nomenclatura2;
	int flagError;

	pArancel1 = (Arancel*)elemento1;
	pArancel2 = (Arancel*)elemento2;

	if(pArancel1 != NULL && pArancel2 != NULL)
	{
		nomenclatura1 = arancel_getNomenclatura(pArancel1, &flagError);
		nomenclatura2 = arancel_getNomenclatura(pArancel2, &flagError);

		if(strncmp(nomenclatura1, nomenclatura2, 128) < 0)
		{
			retorno = -1;
		}
		else if(strncmp(nomenclatura1, nomenclatura2, 128) > 0)
		{
			retorno = 1;
		}
	}

	return retorno;
}

/** \brief Ordena los aranceles por el porcentaje del seguro
 *
 * \param elemento1 void* Puntero al primer elemento a comparar
 * \param elemento2 void* Puntero al segundo elemento a comparar
 * \return int Retora -1 si el porcentaje del seguro del primer elemento es menor o 1 si es mayor
 *
 */
static int ordenarPorSeguro(void* elemento1, void* elemento2)
{
	int retorno;
	Arancel* pArancel1 = NULL;
	Arancel* pArancel2 = NULL;
	float seguro1;
	float seguro2;
	int flagError;

	pArancel1 = (Arancel*)elemento1;
	pArancel2 = (Arancel*)elemento2;

	if(pArancel1 != NULL && pArancel2 != NULL)
	{
		seguro1 = arancel_getPorcentajeSeguro(pArancel1, &flagError);
		seguro2 = arancel_getPorcentajeSeguro(pArancel2, &flagError);

		if(seguro1 < seguro2)
		{
			retorno = -1;
		}
		else if(seguro1 > seguro2)
		{
			retorno = 1;
		}
	}

	return retorno;
}

/** \brief Ordena los aranceles por el porcentaje de la importación
 *
 * \param elemento1 void* Puntero al primer elemento a comparar
 * \param elemento2 void* Puntero al segundo elemento a comparar
 * \return int Retora -1 si el porcentaje de la impórtación del primer elemento es menor o 1 si es mayor
 *
 */
static int ordenarPorImportacion(void* elemento1, void* elemento2)
{
	int retorno;
	Arancel* pArancel1 = NULL;
	Arancel* pArancel2 = NULL;
	float importacion1;
	float importacion2;
	int flagError;

	pArancel1 = (Arancel*)elemento1;
	pArancel2 = (Arancel*)elemento2;

	if(pArancel1 != NULL && pArancel2 != NULL)
	{
		importacion1 = arancel_getPorcentajeImportacion(pArancel1, &flagError);
		importacion2 = arancel_getPorcentajeImportacion(pArancel2, &flagError);

		if(importacion1 < importacion2)
		{
			retorno = -1;
		}
		else if(importacion1 > importacion2)
		{
			retorno = 1;
		}
	}

	return retorno;
}

/** \brief Ordena los aranceles por el porcentaje de la tasa estadística
 *
 * \param elemento1 void* Puntero al primer elemento a comparar
 * \param elemento2 void* Puntero al segundo elemento a comparar
 * \return int Retora -1 si el porcentaje de la tasa estadística del primer elemento es menor o 1 si es mayor
 *
 */
static int ordenarPorTasaEstadistica(void* elemento1, void* elemento2)
{
	int retorno;
	Arancel* pArancel1 = NULL;
	Arancel* pArancel2 = NULL;
	float tasaEstadistica1;
	float tasaEstadistica2;
	int flagError;

	pArancel1 = (Arancel*)elemento1;
	pArancel2 = (Arancel*)elemento2;

	if(pArancel1 != NULL && pArancel2 != NULL)
	{
		tasaEstadistica1 = arancel_getPorcentajeTasaEstadistica(pArancel1, &flagError);
		tasaEstadistica2 = arancel_getPorcentajeTasaEstadistica(pArancel2, &flagError);

		if(tasaEstadistica1 < tasaEstadistica2)
		{
			retorno = -1;
		}
		else if(tasaEstadistica1 > tasaEstadistica2)
		{
			retorno = 1;
		}
	}

	return retorno;
}

/** \brief Ordena los aranceles por el tipo de licencia
 *
 * \param elemento1 void* Puntero al primer elemento a comparar
 * \param elemento2 void* Puntero al segundo elemento a comparar
 * \return int Retora -1 si el tipo de licencia del primer elemento es menor o 1 si es mayor
 *
 */
static int ordenarPorLicencia(void* elemento1, void* elemento2)
{
	int retorno;
	Arancel* pArancel1 = NULL;
	Arancel* pArancel2 = NULL;
	char* tipoLicencia1;
	char* tipoLicencia2;
	int flagError;

	pArancel1 = (Arancel*)elemento1;
	pArancel2 = (Arancel*)elemento2;

	if(pArancel1 != NULL && pArancel2 != NULL)
	{
		tipoLicencia1 = arancel_getTipoLicencia(pArancel1, &flagError);
		tipoLicencia2 = arancel_getTipoLicencia(pArancel2, &flagError);

		if(strncmp(tipoLicencia1, tipoLicencia2, 128) < 0)
		{
			retorno = -1;
		}
		else if(strncmp(tipoLicencia1, tipoLicencia2, 128) > 0)
		{
			retorno = 1;
		}
	}

	return retorno;
}
