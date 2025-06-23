#include "../include/ManejadorUsuario.h"


ManejadorUsuario* ManejadorUsuario::instance = nullptr;

// Constructor
ManejadorUsuario::ManejadorUsuario() {
}

// Get instance - Singleton pattern
ManejadorUsuario* ManejadorUsuario::getInstance() {
    if (instance == nullptr) {
        instance = new ManejadorUsuario();
    }
    return instance;
}


void ManejadorUsuario::agregarCliente(Cliente* cliente) {
    if (cliente != nullptr) {
        this->cliente[cliente->getNick()] = cliente;
    }
}

Cliente* ManejadorUsuario::getCliente(std::string nick) {
    auto it = this->cliente.find(nick);
    if (it != this->cliente.end()) {
        return it->second;
    }
    return nullptr;
}

void ManejadorUsuario::eliminarCliente(Cliente* cliente) {
    if (cliente != nullptr) {
        this->cliente.erase(cliente->getNick());
    }
}

// Propietario methods
void ManejadorUsuario::agregarPropietario(Propietario* propietario) {
    if (propietario != nullptr) {
        this->propietario[propietario->getNick()] = propietario;
    }
}

Propietario* ManejadorUsuario::getPropietario(std::string nick) {
    auto it = this->propietario.find(nick);
    if (it != this->propietario.end()) {
        return it->second;
    }
    return nullptr;
}

void ManejadorUsuario::eliminarPropietario(Propietario* propietario) {
    if (propietario != nullptr) {
        this->propietario.erase(propietario->getNick());
    }
}

// Inmobiliaria methods
void ManejadorUsuario::agregarInmobiliaria(Inmobiliaria* inmobiliaria) {
    if (inmobiliaria != nullptr) {
        this->inmobiliaria[inmobiliaria->getNick()] = inmobiliaria;
    }
}

Inmobiliaria* ManejadorUsuario::getInmobiliaria(std::string nick) {
    auto it = this->inmobiliaria.find(nick);
    if (it != this->inmobiliaria.end()) {
        return it->second;
    }
    return nullptr;
}

std::set<Inmobiliaria*> ManejadorUsuario::getInmobiliarias() {
    std::set<Inmobiliaria*> inmobiliariasSet;
    for (std::map<std::string, Inmobiliaria*>::iterator it = this->inmobiliaria.begin(); it != this->inmobiliaria.end(); ++it) {
        inmobiliariasSet.insert(it->second);
    }
    return inmobiliariasSet;
}
std::set<Propietario*> ManejadorUsuario::getPropietarios() {
    std::set<Propietario*> propietariosSet;
    for (std::map<std::string, Propietario*>::iterator it = this->propietario.begin(); it != this->propietario.end(); ++it) {
        propietariosSet.insert(it->second);
    }
    return propietariosSet;
}

std::set<Cliente*> ManejadorUsuario::getClientes() {
    std::set<Cliente*> clientesSet;
    for (std::map<std::string, Cliente*>::iterator it = this->cliente.begin(); it != this->cliente.end(); ++it) {
        clientesSet.insert(it->second);
    }
    return clientesSet;
}

void ManejadorUsuario::eliminarInmobiliaria(Inmobiliaria* inmobiliaria) {
    if (inmobiliaria != nullptr) {
        this->inmobiliaria.erase(inmobiliaria->getNick());
    }
}
