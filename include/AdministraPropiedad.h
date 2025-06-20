#ifndef ADMINISTRAPROPIEDAD_H
#define ADMINISTRAPROPIEDAD_H
#include <map>
#include "Inmueble.h"
#include "Publicacion.h"

class Inmobiliaria;

class AdministraPropiedad {
    private:
        DTFecha* fecha;
        std::map<int,Publicacion*> publicaciones;
        Inmobiliaria* inmobiliaria;
        Inmueble* inmueble;
        
    public:
        AdministraPropiedad(DTFecha* fecha);
        AdministraPropiedad(Inmobiliaria* inm, Inmueble* inmue, DTFecha* fecha);
        ~AdministraPropiedad();
        Inmueble* getInmueble();
        Inmobiliaria* getInmobiliaria();
        DTFecha* getFecha();
        bool puedeCrear(TipoPublicacion tipo,DTFecha* fecha);
        void eliminarPublicacionesAsoc();
        void eliminarInmobiliaria();
        bool inmobiliariaAsociada(Inmobiliaria* inm);
        void agregarPublicacion(Publicacion* pub);
};

#include "Inmobiliaria.h"

#endif