#ifndef DTINMUEBLEADMINISTRADO_H
#define DTINMUEBLEADMINISTRADO_H
#include "DTFecha.h"

class DTInmuebleAdministrado {
    private:
        int codigo;
        std::string direccion;
        DTFecha* fechaComienzo;

    public:
        DTInmuebleAdministrado(int codigo, std::string direccion, DTFecha* fechaComienzo);
        int getCodigo() const;
        std::string getDireccion() const;
        DTFecha getFechaComienzo() const;
        ~DTInmuebleAdministrado();
        
        // Operator for std::set comparison
        bool operator<(const DTInmuebleAdministrado& other) const;
        DTInmuebleAdministrado(const DTInmuebleAdministrado& other);  
        DTInmuebleAdministrado& operator=(const DTInmuebleAdministrado& other);
};

#endif