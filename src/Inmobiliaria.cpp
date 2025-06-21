#include "../include/Inmobiliaria.h"
#include <algorithm>
#include <iostream>

Inmobiliaria::Inmobiliaria(std::string nickname, std::string contrasena, std::string nombre, std::string email, std::string direccion, std::string url, std::string telefono) : Usuario(nickname, contrasena, nombre, email) {
    this->direccion = direccion;
    this->url = url;
    this->telefono = telefono;
}

Inmobiliaria::~Inmobiliaria() {
    for (AdministraPropiedad* propiedad : propiedadesAdministradas) {
        delete propiedad;
    }
    this->propietariosRepresentados.clear();
}
std::string Inmobiliaria:: getDireccion(){
    return this->direccion;
}
std::string Inmobiliaria:: getUrl(){
    return this->url;
}
std::string Inmobiliaria:: getTelefono(){
    return this->telefono;
}
DTUsuario Inmobiliaria:: getDTUsuario(){
    std::string nickname = this->getNick();
    std::string nombre = this->getNombre();
    DTUsuario dt = DTUsuario(nickname,nombre);
    return dt;
}

AdministraPropiedad* Inmobiliaria::crearPub(int codigoInm, TipoPublicacion tipo, DTFecha* fecha){
    AdministraPropiedad* admin = nullptr;
    bool ok = false;
    for (std::vector<AdministraPropiedad*>::iterator it = this->propiedadesAdministradas.begin(); it != this->propiedadesAdministradas.end(); ++it) {
        Inmueble* i = (*it)->getInmueble();
        int codigo = i->getCodigo();
        if(codigo == codigoInm){
            admin = (*it);
            break;
        }
    }
    ok = admin->puedeCrear(tipo,fecha);
    if (ok)
        return admin;
    else 
        return nullptr;
}

void Inmobiliaria::eliminarAdministracion(AdministraPropiedad* administracion) {
    auto it = std::find(this->propiedadesAdministradas.begin(), this->propiedadesAdministradas.end(), administracion);
    if (it != this->propiedadesAdministradas.end()) {
        this->propiedadesAdministradas.erase(it);
    }
}

std::set<DTInmuebleListado> Inmobiliaria::getInmbueblesNoAdminPropietario() {
    std::set<DTInmuebleListado> inmueblesNoAdministrados;
    for (std::map<std::string,Propietario*>::iterator i = this->propietariosRepresentados.begin(); i != this->propietariosRepresentados.end(); ++i) { //recorrer los propietarios asociados a la inm
        std::set<DTInmuebleListado> listInmueblesPropietario = i->second->getInmueblesNoAdmin(this);
        inmueblesNoAdministrados.insert(listInmueblesPropietario.begin(), listInmueblesPropietario.end());
    }
    return inmueblesNoAdministrados;
}

void Inmobiliaria::altaAdministracionPropiedad(Inmueble* inmueble, DTFecha* fechaActual) {
    AdministraPropiedad* nuevaAdministracion = new AdministraPropiedad(this, inmueble, fechaActual);
    this->propiedadesAdministradas.push_back(nuevaAdministracion);
}

std::set<DTInmuebleAdministrado> Inmobiliaria::coleccionInmuebles() {
    std::set<DTInmuebleAdministrado> inmueblesAdministrados;
    for(std::vector<AdministraPropiedad*>::iterator it = this->propiedadesAdministradas.begin(); it != propiedadesAdministradas.end(); ++it) {
        Inmueble* inmueble = (*it)->getInmueble();
        if (inmueble != nullptr) {
            DTFecha* fechaComienzo = (*it)->getFecha();
            std::cout <<fechaComienzo->toString();
            DTInmuebleAdministrado dt= DTInmuebleAdministrado(inmueble->getCodigo(), inmueble->getDireccion(), fechaComienzo);
            inmueblesAdministrados.insert(dt);
        }
    }
    return inmueblesAdministrados;
}

bool Inmobiliaria::UsuarioSuscrito(std::string nick) {
    for (std::set<ISuscriptor*>::iterator it = this->suscriptores.begin(); it != this->suscriptores.end(); ++it) {
        if ((*it)->getNickname() == nick) {
            return true;
        }
    }
    return false;
}

void Inmobiliaria::representarPropInm(Propietario* p){
    this->propietariosRepresentados.insert(std::make_pair(p->getNick(), p));
}

void Inmobiliaria::agregar(ISuscriptor* o) {
    this->suscriptores.insert(o);
}
void Inmobiliaria::eliminar(ISuscriptor* o) {
    this->suscriptores.erase(o);
}

AdministraPropiedad* Inmobiliaria::getAdm() {
    std::vector<AdministraPropiedad*>::iterator it;
    it = this->propiedadesAdministradas.begin();
    return (*it);
}