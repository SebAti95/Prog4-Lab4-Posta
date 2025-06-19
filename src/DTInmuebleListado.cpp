#include "../include/DTInmuebleListado.h"

DTInmuebleListado::DTInmuebleListado(int codigo, std::string direccion, std::string propietario) {
    this->codigo = codigo;
    this->direccion = direccion;
    this->propietario = propietario;
}

int DTInmuebleListado::getCodigo() const {
    return this->codigo;
}

std::string DTInmuebleListado::getDireccion() const {
    return this->direccion;
}

std::string DTInmuebleListado::getPropietario() const {
    return this->propietario;
}

bool DTInmuebleListado::operator<(const DTInmuebleListado& other) const {
    return this->codigo < other.codigo;
}
