#include "RLE.h"
#include "Excepciones.h"
#include <string>

static const long long CUENTA_MAXIMA = 2000000000LL;

static bool esDigito(char c){
    return c >= '0' && c <= '9';
}

static char* copiarAArreglo(const std::string& s, int& tamSalida){
    tamSalida = (int)s.size();
    char* copia = new char[tamSalida + 1];

    for(int i = 0; i < tamSalida; i++){
        copia[i] = s[i];
    }

    copia[tamSalida] = '\0';
    return copia;
}

char* comprimirRLE(const char* texto, int tam, int& tamSalida){
    if(texto == nullptr || tam < 0){
        lanzarError(PARAMETRO_INVALIDO, "RLE: texto nulo o tamano negativo");
    }

    std::string resultado;
    int i = 0;

    while(i < tam){
        char simbolo = texto[i];
        int cuenta = 1;

        while(i + cuenta < tam && texto[i + cuenta] == simbolo){
            cuenta++;
        }

        resultado += std::to_string(cuenta);

        if(esDigito(simbolo) || simbolo == '\\'){
            resultado += '\\';
        }

        resultado += simbolo;
        i += cuenta;
    }

    return copiarAArreglo(resultado, tamSalida);
}

char* descomprimirRLE(const char* datos, int tam, int& tamSalida){
    if(datos == nullptr || tam < 0){
        lanzarError(PARAMETRO_INVALIDO, "RLE: datos nulos o tamano negativo");
    }

    std::string resultado;
    int i = 0;

    while(i < tam){
        if(!esDigito(datos[i])){
            lanzarError(FORMATO_INVALIDO, "RLE: se esperaba una cantidad");
        }

        long long cuenta = 0;
        while(i < tam && esDigito(datos[i])){
            cuenta = cuenta * 10 + (datos[i] - '0');
            if(cuenta > CUENTA_MAXIMA){
                lanzarError(FORMATO_INVALIDO, "RLE: cantidad demasiado grande");
            }
            i++;
        }

        if(cuenta == 0){
            lanzarError(FORMATO_INVALIDO, "RLE: la cantidad no puede ser 0");
        }

        if(i >= tam){
            lanzarError(FORMATO_INVALIDO, "RLE: falta el simbolo");
        }

        char simbolo = datos[i];
        if(simbolo == '\\'){
            i++;
            if(i >= tam){
                lanzarError(FORMATO_INVALIDO, "RLE: escape sin simbolo");
            }
            simbolo = datos[i];
        }
        i++;

        resultado.append((std::string::size_type)cuenta, simbolo);
    }

    return copiarAArreglo(resultado, tamSalida);
}

bool verificarRLE(const char* texto, int tam){
    int tamComprimido = 0;
    int tamRecuperado = 0;

    char* comprimido = comprimirRLE(texto, tam, tamComprimido);
    char* recuperado = nullptr;
    bool iguales = true;

    try{
        recuperado = descomprimirRLE(comprimido, tamComprimido, tamRecuperado);
    }catch(...){
        delete[] comprimido;
        throw;
    }

    if(tamRecuperado != tam){
        iguales = false;
    }else{
        for(int i = 0; i < tam && iguales; i++){
            if(recuperado[i] != texto[i]) iguales = false;
        }
    }

    delete[] comprimido;
    delete[] recuperado;
    return iguales;
}
