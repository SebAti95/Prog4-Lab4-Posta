#include "../include/ManejadorPublicacion.h"
#include "../include/Casa.h"
#include <cstddef>
#include <iostream>

ManejadorPublicacion* ManejadorPublicacion::instance = nullptr;


ManejadorPublicacion::ManejadorPublicacion() {
    this->publicaciones = std::map<int, Publicacion*>();
    this->inmuebles = std::map<int, Inmueble*>();
}

// Get instance - Singleton pattern
ManejadorPublicacion* ManejadorPublicacion::getInstance() {
    if (instance == nullptr) {
        instance = new ManejadorPublicacion();
    }
    return instance;
}


void ManejadorPublicacion::agregarPublicacion(Publicacion* publicacion) {
    if (publicacion != nullptr) {
        this->publicaciones[publicacion->getCodigo()] = publicacion;
    }
}

void ManejadorPublicacion::eliminarPublicacion(Publicacion* publicacion) {
    if (publicacion != nullptr) {
        this->publicaciones.erase(publicacion->getCodigo());
    }
}

Publicacion* ManejadorPublicacion::getPublicacion(int codigo) {
    if (this->publicaciones.find(codigo) != this->publicaciones.end()) {
        return this->publicaciones[codigo];
    }
    return nullptr;
}


void ManejadorPublicacion::agregarInmueble(Inmueble* inmueble) {
    if (inmueble != nullptr) {
        this->inmuebles[inmueble->getCodigo()] = inmueble;
    }
}

void ManejadorPublicacion::eliminarRelacionInmueble(Inmueble* inmueble) {
    if (inmueble != nullptr) {
        this->inmuebles.erase(inmueble->getCodigo());
    }
}

Inmueble* ManejadorPublicacion::getInmueble(int id) {
    if (this->inmuebles.find(id) != this->inmuebles.end()) {
        return this->inmuebles[id];
    }
    return nullptr;
}

std::set<DTPublicacion> ManejadorPublicacion::listarPublicaciones(TipoPublicacion tipoPublicacion, float precioMinimo, float precioMaximo, TipoInmueble tipoInmueble) {
    std::set<DTPublicacion> publicacionesSet;
    for (std::map<int, Publicacion*>::const_iterator it = this->publicaciones.begin(); it != this->publicaciones.end(); ++it) {
        const std::pair<int, Publicacion*>& pair = *it;
        Publicacion* pub = pair.second;
        if (pub->getTipo() == tipoPublicacion && 
            pub->getPrecio() >= precioMinimo && 
            pub->getPrecio() <= precioMaximo &&
            pub->getActiva()==1 &&
                (pub->getAdmin()->getInmueble()->getTipoInmueble() == tipoInmueble || 
                tipoInmueble == Todos)) {
            publicacionesSet.insert(pub->getDTPublicacion());
        }
    }
    return publicacionesSet;
}

std::set<DTInmuebleListado> ManejadorPublicacion::listarInmuebles() {
    std::set<DTInmuebleListado> inmueblesSet;
    for (std::map<int, Inmueble*>::const_iterator it = this->inmuebles.begin(); it != this->inmuebles.end(); ++it) {
        const std::pair<int, Inmueble*>& pair = *it;
        Inmueble* inm = pair.second;
        DTInmueble* dtInm = inm->getDTInmueble();
        DTInmuebleListado InmList = DTInmuebleListado(dtInm->getCodigo(), dtInm->getDireccion(), inm->getPropietario()->getNickname());
        inmueblesSet.insert(InmList);
    }
    return inmueblesSet;
}



