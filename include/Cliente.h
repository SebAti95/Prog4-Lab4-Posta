#ifndef CLIENTE_H
#define CLIENTE_H

#include <vector>
#include "Usuario.h"
#include "ISuscriptor.h"

class Cliente : public Usuario, public ISuscriptor {
    private:
        std::string apellido;
        std::string documento;
        std::vector<std::string> publicacionesSuscritas; 
    
    public:
        Cliente(std::string nickname, std::string contrasena, std::string nombre, std::string email, std::string apellido, std::string documento);
        ~Cliente();
        std::string getApellido();
        std::string getDocumento();
        virtual void notificar(std::string codigoInmueble);
};

#endif