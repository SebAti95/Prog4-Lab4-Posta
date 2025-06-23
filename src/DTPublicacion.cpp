#include "../include/DTPublicacion.h"

DTPublicacion::DTPublicacion(int codigo, DTFecha* fecha, std::string texto, float precio, std::string inmobiliaria) {
    this->codigo = codigo;
    this->fecha = new DTFecha(fecha);
    this->texto = texto;
    this->precio = precio;
    this->inmobiliaria = inmobiliaria;
}

DTPublicacion::DTPublicacion(const DTPublicacion& other) {
    this->codigo = other.codigo;
    this->texto = other.texto;
    this->precio = other.precio;
    this->inmobiliaria = other.inmobiliaria;
    
    if (other.fecha != nullptr) {
        this->fecha = new DTFecha(other.fecha);
    } else {
        this->fecha = nullptr;
    }
}

int DTPublicacion::getCodigo() const {
    return codigo;
}

DTFecha* DTPublicacion::getFecha() const {
    return fecha;
}

std::string DTPublicacion::getTexto() const {
    return texto;
}

float DTPublicacion::getPrecio() const {
    return precio;
}

std::string DTPublicacion::getInmobiliaria() const{
    return inmobiliaria;
}

DTPublicacion::~DTPublicacion(){
    delete fecha;
}

bool DTPublicacion::operator<(const DTPublicacion& other) const {
    return this->codigo < other.codigo;
}

DTPublicacion& DTPublicacion::operator=(const DTPublicacion& other) {
    if (this != &other) {  
        delete fecha;
        
        this->codigo = other.codigo;
        this->texto = other.texto;
        this->precio = other.precio;
        this->inmobiliaria = other.inmobiliaria;
        
        if (other.fecha != nullptr) {
            this->fecha = new DTFecha(other.fecha);
        } else {
            this->fecha = nullptr;
        }
    }
    return *this;
}
