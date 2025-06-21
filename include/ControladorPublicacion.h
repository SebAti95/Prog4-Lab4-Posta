#ifndef CONTROLADORPUBLICACION_H
#define CONTROLADORPUBLICACION_H

#include <string>
#include <map>
#include <set>

#include "Inmueble.h"
#include "Inmobiliaria.h"
#include "IPublicacion.h"
#include "DTUsuario.h"
#include "Publicacion.h"
#include "ManejadorPublicacion.h"
#include "DTInmuebleListado.h"
#include "DTInmuebleAdministrado.h"
#include "TipoPublicacion.h"
#include "TipoInmueble.h"
#include "ManejadorUsuario.h"
#include "Factory.h"
#include "ControladorFechaActual.h"
#include "DTNotificacion.h"

class ControladorPublicacion : public IPublicacion {
    private:
        static ControladorPublicacion* instance;
        ControladorPublicacion(); // Private constructor for singleton

    public:
        static ControladorPublicacion* getInstance();
        ~ControladorPublicacion();
        std::set<DTInmuebleAdministrado> listarInmueblesAdministrados(std::string nicknameInmobiliaria);
        bool altaPublicacion(std::string nicknameInmobiliaria, int codigoInmueble, TipoPublicacion tipoPublicacion, std::string texto, float precio);

        //caso uso nuevo
        std::set<DTInmuebleListado> listarInmueblesNoAdministrados(std::string nickInmobiliaria);
        void altaAdministraPropiedad(std::string nicknameInmobiliaria, int codigoInmueble);
        std::set<DTPublicacion> listarPublicacion(TipoPublicacion tipoPublicacion, float precioMinimo, float precioMaximo, TipoInmueble tipoInmueble);
        void eliminarInmueble(int codigoInmueble);
        std::set<DTUsuario> listarInmobiliarias();
        std::set<std::string> listarNombreInmobiliarias(std::string nick);
        void suscribirse(std::set<std::string>, std::string nick, std::string tipoAdmin);
        std::set<DTNotificacion> listarNotificaciones(std::string nick, std::string tipoAdmin);
        std::set<std::string> seleccionarSuscripcion(std::string nick, std::string tipoAdmin);
        void eliminarSuscripcion(std::set<std::string> nombresInmobiliarias, std::string nick, std::string tipoAdmin);
        DTInmueble detalleInmueblePublicacion(int codigoPublicacion);
        std::set<DTInmuebleListado> listarInmuebles();
        DTInmueble detalleInmueble(int codigoInmueble);
};

#endif                      