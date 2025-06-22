#include <iostream>
#include "../include/Menu.h"
#include "../include/CargaDatos.h"
#include "../include/TipoInmueble.h"
#include "../include/TipoPublicacion.h"
#include "../include/TipoTecho.h"
#include "../include/Factory.h"
#include "../include/DTApartamento.h"
#include "../include/DTCasa.h"
#include "../include/DTFecha.h"
#include "../include/DTInmueble.h"
#include "../include/DTInmuebleAdministrado.h"
#include "../include/DTInmuebleListado.h"
#include "../include/DTPublicacion.h"
#include "../include/DTUsuario.h"
#include <string>
#include <set>

void mostrarMenu() {
    std::cout << "=== Menu de Operaciones ===" << std::endl;
    std::cout << "1. Alta de Usuario" << std::endl;
    std::cout << "2. Alta de Publicacion" << std::endl;
    std::cout << "3. Consulta de Publicaciones" << std::endl;
    std::cout << "4. Eliminar Inmueble" << std::endl;
    std::cout << "5. Suscribirse a Notificaciones" << std::endl;
    std::cout << "6. Consulta de Notificaciones" << std::endl;
    std::cout << "7. Elimiinar Suscripciones" << std::endl;
    std::cout << "8. Alta de Administracion de Propiedad" << std::endl;
    std::cout << "9. Cargar Datos" << std::endl;
    std::cout << "10. Ver fecha actual" << std::endl;
    std::cout << "11. Asignar fecha actual" << std::endl;
    std::cout << "0. Salir" << std::endl;
    std::cout << "Ingrese el codigo de operacion: ";
}

int obtenerOpcion() {
    int opcion;
    std::cin >> opcion;
    std::cin.ignore();
    return opcion;
}

void ejecutarOpcion(int opcion) {
    switch (opcion) {
        case 1:
            std::cout << " - ALTA DE USUARIO - " << std::endl;
            altaUsuario();
            break;
        case 2:
            std::cout << " - ALTA DE PUBLICACION - " << std::endl;
            altaPublicacion();
            break;
        case 3:
            std::cout << " - CONSULTA DE PUBLICACIONES - " << std::endl;
            consultaPublicaciones();
            break;
        case 4:
            std::cout << " - ELIMINAR INMUEBLE - " << std::endl;
            eliminarInmueble();
            break;
        case 5:
            std::cout << " - SUSCRIBIRSE A NOTIFICACIONES - " << std::endl;
            suscribirseNotificaciones();
            break;
        case 6:
            std::cout << " - CONSLTAR NOTIFICACIONES - " << std::endl;
            consultaNotificaciones();
            break;
        case 7:
            std::cout << " - ELIMINAR SUSCRIPCIONES - " << std::endl;
            eliminarSuscripciones();
            break;
        case 8:
            std::cout << " - ALTA ADMINISTRACION DE PROPIEDAD - " << std::endl;
            altaAdministracionPropiedad();
            break;
        case 9:
            std::cout << " - CARGAR DATOS - " << std::endl;
            cargarDatos();
            break;
        case 10:
            std::cout << " - VER FECHA ACTUAL - " << std::endl;
            verFechaActual();
            break;
        case 11:
            std::cout << " - ASIGNAR FECHA ACTUAL - " << std::endl;
            asignarFechaActual();
            break;
        case 0:
            std::cout << "Saliendo del programa..." << std::endl;
            exit(0);
        default:
            std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
    }
}

void altaUsuario(){

    Factory* factory = Factory::getInstance();

    std::cout << "Ingrese el tipo de usuario (0: Cliente, 1: Inmobiliaria, 2: Propietario): ";
    int tipoUsuario;
    std::cin >> tipoUsuario;
    std::cin.ignore();
    if (tipoUsuario < 0 || tipoUsuario > 2){
        std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
        return;
    }

    bool usuarioOk = false;
    
    std::string nickname;
    std::string contrasena;
    std::string nombre;
    std::string email;
    std::string apellido;
    std::string documento;
    std::string url;
    std::string telefono;
    std::string direccion;
    std::string cuentaBancaria;
    
    std::cout << "Nickname: ";
    std::getline(std::cin, nickname);
    std::cout << "Contrasena: ";
    std::getline(std::cin, contrasena);
    std::cout << "Nombre: ";
    std::getline(std::cin, nombre);
    std::cout << "Email: ";
    std::getline(std::cin, email);

    if (tipoUsuario == 0){
        std::cout << "Apellido: ";
        std::getline(std::cin, apellido);
        std::cout << "Documento: ";
        std::getline(std::cin, documento);
        usuarioOk = factory->getIControladorUsuario()->altaCliente(nickname, contrasena, nombre, email, apellido, documento);

    }else if (tipoUsuario == 1){
        std::cout << "Direccion: ";
        std::getline(std::cin, direccion);
        std::cout << "URL: ";
        std::getline(std::cin, url);
        std::cout << "Telefono: ";
        std::getline(std::cin, telefono);
        usuarioOk = factory->getIControladorUsuario()->altaInmobiliaria(nickname, contrasena, nombre, email, direccion, url, telefono);

    }else if (tipoUsuario == 2){
        std::cout << "Cuenta Bancaria: ";
        std::getline(std::cin, cuentaBancaria);
        std::cout << "Telefono: ";
        std::getline(std::cin, telefono);
        usuarioOk = factory->getIControladorUsuario()->altaPropietario(nickname, contrasena, nombre, email, cuentaBancaria, telefono);

    }
    if (usuarioOk){
        if (tipoUsuario == 1 || tipoUsuario == 2){
            int salir = 1;
            std::cout << "¿Quiere ingresar los datos relacionados? (1: Si, 0: No): ";
            std::cin >> salir;
            std::cin.ignore();
            std::string inmuebleDireccion;
            int numeroPuerta;
            int superficie;
            int anoConstruccion;
            while (salir != 0){
                if (tipoUsuario == 1){
                    std::cout << "Lista de Propietarios:\n";
                    std::set<DTUsuario> ColeccionPropietarios = factory->getIControladorUsuario()->listarPropietarios();
                    //Recorrer la coleccion Mostrar "- Nickname: xx, Nombre: zz";
                    for (std::set<DTUsuario>::iterator it = ColeccionPropietarios.begin(); it != ColeccionPropietarios.end(); ++it) {
                        std::string nick = it->getNickname(); 
                        std::string nombre = it->getNombre(); 
                        std::cout << "- Nickname: " << nick << ", Nombre: " << nombre << std::endl;
                    }
                    std::cout << "Nickname propietario a representar: ";
                    std::string nicknamePropietario;
                    std::getline(std::cin, nicknamePropietario);
                    factory->getIControladorUsuario()->representarPropietario(nicknamePropietario);
                }else if (tipoUsuario == 2){
                    int tipoInmueble;
                    std::cout << "Indique el tipo de inmueble (1: Casa, 0: Apartamento): ";
                    std::cin >> tipoInmueble;
                    std::cin.ignore();
    
                    std::cout << "Direccion: ";
                    std::getline(std::cin, inmuebleDireccion);
                    std::cout << "Numero de Puerta: ";
                    std::cin >> numeroPuerta;
                    std::cin.ignore(); 
                    std::cout << "Superficie: ";
                    std::cin >> superficie;
                    std::cin.ignore();
                    std::cout << "Ano de Construccion: ";
                    std::cin >> anoConstruccion;
                    std::cin.ignore();

                    if (tipoInmueble == 1){
                        std::cout << "Es PH (1 para si, 0 para no): ";
                        int inEsPH;
                        std::cin >> inEsPH;
                        bool esPH = (inEsPH == 1);
                        std::cin.ignore();
                        std::cout << "Tipo de Techo (0: Liviano 1: A dos aguas, 2: Plano): ";
                        int inTipoTecho;
                        std::cin >> inTipoTecho;
                        std::cin.ignore();
                        TipoTecho techo = Liviano;
                        if(inTipoTecho == 1){
                            techo = A_dos_aguas;
                        }else if (inTipoTecho == 2){
                            techo = Plano;
                        }
                        factory->getIControladorUsuario()->altaCasa(inmuebleDireccion, numeroPuerta, superficie, anoConstruccion, esPH, techo);
                    }else{
                        int piso;
                        std::cout << "Piso: ";
                        std::cin >> piso;
                        std::cin.ignore();
                        std::cout << "Tiene Ascensor (1 para si, 0 para no): ";
                        int inTieneAscensor;
                        std::cin >> inTieneAscensor;
                        bool tieneAscensor = (inTieneAscensor == 1);
                        std::cin.ignore();
                        std::cout << "Gastos Comunes: ";
                        float gastosComunes;
                        std::cin >> gastosComunes;
                        std::cin.ignore();
                        factory->getIControladorUsuario()->altaApartamento(inmuebleDireccion, numeroPuerta, superficie, anoConstruccion, piso, tieneAscensor, gastosComunes);
                    }
                }
                std::cout << "¿Quiere seguir ingresando? (1: Si, 0: No): ";
                std::cin >> salir;
                std::cin.ignore();
            }
        }
        //TODO: controlador->finalizarAltaUsuario();
    }else{
        std::cout << "Error al crear el usuario" << std::endl;
    }
}

void altaPublicacion(){

    Factory* factory = Factory::getInstance();

    std::cout << "Lista de Inmobiliarias:\n";
    //TODO: Coleccion de DTUsuario = controlador->listarInmobiliarias();
    std::set<DTUsuario> ColInmobiliarias=factory->getIControladorUsuario()->listarInmobiliarias();
    //Recorrer la coleccion Mostrar "- Nickname: xx, Nombre: zz";
    for (std::set<DTUsuario>::iterator it = ColInmobiliarias.begin(); it != ColInmobiliarias.end(); ++it) {
            std::string nick = it->getNickname(); // Dereference the iterator
            std::string nombre = it->getNombre(); // Dereference the iterator
            std::cout << "- Nickname: " << nick << ", Nombre: " << nombre << std::endl;
    }
    std::cout << "Nickname de la inmobiliaria: ";
    std::string nicknameInmobiliaria;
    std::getline(std::cin, nicknameInmobiliaria);

    //TODO: Coleccion de DTInmuebleAdministrado = controlador->listarInmueblesAdministrados(nicknameInmobiliaria);
    std::set<DTInmuebleAdministrado> ColInmueblesAdmin = factory->getIControladorPublicacion()->listarInmueblesAdministrados(nicknameInmobiliaria);

    //Recorrer la coleccion Mostrar "- Codigo: xx, Direccion: yy, FechaComienzo: dd/mm/aaaa"
    for (std::set<DTInmuebleAdministrado>::const_iterator it = ColInmueblesAdmin.begin(); it != ColInmueblesAdmin.end(); ++it) {
            int codigo = it->getCodigo(); 
            std::string dir=it->getDireccion();
            DTFecha f=it->getFechaComienzo();
            std::string fecha=f.toString();
            std::cout << "- Codigo: " << codigo << ", Direccion: " << dir << ", FechaComienzo: " << fecha  << std::endl;
    }

    int codigoInmueble;
    std::cout << "Inmueble: ";
    std::cin >> codigoInmueble;
    std::cin.ignore();
    int inTipoPublicacion;
    std::cout << "Tipo de Publicacion: (1: Venta, 0: Alquiler)";
    std::cin >> inTipoPublicacion;
    TipoPublicacion tipoPublicacion = Alquiler;
    if(inTipoPublicacion == 1){
        tipoPublicacion = Venta;
    }
    std::cin.ignore();
    std::cout << "Texto: ";
    std::string texto;
    std::getline(std::cin, texto);
    std::cout << "Precio: ";
    float precio;
    std::cin >> precio;
    std::cin.ignore();

    //TODO:Controlador->altaPublicacion(nicknameInmobiliaria, codigoInmueble, tipoPublicacion, texto, precio)
    bool resultado = factory->getIControladorPublicacion()->altaPublicacion(nicknameInmobiliaria, codigoInmueble, tipoPublicacion, texto, precio);
    if (resultado == true) {
        std::cout << "Publicacion dada de alta con exito" << std::endl;
    } else {
        std::cout << "Publicacion no dada de alta, ya existe una publicacion de misma fecha y tipo" << std::endl;
    }
}
void consultaPublicaciones(){

    Factory* factory = Factory::getInstance();

    int inTipoPublicacion;
    std::cout << "Tipo de Publicacion: (1: Venta, 0: Alquiler)";
    std::cin >> inTipoPublicacion;
    TipoPublicacion tipoPublicacion = Alquiler;
    if(inTipoPublicacion == 1){
        tipoPublicacion = Venta;
    }
    std::cin.ignore();
    std::cout << "Precio (Min): ";
    float precioMinimo;
    std::cin >> precioMinimo;
    std::cin.ignore();
    std::cout << "Precio (Max): ";
    float precioMaximo;
    std::cin >> precioMaximo;
    std::cin.ignore();
    int inTipoInmueble;
    std::cout << "Tipo de Inmueble: (1: Casa, 2: Apartamento, 0: Todos)";
    std::cin >> inTipoInmueble;
    std::cin.ignore();
    TipoInmueble tipoInmueble = Todos;
    if(inTipoInmueble == 1){
        tipoInmueble = Casa;
    }else if(inTipoInmueble == 2){
        tipoInmueble = Apartamento;
    }
    std::cout << "Publicaciones encontradas:\n";
    //TODO: Coleccion de DTPublicacion = Controlador->listarPublicacion(tipoPublicacion, precionMinimo, precioMaximo, tipoInmueble);
    std::set<DTPublicacion> ColeccionDTPublicacion=factory->getIControladorPublicacion()->listarPublicacion(tipoPublicacion, precioMinimo, precioMaximo, tipoInmueble);

    //Recorrer la coleccion Mostrar "- Codigo: xx, fecha: dd/mm/yyyy, texto: zzz, precio: aaa, inmobiliaria: bbb";
    for (std::set<DTPublicacion>::const_iterator it = ColeccionDTPublicacion.begin(); it != ColeccionDTPublicacion.end(); ++it) {
            int codigo = it->getCodigo(); // Dereference the iterator
            // Get inmueble to access propietario information
            DTFecha* f=it->getFecha();
            std::string fecha=f->toString();
            std::string txt=it->getTexto();
            float precio=it->getPrecio();
            std::string inm=it->getInmobiliaria();
            std::cout << "- Codigo: " << codigo << ", fecha:: " << fecha << ", texto: " << txt << ", precio: " << precio << ", inmobiliaria: " << inm << std::endl;
    }

    int verDetalle;
    std::cout << "Ver detalle de la publicacion: (1: Si, 0: No)";
    std::cin >> verDetalle;
    std::cin.ignore();
    if (verDetalle == 1){
        std::cout << "Codigo de publicacion: ";
        int codigoPublicacion;
        std::cin >> codigoPublicacion;
        std::cin.ignore();
        std::cout << "Detalle del inmueble:\n";
        // Si es apartamento-> "Codigo: aaa, direccion: bbb, nro. puerta: ccc, superficie: xx m2, consturccion: dddd, piso: xx, ascensor: Si/No, gastos comunes: yyy"
        // Si es casa-> "Codigo: aaa, direccion: bbb, nro. puerta: ccc, superficie: xx m2, consturccion: dddd, PH: Si/No, Tipo de techo: Liviano/A dos aguas/Plano"
       DTInmueble* dt = factory->getIControladorPublicacion()->detalleInmueblePublicacion(codigoPublicacion);
        if (DTCasa* casa = dynamic_cast<DTCasa*>(dt)) {
            std::cout << "Codigo: " << casa->getCodigo()
                    << ", Direccion: " << casa->getDireccion()
                    << ", Nro. Puerta: " << casa->getNumeroPuerta()
                    << ", Superficie: " << casa->getSuperficie()
                    << ", Construccion: " << casa->getAnioConstruccion()
                    << ", PH: " << (casa->getEsPH() ? "Si" : "No")
                    << ", Tipo de techo: " << casa->getTecho() << std::endl;
        } else if (DTApartamento* apartamento = dynamic_cast<DTApartamento*>(dt)) {
            std::cout << "Codigo: " << apartamento->getCodigo()
                    << ", Direccion: " << apartamento->getDireccion()
                    << ", Nro. Puerta: " << apartamento->getNumeroPuerta()
                    << ", Superficie: " << apartamento->getSuperficie()
                    << ", Construccion: " << apartamento->getAnioConstruccion()
                    << ", Piso: " << apartamento->getPiso()
                    << ", Ascensor: " << (apartamento->getTieneAscensor() ? "Si" : "No")
                    << ", Gastos comunes: " << apartamento->getGastosComunes()
                    << std::endl;
        }
    }
}

void eliminarInmueble(){

    Factory* factory = Factory::getInstance();
    std::cout << "Listado de inmuebles:\n";
    // Coleccion de DTInmuebleListado = Controlador->listarInmuebles();
    //Recorrer la coleccion Mostrar "- Codigo: xx, direccion: xxxx, propietario: bbbbb";
    std::set<DTInmuebleListado> inmuebles = factory->getIControladorPublicacion()->listarInmuebles();
    for (std::set<DTInmuebleListado>::iterator it = inmuebles.begin(); it != inmuebles.end(); ++it) {
        DTInmuebleListado inmueble = *it; 
        std::cout << "- Codigo: " << inmueble.getCodigo() 
                  << ", direccion: " << inmueble.getDireccion() 
                  << ", propietario: " << inmueble.getPropietario() << "\n";
    }
    std::cout << "Codigo del inmueble a eliminar: ";
    int codigoInmueble;
    std::cin >> codigoInmueble;
    std::cin.ignore();
    std::cout << "Detalle del inmueble:\n";
    //TODO: DTInmueble = Controlador->detalleInmueble(codigoInmueble)
    //Mostrarlo:
    // Si es apartamento-> "Codigo: aaa, direccion: bbb, nro. puerta: ccc, superficie: xx m2, consturccion: dddd, piso: xx, ascensor: Si/No, gastos comunes: yyy"
    // Si es casa-> "Codigo: aaa, direccion: bbb, nro. puerta: ccc, superficie: xx m2, consturccion: dddd, PH: Si/No, Tipo de techo: Liviano/A dos aguas/Plano"
    DTInmueble* dt = factory->getIControladorPublicacion()->detalleInmueble(codigoInmueble);
    if (DTCasa* casa = dynamic_cast<DTCasa*>(dt)) {
            std::cout << "Codigo: " << casa->getCodigo()
                    << ", Direccion: " << casa->getDireccion()
                    << ", Nro. Puerta: " << casa->getNumeroPuerta()
                    << ", Superficie: " << casa->getSuperficie()
                    << ", Construccion: " << casa->getAnioConstruccion()
                    << ", PH: " << (casa->getEsPH() ? "Si" : "No")
                    << ", Tipo de techo: " << casa->getTecho() << std::endl;
        } else if (DTApartamento* apartamento = dynamic_cast<DTApartamento*>(dt)) {
            std::cout << "Codigo: " << apartamento->getCodigo()
                    << ", Direccion: " << apartamento->getDireccion()
                    << ", Nro. Puerta: " << apartamento->getNumeroPuerta()
                    << ", Superficie: " << apartamento->getSuperficie()
                    << ", Construccion: " << apartamento->getAnioConstruccion()
                    << ", Piso: " << apartamento->getPiso()
                    << ", Ascensor: " << (apartamento->getTieneAscensor() ? "Si" : "No")
                    << ", Gastos comunes: " << apartamento->getGastosComunes()
                    << std::endl;
        }

    int deseaEliminar;
    std::cout << "¿Desea eliminar?: (1: Si, 0: No)";
    std::cin >> deseaEliminar;
    std::cin.ignore();
    if (deseaEliminar == 1){
        //TODO: Controlador->eliminarInmueble(codigoInmueble)
        factory->getIControladorPublicacion()->eliminarInmueble(codigoInmueble);
    }
}

void suscribirseNotificaciones(){
    Factory* factory = Factory::getInstance();
    std::cout << "Usuarios: ";
    std::set<DTUsuario> Clientes = factory->getIControladorUsuario()->listarClientes();
    std::set<DTUsuario> Propietarios = factory->getIControladorUsuario()->listarPropietarios();
    for (std::set<DTUsuario>::const_iterator it = Clientes.begin(); it != Clientes.end(); ++it) {
        std::cout << "Nickname: "<< it->getNickname() << std::endl;
    }
    for (std::set<DTUsuario>::const_iterator it = Propietarios.begin(); it != Propietarios.end(); ++it) {
       std::cout << "Nickname: "<< it->getNickname() << std::endl;
    }
    std::cout << "Ingrese su nickname: ";
    std::string nick;
    std::cin >> nick;
    std::cout << "Listado de Inmobiliarias:\n";
    std::set<std::string> nombresInmobiliarias = factory->getIControladorPublicacion()->listarNombreInmobiliarias(nick);
    //Recorrer la coleccion Mostra;
    for (std::set<std::string>::iterator it = nombresInmobiliarias.begin(); it != nombresInmobiliarias.end(); ++it) {
        std::cout << "- Nombre: " << (*it) << std::endl;
    }
    std::cout << "Seleccione las inmobiliarias a las que desea suscribirse (separadas por comas): ";
    std::string input;
    std::getline(std::cin, input);
    std::set<std::string> nombresSeleccionados;
    std::string delimiter = ",";
    size_t pos = 0;
    while ((pos = input.find(delimiter)) != std::string::npos) {
        std::string token = input.substr(0, pos);
        nombresSeleccionados.insert(token);
        input.erase(0, pos + delimiter.length());
    }
    factory->getIControladorPublicacion()->suscribirse(nombresSeleccionados, nick);
}

void consultaNotificaciones(){
    Factory* factory = Factory::getInstance();
    std::cout << "Usuarios: ";
    std::set<DTUsuario> Clientes = factory->getIControladorUsuario()->listarClientes();
    std::set<DTUsuario> Propietarios = factory->getIControladorUsuario()->listarPropietarios();
    for (std::set<DTUsuario>::const_iterator it = Clientes.begin(); it != Clientes.end(); ++it) {
        std::cout << "Nickname: "<< it->getNickname() << std::endl;
    }
    for (std::set<DTUsuario>::const_iterator it = Propietarios.begin(); it != Propietarios.end(); ++it) {
       std::cout << "Nickname: "<< it->getNickname() << std::endl;
    }
    std::cout << "Ingrese su nickname: ";
    std::string nick;
    std::cin >> nick;
    std::cout << "Listado de Notificaciones:\n";
    std::set<DTNotificacion> notificaciones = factory->getIControladorPublicacion()->listarNotificaciones(nick);
    //Recorrer la coleccion Mostrar "- Codigo: xx texto: zzz, inmobiliaria: bbb";
    for (std::set<DTNotificacion>::const_iterator it = notificaciones.begin(); it != notificaciones.end(); ++it) {
        std::string codigo = it->getCodigoPub(); 
        std::string txt=it->getTextoPub();
        std::string inm=it->getNicknameInmobiliaria();
        std::string tipo = it->getTipoInmueblePub();
        std::cout << "- Codigo: " << codigo 
                  << ", Texto: " << txt 
                  << ", Inmobiliaria: " << inm 
                  << ", Tipo de Inmueble: " << tipo << std::endl;
    }
}

void eliminarSuscripciones(){
    Factory* factory = Factory::getInstance();
    std::cout << "Ingrese su nickname: ";
    std::cout << "Usuarios: ";
    std::set<DTUsuario> Clientes = factory->getIControladorUsuario()->listarClientes();
    std::set<DTUsuario> Propietarios = factory->getIControladorUsuario()->listarPropietarios();
    for (std::set<DTUsuario>::const_iterator it = Clientes.begin(); it != Clientes.end(); ++it) {
        std::cout << "Nickname: "<< it->getNickname() << std::endl;
    }
    for (std::set<DTUsuario>::const_iterator it = Propietarios.begin(); it != Propietarios.end(); ++it) {
       std::cout << "Nickname: "<< it->getNickname() << std::endl;
    }
    std::string nick;
    std::cin >> nick;
    std::cout << "Listado de Inmobiliarias Suscritas:\n";
    std::set<std::string> inmobiliariasSuscritas = factory->getIControladorPublicacion()->seleccionarSuscripcion(nick);
    //Recorrer la coleccion Mostrar "- Nombre: xx";
    for (std::set<std::string>::const_iterator it = inmobiliariasSuscritas.begin(); it != inmobiliariasSuscritas.end(); ++it) {
        std::cout << "- Nombre: " << *it << std::endl;
    }
    std::cout << "Seleccione las inmobiliarias a las que desea eliminar la suscripcion (separadas por comas): ";
    std::string input;
    std::getline(std::cin, input);
    std::set<std::string> nombresSeleccionados;
    std::string delimiter = ",";
    size_t pos = 0;
    while ((pos = input.find(delimiter)) != std::string::npos) {
        std::string token = input.substr(0, pos);
        nombresSeleccionados.insert(token);
        input.erase(0, pos + delimiter.length());
    }
    factory->getIControladorPublicacion()->eliminarSuscripcion(nombresSeleccionados, nick);

}

void altaAdministracionPropiedad(){
    Factory* factory = Factory::getInstance();

    std::cout << "Lista de Inmobiliarias:\n";
    //TODO: Coleccion de DTUsuario = controlador->listarInmobiliarias();
    std::set<DTUsuario> ColInmobiliarias=factory->getIControladorUsuario()->listarInmobiliarias();
    //Recorrer la coleccion Mostrar "- Nickname: xx, Nombre: zz";
    for (std::set<DTUsuario>::iterator it = ColInmobiliarias.begin(); it != ColInmobiliarias.end(); ++it) {
            std::string nick = it->getNickname(); 
            std::string nombre = it->getNombre(); 
            std::cout << "- Nickname: " << nick << ", Nombre: " << nombre << std::endl;
    }
    std::cout << "Nickname de la inmobiliaria: ";
    std::string nicknameInmobiliaria;
    std::getline(std::cin, nicknameInmobiliaria);

    //TODO: Coleccion de DTInmuebleListado = Controlador->listarInmueblesNoAdministradosInmobiliaria(nicknameInmobiliaria);
    std::set<DTInmuebleListado> ColDTInmuebleListado = factory->getIControladorPublicacion()->listarInmueblesNoAdministrados(nicknameInmobiliaria);

    //Recorrer la coleccion Mostrar "- Codigo: xx, direccion: xxxx, propietario: bbbbb";
    for (std::set<DTInmuebleListado>::const_iterator it =  ColDTInmuebleListado.begin(); it !=  ColDTInmuebleListado.end(); ++it) {
            int codigo = it->getCodigo(); 
            std::string dir=it->getDireccion();
            std::string propietario=it->getPropietario();
            std::cout << "- Codigo: " << codigo << ", Direccion: " << dir << ", Propietario: " << propietario << std::endl;
    }
    std::cout << "Codigo del inmueble a administrar: ";
    int codigoInmueble;
    std::cin >> codigoInmueble;
    std::cin.ignore();

    //TODO: Controlador->altaAdministraPropiedad(nicknameInmobiliaria, codigoInmueble);
    factory->getIControladorPublicacion()->altaAdministraPropiedad(nicknameInmobiliaria, codigoInmueble);
}

void cargarDatos(){
    CargaDatos* c = CargaDatos::getInstance();
    try {
        c->cargarClientes();
        c->cargarPropietarios();
        c->cargarInmobiliarias();
        c->cargarInmuebles();
        c->cargarRepresentaciones();
        c->cargarAdministraPropiedades();
        c->cargarPublicaciones();
        c->cargarSuscripciones();
    } catch (const std::exception& e) {
        // Manejo de excepciones, si es necesario
        std::cerr << "Error al cargar los datos: " << e.what() << std::endl;
    }
}

 void verFechaActual(){
    Factory* factory = Factory::getInstance();
    IControladorFechaActual* cfecha = factory->getControladorFechaActual();
    DTFecha* fechaActual = cfecha->getFechaActual();
    std::cout << "fecha actual: " << fechaActual;
    delete fechaActual;
 }

 void asignarFechaActual(){
    Factory* factory = Factory::getInstance();
    IControladorFechaActual* cfecha = factory->getControladorFechaActual();
    std::cout << "dia: ";
    int dia;
    std::cin >> dia;
    std::cin.ignore();
    std::cout << "mes: ";
    int mes;
    std::cin >> mes;
    std::cin.ignore();
    std::cout << "ano: ";
    int ano;
    std::cin >> ano;
    std::cin.ignore();
    cfecha->setNewFechaActual(dia, mes, ano);
 }