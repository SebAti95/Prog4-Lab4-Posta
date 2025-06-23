#include "../include/AdministraPropiedad.h"
#include <iostream>

// Constructor
/*
AdministraPropiedad::AdministraPropiedad(DTFecha* fecha) {
    this->fecha = fecha;
    this->inmobiliaria = nullptr;
    this->inmueble = nullptr;
}
*/

AdministraPropiedad::AdministraPropiedad(Inmobiliaria* inm, Inmueble* inmue, DTFecha* fecha) {
    this->inmobiliaria = inm;
    this->inmueble = inmue;
    this->fecha = new DTFecha(fecha);
    this->inmueble->asociarAdministracionPropiedad(this);
    //std::cout << "- Fecha: " << this->inmueble->getAdmin()->getFecha()->toString() << std::endl;
}

// Destructor implementation
AdministraPropiedad::~AdministraPropiedad() {
    // Delete the fecha pointer
    if (this->fecha != nullptr) {
        delete this->fecha;
        this->fecha = nullptr;
    }
    this->eliminarPublicacionesAsoc();
    
    // Only call the relationship elimination methods if the pointers are still valid
    // This prevents circular deletion issues when the inmueble is being deleted
    /*if (inmobiliaria != nullptr) {
        inmobiliaria->eliminarAdministracion(this);
        inmobiliaria = nullptr;
    }
    if (inmueble != nullptr) {
        inmueble->eliminarAdministracion(this);
        inmueble = nullptr;
    }*/
    this->eliminarRelacionInmobiliaria();
    //this->eliminarRelacionInmueble();
    //delete this;
    // Delete all publication objects in the map
    /*
    for (std::map<int, Publicacion*>::iterator it = publicaciones.begin(); it != publicaciones.end(); ++it) {
        if (it->second != nullptr) {
            delete it->second;
        }
    }
    */
    
    // Clear the map
    //publicaciones.clear();
    
    // Set pointers to nullptr (we don't delete inmobiliaria or inmueble 
    // as they are likely managed elsewhere)
    //inmobiliaria = nullptr;
    //inmueble = nullptr;
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
// Implementation of pudoCrear method
bool AdministraPropiedad::puedeCrear(TipoPublicacion tipo,DTFecha* fecha) {
    // Implementation pending
    bool pub = false;
    for(std::map<int, Publicacion*>::iterator it = publicaciones.begin(); it != publicaciones.end(); ++it) {
       pub = ((it->second->getTipo()==tipo) && (it->second->getFechaDatos() == fecha)); //por lo visto, get fecha devuelve DTFecha pero como puntero, capaz hacer un getFechaDatos y que devuelva un DTFecha NO PUNTERO
       if(pub == true) {
        break;
       }
    }
    return !pub;
}

// Implementation of eliminarPublicacionesAsoc method
void AdministraPropiedad::eliminarPublicacionesAsoc() {
    // Delete all publication objects in the map
    for (std::map<int, Publicacion*>::iterator it = publicaciones.begin(); it != publicaciones.end(); ++it) {
        if (it->second != nullptr) {
            
            delete it->second;
            it->second = nullptr; // Set to nullptr after deletion
        }
    }
    /*
    for (auto& pair : publicaciones) {
        if (pair.second != nullptr) {
            delete pair.second;
            pair.second = nullptr;
        }
    }
    */
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
