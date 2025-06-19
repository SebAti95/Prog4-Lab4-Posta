#include "../include/Inmueble.h"

Inmueble::Inmueble(int codigo, std::string direccion, int numeroPuerta, int superficie, int anoConstruccion, Propietario* propietario) {
    this->codigo = codigo;
    this->direccion = direccion;
    this->numeroPuerta = numeroPuerta;
    this->superficie = superficie;
    this->anoConstruccion = anoConstruccion;
    this->propietario = propietario;
}

Inmueble::~Inmueble() {
    removePropietario();
    this->administraciones.clear();
    // Removed 'delete this' which causes undefined behavior
}
int Inmueble::getCodigo() {
    return this->codigo;
}
std::string Inmueble::getDireccion() {
    return this->direccion;
}
int Inmueble::getNumeroPuerta() {
    return this->numeroPuerta;
}
int Inmueble::getSuperficie() {
    return this->superficie;
}
int Inmueble::getAnoConstruccion() {
    return this->anoConstruccion;
}
void Inmueble::removePropietario() {
    int codigoInmu = this->getCodigo();
    this->propietario->removeInmueble(codigoInmu);
    this->propietario = NULL;
}
DTInmueble Inmueble::getDTInmueble() {
    return DTInmueble(this->codigo, this->direccion, this->numeroPuerta, this->superficie, this->anoConstruccion);
}
bool Inmueble::esAdministrado(Inmobiliaria* inm) {
    std::vector<AdministraPropiedad*>::iterator i;
    for (i = this->administraciones.begin(); i != this->administraciones.end(); ++i) { 
        bool administra = (*i)->inmobiliariaAsociada(inm);
        if (administra == true){
            return true;
            break;
        }
    }
    return false;
}

void Inmueble::asociarAdministracionPropiedad(AdministraPropiedad* adminPropiedad) {
    this->administraciones.push_back(adminPropiedad);
}

std::vector<AdministraPropiedad*> Inmueble::getAdminis() {
    return this->administraciones;
}

void Inmueble::setPropietario(Propietario* propietario) {
    this->propietario = propietario;
}

Propietario* Inmueble::getPropietario(){
    return this->propietario;
};
