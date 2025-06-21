#ifndef CLIENTE_H
#define CLIENTE_H

#include <vector>
#include <set>
#include <algorithm>
#include "Usuario.h"
#include "ISuscriptor.h"
#include "DTNotificacion.h"

class Cliente : public Usuario, public ISuscriptor {
    private:
        std::string apellido;
        std::string documento;
        std::vector<std::string> publicacionesSuscritas;
        std::vector<std::string> inmobiliariasSuscritas; 
        std::vector<DTNotificacion> notificaciones;
    
    public:
        Cliente(std::string nickname, std::string contrasena, std::string nombre, std::string email, std::string apellido, std::string documento);
        ~Cliente();
        std::string getApellido();
        std::string getDocumento();
        std::set<DTNotificacion> getNotificaciones() const;
        virtual void notificar(DTNotificacion notificacion);
        virtual std::string getNickname() const;
        std::set<std::string> getInmobiliariasSuscritas() const;
        void eliminarSuscripcion(std::string nombreInmobiliaria);
};

#endif