#include "../include/ManejadorPublicacion.h"
#include "../include/Casa.h"
#include <cstddef>
#include <iostream>

// Initialize static instance pointer to nullptr
ManejadorPublicacion* ManejadorPublicacion::instance = nullptr;

// Constructor - initializes the maps
ManejadorPublicacion::ManejadorPublicacion() {
    // Initialize empty maps
    this->publicaciones = std::map<int, Publicacion*>();
    this->inmuebles = std::map<int, Inmueble*>();
    // this->inmobiliarias = std::map<std::string, Inmobiliaria*>();
}

// Get instance - Singleton pattern
ManejadorPublicacion* ManejadorPublicacion::getInstance() {
    if (instance == nullptr) {
        instance = new ManejadorPublicacion();
    }
    return instance;
}

// Methods for managing Publicacion objects
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

// Methods for managing Inmueble objects
void ManejadorPublicacion::agregarInmueble(Inmueble* inmueble) {
    if (inmueble != nullptr) {
        this->inmuebles[inmueble->getCodigo()] = inmueble;
    }
}

void ManejadorPublicacion::eliminarInmueble(Inmueble* inmueble) {
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
        //std::cout << pub->getTipo();
        if (pub->getTipo() == tipoPublicacion && 
            pub->getPrecio() >= precioMinimo && 
            pub->getPrecio() <= precioMaximo &&
            pub->getAdmin()->getInmueble()->getTipoInmueble() == tipoInmueble) {
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

// Methods for managing Inmobiliaria objects
// void ManejadorPublicacion::agregarInmobiliaria(Inmobiliaria* inmobiliaria) {
//     if (inmobiliaria != nullptr) {
//         this->inmobiliarias[inmobiliaria->getNick()] = inmobiliaria;
//     }
// }

// void ManejadorPublicacion::eliminarInmobiliaria(Inmobiliaria* inmobiliaria) {
//     if (inmobiliaria != nullptr) {
//         this->inmobiliarias.erase(inmobiliaria->getNick());
//     }
// }

// Inmobiliaria* ManejadorPublicacion::getInmobiliaria(std::string nick) {
//     if (this->inmobiliarias.find(nick) != this->inmobiliarias.end()) {
//         return this->inmobiliarias[nick];
//     }
//     return nullptr;
// }

