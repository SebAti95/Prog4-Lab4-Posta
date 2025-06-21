#ifndef IPUBLICACION_H
#define IPUBLICACION_H  
#include <string>

#include <set>
#include "DTInmuebleAdministrado.h"
#include "DTInmuebleListado.h"
#include "DTInmueble.h"
#include "DTPublicacion.h"
#include "DTNotificacion.h"
#include "DTUsuario.h"
#include "TipoPublicacion.h"
#include "TipoInmueble.h"

class IPublicacion {
public:
    IPublicacion();
    virtual ~IPublicacion();
    virtual std::set<DTUsuario> listarInmobiliarias() = 0;
    virtual std::set<DTInmuebleAdministrado> listarInmueblesAdministrados(std::string nicknameInmobiliaria) = 0;
    virtual bool altaPublicacion(std::string nicknameInmobiliaria, int codigoInmueble, TipoPublicacion tipoPublicacion, std::string texto, float precio) = 0;
    virtual std::set<DTPublicacion> listarPublicacion(TipoPublicacion tipoPublicacion, float precioMinimo, float precioMaximo, TipoInmueble tipoInmueble) = 0;
    virtual void eliminarInmueble(int codigoInmueble) = 0;
    virtual void altaAdministraPropiedad(std::string nicknameInmobiliaria, int codigoInmueble) = 0;
    virtual std::set<DTInmuebleListado> listarInmueblesNoAdministrados(std::string nickInmobiliaria) = 0;
    virtual DTInmueble detalleInmueblePublicacion(int codigoPublicacion) = 0;
    virtual std::set<DTInmuebleListado> listarInmuebles() = 0;
    virtual DTInmueble detalleInmueble(int codigoInmueble) = 0;
    
};

#endif 