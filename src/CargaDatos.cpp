#include "../include/CargaDatos.h"
#include <cstddef>
#include <stdexcept> 
#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/Factory.h"

CargaDatos* CargaDatos::instance = NULL;

CargaDatos::CargaDatos() {
}
CargaDatos::~CargaDatos() {
}
void CargaDatos::cargarClientes() {
    IUsuario* iu = Factory::getInstance()->getIControladorUsuario();
    std::ifstream f("./datos/Usuario_Cliente.csv");
    std::string linea;

    while (std::getline(f, linea)) {
        auto c = split(linea, ',');
        if (c.size() < 6) continue;

        std::string nick      = c[0];
        std::string clave     = c[1];
        std::string nombre    = c[2];
        std::string email     = c[3];
        std::string apellido  = c[4];
        std::string documento = c[5];

        try {
            iu->altaCliente(nick, nombre, clave, email, apellido, documento);
        } catch (const std::exception& e) {
            std::cerr << "Error en altaCliente " << nick << ": " << e.what() << "\n";
        }
    }
}   

void CargaDatos::cargarPropietarios() {
    IUsuario* iu = Factory::getInstance()->getIControladorUsuario();
    std::ifstream f("./datos/Usuario_Propietario.csv");
    std::string linea;
    while (std::getline(f, linea)) {
        auto c = split(linea, ',');
        if (c.size() < 6) continue;

        std::string nick     = c[0];
        std::string clave    = c[1];
        std::string nombre   = c[2];
        std::string email    = c[3];
        std::string telefono = c[4];
        std::string cuenta   = c[5];

        
        // Crear el propietario y agregarlo al controlador
        try {
            iu->altaPropietario(nick, clave, nombre, email, telefono, cuenta);
        } catch (const std::exception& e) {
            // Manejo de excepciones, si es necesario
            std::cerr << "Error al cargar propietario: " << nick << ":"<< e.what() << std::endl;
        }
    }
}

void CargaDatos::cargarInmobiliarias() {
    IUsuario* iu = Factory::getInstance()->getIControladorUsuario();
    std::ifstream f("./datos/Usuario_Inmobiliaria.csv");
    std::string linea;
    while (std::getline(f, linea)) {
        auto c = split(linea, ',');
        if (c.size() < 7) continue;

        std::string nick      = c[0];
        std::string clave     = c[1];
        std::string nombre    = c[2];
        std::string email     = c[3];
        std::string direccion = c[4];
        std::string url       = c[5];
        std::string telefono  = c[6];
        
        try {
            iu->altaInmobiliaria(nick, clave, nombre, email, telefono, direccion, url);
        } catch (const std::exception& e) {
            std::cerr << "Error al cargar inmobiliaria: " << nick << ":"<< e.what() << std::endl;
        }
    }
}

void CargaDatos::cargarInmuebles() {
    IUsuario* iu = Factory::getInstance()->getIControladorUsuario();
    std::ifstream f("./datos/Propietarios_Dueno_Inmueble.csv");
    std::string linea;

    while (std::getline(f, linea)) {
        auto c = split(linea, ',');
        if (c.size() < 7) {
            std::cout << "Línea ignorada (muy pocos campos): " << linea << std::endl;
            continue;
        }

        std::string nickPropietario = c[0]; // propietario
        //int codigoInmuebleCSV = std::stoi(c[1]); // código del inmueble en el CSV
        std::string tipo = c[2]; // "casa" o "apartamento"
        
        std::string direccion      = c[3];
        int puerta                 = std::stoi(c[4]);
        float superficie           = std::stof(c[5]);
        int anio                   = std::stoi(c[6]);

        try {
            
            iu->setNicknamePropietario(nickPropietario);
            
            if (tipo == "Casa") {
                try {
                    bool esPH = toBool(c[7]);
                    std::string techo = c[8];
                    TipoTecho tipoTecho;
                    if (techo == "Liviano") {
                        tipoTecho = TipoTecho::Liviano;
                    } else if (techo == "A dos aguas") {
                        tipoTecho = TipoTecho::A_dos_aguas;
                    } else if (techo == "Plano") {
                        tipoTecho = TipoTecho::Plano;
                    } else {
                        throw std::invalid_argument("Tipo de techo desconocido: " + techo);
                    }

                    iu->altaCasa(direccion, puerta, superficie, anio, esPH, tipoTecho);
                } catch (const std::exception& ex) {
                    std::cerr << "  --> Error creando casa: " << ex.what() << std::endl;
                }
            } else if (tipo == "Apartamento") {
                if (c.size() < 12) {
                    std::cerr << "  --> Error: Apartamento requiere al menos 12 campos, encontrados " << c.size() << std::endl;
                    continue;
                }
                int piso = std::stoi(c[9]);
                bool ascensor = toBool(c[10]);
                float gastosComunes = std::stof(c[11]);

                iu->altaApartamento(direccion, puerta, superficie, anio, piso, ascensor, gastosComunes);
            } else {
                std::cerr << "Tipo de inmueble desconocido: " << tipo << "\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Error en altaInmueble (" << tipo << "): " << e.what() << "\n";
        }
    }
}

void CargaDatos::cargarRepresentaciones() {
    IUsuario* iu = Factory::getInstance()->getIControladorUsuario();
    std::ifstream f("./datos/Inmobiliaria_Representa_Propietario.csv");
    std::string linea;

    std::string actualInmobiliaria = "";

    while (std::getline(f, linea)) {
        auto c = split(linea, ',');
        if (c.size() < 2) continue;

        std::string nickInmo = c[0];
        std::string nickProp = c[1];

        try {
            iu->setNicknameInmobiliaria(nickInmo);
            iu->representarPropietario(nickProp);
        } catch (const std::exception& e) {
            std::cerr << "Error al representar " << nickProp << ": " << e.what() << "\n";
        }
    }
}

void CargaDatos::cargarAdministraPropiedades() {
    IPublicacion* ip = Factory::getInstance()->getIControladorPublicacion();
    std::ifstream f("./datos/Inmobiliaria_AdministraPropiedad_Inmueble.csv");
    std::string linea;

    while (std::getline(f, linea)) {
        auto c = split(linea, ',');
        if (c.size() < 3) continue;

        std::string nickInmo = c[0];
        int codigo = std::stoi(c[1]);
        std::string fechaStr = c[2];

        try {
            setFechaSistema(fechaStr);
            ip->altaAdministraPropiedad(nickInmo, codigo);
        } catch (const std::exception& e) {
            std::cerr << "Error en altaAdministraPropiedad: " << nickInmo << ", " << codigo
                      << " → " << e.what() << "\n";
        }
    }
}
void CargaDatos::cargarSuscripciones() {
    IPublicacion* ip = Factory::getInstance()->getIControladorPublicacion();
    std::ifstream f("./datos/Suscripcion_Inmobiliaria.csv");
    std::string linea;

    std::map<std::string, std::set<std::string> > subsPorUsuario;

    while (std::getline(f, linea)) {
        std::vector<std::string> c = split(linea, ',');
        if (c.size() < 2) continue;

        std::string nickUsuario = c[0];
        std::string nickInmo    = c[1];

        subsPorUsuario[nickUsuario].insert(nickInmo);
    }
    for (std::map<std::string, std::set<std::string>>::iterator it = subsPorUsuario.begin(); it != subsPorUsuario.end(); ++it) {
        std::string nickUsuario = it->first;
        std::set<std::string> inmobiliarias = it->second;

        try {
            ip->suscribirse(inmobiliarias, nickUsuario);
        } catch (const std::exception& e) {
            std::cerr << "Error al suscribir " << nickUsuario << ": " << e.what() << "\n";
        }
    }
}

void CargaDatos::cargarPublicaciones() {
    IPublicacion* ip = Factory::getInstance()->getIControladorPublicacion();
    std::ifstream f("./datos/AdministraPropiedad_Genera_Publicacion.csv");
    std::string linea;



    while (std::getline(f, linea)) {
        auto c = split(linea, ',');
        if (c.size() < 8) continue;

        std::string nickInmo     = c[0];
        int codigoInmueble       = std::stoi(c[1]);
        std::string fechaStr     = c[3];
        std::string tipoStr      = c[4];
        std::string texto        = c[5];
        float precio             = std::stof(c[6]);
        std::string activaStr = c[7]; 

        try {
            setFechaSistema(fechaStr);
            TipoPublicacion tipo;
            if (tipoStr == "Venta") tipo = TipoPublicacion::Venta;
            else if (tipoStr == "Alquiler") tipo = TipoPublicacion::Alquiler;
            else throw std::invalid_argument("Tipo de publicación inválido: " + tipoStr);
            ip->altaPublicacion(nickInmo, codigoInmueble, tipo, texto, precio);
        } catch (const std::exception& e) {
            std::cerr << "Error en altaPublicacion de " << nickInmo << " → " << e.what() << "\n";
        }
    }
}


std::vector<std::string> CargaDatos::split(const std::string& str, char sep) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, sep)) {
        result.push_back(item);
    }
    return result;
}

bool CargaDatos::toBool(const std::string& str) {
    return (str == "1" || str == "true" || str == "True");
}

void CargaDatos::setFechaSistema(const std::string& fechaStr) {
    int d, m, a;
    char sep;
    std::stringstream ss(fechaStr);
    ss >> d >> sep >> m >> sep >> a;

    IControladorFechaActual* reloj = Factory::getInstance()->getControladorFechaActual();
    reloj->setNewFechaActual(d, m, a);
}

CargaDatos* CargaDatos::getInstance() {
    if (instance == 0) {
        instance = new CargaDatos();
    }
    return instance;
}