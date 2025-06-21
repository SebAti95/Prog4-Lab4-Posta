#ifndef PUBLICACION_H
#define PUBLICACION_H
#include <string>
#include <vector>
#include "DTFecha.h"
#include "TipoPublicacion.h"

class AdministraPropiedad; // Forward declaration

class Publicacion {
private:
    int codigo;
    DTFecha* fecha;
    TipoPublicacion tipo;
    std::string texto;
    float precio;
    bool activa;
    AdministraPropiedad* ap;

public:
    Publicacion(int codigo, DTFecha* fecha, TipoPublicacion tipo, std::string texto, float precio, bool activa, AdministraPropiedad* ap);
    ~Publicacion();
    int getCodigo();
    DTFecha* getFecha();
    TipoPublicacion getTipo();
    std::string getTexto();
    float getPrecio();
    bool getActiva();
};

#endif