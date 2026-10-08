#include "Excepciones.h"

void lanzarError(TipoError tipo, const char* detalle){
    ErrorPractica error;
    error.tipo = tipo;

    int i = 0;
    while(detalle != nullptr && detalle[i] != '\0' && i < 127){
        error.mensaje[i] = detalle[i];
        i++;
    }
    error.mensaje[i] = '\0';

    throw error;
}

const char* nombreTipoError(TipoError tipo){
    switch(tipo){
    case PARAMETRO_INVALIDO: return "Parametro invalido";
    case ARCHIVO_NO_ABRE:    return "No se pudo abrir el archivo";
    case FORMATO_INVALIDO:   return "Formato invalido";
    case ERROR_PROCESAMIENTO:return "Error de procesamiento";
    }
    return "Error desconocido";
}
