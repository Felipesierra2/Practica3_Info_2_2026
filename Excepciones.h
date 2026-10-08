#ifndef EXCEPCIONES_H
#define EXCEPCIONES_H

enum TipoError {
    PARAMETRO_INVALIDO,
    ARCHIVO_NO_ABRE,
    FORMATO_INVALIDO,
    ERROR_PROCESAMIENTO
};

struct ErrorPractica {
    TipoError tipo;
    char mensaje[128];
};

void lanzarError(TipoError tipo, const char* detalle);

// Texto corto que describe el tipo de error
const char* nombreTipoError(TipoError tipo);

#endif
