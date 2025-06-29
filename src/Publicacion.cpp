#include "../include/Publicacion.h"
#include "../include/AdministraPropiedad.h"

Publicacion::Publicacion(int codigo, DTFecha* fecha, TipoPublicacion tipo, std::string texto, float precio, bool activa, AdministraPropiedad* ap) {
    this->codigo = codigo;
    this->fecha = new DTFecha(fecha);
    this->tipo = tipo;
    this->texto = texto;
    this->precio = precio;
    this->activa = activa;
    this->ap = ap;
}

Publicacion::~Publicacion() {
    if (this->fecha != nullptr) {
        delete this->fecha;
        this->fecha = nullptr;
    }
}

int Publicacion::getCodigo() {
    return this->codigo;
}

DTFecha* Publicacion::getFecha() {
    return this->fecha;
}

DTFecha Publicacion::getFechaDatos() {
    return this->fecha;
}

TipoPublicacion Publicacion::getTipo() {
    return this->tipo;
}

std::string Publicacion::getTexto() {
    return this->texto;
}

float Publicacion::getPrecio() {
    return this->precio;
}

bool Publicacion::getActiva() {
    return this->activa;
}

AdministraPropiedad* Publicacion::getAdmin() {
    return this->ap;
}

DTPublicacion Publicacion::getDTPublicacion() {
    std::string nombreInmobiliaria = this->ap->getInmobiliaria()->getNick();
    return DTPublicacion(this->codigo, this->fecha, this->texto, this->precio, nombreInmobiliaria);
}

DTNotificacion Publicacion::getDTNotificacion(TipoInmueble tipoInmueble, std::string nick) {
   std::string tipo, tipoPub;
    if (tipoInmueble == TipoInmueble::Casa) {
       tipo = "Casa";
    } else if (tipoInmueble == TipoInmueble::Apartamento) {
        tipo = "Apartamento";
    }
    std::string codigoStr = std::to_string(this->codigo);
    if (this->tipo == TipoPublicacion::Alquiler) {
        tipoPub = "Alquiler";
    } else if (this->tipo == TipoPublicacion::Venta) {
        tipoPub = "Venta";
    }
    return DTNotificacion(nick, codigoStr, this->texto, tipoPub, tipo);
}

void Publicacion::setActiva(bool valor) {
    this->activa = valor;
}