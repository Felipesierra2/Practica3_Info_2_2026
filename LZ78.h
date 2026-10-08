#ifndef LZ78_H
#define LZ78_H
#include "structs.h"

const int BYTES_POR_PAR = 5;

Salida* comprimirLZ78(const char* texto, int tam, int& cantidadSalida);

char* descomprimirLZ78(const Salida* salida, int cantidadSalida, int& tamSalida);

char* serializarSalida(const Salida* salida, int cantidadSalida, int& tamBytes);
Salida* deserializarSalida(const char* bytes, int tamBytes, int& cantidadSalida);

void liberarSalida(Salida*& salida, int& cantidad);

#endif

