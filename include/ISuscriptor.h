#ifndef ISUSCRIPTOR_H
#define ISUSCRIPTOR_H
#include <string>

class ISuscriptor {
    public:
        virtual void notificar(std::string codigoInmueble) = 0; 
        virtual ~ISuscriptor() {} 
};

#endif
