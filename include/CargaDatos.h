#ifndef CARGADATOS_H
#define CARGADATOS_H
#include <vector>

class CargaDatos {
    private:
        static CargaDatos* instance;
        CargaDatos();

    public:
        static CargaDatos* getInstance();
        ~CargaDatos();
        void cargarClientes();
        void cargarPropietarios();
        void cargarInmobiliarias();
        void cargarInmuebles();
        void cargarRepresentaciones();
        void cargarAdministraPropiedades();
        void cargarPublicaciones();
        void cargarSuscripciones();
        std::vector<std::string> split(const std::string& str, char sep);
        bool toBool(const std::string& str);
        void setFechaSistema(const std::string& fechaStr);
};

#endif