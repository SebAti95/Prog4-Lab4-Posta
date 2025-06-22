#include "../include/ControladorPublicacion.h"
#include <cstddef>
#include <iostream>

// Initialize the static instance to nullptr
ControladorPublicacion* ControladorPublicacion::instance = nullptr;

// Constructor
ControladorPublicacion::ControladorPublicacion() { 
    this->codigoUltimaPublicacion=0;
}

// Singleton getInstance method
ControladorPublicacion* ControladorPublicacion::getInstance() {
    if (instance == nullptr) {
        instance = new ControladorPublicacion();
    }
    return instance;
}

// Destructor
ControladorPublicacion::~ControladorPublicacion() {
    // Any cleanup if needed
}

// Implement the rest of the methods here
// These would be stubs for now until full implementation is needed


std::set<DTInmuebleAdministrado> ControladorPublicacion::listarInmueblesAdministrados(std::string nicknameInmobiliaria) {
    std::set<DTInmuebleAdministrado> res;
    ManejadorUsuario* m = ManejadorUsuario::getInstance();
    Inmobiliaria* inm = m->getInmobiliaria(nicknameInmobiliaria);
    //std::cout << "- Fecha: " << inm->getAdm()->getFecha()->toString() << std::endl;
    res = inm->coleccionInmuebles();
    /*
    std::set<DTInmuebleAdministrado>::iterator it;
    it = res.begin();
    std::cout << (*it).getFechaComienzo().toString();
    */
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
    AdministraPropiedad* admin = inm->crearPub(codigoInmueble, tipoPublicacion, fechaActual);
    bool exito = admin != nullptr;
    if(exito == true){
        codigoPub = this->codigoUltimaPublicacion;
        this->codigoUltimaPublicacion++;
        Publicacion* p = new Publicacion(codigoPub, fechaActual, tipoPublicacion, texto, precio, false, admin);
        admin->agregarPublicacion(p);
        m->agregarPublicacion(p);
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
    //std::map<int, Inmueble*>::iterator it;
    //it = manejPub->inmuebles.find(codigoInmueble);
    Inmueble* inm = manejPub->getInmueble(codigoInmueble);
    if (inm != nullptr) {
        inm->removePropietario();
        std::vector<AdministraPropiedad*>::iterator it;
        std::vector<AdministraPropiedad*> adminis = inm->getAdminis();
        
        // Delete the AdministraPropiedad objects - their destructors will handle relationship cleanup
        for (it = adminis.begin(); it != adminis.end(); ++it) {
            delete (*it);
        }
        
        // Remove the inmueble from the manager's map
        manejPub->eliminarRelacionInmueble(inm);
        // Then delete the inmueble object itself
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
    return notificaciones;
}   

std::set<std::string> ControladorPublicacion::seleccionarSuscripcion(std::string nick) {
    ManejadorUsuario* m = ManejadorUsuario::getInstance();
   ISuscriptor* admin = m->getCliente(nick);
    if (admin == nullptr) {
        admin = m->getPropietario(nick);
    }
    std::set<std::string> nombresInmobiliarias;
    for(std::set<std::string>::iterator it = admin->getInmobiliariasSuscritas().begin(); it != admin->getInmobiliariasSuscritas().end(); ++it) {
        nombresInmobiliarias.insert(*it);
    }
    return nombresInmobiliarias;
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
    std::set<DTInmuebleListado> inmuebles = m->listarInmuebles(); // Use a public method to access inmuebles
    return inmuebles;
}

DTInmueble* ControladorPublicacion::detalleInmueble(int codigoInmueble) {
    ManejadorPublicacion* m = ManejadorPublicacion::getInstance();
    Inmueble* inmueble = m->getInmueble(codigoInmueble);
    return inmueble->getDTInmueble();
}

//hola soy seba :D
