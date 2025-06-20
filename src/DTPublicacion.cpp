#include "../include/DTPublicacion.h"

DTPublicacion::DTPublicacion(int codigo, DTFecha* fecha, std::string texto, std::string precio, std::string inmobiliaria) {
    this->codigo = codigo;
    this->fecha = new DTFecha(fecha);
    this->texto = texto;
    this->precio = precio;
    this->inmobiliaria = inmobiliaria;
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

std::string DTPublicacion::getPrecio() const {
    return precio;
}

std::string DTPublicacion::getInmobiliaria() const{
    return inmobiliaria;
}

DTPublicacion::~DTPublicacion(){
    delete fecha;
}