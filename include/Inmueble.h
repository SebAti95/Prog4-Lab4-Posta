#ifndef INMUEBLE_H
#define INMUEBLE_H
#include <string>
#include <vector>
#include "DTInmueble.h"
#include "TipoInmueble.h"

class AdministraPropiedad;

class Propietario;

class Inmobiliaria;

class Inmueble {
    private:
        int codigo;
        std::string direccion;
        int numeroPuerta;
        int superficie;
        int anoConstruccion;
        std::vector<AdministraPropiedad*> administraciones;
        Propietario* propietario;

    public:
        Inmueble(int codigo, std::string direccion, int numeroPuerta, int superficie, int anoConstruccion, Propietario* propietario);
        ~Inmueble();
        int getCodigo();
        std::string getDireccion();
        int getNumeroPuerta();
        int getSuperficie();
        int getAnoConstruccion();
        void setPropietario(Propietario* propietario);
        Propietario* getPropietario();
        DTInmueble getDTInmueble();
        void removePropietario();
        void eliminarAdministracion(AdministraPropiedad* administracion);
        bool esAdministrado(Inmobiliaria* inm);
        void asociarAdministracionPropiedad(AdministraPropiedad* adminPropiedad);
        std::vector<AdministraPropiedad*> getAdminis();
        virtual TipoInmueble getTipoInmueble() = 0; 
};

#include "AdministraPropiedad.h"
#include "Propietario.h"
#endif