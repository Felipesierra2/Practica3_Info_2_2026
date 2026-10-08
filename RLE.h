#ifndef RLE_H
#define RLE_H

char* comprimirRLE(const char* texto, int tam, int& tamSalida);
char* descomprimirRLE(const char* datos, int tam, int& tamSalida);

bool verificarRLE(const char* texto, int tam);

#endif
