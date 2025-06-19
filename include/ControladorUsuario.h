#ifndef CONTROLADORUSUARIO_H
#define CONTROLADORUSUARIO_H

#include "IUsuario.h"
#include <set>
#include <string>
#include "DTUsuario.h"
#include "Casa.h"
#include "Apartamento.h"

// Forward declaration
class ManejadorUsuario;

class ManejadorPublicacion;

class ControladorUsuario : public IUsuario {
    private:
        static ControladorUsuario* instance;
        ControladorUsuario(); // Private constructor for singleton
        std::string nicknameInmobiliaria;
        std::string nicknamePropietario;
        int codigoInmueble;
        
    public:
        static ControladorUsuario* getInstance();
        ~ControladorUsuario();
        
        // Methods from IUsuario interface
        virtual bool altaCliente(std::string nick, std::string nombre, std::string contraseña, std::string email, std::string apellido, std::string CI);
        virtual bool altaPropietario(std::string nick, std::string contraseña, std::string nombre, std::string email, std::string cuenta, std::string tel);
        virtual bool altaInmobiliaria(std::string nick, std::string contraseña, std::string nombre, std::string email, std::string direccion, std::string url, std::string tel);
        
        //Caso de uso nuevo
        virtual std::set<DTUsuario> listarInmobiliarias();
        virtual std::set<DTUsuario> listarPropietarios();
        
        virtual void representarPropietario(std::string nicknamePropietario);
        virtual void altaCasa(std::string direccion, int numeroPuerta, float superficie, int anoConstruccion, bool esPH, TipoTecho techo);
        virtual void altaApartamento(std::string direccion, int numeroPuerta, float superficie, int anoConstruccion, int piso, bool tieneAscensor, float gastosComunes);

};

#endif
