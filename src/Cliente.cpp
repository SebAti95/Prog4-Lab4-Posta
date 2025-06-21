#include "../include/Cliente.h"

Cliente::Cliente(std::string nickname, std::string contrasena, std::string nombre, std::string email, std::string apellido, std::string documento) 
    : Usuario(nickname, contrasena, nombre, email){
    this->apellido = apellido;
    this->documento = documento;
}

Cliente::~Cliente() {
    this->publicacionesSuscritas.clear();
}

std::string Cliente::getApellido() {
    return this->apellido;
}
std::string Cliente::getDocumento() {
    return this->documento;
}
void Cliente::notificar(DTNotificacion notificacion) {
    this->publicacionesSuscritas.push_back(notificacion.getCodigoPub());
};

std::string Cliente::getNickname() const {
    return this->getNick();
}
std::set<DTNotificacion> Cliente::getNotificaciones() const {
    std::set<DTNotificacion> notificacionesSet;
    for (std::vector<DTNotificacion>::const_iterator it = this->notificaciones.begin(); it != this->notificaciones.end(); ++it) {
        const DTNotificacion& notificacion = *it;
        notificacionesSet.insert(notificacion);
    }
    return notificacionesSet;
}

std::set<std::string> Cliente::getInmobiliariasSuscritas() const {
    std::set<std::string> inmobiliariasSet;
    for (std::vector<std::string>::const_iterator it = this->inmobiliariasSuscritas.begin(); it != this->inmobiliariasSuscritas.end(); ++it) {
        inmobiliariasSet.insert(*it);
    }
    return inmobiliariasSet;
}

void Cliente::eliminarSuscripcion(std::string nombreInmobiliaria) {
    std::vector<std::string>::iterator it = std::find(this->inmobiliariasSuscritas.begin(), this->inmobiliariasSuscritas.end(), nombreInmobiliaria);
    if (it != this->inmobiliariasSuscritas.end()) {
        this->inmobiliariasSuscritas.erase(it);
    }
}