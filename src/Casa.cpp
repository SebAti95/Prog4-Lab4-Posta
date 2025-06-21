#include "../include/Casa.h"
#include "../include/DTCasa.h"

Casa::Casa(bool esPH, TipoTecho techo) : Inmueble(0, "", 0, 0, 0, nullptr) {
    this->esPH = esPH;
    this->techo = techo;
}

Casa::Casa(int codigo, std::string direccion, int numeroPuerta, float superficie, int anoConstruccion, bool esPH, TipoTecho techo) 
    : Inmueble(codigo, direccion, numeroPuerta, superficie, anoConstruccion, nullptr) {
    this->esPH = esPH;
    this->techo = techo;
}

Casa::~Casa() {
    delete this;
}
bool Casa::getEsPH() {
    return this->esPH;
}
TipoTecho Casa::getTecho() {
    return this->techo;
}
TipoInmueble Casa::getTipoInmueble() {
    return TipoInmueble::Casa;
}

DTInmueble* Casa::getDTInmueble() {
    return new DTCasa(getCodigo(), getDireccion(), getNumeroPuerta(), getSuperficie(), getAnoConstruccion(), esPH, techo);
}
