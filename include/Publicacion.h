#ifndef PUBLICACION_H
#define PUBLICACION_H
#include <string>
#include <vector>
#include "DTFecha.h"
#include "TipoPublicacion.h"

class Publicacion {
private:
    int codigo;
    DTFecha* fecha;
    TipoPublicacion tipo;
    std::string texto;
    float precio;
    bool activa;

public:
    Publicacion(int codigo, DTFecha* fecha, TipoPublicacion tipo, std::string texto, float precio, bool activa);
    ~Publicacion();
    int getCodigo();
    DTFecha* getFecha();
    TipoPublicacion getTipo();
    std::string getTexto();
    float getPrecio();
    bool getActiva();
};

#endif