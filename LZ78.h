#ifndef LZ78_H
#define LZ78_H

#include "structs.h"
char* agregarCaracter(char* frase, char caracter);
bool compararFrases(char* frase1, char* frase2);
int buscarEnDiccionario(Entrada* diccionario, int cantidad, char* fraseActual);
char* copiarFrase(char* frase);
void agregarAlDiccionario(Entrada*& diccionario, int& cantidad, char* frase);
#endif // LZ78_H
