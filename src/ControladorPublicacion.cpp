#include "../include/ControladorPublicacion.h"
#include <cstddef>

// Initialize the static instance to nullptr
ControladorPublicacion* ControladorPublicacion::instance = nullptr;

// Constructor
ControladorPublicacion::ControladorPublicacion() { }

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

std::set<DTUsuario> ControladorPublicacion::listarInmobiliarias() {
    // Implementation pending
    std::set<DTUsuario> res;
    ManejadorUsuario* m = ManejadorUsuario::getInstance();
    std::set<Inmobiliaria*> li = m->getInmobiliarias();  
    for(std::set<Inmobiliaria*>::iterator i = li.begin(); i != li.end(); ++i) { // recorro inmobiliarias
        DTUsuario dt = (*i)->getDTUsuario();
        res.insert(dt);
    }
    return res;//std::set<DTUsuario>();
}

std::set<DTInmuebleAdministrado> ControladorPublicacion::listarInmueblesAdministrados(std::string nicknameInmobiliaria) {
    std::set<DTInmuebleAdministrado> res;
    ManejadorUsuario* m = ManejadorUsuario::getInstance();
    Inmobiliaria* inm = m->getInmobiliaria(nicknameInmobiliaria);
    res = inm->coleccionInmuebles();
    return res;
}

bool ControladorPublicacion::altaPublicacion(std::string nicknameInmobiliaria, int codigoInmueble, TipoPublicacion tipoPublicacion, std::string texto, float precio) {
    ManejadorUsuario* mu = ManejadorUsuario::getInstance();
    Inmobiliaria* inm = mu->getInmobiliaria(nicknameInmobiliaria);
    ManejadorPublicacion* m = ManejadorPublicacion::getInstance();
    Factory* factory = Factory::getInstance();
    IControladorFechaActual* cfecha = factory->getControladorFechaActual();
    DTFecha* fechaActual = cfecha->getFechaActual();
    AdministraPropiedad* admin = inm->crearPub(codigoInmueble, tipoPublicacion, fechaActual);
    bool exito = admin != nullptr;
    if(exito){
        Publicacion* p = new Publicacion(codigoInmueble, fechaActual, tipoPublicacion, texto, precio, true, admin);
        admin->agregarPublicacion(p);
        m->agregarPublicacion(p);
    }
    return exito;
}

std::set<DTPublicacion> ControladorPublicacion::listarPublicacion(TipoPublicacion tipoPublicacion, float precioMinimo, float precioMaximo, TipoInmueble tipoInmueble) {
    // Implementation pending
    return std::set<DTPublicacion>();
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
        for (it = adminis.begin(); it != adminis.end(); ++it) {
            (*it)->eliminarPublicacionesAsoc();
            (*it)->eliminarInmobiliaria();
            (*it)->eliminarInmueble();
            
        }
        
    }
}

void ControladorPublicacion::altaAdministraPropiedad(std::string nicknameInmobiliaria, int codigoInmueble) {
    ManejadorUsuario* m = ManejadorUsuario::getInstance();
    Inmobiliaria* inm = m->getInmobiliaria(nicknameInmobiliaria);
    ManejadorPublicacion* mp = ManejadorPublicacion::getInstance();
    Inmueble* inmueble = mp->getInmueble(codigoInmueble);
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

void ControladorPublicacion::suscribirse(std::set<std::string> nombresInmobiliarias, std::string nick, std::string tipoAdmin) {
    ManejadorUsuario* m = ManejadorUsuario::getInstance();
    ISuscriptor* admin = nullptr;
    if (tipoAdmin != "cliente") {
        admin = m->getCliente(nick);
    } else {
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

std::set<DTNotificacion> ControladorPublicacion::listarNotificaciones(std::string nick, std::string tipoAdmin) {
    ManejadorUsuario* m = ManejadorUsuario::getInstance();
    ISuscriptor* admin = nullptr;
    if (tipoAdmin != "cliente") {
        admin = m->getCliente(nick);
    } else {
        admin = m->getPropietario(nick);
    }
    std::set<DTNotificacion> notificaciones = admin->getNotificaciones();
}   

std::set<std::string> ControladorPublicacion::seleccionarSuscripcion(std::string nick, std::string tipoAdmin) {
    ManejadorUsuario* m = ManejadorUsuario::getInstance();
    ISuscriptor* admin = nullptr;
    if (tipoAdmin != "cliente") {
        admin = m->getCliente(nick);
    } else {
        admin = m->getPropietario(nick);
    }
    std::set<std::string> nombresInmobiliarias;
    for(std::set<std::string>::iterator it = admin->getInmobiliariasSuscritas().begin(); it != admin->getInmobiliariasSuscritas().end(); ++it) {
        nombresInmobiliarias.insert(*it);
    }
    return nombresInmobiliarias;
}

void ControladorPublicacion::eliminarSuscripcion(std::set<std::string> nombresInmobiliarias, std::string nick, std::string tipoAdmin) {
    ManejadorUsuario* m = ManejadorUsuario::getInstance();
    ISuscriptor* admin = nullptr;
    if (tipoAdmin != "cliente") {
        admin = m->getCliente(nick);
    } else {
        admin = m->getPropietario(nick);
    }
    for (std::set<std::string>::iterator it = nombresInmobiliarias.begin(); it != nombresInmobiliarias.end(); ++it) {
        Inmobiliaria* inm = m->getInmobiliaria(*it);
        inm->eliminar(admin);
        admin->eliminarSuscripcion(*it);
    }
}


DTInmueble ControladorPublicacion::detalleInmueblePublicacion(int codigoPublicacion){
    // ManejadorPublicacion* m = ManejadorPublicacion::getInstance();
    // Publicacion* p=m->getPublicacion(codigoPublicacion);
    
}

//hola soy seba :D
