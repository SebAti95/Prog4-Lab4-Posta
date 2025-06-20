#ifndef ISUSCRIPTOR_H
#define ISUSCRIPTOR_H
#include <string>

class ISuscriptor {
    public:
        virtual void notificar(DTNotificacion notificacion) = 0; 
        virtual ~ISuscriptor() {} 
        virtual std::string getNickname() const = 0;
        virtual std::set<DTNotificacion> getNotificaciones() const = 0;
        virtual std::set<std::string> getInmobiliariasSuscritas() const = 0;
        virtual void eliminarSuscripcion(std::string nombreInmobiliaria) = 0;
};

#endif
