#ifndef ARCHIVOS_H
#define ARCHIVOS_H

char* leerArchivo(const char* nombre, int& tam);

void escribirArchivo(const char* nombre, const char* datos, int tam);

bool sonIguales(const char* a, int tamA, const char* b, int tamB);

#endif
