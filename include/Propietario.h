#ifndef PROPIETARIO_H
#define PROPIETARIO_H

#include <string>
#include <map>
#include <set>
#include <algorithm>
#include "Usuario.h"
#include "DTInmuebleListado.h"
#include "Inmueble.h"
#include "ISuscriptor.h"
#include "DTUsuario.h"
#include "DTNotificacion.h"


class Propietario : public Usuario, public ISuscriptor {
    private:
        std::string cuentaBancaria;
        std::string telefono;
        std::vector<std::string> publicacionesSuscritas;
        std::vector<std::string> inmobiliariasSuscritas;
        std::map<int,Inmueble*> inmuebles;
        std::vector<DTNotificacion> notificaciones;

    public:
        Propietario(std::string nickname, std::string contrasena, std::string nombre, std::string email, std::string cuentaBancaria, std::string telefono);
        ~Propietario();
        std::string getCuentaBancaria();
        std::string getTelefono();
        virtual void notificar(DTNotificacion notificacion);
        std::set<DTInmuebleListado> getInmueblesNoAdmin(Inmobiliaria* inm);
        void asociarInmueble(Inmueble* inmueble, int codigo);
        void removeInmueble(int codigoInmueble);
        DTUsuario getDTUsuario();
        void agregarSuscripcion(std::string nombreInmobiliaria);
        std::set<DTNotificacion> getNotificaciones() const;
        std::set<std::string> getInmobiliariasSuscritas() const;
        void eliminarSuscripcion(std::string nombreInmobiliaria);
};

#endif