#ifndef MANEJADORPUBLICACION_H
#define MANEJADORPUBLICACION_H

#include <map>
#include <string>
#include "Publicacion.h"
#include "Inmobiliaria.h"
#include "Casa.h"

class ManejadorPublicacion {
    private:
        static ManejadorPublicacion* instance;
        ManejadorPublicacion();
        std::map<int, Publicacion*> publicaciones;
        std::map<int, Inmueble*> inmuebles; 

    public:
    static ManejadorPublicacion* getInstance();
    void agregarPublicacion(Publicacion* publicacion);
    void agregarInmueble(Inmueble* inmueble);
    void eliminarPublicacion(Publicacion* publicacion);
    void eliminarInmueble(Inmueble* inmueble);
    Publicacion* getPublicacion(int codigo);
    Inmueble* getInmueble(int id);
};
#endif
