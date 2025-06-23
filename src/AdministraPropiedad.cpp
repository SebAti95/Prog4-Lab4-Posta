#include "../include/AdministraPropiedad.h"
#include <iostream>



AdministraPropiedad::AdministraPropiedad(Inmobiliaria* inm, Inmueble* inmue, DTFecha* fecha) {
    this->inmobiliaria = inm;
    this->inmueble = inmue;
    this->fecha = new DTFecha(fecha);
    this->inmueble->asociarAdministracionPropiedad(this);
    
}


AdministraPropiedad::~AdministraPropiedad() {

    if (this->fecha != nullptr) {
        delete this->fecha;
        this->fecha = nullptr;
    }
    this->eliminarPublicacionesAsoc();
    this->eliminarRelacionInmobiliaria();
}
Inmueble* AdministraPropiedad::getInmueble(){
    return this->inmueble;
}
Inmobiliaria* AdministraPropiedad::getInmobiliaria(){
    return this->inmobiliaria;
}
DTFecha* AdministraPropiedad::getFecha(){
    return this->fecha;
}

bool AdministraPropiedad::puedeCrear(TipoPublicacion tipo,DTFecha* fecha) {
    
    bool pub = false;
    for(std::map<int, Publicacion*>::iterator it = publicaciones.begin(); it != publicaciones.end(); ++it) {
       pub = ((it->second->getTipo()==tipo) && (it->second->getFechaDatos() == fecha)); //por lo visto, get fecha devuelve DTFecha pero como puntero, capaz hacer un getFechaDatos y que devuelva un DTFecha NO PUNTERO
       if(pub == true) {
        break;
       }
    }
    return !pub;
}


void AdministraPropiedad::eliminarPublicacionesAsoc() {

    for (std::map<int, Publicacion*>::iterator it = publicaciones.begin(); it != publicaciones.end(); ++it) {
        if (it->second != nullptr) {

            delete it->second;
            it->second = nullptr; 
        }
    }
    this->publicaciones.clear();
}

void AdministraPropiedad::eliminarRelacionInmobiliaria() {
    this->inmobiliaria->eliminarAdministracion(this);
    this->inmobiliaria = nullptr;
}

void AdministraPropiedad::eliminarRelacionInmueble() {
    this->inmueble->eliminarAdministracion(this);
    this->inmueble = nullptr;
}

bool AdministraPropiedad::inmobiliariaAsociada(Inmobiliaria* inm) {
    return (this->inmobiliaria == inm);
}

void AdministraPropiedad::agregarPublicacion(Publicacion* p) {
    int codigo = p->getCodigo();
    this->publicaciones[codigo]=p;
}

std::map<int, Publicacion*> AdministraPropiedad::getPublicaciones() {
    return this->publicaciones;
}

std::map<int, Publicacion*>& AdministraPropiedad::getPublicacionesRef() {
    return this->publicaciones;
}

bool AdministraPropiedad::esActiva(TipoPublicacion tipo, DTFecha* fecha) {
    bool activa = true;
    std::map<int, Publicacion*>::iterator it;
    for (it = this->publicaciones.begin(); it != this->publicaciones.end(); ++it) {
        if ((it->second->getTipo() == tipo) && (it->second->getActiva() == true)){
            if((it->second->getFechaDatos() < fecha)){
                it->second->setActiva(false);
            }
            else activa=false;
            break;
        }
    }
    return activa;
}
