#ifndef DTNOTIFICACION_H
#define DTNOTIFICACION_H
#include <string>

class DTNotificacion {
    private:
        std::string nicknameInmobiliaria;
        std::string codigoPub;
        std::string textoPub;
        std::string tipoPub;
        std::string tipoInmueblePub;
    public:
        DTNotificacion(std::string nicknameInmobiliaria, std::string codigoPub, std::string textoPub, std::string tipoPub, std::string tipoInmueblePub);
        std::string getNicknameInmobiliaria() const;
        std::string getCodigoPub() const;
        std::string getTextoPub() const;
        std::string getTipoPub() const;
        std::string getTipoInmueblePub() const;
        bool operator<(const DTNotificacion& other) const;
};

#endif 