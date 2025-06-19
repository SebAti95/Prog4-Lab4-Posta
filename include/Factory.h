#ifndef FACTORY_H
#define FACTORY_H

#include "IControladorFechaActual.h"
#include "IUsuario.h"
#include "IPublicacion.h"


class Factory {
    private:
        static Factory* instance;
        Factory();

    public:
        static Factory* getInstance();
        IControladorFechaActual* getControladorFechaActual();
        IUsuario* getIControladorUsuario();
        IPublicacion* getIControladorPublicacion();
        //TODO: Get interfaces de controladores
        ~Factory();
};

#endif