/*
 ============================================================================
 Name        : PrimerExamen.c
 Author      : Mateo Luchetti Capalbo
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Cliente.h"
#include "Compra.h"
#include "Relacion.h"
#include "Informes.h"
#include "utn.h"
#define CANT_CLIENTES 100
#define CANT_COMPRAS 1000

int main(void)
{
	int opcionMenu;
	Cliente arrayClientes[CANT_CLIENTES];
	Compra arrayCompras[CANT_COMPRAS];

	cliente_inicializar(arrayClientes, CANT_CLIENTES);
	compra_inicializar(arrayCompras, CANT_COMPRAS);
	//cliente_harcodeo(arrayClientes, 3);
	//compra_harcodeo(arrayCompras, 7);

	do
	{
		utn_getNumero(&opcionMenu,  "\n\n1) Alta cliente\n"
									"2) Modificar datos de cliente\n"
									"3) Baja cliente\n"
									"4) Realizar compra\n"
									"5) Pagar compra\n"
									"6) Cancelar compra\n"
									"7) Mostrar clientes\n"
									"8) Informe\n"
									"0) Salir\n",
									"\nError. Elija una de las opciónes del menú escribiendo el número correspondiente", 0, 8, 3);

		switch(opcionMenu)
		{
			case 1:
			{
				cliente_alta(arrayClientes, cliente_buscarIndiceVacio(arrayClientes, CANT_CLIENTES));
				break;
			}
			case 2:
			{
				cliente_modificar(arrayClientes, CANT_CLIENTES);
				break;
			}
			case 3:
			{
				cliente_baja(arrayClientes, arrayCompras, CANT_CLIENTES, CANT_COMPRAS);
				break;
			}
			case 4:
			{
				compra_alta(arrayCompras, arrayClientes, CANT_COMPRAS, CANT_CLIENTES, compra_buscarIndiceVacio(arrayCompras, CANT_COMPRAS));
				break;
			}
			case 5:
			{
				compra_pagarImporte(arrayCompras, arrayClientes, CANT_COMPRAS, CANT_CLIENTES);
				break;
			}
			case 6:
			{
				compra_baja(arrayCompras, arrayClientes, CANT_COMPRAS, CANT_CLIENTES);
				break;
			}
			case 7:
			{
				info_mostrarTodo(arrayClientes, arrayCompras, CANT_CLIENTES, CANT_COMPRAS);
				break;
			}
			case 8:
			{
				info_mostrarInformes(arrayCompras, CANT_COMPRAS);
				break;
			}
		}
	}while(opcionMenu != 0);

	return EXIT_SUCCESS;
}
