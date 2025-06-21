# Variables
CXX = g++
CXXFLAGS = -Wall -g -Iinclude
SRC_DIR = src
OBJ_DIR = obj
BIN = lab4

# Archivos fuente y objetos
SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/CargaDatos.cpp \
       $(SRC_DIR)/Cliente.cpp \
       $(SRC_DIR)/ControladorFechaActual.cpp \
       $(SRC_DIR)/ControladorUsuario.cpp \
       $(SRC_DIR)/DTApartamento.cpp \
       $(SRC_DIR)/DTCasa.cpp \
       $(SRC_DIR)/DTFecha.cpp \
       $(SRC_DIR)/DTInmueble.cpp \
       $(SRC_DIR)/DTInmuebleAdministrado.cpp \
       $(SRC_DIR)/DTInmuebleListado.cpp \
       $(SRC_DIR)/DTNotificacion.cpp \
       $(SRC_DIR)/DTPublicacion.cpp \
       $(SRC_DIR)/DTUsuario.cpp \
       $(SRC_DIR)/Factory.cpp \
       $(SRC_DIR)/Casa.cpp \
       $(SRC_DIR)/Apartamento.cpp \
       $(SRC_DIR)/Inmobiliaria.cpp \
       $(SRC_DIR)/Inmueble.cpp \
       $(SRC_DIR)/Publicacion.cpp \
       $(SRC_DIR)/IPublicacion.cpp \
       $(SRC_DIR)/ISuscriptor.cpp \
       $(SRC_DIR)/ManejadorUsuario.cpp \
       $(SRC_DIR)/Menu.cpp \
       $(SRC_DIR)/Propietario.cpp \
       $(SRC_DIR)/AdministraPropiedad.cpp \
       $(SRC_DIR)/ControladorPublicacion.cpp \
       $(SRC_DIR)/ManejadorPublicacion.cpp \
       $(SRC_DIR)/Usuario.cpp

OBJS = $(SRCS:.cpp=.o)

# Regla principal
all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(BIN) $(OBJS)

rebuild: clean all