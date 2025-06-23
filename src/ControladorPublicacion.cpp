#include "../include/ControladorPublicacion.h"
#include <cstddef>
#include <iostream>


ControladorPublicacion* ControladorPublicacion::instance = nullptr;

// Constructor
ControladorPublicacion::ControladorPublicacion() { 
    this->codigoUltimaPublicacion=1;
}

// Singleton getInstance
ControladorPublicacion* ControladorPublicacion::getInstance() {
    if (instance == nullptr) {
        instance = new ControladorPublicacion();
    }
    return instance;
}

// Destructor
ControladorPublicacion::~ControladorPublicacion() {
    instance = NULL;
}



std::set<DTInmuebleAdministrado> ControladorPublicacion::listarInmueblesAdministrados(std::string nicknameInmobiliaria) {
    std::set<DTInmuebleAdministrado> res;
    ManejadorUsuario* m = ManejadorUsuario::getInstance();
    Inmobiliaria* inm = m->getInmobiliaria(nicknameInmobiliaria);
    res = inm->coleccionInmuebles();
    return res;
}

bool ControladorPublicacion::altaPublicacion(std::string nicknameInmobiliaria, int codigoInmueble, TipoPublicacion tipoPublicacion, std::string texto, float precio) {
    int codigoPub;
    ManejadorUsuario* mu = ManejadorUsuario::getInstance();
    Inmobiliaria* inm = mu->getInmobiliaria(nicknameInmobiliaria);
    ManejadorPublicacion* m = ManejadorPublicacion::getInstance();
    Factory* factory = Factory::getInstance();
    IControladorFechaActual* cfecha = factory->getControladorFechaActual();
    DTFecha* fechaActual = cfecha->getFechaActual();
    AdministraPropiedad* admin = inm->crearPub(codigoInmueble, tipoPublicacion, fechaActual); //Admin es la instancia de AdministraPropiedad que apunta al inmueble que queremos publicar
    bool exito = (admin != nullptr);
    if(exito == true){
        codigoPub = this->codigoUltimaPublicacion;
        this->codigoUltimaPublicacion++;
        bool activa=admin->esActiva(tipoPublicacion,fechaActual);
        Publicacion* p = new Publicacion(codigoPub, fechaActual, tipoPublicacion, texto, precio, activa, admin);
        admin->agregarPublicacion(p);
        m->agregarPublicacion(p);
        std::set<ISuscriptor*> suscriptores = inm->getSuscriptores();
        Inmueble* inmu = m->getInmueble(codigoInmueble);
        if (p->getActiva()){
            for (std::set<ISuscriptor*>::iterator it = suscriptores.begin(); it != suscriptores.end(); ++it) {
                (*it)->notificar(p->getDTNotificacion(inmu->getTipoInmueble(), inm->getNick()));
            }
        }
    }
    else {
        delete fechaActual;
    }
    return exito;
}

std::set<DTPublicacion> ControladorPublicacion::listarPublicacion(TipoPublicacion tipoPublicacion, float precioMinimo, float precioMaximo, TipoInmueble tipoInmueble) {
    ManejadorPublicacion* m = ManejadorPublicacion::getInstance();
    std::set<DTPublicacion> publicaciones = m->listarPublicaciones(tipoPublicacion, precioMinimo, precioMaximo, tipoInmueble);
    return publicaciones;
}


void ControladorPublicacion::eliminarInmueble(int codigoInmueble) {
    ManejadorPublicacion* manejPub = ManejadorPublicacion::getInstance();
    Inmueble* inm = manejPub->getInmueble(codigoInmueble);
    if (inm != nullptr) {
        std::vector<AdministraPropiedad*>& adminis = inm->getAdminis();        
        std::vector<AdministraPropiedad*>::iterator it;
        std::map<int, Publicacion*>::iterator dt;
        for (it = adminis.begin(); it != adminis.end(); ++it) {
        std::map<int, Publicacion*>& pubs = (*it)->getPublicacionesRef();        
            for (dt = pubs.begin(); dt != pubs.end(); ++dt) {
                Publicacion* pub = dt->second;
                manejPub->eliminarPublicacion(pub);
            }
            delete (*it);
        }        
        adminis.clear();
        std::cout << "Administrador de propiedad eliminado." << std::endl;
        manejPub->eliminarRelacionInmueble(inm);
        std::cout << "Administrador de propiedad eliminado." << std::endl;
        delete inm;
    }
    else {
        std::cout << "El inmueble con codigo " << codigoInmueble << " no existe." << std::endl;
    }
}

void ControladorPublicacion::altaAdministraPropiedad(std::string nicknameInmobiliaria, int codigoInmueble) {
    ManejadorUsuario* m = ManejadorUsuario::getInstance();
    Inmobiliaria* inm = m->getInmobiliaria(nicknameInmobiliaria);
    ManejadorPublicacion* mp = ManejadorPublicacion::getInstance();
    Inmueble* inmueble = mp->getInmueble(codigoInmueble);
    
    if (inmueble == nullptr) {
        std::cerr << "Error: No se encontró el inmueble con código " << codigoInmueble << std::endl;
        return;
    }
    
    Factory* factory = Factory::getInstance();
    IControladorFechaActual* cfecha = factory->getControladorFechaActual();
    DTFecha* fechaActual = cfecha->getFechaActual();
    inm->altaAdministracionPropiedad(inmueble, fechaActual);
    delete fechaActual;
}

std::set<DTInmuebleListado> ControladorPublicacion::listarInmueblesNoAdministrados(std::string nickInmobiliaria) {
    ManejadorUsuario* m = ManejadorUsuario::getInstance();
    Inmobiliaria* inm = m->getInmobiliaria(nickInmobiliaria);
    std::set<DTInmuebleListado> listInmuebles = inm->getInmbueblesNoAdminPropietario();
    return listInmuebles;             
}

std::set<std::string> ControladorPublicacion::listarNombreInmobiliarias(std::string nick) {
    ManejadorUsuario* m = ManejadorUsuario::getInstance();
    std::set<Inmobiliaria*> inmobiliarias = m->getInmobiliarias();
    std::set<std::string> nombres;
    for (std::set<Inmobiliaria*>::iterator it = inmobiliarias.begin(); it != inmobiliarias.end(); ++it) {
        if(!(*it)->UsuarioSuscrito(nick)){
            nombres.insert((*it)->getNick());
        }
    }
    return nombres;
}

void ControladorPublicacion::suscribirse(std::set<std::string> nombresInmobiliarias, std::string nick) {
    ManejadorUsuario* m = ManejadorUsuario::getInstance();
    ISuscriptor* admin = m->getCliente(nick);
    if (admin == nullptr) {
        admin = m->getPropietario(nick);
    }
    for (std::set<std::string>::iterator it = nombresInmobiliarias.begin(); it != nombresInmobiliarias.end(); ++it) {
        Inmobiliaria* inm = m->getInmobiliaria(*it);
        inm->agregar(admin);
        Propietario* propietario = dynamic_cast<Propietario*>(admin); // Cast admin to Propietario
        if (propietario) {
            propietario->agregarSuscripcion(*it);
        }
    }
}

std::set<DTNotificacion> ControladorPublicacion::listarNotificaciones(std::string nick) {
    ManejadorUsuario* m = ManejadorUsuario::getInstance();
    ISuscriptor* admin = m->getCliente(nick);
    if (admin == nullptr) {
        admin = m->getPropietario(nick);
    }
    std::set<DTNotificacion> notificaciones = admin->getNotificaciones();
    admin->limpiarNotificaciones();
    return notificaciones;
}   

std::set<std::string> ControladorPublicacion::seleccionarSuscripcion(std::string nick) {
    ManejadorUsuario* m = ManejadorUsuario::getInstance();
    std::set<Inmobiliaria*> inmobiliarias = m->getInmobiliarias();
    std::set<std::string> nombres;
    for (std::set<Inmobiliaria*>::iterator it = inmobiliarias.begin(); it != inmobiliarias.end(); ++it) {
        if((*it)->UsuarioSuscrito(nick)){
            nombres.insert((*it)->getNick());
        }
    }
    return nombres;
}

void ControladorPublicacion::eliminarSuscripcion(std::set<std::string> nombresInmobiliarias, std::string nick) {
    ManejadorUsuario* m = ManejadorUsuario::getInstance();
    ISuscriptor* admin = m->getCliente(nick);
    if (admin == nullptr) {
        admin = m->getPropietario(nick);
    }
    for (std::set<std::string>::iterator it = nombresInmobiliarias.begin(); it != nombresInmobiliarias.end(); ++it) {
        Inmobiliaria* inm = m->getInmobiliaria(*it);
        inm->eliminar(admin);
        admin->eliminarSuscripcion(*it);
    }
}

DTInmueble* ControladorPublicacion::detalleInmueblePublicacion(int codigoPublicacion){
    ManejadorPublicacion* m = ManejadorPublicacion::getInstance();
    Publicacion* pub = m->getPublicacion(codigoPublicacion);
    Inmueble* inm = pub->getAdmin()->getInmueble();
    return inm->getDTInmueble();
}

std::set<DTInmuebleListado> ControladorPublicacion::listarInmuebles() {
    ManejadorPublicacion* m = ManejadorPublicacion::getInstance();
    std::set<DTInmuebleListado> inmuebles = m->listarInmuebles();
    return inmuebles;
}

DTInmueble* ControladorPublicacion::detalleInmueble(int codigoInmueble) {
    ManejadorPublicacion* m = ManejadorPublicacion::getInstance();
    Inmueble* inmueble = m->getInmueble(codigoInmueble);
    return inmueble->getDTInmueble();
}
