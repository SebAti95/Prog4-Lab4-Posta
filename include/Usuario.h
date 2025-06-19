#ifndef USUARIO_H
#define USUARIO_H

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
        std::string getNick();
        std::string getPasswd();
        std::string getNombre();
        std::string getEmail();
};

#endif