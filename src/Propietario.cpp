#include "../include/Propietario.h"
#include <iostream>

Propietario::Propietario(std::string nickname, std::string contrasena, std::string nombre, std::string email, std::string cuenta, std::string telefono) : Usuario(nickname, contrasena, nombre, email) {
    this->cuentaBancaria = cuenta;
    this->telefono = telefono;
};

Propietario::~Propietario(){
    this->publicacionesSuscritas.clear();
    //Eliminar cada uno de los inmuebles antes del clear...
    this->inmuebles.clear();
};

std::string Propietario::getCuentaBancaria(){
    return this->cuentaBancaria;
};
std::string Propietario::getTelefono(){
    return this->telefono;
};


void Propietario::notificar(DTNotificacion notificacion) {
    this->notificaciones.push_back(notificacion);
};

std::string Propietario::getNickname() const {
    return this->getNick();
}

std::set<DTInmuebleListado> Propietario::getInmueblesNoAdmin(Inmobiliaria* inm) {
    std::set<DTInmuebleListado> inmueblesNoAdministrados;
   for (std::map<int,Inmueble*>::iterator i = this->inmuebles.begin(); i != this->inmuebles.end(); ++i) {
        bool administrado = i->second->esAdministrado(inm);
        if(!administrado){
            int codigo = i->second->getCodigo();
            std::string direccion = i->second->getDireccion();
            std::string propietario=this->getNick();
            DTInmuebleListado DT=DTInmuebleListado(codigo, direccion,  propietario); 
            inmueblesNoAdministrados.insert(DT);
        };
    }
    return inmueblesNoAdministrados;
}

void Propietario::removeInmueble(int codigoInmueble) {
    this->inmuebles.erase(codigoInmueble);
}

void Propietario::asociarInmueble(Inmueble* inmueble, int codigo) {
    this->inmuebles[codigo] = inmueble;
}

void Propietario::agregarSuscripcion(std::string nombreInmobiliaria) {
    this->inmobiliariasSuscritas.push_back(nombreInmobiliaria);
}

std::set<DTNotificacion> Propietario::getNotificaciones() const {
    std::set<DTNotificacion> notificacionesSet;
    for (std::vector<DTNotificacion>::const_iterator it = this->notificaciones.begin(); it != this->notificaciones.end(); ++it) {
        const DTNotificacion& notificacion = *it;
        notificacionesSet.insert(notificacion);
    }
    return notificacionesSet;
}

void Propietario::limpiarNotificaciones() {
    this->notificaciones.clear();
}

std::set<std::string> Propietario::getInmobiliariasSuscritas() const {
    std::set<std::string> inmobiliariasSet;
    for (std::vector<std::string>::const_iterator it = this->inmobiliariasSuscritas.begin(); it != this->inmobiliariasSuscritas.end(); ++it) {
        inmobiliariasSet.insert(*it);
    }
    return inmobiliariasSet;
}

void Propietario::eliminarSuscripcion(std::string nombreInmobiliaria) {
    std::vector<std::string>::iterator it = std::find(this->inmobiliariasSuscritas.begin(), this->inmobiliariasSuscritas.end(), nombreInmobiliaria);
    if (it != this->inmobiliariasSuscritas.end()) {
        this->inmobiliariasSuscritas.erase(it);
    }
}