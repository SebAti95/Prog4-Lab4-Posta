#ifndef MANEJADORUSUARIO_H
#define MANEJADORUSUARIO_H

#include <map>
#include "IUsuario.h"
#include "Cliente.h"
#include "Inmobiliaria.h"
#include "Propietario.h"

class ManejadorUsuario {
    private:
        static ManejadorUsuario* instance;
        ManejadorUsuario();
        std::map<std::string, Cliente*> cliente;
        std::map<std::string, Inmobiliaria*> inmobiliaria;
        std::map<std::string, Propietario*> propietario;

    public:
        static ManejadorUsuario* getInstance();
        void agregarCliente(Cliente* cliente);
        void agregarPropietario(Propietario* propietario);
        void agregarInmobiliaria(Inmobiliaria* inmobiliaria);
        void eliminarCliente(Cliente* cliente);
        void eliminarPropietario(Propietario* propietario);
        void eliminarInmobiliaria(Inmobiliaria* inmobiliaria);
        Cliente* getCliente(std::string nick);
        Inmobiliaria* getInmobiliaria(std::string nick);
        Propietario* getPropietario(std::string nick);
        std::set<Inmobiliaria*> getInmobiliarias();     
        std::set<Propietario*> getPropietarios();   
        std::set<Cliente*> getClientes();

};

#endif