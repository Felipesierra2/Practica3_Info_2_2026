#include <iostream>
#include "RLE.h"
#include "LZ78.h"
#include "Encriptacion.h"
#include "Archivos.h"
#include "Excepciones.h"

const int METODO_RLE = 1;
const int METODO_LZ78 = 2;
const int TAM_NOMBRE = 256;

int pedirEntero(const char* mensaje){
    int valor;
    std::cout << mensaje;

    if(!(std::cin >> valor)){
        lanzarError(PARAMETRO_INVALIDO, "Se esperaba un numero entero");
    }
    return valor;
}

void pedirNombre(const char* mensaje, char* nombre){
    std::cout << mensaje;

    if(!(std::cin >> nombre)){
        lanzarError(PARAMETRO_INVALIDO, "Nombre de archivo invalido");
    }
}

char* comprimirDatos(int metodo, const char* texto, int tam, int& tamSalida){
    if(metodo == METODO_RLE){
        return comprimirRLE(texto, tam, tamSalida);
    }

    int cantidad = 0;
    Salida* pares = comprimirLZ78(texto, tam, cantidad);
    char* bytes = serializarSalida(pares, cantidad, tamSalida);
    liberarSalida(pares, cantidad);
    return bytes;
}

char* descomprimirDatos(int metodo, const char* datos, int tam, int& tamSalida){
    if(metodo == METODO_RLE){
        return descomprimirRLE(datos, tam, tamSalida);
    }

    int cantidad = 0;
    Salida* pares = deserializarSalida(datos, tam, cantidad);
    char* texto = nullptr;

    try{
        texto = descomprimirLZ78(pares, cantidad, tamSalida);
    }catch(...){
        liberarSalida(pares, cantidad);
        throw;
    }

    liberarSalida(pares, cantidad);
    return texto;
}

void ejecutarPractica(){
    int metodo = pedirEntero("Metodo de compresion (1 = RLE, 2 = LZ78): ");
    if(metodo != METODO_RLE && metodo != METODO_LZ78){
        lanzarError(PARAMETRO_INVALIDO, "El metodo debe ser 1 o 2");
    }

    int n = pedirEntero("Rotacion n (1 a 7): ");
    int clave = pedirEntero("Clave K (0 a 255): ");
    if(clave < 0 || clave > 255){
        lanzarError(PARAMETRO_INVALIDO, "La clave K debe estar entre 0 y 255");
    }
    unsigned char K = (unsigned char)clave;

    char entrada[TAM_NOMBRE], cifrado[TAM_NOMBRE], salida[TAM_NOMBRE];
    pedirNombre("Archivo de entrada (texto original): ", entrada);
    pedirNombre("Archivo para el resultado encriptado: ", cifrado);
    pedirNombre("Archivo para el texto recuperado: ", salida);

    char* original = nullptr;
    char* comprimido = nullptr;
    char* desdeArchivo = nullptr;
    char* recuperado = nullptr;
    char* verificacion = nullptr;

    try{
        int tamOriginal = 0, tamComprimido = 0, tamLeido = 0, tamRecuperado = 0, tamVerif = 0;

        original = leerArchivo(entrada, tamOriginal);

        comprimido = comprimirDatos(metodo, original, tamOriginal, tamComprimido);
        encriptarDatos(comprimido, tamComprimido, n, K);
        escribirArchivo(cifrado, comprimido, tamComprimido);

        desdeArchivo = leerArchivo(cifrado, tamLeido);
        desencriptarDatos(desdeArchivo, tamLeido, n, K);
        recuperado = descomprimirDatos(metodo, desdeArchivo, tamLeido, tamRecuperado);
        escribirArchivo(salida, recuperado, tamRecuperado);

        verificacion = leerArchivo(salida, tamVerif);

        std::cout << "Tamano original: " << tamOriginal << " bytes" << std::endl;
        std::cout << "Tamano comprimido: " << tamComprimido << " bytes" << std::endl;

        if(sonIguales(original, tamOriginal, verificacion, tamVerif)){
            std::cout << "OK: el texto recuperado coincide con el original." << std::endl;
        }else{
            std::cout << "ERROR: el texto recuperado NO coincide con el original." << std::endl;
        }
    }catch(...){
        delete[] original;
        delete[] comprimido;
        delete[] desdeArchivo;
        delete[] recuperado;
        delete[] verificacion;
        throw;
    }

    delete[] original;
    delete[] comprimido;
    delete[] desdeArchivo;
    delete[] recuperado;
    delete[] verificacion;
}

int main(){
    try{
        ejecutarPractica();
    }catch(const ErrorPractica& error){
        std::cout << "Error (" << nombreTipoError(error.tipo) << "): " << error.mensaje << std::endl;
        return 1;
    }

    return 0;
}



