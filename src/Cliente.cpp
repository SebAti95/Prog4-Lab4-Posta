#include "../include/Cliente.h"

Cliente::Cliente(std::string nickname, std::string contrasena, std::string nombre, std::string email, std::string apellido, std::string documento) 
    : Usuario(nickname, contrasena, nombre, email){
    this->apellido = apellido;
    this->documento = documento;
}

Cliente::~Cliente() {
    this->publicacionesSuscritas.clear();
    delete this;
}

std::string Cliente::getApellido() {
    return this->apellido;
}
std::string Cliente::getDocumento() {
    return this->documento;
}
void Cliente::notificar(std::string codigoInmueble) {
    this->publicacionesSuscritas.push_back(codigoInmueble);
}
