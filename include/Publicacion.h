#ifndef PUBLICACION_H
#define PUBLICACION_H
#include <string>
#include <vector>
#include "DTFecha.h"
#include "TipoPublicacion.h"
#include "DTPublicacion.h"
#include "DTNotificacion.h"

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
    DTFecha getFechaDatos();
    TipoPublicacion getTipo();
    std::string getTexto();
    AdministraPropiedad* getAdmin();
    float getPrecio();
    bool getActiva();
    DTPublicacion getDTPublicacion();
    DTNotificacion getDTNotificacion(TipoInmueble tipoInmueble, std::string nickInmob);
    void setActiva(bool valor);
};

#endif