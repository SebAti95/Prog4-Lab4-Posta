#ifndef IUSUARIO_H
#define IUSUARIO_H
#include <string>
#include <set>
#include "DTUsuario.h"
#include "TipoTecho.h"

class ControladorUsuario;

class IUsuario {
public:
    virtual ~IUsuario() {}
    virtual bool altaCliente(std::string nick, std::string nombre, std::string contraseña, std::string email, std::string apellido, std::string CI) = 0;
    virtual bool altaPropietario(std::string nick, std::string contraseña, std::string nombre, std::string email, std::string cuenta, std::string tel) = 0;
    virtual bool altaInmobiliaria(std::string nick, std::string contraseña, std::string nombre, std::string email, std::string direccion, std::string url, std::string tel) = 0;
    virtual std::set<DTUsuario> listarPropietarios()= 0;
    virtual std::set<DTUsuario> listarInmobiliarias() = 0;
    virtual void representarPropietario(std::string nicknamePropietario)=0;
    virtual void altaCasa(std::string direccion, int numeroPuerta, float superficie, int anoConstruccion, bool esPH, TipoTecho techo) = 0;
    virtual void altaApartamento(std::string direccion, int numeroPuerta, float superficie, int anoConstruccion, int piso, bool tieneAscensor, float gastosComunes) = 0;
};

#include "ControladorUsuario.h"

#endif 