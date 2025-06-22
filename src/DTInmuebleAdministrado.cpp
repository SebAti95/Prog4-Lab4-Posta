#include "../include/DTInmuebleAdministrado.h"

DTInmuebleAdministrado::DTInmuebleAdministrado(int codigo, std::string direccion, DTFecha* fechaComienzo) {
    this->codigo = codigo;
    this->direccion = direccion;
    this->fechaComienzo = new DTFecha(fechaComienzo);
}

DTInmuebleAdministrado::DTInmuebleAdministrado(const DTInmuebleAdministrado& other) {
    //std::cout << "[DEBUG] Copy constructor DTInmuebleAdministrado llamado" << std::endl;
    this->codigo = other.codigo;
    this->direccion = other.direccion;
    
    if (other.fechaComienzo != nullptr) {
        //std::cout << "[DEBUG] Copiando fecha en copy constructor: " << other.fechaComienzo->toString() << std::endl;
        this->fechaComienzo = new DTFecha(other.fechaComienzo);
        //std::cout << "[DEBUG] Fecha copiada exitosamente en copy constructor" << std::endl;
    } else {
        this->fechaComienzo = nullptr;
    }
}

DTInmuebleAdministrado& DTInmuebleAdministrado::operator=(const DTInmuebleAdministrado& other) {
    //std::cout << "[DEBUG] Assignment operator DTInmuebleAdministrado llamado" << std::endl;
    if (this != &other) {  // Self-assignment check
        // Clean up existing resources
        delete fechaComienzo;
        
        // Copy new data
        this->codigo = other.codigo;
        this->direccion = other.direccion;
        
        if (other.fechaComienzo != nullptr) {
            //std::cout << "[DEBUG] Copiando fecha en assignment operator: " << other.fechaComienzo->toString() << std::endl;
            this->fechaComienzo = new DTFecha(other.fechaComienzo);
            //std::cout << "[DEBUG] Fecha copiada exitosamente en assignment operator" << std::endl;
        } else {
            this->fechaComienzo = nullptr;
        }
    }
    return *this;
}

int DTInmuebleAdministrado::getCodigo() const {
    return codigo;
}

std::string DTInmuebleAdministrado::getDireccion() const {
    return direccion;
}

DTFecha DTInmuebleAdministrado::getFechaComienzo() const{
    return fechaComienzo;
}

DTInmuebleAdministrado::~DTInmuebleAdministrado(){
    delete fechaComienzo;
}

bool DTInmuebleAdministrado::operator<(const DTInmuebleAdministrado& other) const {
    return this->codigo < other.codigo;
}
