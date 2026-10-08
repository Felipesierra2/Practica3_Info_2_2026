#include "Encriptacion.h"
#include "Excepciones.h"

static void validarRotacion(int n){
    if(n <= 0 || n >= 8){
        lanzarError(PARAMETRO_INVALIDO, "La rotacion n debe cumplir 0 < n < 8");
    }
}

unsigned char rotarIzquierda(unsigned char byte, int n){
    validarRotacion(n);
    // Los bits que salen por la izquierda reentran por la derecha
    return (unsigned char)((byte << n) | (byte >> (8 - n)));
}

unsigned char rotarDerecha(unsigned char byte, int n){
    validarRotacion(n);
    return (unsigned char)((byte >> n) | (byte << (8 - n)));
}

unsigned char encriptarByte(unsigned char byte, int n, unsigned char K){
    unsigned char rotado = rotarIzquierda(byte, n);
    return rotado ^ K;
}

unsigned char desencriptarByte(unsigned char byte, int n, unsigned char K){
    // A XOR K XOR K = A, asi que primero se deshace el XOR
    unsigned char sinXor = byte ^ K;
    return rotarDerecha(sinXor, n);
}

void encriptarDatos(char* datos, int tam, int n, unsigned char K){
    if(tam < 0 || (tam > 0 && datos == nullptr)){
        lanzarError(PARAMETRO_INVALIDO, "Encriptacion: datos invalidos");
    }
    validarRotacion(n);

    for(int i = 0; i < tam; i++){
        datos[i] = (char)encriptarByte((unsigned char)datos[i], n, K);
    }
}

void desencriptarDatos(char* datos, int tam, int n, unsigned char K){
    if(tam < 0 || (tam > 0 && datos == nullptr)){
        lanzarError(PARAMETRO_INVALIDO, "Desencriptacion: datos invalidos");
    }
    validarRotacion(n);

    for(int i = 0; i < tam; i++){
        datos[i] = (char)desencriptarByte((unsigned char)datos[i], n, K);
    }
}
