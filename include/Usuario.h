#ifndef USUARIO_H
#define USUARIO_H
#include "DTUsuario.h"

#include <string>

class Usuario {
    private:
        std::string nickname;
        std::string contrasena;
        std::string nombre;
        std::string email;

    public:
        Usuario(std::string nickname, std::string contrasena, std::string nombre, std::string email);
        virtual ~Usuario();
        DTUsuario getDTUsuario() const;
        std::string getNick() const;
        std::string getPasswd();
        std::string getNombre();
        std::string getEmail();
};

#endif