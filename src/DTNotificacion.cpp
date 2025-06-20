#include "../include/DTNotificacion.h"

DTNotificacion::DTNotificacion(std::string nicknameInmobiliaria, std::string codigoPub, std::string textoPub, std::string tipoPub, std::string tipoInmueblePub) {
    this->nicknameInmobiliaria = nicknameInmobiliaria;
    this->codigoPub = codigoPub;
    this->textoPub = textoPub;
    this->tipoPub = tipoPub;
    this->tipoInmueblePub = tipoInmueblePub;
}
std::string DTNotificacion::getNicknameInmobiliaria() const {
    return nicknameInmobiliaria;
}
std::string DTNotificacion::getCodigoPub() const {
    return codigoPub;
}
std::string DTNotificacion::getTextoPub() const {
    return textoPub;
}
std::string DTNotificacion::getTipoPub() const {
    return tipoPub;
}
std::string DTNotificacion::getTipoInmueblePub() const {
    return tipoInmueblePub;
}
bool DTNotificacion::operator<(const DTNotificacion& other) const {
    return this->codigoPub < other.codigoPub;
}