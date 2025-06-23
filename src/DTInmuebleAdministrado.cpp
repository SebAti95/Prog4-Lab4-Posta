#include "../include/DTInmuebleAdministrado.h"

DTInmuebleAdministrado::DTInmuebleAdministrado(int codigo, std::string direccion, DTFecha* fechaComienzo) {
    this->codigo = codigo;
    this->direccion = direccion;
    this->fechaComienzo = new DTFecha(fechaComienzo);
}

DTInmuebleAdministrado::DTInmuebleAdministrado(const DTInmuebleAdministrado& other) {
    this->codigo = other.codigo;
    this->direccion = other.direccion;
    
    if (other.fechaComienzo != nullptr) {
        this->fechaComienzo = new DTFecha(other.fechaComienzo);
    } else {
        this->fechaComienzo = nullptr;
    }
}

DTInmuebleAdministrado& DTInmuebleAdministrado::operator=(const DTInmuebleAdministrado& other) {
    if (this != &other) {  
        delete fechaComienzo;
        
        this->codigo = other.codigo;
        this->direccion = other.direccion;
        
        if (other.fechaComienzo != nullptr) {
            this->fechaComienzo = new DTFecha(other.fechaComienzo);
        } else {
            this->fechaComienzo = nullptr;
        }
    }
    return *this;
}

int DTInmuebleAdministrado::getCodigo() const {
    return codigo;
}

std::string DTInmuebleAdministrado::getDireccion() const {
    return direccion;
}

DTFecha DTInmuebleAdministrado::getFechaComienzo() const{
    return fechaComienzo;
}

DTInmuebleAdministrado::~DTInmuebleAdministrado(){
    delete fechaComienzo;
}

bool DTInmuebleAdministrado::operator<(const DTInmuebleAdministrado& other) const {
    return this->codigo < other.codigo;
}
