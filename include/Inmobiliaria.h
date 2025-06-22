#ifndef INMOBILIARIA_H 
#define INMOBILIARIA_H

#include <map>
#include <vector>
#include <set>
#include "Usuario.h"
#include "Inmueble.h"
#include "ISuscriptor.h"
#include "DTInmuebleAdministrado.h"
#include "DTInmuebleListado.h"
#include "DTUsuario.h"

class AdministraPropiedad;

class Propietario;

class Inmobiliaria : public Usuario {
    private:
        std::string direccion;
        std::string url;
        std::string telefono;
        std::set<ISuscriptor*> suscriptores;
        std::map<std::string,Propietario*> propietariosRepresentados;
        std::vector<AdministraPropiedad*> propiedadesAdministradas;
        
    public:
        Inmobiliaria(std::string nickname, std::string contrasena, std::string nombre, std::string email, std::string direccion, std::string url, std::string telefono);
        ~Inmobiliaria();
        std::string getDireccion();
        std::string getUrl();
        std::string getTelefono();
        std::set<DTInmuebleAdministrado> coleccionInmuebles();
        void agregar(ISuscriptor* o);
        void eliminar(ISuscriptor* o);
        AdministraPropiedad* crearPub(int codigoInmueble, TipoPublicacion TipoPublicacion, DTFecha* fecha);
        void eliminarAdministracion(AdministraPropiedad* administracion);
        DTUsuario getDTUsuario();
        std::set<ISuscriptor*> getSuscriptores();
        //caso nuevo
        std::set<DTInmuebleListado> getInmbueblesNoAdminPropietario();
        void altaAdministracionPropiedad(Inmueble* inmueble, DTFecha* fechaActual);
        bool UsuarioSuscrito(std::string nick);
        void representarPropInm(Propietario* p);
        AdministraPropiedad* getAdm();
};

#include "AdministraPropiedad.h"
#include "Propietario.h"

#endif
