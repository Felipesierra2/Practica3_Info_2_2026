#ifndef ENCRIPTACION_H
#define ENCRIPTACION_H

unsigned char rotarIzquierda(unsigned char byte, int n);
unsigned char rotarDerecha(unsigned char byte, int n);

unsigned char encriptarByte(unsigned char byte, int n, unsigned char K);
unsigned char desencriptarByte(unsigned char byte, int n, unsigned char K);

void encriptarDatos(char* datos, int tam, int n, unsigned char K);
void desencriptarDatos(char* datos, int tam, int n, unsigned char K);

#endif

