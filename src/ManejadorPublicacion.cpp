#include "../include/ManejadorPublicacion.h"
#include "../include/Casa.h"
#include <cstddef>

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

// Method to add Casa (which inherits from Inmueble)
void ManejadorPublicacion::agregarCasa(Casa* casa) {
    if (casa != nullptr) {
        this->inmuebles[casa->getCodigo()] = casa;
    }
}
