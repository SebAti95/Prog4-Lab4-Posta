#include "../include/Inmueble.h"
#include <algorithm>

Inmueble::Inmueble(int codigo, std::string direccion, int numeroPuerta, int superficie, int anoConstruccion, Propietario* propietario) {
    this->codigo = codigo;
    this->direccion = direccion;
    this->numeroPuerta = numeroPuerta;
    this->superficie = superficie;
    this->anoConstruccion = anoConstruccion;
    this->propietario = propietario;
}

Inmueble::~Inmueble() {
    if (propietario != nullptr) {
        removePropietario();
    }
    this->administraciones.clear();
    //delete this;
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

std::vector<AdministraPropiedad*>& Inmueble::getAdminis() {
    return this->administraciones;
}

void Inmueble::setPropietario(Propietario* propietario) {
    this->propietario = propietario;
}

Propietario* Inmueble::getPropietario(){
    return this->propietario;
};

void Inmueble::eliminarAdministracion(AdministraPropiedad* administracion) {
    //auto it = std::find(this->administraciones.begin(), this->administraciones.end(), administracion);
    /*if (it != this->administraciones.end()) {
        this->administraciones.erase(it);
    }*/
}

AdministraPropiedad* Inmueble::getAdmin() {
    std::vector<AdministraPropiedad*>::iterator it;
    it = this->administraciones.begin();
    return (*it);
}