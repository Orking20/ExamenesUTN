/*
 ============================================================================
 Name        : Examen1.c
 Author      : Mateo Luchetti Capalbo
 Version     :
 Copyright   : Your copyright notice
 Description : Primer exámen de Programación y Laboratorio 1
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "Contratacion.h"
#include "Pantalla.h"
#include "Relacion.h"
#define CANT_PANTALLAS 100
#define CANT_CONTRATACIONES 1000

int main(void)
{
	Pantalla arrayPantallas[CANT_PANTALLAS];
	Contratacion arrayContrataciones[CANT_CONTRATACIONES];
	int opcionMenu;

	inicializarPantalla(arrayPantallas, CANT_PANTALLAS);
	inicializarContratacion(arrayContrataciones, CANT_CONTRATACIONES);

	do
	{
		utn_getNumero(&opcionMenu, "\n1) Cargar pantalla\n2) Modificar pantalla\n3) Borrar pantalla\n4) Contratar publicidad\n5) Modificar condiciones de publicacion\n6) Cancelar contratación\n7) Listar pagos\n8) Listar contrataciones\n9) Listar pantallas\n10) Informe\n11) Salir\n", "Error. Ingrese un número de los del menú\n", 1, 11, 3);

		switch(opcionMenu)
		{
			case 1:
			{
				altaPantalla(arrayPantallas, buscarIndiceVacioPantalla(arrayPantallas, CANT_PANTALLAS));
				break;
			}
			case 2:
			{
				modificarPantalla(arrayPantallas, CANT_PANTALLAS);

				break;
			}
			case 3:
			{
				bajaPantalla(arrayPantallas, arrayContrataciones, CANT_PANTALLAS);
				break;
			}
			case 4:
			{
				altaContratacion(arrayContrataciones, arrayPantallas, buscarIndiceVacioContratacion(arrayContrataciones, CANT_CONTRATACIONES), CANT_PANTALLAS);
				break;
			}
			case 5:
			{
				modificarContratacion(arrayContrataciones, arrayPantallas, CANT_CONTRATACIONES);
				break;
			}
			case 6:
			{
				borrarContratacion(arrayContrataciones, arrayPantallas, CANT_CONTRATACIONES);
				break;
			}
			case 7:
			{
				consultaFacturacion(arrayContrataciones, arrayPantallas, CANT_CONTRATACIONES);
				break;
			}
			case 8:
			{
				mostrarContratacion(arrayContrataciones, arrayPantallas, CANT_CONTRATACIONES);
				//listarContrataciones();
				break;
			}
			case 9:
			{
				mostrarPantalla(arrayPantallas, CANT_PANTALLAS);
				break;
			}
			case 10:
			{
				//Informe();
				break;
			}
		}
	}while(opcionMenu != 11);

	return EXIT_SUCCESS;
}
