/*
 * parser.h
 *
 *  Created on: 17 jun. 2021
 *      Author: mateo
 */

#ifndef PARSER_H_
#define PARSER_H_

int parser_articulo(FILE* pFile, LinkedList* pArrayListArticulo);
int parser_arancel(FILE* pFile, LinkedList* pListaArancel);
int parser_barco(FILE* pFile, Barco* pBarco);
int parser_avion(FILE* pFile, Avion* pAvion);

#endif /* PARSER_H_ */
