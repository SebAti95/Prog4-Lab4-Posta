#include "../include/AdministraPropiedad.h"

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

    // Initialize the publicaciones map
    //this->publicaciones = std::map<int, Publicacion*>();

    inmueble->asociarAdministracionPropiedad(this);
}

// Destructor implementation
AdministraPropiedad::~AdministraPropiedad() {
    // Delete the fecha pointer
    if (fecha != nullptr) {
        delete fecha;
        fecha = nullptr;
    }
    
    // Delete all publication objects in the map
    for (std::map<int, Publicacion*>::iterator it = publicaciones.begin(); it != publicaciones.end(); ++it) {
        if (it->second != nullptr) {
            delete it->second;
        }
    }
    
    // Clear the map
    publicaciones.clear();
    
    // Set pointers to nullptr (we don't delete inmobiliaria or inmueble 
    // as they are likely managed elsewhere)
    inmobiliaria = nullptr;
    inmueble = nullptr;
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
       pub = ((it->second->getTipo()==tipo) && (it->second->getFecha() == fecha));
       if(pub)
        break;
    }
    return !pub;
}

// Implementation of eliminarPublicacionesAsoc method
void AdministraPropiedad::eliminarPublicacionesAsoc() {
    // Delete all publication objects in the map
    for (auto& pair : publicaciones) {
        if (pair.second != nullptr) {
            delete pair.second;
        }
    }
    // Clear the map
    publicaciones.clear();
}

void AdministraPropiedad::eliminarInmobiliaria() {
    this->inmobiliaria->eliminarAdministracion(this);
    this->inmobiliaria = nullptr;
}

void AdministraPropiedad::eliminarInmueble() {
    this->inmueble->eliminarAdministracion(this);
    this->inmueble = nullptr;
}

bool AdministraPropiedad::inmobiliariaAsociada(Inmobiliaria* inm) {
    return (this->inmobiliaria == inm);
}

void AdministraPropiedad::agregarPublicacion(Publicacion* p) {
    for (std::map<int, Publicacion*>::iterator it = this->publicaciones.begin(); it != this->publicaciones.end(); ++it) {
        if ((*it).second->getActiva() == true && (*it).second->getFecha() < p->getFecha()) {
            (*it).second->setActiva(false);
            p->setActiva(true);
            break;
        }
    }
    int codigo = p->getCodigo();
    this->publicaciones[codigo]=p;
}