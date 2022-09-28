using namespace std;
#include <iostream>
#include <cstring>
#include <string.h>
#include "clases.h"

void cargarJugadorDat();
void cargarPartidoDat();
void leerJugadorDat();
void leerPartidoDat();
void edadPromedio();
void maximoGoleador();
void jugadoresSinJugar();
void leerJugadoresSinJugar();
void expulsionesMensuales();

int main()
{
    int opt, opt1;
    bool salir = false;
    while(!salir){
        std::cout << "1. CANTIDAD DE EXPULSIONES POR MES" << std::endl;
        std::cout << "2. EDAD CON MAYOR CANTIDAD DE JUGADORES (ENTRE 17 Y 41)" << std::endl;
        std::cout << "3. MAXIMO GOLEADOR" << std::endl << std::endl;
        std::cout << "4. GENERAR ARCHIVO JUGADORES SIN JUGAR" << std::endl;
        std::cout << "5. LEER ARCHIVO JUGADORES SIN JUGAR" << std::endl << std::endl;
        std::cout << "9. CARGAR ARCHIVOS (TEST)" << std::endl << std::endl;
        std::cout << "Opcion: ";
        std::cin >> opt;
        system("cls");

        switch(opt){
            case 1:
                expulsionesMensuales();
                break;
            case 2:
                edadPromedio();
                break;
            case 3:
                maximoGoleador();
                break;
            case 4:
                jugadoresSinJugar();
                break;
            case 5:
                leerJugadoresSinJugar();
                break;
            case 9:
                std::cout << "1. CARGAR ARCHIVO JUGADOR.DAT" << std::endl;
                std::cout << "2. CARGAR ARCHIVO PARTIDO.DAT" << std::endl << std::endl;
                std::cout << "3. LEER ARCHIVO JUGADOR.DAT" << std::endl;
                std::cout << "4. LEER ARCHIVO PARTIDO.DAT" << std::endl << std::endl;
                std::cout << "Opcion: ";
                std::cin >> opt1;
                switch(opt1){
                    case 1:
                        cargarJugadorDat();
                        break;
                    case 2:
                        cargarPartidoDat();
                        break;
                    case 3:
                        leerJugadorDat();
                        break;
                    case 4:
                        leerPartidoDat();
                        break;
                }
                break;
            default:
                salir = true;
                break;
        }
        system("pause");
        system("cls");
    }
}

//1
void expulsionesMensuales(){
    int vExpulsiones[12] = {0};
    int pos = 0;
    Partido reg;
    while(reg.leerDeDisco(pos++)){
        if(reg.getExpulsado()){
            vExpulsiones[reg.getMesPartido()-1]++;
        }
    }

    std::cout << "<<EXPULSIONES POR MES>>\n";
    for(int i = 0; i < 12; i++){
        std::cout << "Mes " << i+1 << ": " << vExpulsiones[i] << " expulsiones" << std::endl;
    }
}

//2
void edadPromedio(){
    int vEdad[25] = {0};
    int pos = 0;
    int edadProm = 0;
    Jugador reg;

    while(reg.leerDeDisco(pos++)){
        vEdad[reg.getEdadJugador()-17]++;
    }


    int cant = vEdad[0];
    for(int i = 0; i < 24; i++){
        if(vEdad[i] >= cant){
            cant = vEdad[i];
            edadProm = i;
        }
    }
    std::cout << "<<EDAD CON MAS JUGADORES>>\n";
    std::cout << "La edad con mayor cantidad de jugadores es: " << edadProm+17 << " anios\n";
}

//3

int contarGoles(const char codigoJugador[5]){
    int pos = 0;
    Partido reg;
    int acuGoles = 0;
    while(reg.leerDeDisco(pos++)){
        if(strcmp(codigoJugador, reg.getCodigoJugador()) == 0){
            acuGoles += reg.getGoles();
        }
    }
    return acuGoles;
}
void maximoGoleador(){
    int pos = 0;
    int maxGoles = 0;
    char nombreGoleador[30];
    Jugador reg;
    while(reg.leerDeDisco(pos++)){
        if(contarGoles(reg.getCodigoJugador()) > maxGoles){
            maxGoles = contarGoles(reg.getCodigoJugador());
            strcpy(nombreGoleador, reg.getNombreJugador());
        }
    }
    std::cout << "<<MAXIMO GOLEADOR>>\n";
    std::cout << "El jugador con mas goles es '" << nombreGoleador << "' con " << maxGoles << " goles" << std::endl;
}

//4
bool participacionJugador(const char codigoJugador[5]){
    int pos = 0;
    Partido reg;

    while(reg.leerDeDisco(pos++)){
        if(strcmp(codigoJugador, reg.getCodigoJugador()) == 0){
            return true;
        }
    }
    return false;
}


void jugadoresSinJugar(){
    JugadorSinJugar reg;
    Jugador jugador;
    reg.resetArchivo();
    int pos = 0;
    while(jugador.leerDeDisco(pos++)){
        if(!participacionJugador(jugador.getCodigoJugador())){
            reg.setNombreJugador(jugador.getNombreJugador());
            reg.setCodigoJugador(jugador.getCodigoJugador());
            reg.setCodigoEquipo(jugador.getCodigoEquipo());
            reg.grabarEnDisco();
        }
    }

}

//5
void leerJugadoresSinJugar(){
    int pos = 0;
    JugadorSinJugar reg;
    while(reg.leerDeDisco(pos++)){
        reg.mostrar();
    }
}

bool buscarJugador(const char codJugador[5]){
    Jugador reg;
    int pos = 0;
    while(reg.leerDeDisco(pos++)){
        if(strcmp(reg.getCodigoJugador(), codJugador) == 0){
            return true;
        }
    }
    return false;
}

void cargarJugadorDat(){
    int salir;
    char codJugador[5];
    do{
        std::cout << "<< CARGA JUGADOR >>\n";
        Jugador jugador;

        std::cout << "Ingrese el codigo del jugador: ";
        cargarCadena(codJugador, 4);
        while(buscarJugador(codJugador)){
            std::cout << "El jugador ya existe. Vuelva a ingresar: ";
            std::cin >> codJugador;
        }
        jugador.cargar(codJugador);

        if(jugador.grabarEnDisco()) std::cout << "Cargado correctamente\n";
        else std::cout << "No se pudo grabar en disco\n\n";
        std::cout << "Desea volver a ingresar? (1. si - 0 - no): ";
        std::cin >> salir;

        system("cls");
    }while(salir != 0);
}

void cargarPartidoDat(){
    int salir;
    do{
        std::cout << "<< CARGA PARTIDO >>\n";
        Partido partido;

        partido.cargar();

        if(partido.grabarEnDisco()) std::cout << "Cargado correctamente\n";
        else std::cout << "No se pudo grabar en disco\n\n";
        std::cout << "Desea volver a ingresar? (1. si - 0 - no): ";
        std::cin >> salir;

        system("cls");
    } while(salir != 0);
}

void leerPartidoDat(){
    int pos = 0;
    Partido reg;
    while(reg.leerDeDisco(pos++)){
        reg.mostrar();
    }

}
void leerJugadorDat(){
    int pos = 0;
    Jugador reg;

    while(reg.leerDeDisco(pos++)){
        reg.mostrar();
    }
}
