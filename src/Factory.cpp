#include "../include/Factory.h"
#include "../include/ControladorFechaActual.h"
#include "../include/ControladorPublicacion.h"
#include "../include/ControladorUsuario.h"
#include <cstddef>

Factory* Factory::instance = NULL;

Factory::Factory() {
}

Factory* Factory::getInstance() {
    if (instance == NULL) {
        instance = new Factory();
    }
    return instance;
}

IControladorFechaActual* Factory::getControladorFechaActual(){
    return ControladorFechaActual::getInstance();
}

IUsuario* Factory::getIControladorUsuario() {
    return ControladorUsuario::getInstance();
}

IPublicacion* Factory::getIControladorPublicacion() {
    return ControladorPublicacion::getInstance();
}