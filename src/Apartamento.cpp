#include "../include/Apartamento.h"
#include "../include/DTApartamento.h"

Apartamento::Apartamento(int piso, bool tieneAscensor, float gastosComunes) 
    : Inmueble(0, "", 0, 0, 0, nullptr) {
    this->piso = piso;
    this->tieneAscensor = tieneAscensor;
    this->gastosComunes = gastosComunes;
}
Apartamento::Apartamento(int codigo, std::string direccion, int numeroPuerta, float superficie, int anoConstruccion, int piso, bool tieneAscensor, float gastosComunes) 
    : Inmueble(codigo, direccion, numeroPuerta, superficie, anoConstruccion, nullptr) {
    this->piso = piso;
    this->tieneAscensor = tieneAscensor;
    this->gastosComunes = gastosComunes;
}
Apartamento::~Apartamento() {
    delete this;
}
int Apartamento::getPiso() {
    return this->piso;
}
bool Apartamento::getTieneAscensor() {
    return this->tieneAscensor;
}
float Apartamento::getGastosComunes() {
    return this->gastosComunes;
}
TipoInmueble Apartamento::getTipoInmueble() {
    return TipoInmueble::Apartamento;
}

DTInmueble* Apartamento::getDTInmueble() {
    return new DTApartamento(getCodigo(), getDireccion(), getNumeroPuerta(), getSuperficie(), getAnoConstruccion(), piso, tieneAscensor, gastosComunes);
}

