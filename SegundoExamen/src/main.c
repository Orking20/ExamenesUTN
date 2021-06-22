/*
 ============================================================================
 Name        : SegundoExamen.c
 Author      : Mateo Luchetti Capalbo
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "../inc/utn.h"
#include "../inc/LinkedList.h"
#include "../inc/menu.h"
#include "../inc/Controller.h"
#include "../inc/Informes.h"

int main(void)
{
	int opcionMenu;
	LinkedList* listaArticulos = ll_newLinkedList();
	LinkedList* listaAranceles = ll_newLinkedList();
	Barco barco;
	Avion avion;

	controller_cargarArticulos(listaArticulos);
	controller_cargarArancel(listaAranceles);
	controller_cargarBarco(&barco);
	controller_cargarAvion(&avion);

	informe_listarCostoArgentino(listaArticulos, listaAranceles, barco, avion);

	do{
		utn_getNumero(&opcionMenu, "\n\n1) Artículos"
								   "\n2) Posición arancelaria"
								   "\n3) Transporte marítimo"
								   "\n4) Transporte aéreo"
								   "\n5) Mostrar costo argentino"
								   "\n0) Salir", "\nError. Ingrese una de las opciones del menú", 0, 5);

		switch(opcionMenu)
		{
			case 1:
			{
				opcionArticulos(listaArticulos, listaAranceles);
				break;
			}
			case 2:
			{
				opcionPosicionArancelaria(listaAranceles, listaArticulos);
				break;
			}
			case 3:
			{
				opcionTransporteMaritimo(barco);
				break;
			}
			case 4:
			{
				opcionTransporteAereo(avion);
				break;
			}
			case 5:
			{
				opcionInformes(listaArticulos, listaAranceles, barco, avion);
				break;
			}
		}
	}while(opcionMenu != 0);

	return EXIT_SUCCESS;
}
