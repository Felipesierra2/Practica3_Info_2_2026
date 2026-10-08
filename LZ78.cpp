#include "LZ78.h"
#include "Excepciones.h"
#include "structs.h"

static int buscarEnDiccionario(const Entrada* diccionario, int cantidad, int prefijo, char caracter){
    for(int i = 0; i < cantidad; i++){
        if(diccionario[i].prefijo == prefijo && diccionario[i].caracter == caracter){
            return i + 1;
        }
    }
    return 0;
}

static void agregarEntrada(Entrada*& diccionario, int& cantidad, int& capacidad, int prefijo, char caracter){
    if(cantidad == capacidad){
        int nuevaCapacidad = (capacidad == 0) ? 16 : capacidad * 2;
        Entrada* copia = new Entrada[nuevaCapacidad];

        for(int i = 0; i < cantidad; i++){
            copia[i] = diccionario[i];
        }

        delete[] diccionario;
        diccionario = copia;
        capacidad = nuevaCapacidad;
    }

    diccionario[cantidad].prefijo = prefijo;
    diccionario[cantidad].caracter = caracter;
    cantidad++;
}

static void agregarSalida(Salida*& salida, int& cantidad, int& capacidad, int indice, char frase){
    if(cantidad == capacidad){
        int nuevaCapacidad = (capacidad == 0) ? 16 : capacidad * 2;
        Salida* copia = new Salida[nuevaCapacidad];

        for(int i = 0; i < cantidad; i++){
            copia[i] = salida[i];
        }

        delete[] salida;
        salida = copia;
        capacidad = nuevaCapacidad;
    }

    salida[cantidad].indice = indice;
    salida[cantidad].frase = frase;
    cantidad++;
}

void liberarSalida(Salida*& salida, int& cantidad){
    delete[] salida;
    salida = nullptr;
    cantidad = 0;
}

Salida* comprimirLZ78(const char* texto, int tam, int& cantidadSalida){
    if(texto == nullptr || tam < 0){
        lanzarError(PARAMETRO_INVALIDO, "LZ78: texto nulo o tamano negativo");
    }

    for(int i = 0; i < tam; i++){
        if(texto[i] == '\0'){
            lanzarError(PARAMETRO_INVALIDO, "LZ78: el texto contiene el byte 0");
        }
    }

    Entrada* diccionario = nullptr;
    int cantidadDic = 0;
    int capacidadDic = 0;

    Salida* salida = nullptr;
    cantidadSalida = 0;
    int capacidadSalida = 0;

    int actual = 0;

    for(int i = 0; i < tam; i++){
        char c = texto[i];
        int encontrada = buscarEnDiccionario(diccionario, cantidadDic, actual, c);

        if(encontrada != 0){
            actual = encontrada;
        }else{
            agregarSalida(salida, cantidadSalida, capacidadSalida, actual, c);
            agregarEntrada(diccionario, cantidadDic, capacidadDic, actual, c);
            actual = 0;
        }
    }

    if(actual != 0){
        agregarSalida(salida, cantidadSalida, capacidadSalida, actual, '\0');
    }

    delete[] diccionario;
    return salida;
}

static void validarSalida(const Salida* salida, int cantidadSalida){
    if(cantidadSalida < 0 || (cantidadSalida > 0 && salida == nullptr)){
        lanzarError(PARAMETRO_INVALIDO, "LZ78: salida invalida");
    }

    int frasesConocidas = 0;

    for(int k = 0; k < cantidadSalida; k++){
        if(salida[k].indice < 0 || salida[k].indice > frasesConocidas){
            lanzarError(FORMATO_INVALIDO, "LZ78: indice que no existe en el diccionario");
        }

        if(salida[k].frase == '\0'){
            if(k != cantidadSalida - 1){
                lanzarError(FORMATO_INVALIDO, "LZ78: par sin caracter que no es el ultimo");
            }
        }else{
            frasesConocidas++;
        }
    }
}

char* descomprimirLZ78(const Salida* salida, int cantidadSalida, int& tamSalida){
    validarSalida(salida, cantidadSalida);

    Entrada* diccionario = new Entrada[cantidadSalida + 1];
    int* longitud = new int[cantidadSalida + 1];
    int cantidadDic = 0;
    longitud[0] = 0;
    tamSalida = 0;

    for(int k = 0; k < cantidadSalida; k++){
        int largo = longitud[salida[k].indice];

        if(salida[k].frase != '\0'){
            largo++;
            diccionario[cantidadDic].prefijo = salida[k].indice;
            diccionario[cantidadDic].caracter = salida[k].frase;
            cantidadDic++;
            longitud[cantidadDic] = largo;
        }

        tamSalida += largo;
    }

    char* texto = new char[tamSalida + 1];
    int posicion = 0;

    for(int k = 0; k < cantidadSalida; k++){
        int largo = longitud[salida[k].indice];
        if(salida[k].frase != '\0') largo++;

        int fin = posicion + largo - 1;

        if(salida[k].frase != '\0'){
            texto[fin] = salida[k].frase;
            fin--;
        }

        int frase = salida[k].indice;
        while(frase != 0){
            texto[fin] = diccionario[frase - 1].caracter;
            fin--;
            frase = diccionario[frase - 1].prefijo;
        }

        posicion += largo;
    }

    texto[tamSalida] = '\0';

    delete[] diccionario;
    delete[] longitud;
    return texto;
}

char* serializarSalida(const Salida* salida, int cantidadSalida, int& tamBytes){
    if(cantidadSalida < 0 || (cantidadSalida > 0 && salida == nullptr)){
        lanzarError(PARAMETRO_INVALIDO, "LZ78: salida invalida al serializar");
    }

    tamBytes = cantidadSalida * BYTES_POR_PAR;
    char* bytes = new char[tamBytes + 1];

    for(int i = 0; i < cantidadSalida; i++){
        int base = i * BYTES_POR_PAR;
        unsigned int indice = (unsigned int)salida[i].indice;

        bytes[base]     = (char)((indice >> 24) & 0xFF);
        bytes[base + 1] = (char)((indice >> 16) & 0xFF);
        bytes[base + 2] = (char)((indice >> 8) & 0xFF);
        bytes[base + 3] = (char)(indice & 0xFF);
        bytes[base + 4] = salida[i].frase;
    }

    bytes[tamBytes] = '\0';
    return bytes;
}

Salida* deserializarSalida(const char* bytes, int tamBytes, int& cantidadSalida){
    if(tamBytes < 0 || (tamBytes > 0 && bytes == nullptr)){
        lanzarError(PARAMETRO_INVALIDO, "LZ78: bytes invalidos");
    }

    if(tamBytes % BYTES_POR_PAR != 0){
        lanzarError(FORMATO_INVALIDO, "LZ78: el tamano no es multiplo de 5 bytes");
    }

    cantidadSalida = tamBytes / BYTES_POR_PAR;
    if(cantidadSalida == 0) return nullptr;

    Salida* salida = new Salida[cantidadSalida];

    for(int i = 0; i < cantidadSalida; i++){
        int base = i * BYTES_POR_PAR;

        unsigned int indice = ((unsigned int)(unsigned char)bytes[base] << 24)
                              | ((unsigned int)(unsigned char)bytes[base + 1] << 16)
                              | ((unsigned int)(unsigned char)bytes[base + 2] << 8)
                              |  (unsigned int)(unsigned char)bytes[base + 3];

        salida[i].indice = (int)indice;
        salida[i].frase = bytes[base + 4];
    }

    return salida;
}







