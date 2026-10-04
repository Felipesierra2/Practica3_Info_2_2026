#include "LZ78.h"
#include <cstring>

char* agregarCaracter(char* frase, char caracter){
    int tam = strlen(frase) + 2;
    char* copia = new char[tam];

    for(int i = 0; i < tam - 2; i++){
        copia[i] = frase[i];
    }

    copia[tam - 2] = caracter;
    copia[tam - 1] = '\0';
    return copia;
}

bool compararFrases(char* frase1, char* frase2){
    int i = 0;

    while(frase1[i] != '\0' && frase2[i] != '\0'){
        if(frase1[i] != frase2[i])
            return false;

        i++;
    }

    return frase1[i] == '\0' && frase2[i] == '\0';
}

int buscarEnDiccionario(Entrada* diccionario, int cantidad, char* fraseActual){
    for(int i = 0; i < cantidad; i++){
        char* palabra = diccionario[i].dic;
        if(compararFrases(palabra,fraseActual)){
            return i;
        }
    }

    return -1;
}

char* copiarFrase(char* frase){
    int tam = strlen(frase) + 1;
    char* copia = new char[tam];

    for(int i = 0; i < tam - 1; i++){
        copia[i] = frase[i];
    }

    copia[tam - 1] = '\0';
    return copia;
}

void agregarAlDiccionario(Entrada*& diccionario, int& cantidad, char* frase){
    Entrada* diccionarioCopia;
    char* fraseCopia = copiarFrase(frase);
    diccionarioCopia = new Entrada[cantidad + 1];
    diccionarioCopia = diccionario;
}








