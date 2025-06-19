#ifndef INMUEBLE_H
#define INMUEBLE_H
#include <string>
#include <vector>
#include "DTInmueble.h"

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
        bool esAdministrado(Inmobiliaria* inm);
        void asociarAdministracionPropiedad(AdministraPropiedad* adminPropiedad);
        std::vector<AdministraPropiedad*> getAdminis();

};

#include "AdministraPropiedad.h"
#include "Propietario.h"
#endif