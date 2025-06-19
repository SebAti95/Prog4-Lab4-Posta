#include "../include/Apartamento.h"

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
    // Destructor logic if needed
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

