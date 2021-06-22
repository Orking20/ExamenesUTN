/*
 * menu.c
 *
 *  Created on: 16 jun. 2021
 *      Author: mateo
 */


#include <stdio.h>
#include <stdlib.h>
#include "../inc/LinkedList.h"
#include "../inc/Controller.h"
#include "../inc/utn.h"
#include "../inc/Calculos.h"
#include "../inc/Informes.h"

void opcionArticulos(LinkedList* pListaArticulos, LinkedList* pListaAranceles)
{
	int opcionMenu;

	do
	{
		printf("\n\n--------Artículos--------");
		opcionMenu = 0;
		utn_getNumero(&opcionMenu, "\n1) Cargar"
								   "\n2) Modificar"
								   "\n3) Eliminar"
								   "\n4) Mostrar"
								   "\n5) Mostrar ordenados"
								   "\n0) Volver", "\nError. Ingrese una de las opciones del menú", 0, 5);
		switch(opcionMenu)
		{
			case 1:
			{
				controller_altaArticulo(pListaArticulos, pListaAranceles);
				controller_guardarArticulos(pListaArticulos, pListaAranceles);
				break;
			}
			case 2:
			{
				controller_modificarArticulo(pListaArticulos, pListaAranceles);
				controller_guardarArticulos(pListaArticulos, pListaAranceles);
				break;
			}
			case 3:
			{
				controller_bajaArticulo(pListaArticulos, pListaAranceles);
				controller_guardarArticulos(pListaArticulos, pListaAranceles);
				break;
			}
			case 4:
			{
				controller_listarArticulo(pListaArticulos, pListaAranceles);
				break;
			}
			case 5:
			{
				controller_ordenarArticulos(pListaArticulos, pListaAranceles);
				break;
			}
		}
	}while(opcionMenu != 0);
}

void opcionPosicionArancelaria(LinkedList* pListaArancel, LinkedList* pListaArticulo)
{
	int opcionMenu;

	do
	{
		printf("\n\n--------Posición arancelaria--------");
		utn_getNumero(&opcionMenu, "\n1) Cargar"
								   "\n2) Modificar"
								   "\n3) Eliminar"
								   "\n4) Mostrar"
								   "\n5) Mostrar ordenados"
								   "\n0) Volver", "\nError. Ingrese una de las opciones del menú", 0, 5);
		switch(opcionMenu)
		{
			case 1:
			{
				controller_altaArancel(pListaArancel);
				controller_guardarArancel(pListaArancel);
				break;
			}
			case 2:
			{
				controller_modificarArancel(pListaArancel);
				controller_guardarArancel(pListaArancel);
				break;
			}
			case 3:
			{
				controller_bajaArancel(pListaArancel, pListaArticulo);
				controller_guardarArancel(pListaArancel);
				controller_guardarArticulos(pListaArticulo, pListaArancel);
				break;
			}
			case 4:
			{
				controller_listarArancel(pListaArancel);
				break;
			}
			case 5:
			{
				controller_ordenarAranceles(pListaArancel);
				break;
			}
		}
	}while(opcionMenu != 0);
}

void opcionTransporteMaritimo(Barco barco)
{
	int opcionMenu;

	do
	{
		printf("\n\n--------Transporte marítimo--------");
		utn_getNumero(&opcionMenu, "\n1) Cargar"
								   "\n2) Modificar"
								   "\n3) Mostrar"
								   "\n0) Volver", "\nError. Ingrese una de las opciones del menú", 0, 3);
		switch(opcionMenu)
		{
			case 1:
			{
				controller_altaBarco(&barco);
				controller_guardarBarco(&barco);
				break;
			}
			case 2:
			{
				controller_modificarBarco(&barco);
				controller_guardarBarco(&barco);
				break;
			}
			case 3:
			{
				controller_listarBarco(barco);
				break;
			}
		}
	}while(opcionMenu != 0);
}

void opcionTransporteAereo(Avion avion)
{
	int opcionMenu;

	do
	{
		printf("\n\n--------Transporte aéreo--------");
		utn_getNumero(&opcionMenu, "\n1) Cargar"
								   "\n2) Modificar"
								   "\n3) Mostrar"
								   "\n0) Volver", "\nError. Ingrese una de las opciones del menú", 0, 3);
		switch(opcionMenu)
		{
			case 1:
			{
				controller_altaAvion(&avion);
				controller_guardarAvion(&avion);
				break;
			}
			case 2:
			{
				controller_modificarAvion(&avion);
				controller_guardarAvion(&avion);
				break;
			}
			case 3:
			{
				controller_listarAvion(avion);
				break;
			}
		}
	}while(opcionMenu != 0);
}

void opcionInformes(LinkedList* pListaArticulos, LinkedList* pListaAranceles, Barco barco, Avion avion)
{
	int opcionMenu;

	do
	{
		printf("\n\n--------Informes--------");
		utn_getNumero(&opcionMenu, "\n1) Costo argentino de todos los artículos"
								   "\n2) Listar articulos con FOB superior a 200"
								   "\n0) Volver", "\nError. Ingrese una de las opciones del menú", 0, 2);
		switch(opcionMenu)
		{
			case 1:
			{
				informe_listarCostoArgentino(pListaArticulos, pListaAranceles, barco, avion);
				break;
			}
			case 2:
			{
				controller_listarArticulosFobAltos(pListaArticulos);
				break;
			}
			case 3:
			{
				break;
			}
		}
	}while(opcionMenu != 0);
}
