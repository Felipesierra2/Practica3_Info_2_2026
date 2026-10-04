#include <cstring>
#include <iostream>
#include "LZ78.h"
#include "structs.h"

using namespace std;

int main(){
    char prueba[] = "ABABACAA";
    int p = 0; //indice de la posicion del arreglo de prueba
    char* frase = new char[1];
    frase[0] = '\0';
    char* fraseActual;

    Entrada* diccionario;
    int tamDic = 0;

    Salida* salida;
    salida->indice = 0;


    while(prueba[p] != '\0'){
        frase = diccionario[p].dic;
        fraseActual = agregarCaracter(frase, prueba[p]);
        if(compararFrases(frase,fraseActual)){
            salida->indice = buscarEnDiccionario(diccionario, tamDic, fraseActual);
        }
        p++;
    }

    // Salida* salida;

    return 0;
}



