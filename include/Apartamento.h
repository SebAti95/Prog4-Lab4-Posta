#ifndef APARTAMENTO_H
#define APARTAMENTO_H

#include "Inmueble.h"

class Apartamento : public Inmueble {
    private:
        int piso;
        bool tieneAscensor;
        float gastosComunes;

    public:
        Apartamento(int piso, bool tieneAscensor, float gastosComunes);
        Apartamento(int codigo, std::string direccion, int numeroPuerta, float superficie, int anoConstruccion, int piso, bool tieneAscensor, float gastosComunes); 
        ~Apartamento();
        int getPiso();
        bool getTieneAscensor();
        float getGastosComunes();
        TipoInmueble getTipoInmueble();
};

#endif