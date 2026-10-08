#include "Archivos.h"
#include "Excepciones.h"
#include <fstream>

char* leerArchivo(const char* nombre, int& tam){
    if(nombre == nullptr){
        lanzarError(PARAMETRO_INVALIDO, "Nombre de archivo nulo");
    }

    std::ifstream archivo(nombre, std::ios::binary);
    if(!archivo.is_open()){
        lanzarError(ARCHIVO_NO_ABRE, nombre);
    }

    // Se obtiene el tamano posicionandose al final
    archivo.seekg(0, std::ios::end);
    std::streamoff fin = archivo.tellg();
    archivo.seekg(0, std::ios::beg);

    if(fin < 0){
        lanzarError(ERROR_PROCESAMIENTO, "No se pudo determinar el tamano del archivo");
    }

    tam = (int)fin;
    char* datos = new char[tam + 1];

    if(tam > 0){
        archivo.read(datos, tam);
        if(archivo.gcount() != tam){
            delete[] datos;
            lanzarError(ERROR_PROCESAMIENTO, "Lectura incompleta del archivo");
        }
    }

    datos[tam] = '\0';
    return datos;
}

void escribirArchivo(const char* nombre, const char* datos, int tam){
    if(nombre == nullptr || tam < 0 || (tam > 0 && datos == nullptr)){
        lanzarError(PARAMETRO_INVALIDO, "Parametros invalidos al escribir archivo");
    }

    std::ofstream archivo(nombre, std::ios::binary);
    if(!archivo.is_open()){
        lanzarError(ARCHIVO_NO_ABRE, nombre);
    }

    if(tam > 0){
        archivo.write(datos, tam);
    }

    if(!archivo.good()){
        lanzarError(ERROR_PROCESAMIENTO, "Fallo al escribir el archivo");
    }
}

bool sonIguales(const char* a, int tamA, const char* b, int tamB){
    if(tamA != tamB) return false;

    for(int i = 0; i < tamA; i++){
        if(a[i] != b[i]) return false;
    }

    return true;
}

