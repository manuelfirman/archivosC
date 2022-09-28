#include <iostream>
#include <cstring>
#include <string.h>

#include "clasesLoteria.h"


void generarArchivoGanadores();
void billetesVendidosPP();
void gananciaLoteria();
void cargarSorteo();
void cargarBillete();
void leerSorteos();
void leerBilletes();
bool buscarCodSorteo(int);
bool buscarNumBillete(int );
void cargar1();
void cargar2();
void leerArchivoGanadores();


int main(){

    int sorteo, billete;
    int opt, opt1;
    bool salir = false;
    Billete regBilletes;
    Sorteo regSorteos;

//    regBilletes.resetArchivo();
//    regSorteos.resetArchivo();

    while(!salir){
        std::cout << "1. GENERAR ARCHIVO GANADORES" << std::endl;
        std::cout << "2. BILLETES VENDIDOS POR PROVINCIA" << std::endl;
        std::cout << "3. GANANCIA/PERDIDA POR CADA SORTEO" << std::endl << std::endl;
        std::cout << "4. LEER GANANCIA/PERDIDA POR CADA SORTEO" << std::endl << std::endl;
        std::cout << "9. GESTION DE ARCHIVOS" << std::endl << std::endl;
        std::cout << "0. SALIR" << std::endl << std::endl;
        std::cout << "Opcion: ";
        std::cin >> opt;
        system("cls");
        switch(opt){
            case 1:
                generarArchivoGanadores();
                break;
            case 2:
                billetesVendidosPP();
                break;
            case 3:
                gananciaLoteria();
                break;
            case 4:
                leerArchivoGanadores();
                break;
            case 9:
                std::cout << "<< GESTION DE ARCHIVOS >>" << std::endl;
                std::cout << "1. CARGAR REGISTRO SORTEO" << std::endl;
                std::cout << "2. CARGAR REGISTRO BILLETE" << std::endl;
                std::cout << "3. LEER REGISTRO SORTEO" << std::endl;
                std::cout << "4. LEER REGISTRO BILLETE" << std::endl;
                std::cin >> opt1;
                switch(opt1){
                    case 1:
                        cargar1();
                        break;
                    case 2:
                        cargar2();
                        break;
                    case 3:
                        leerSorteos();
                        break;
                    case 4:
                        leerBilletes();
                        break;
                    default:
                        break;
                }
                break;
            case 0:
                salir = true;
                break;
        }
        system("pause");
        system("cls");
    }
    return 0;
}

void cargar1(){
    Sorteo reg;
    reg.cargarSorteo();
    if(reg.grabarEnDisco()) std::cout << "Cargado\n";
    else std::cout << "Error al cargar\n";
}

void cargar2(){
    Billete reg;
    reg.cargarBillete();
    if(reg.grabarEnDisco()) std::cout << "Cargado\n";
    else std::cout << "Error al cargar\n";
}

bool buscarGanador(int numero){
    Sorteo reg;
    int pos = 0;
    while(reg.leerDeDisco(pos++)){
        if(reg.getNumeroGanador() == numero){
            return true;
        }
    }
    return false;
}

bool buscarCodSorteo(int codSorteo){
    int pos = 0;
    Sorteo reg;
    while(reg.leerDeDisco(pos++)){
        if(reg.getNumeroGanador() == codSorteo){
            return true;
        }
    }
    return false;
}

void leerArchivoGanadores(){
    int pos = 0;
    Ganadores reg;
    while(reg.leerDeDisco(pos++)){
        reg.mostrar();
    }
}

void generarArchivoGanadores(){
    Billete billete;
    Ganadores reg;
    int pos = 0;
    reg.resetArchivo();
    while(billete.leerDeDisco(pos++)){
        if(buscarGanador(billete.getNumero())){
            reg.setCodigoSorteo(billete.getCodigoSorteo());
            reg.setCodigoProvincia(billete.getCodigoProvincia());
            reg.setMesSorteo(billete.getMes());
            reg.setNumeroGanador(billete.getNumero());
            if(reg.grabarEnDisco()) std::cout << "Correcto\n";
            else std::cout << "Error\n";
        }
    }
}

void billetesVendidosPP(){
    int mProvincias[24][12] = {0};
    int pos = 0;
    Billete reg;
    while(reg.leerDeDisco(pos++)){
        mProvincias[reg.getCodigoProvincia()-1][reg.getMes()-1]++;
    }

    for(int i = 0; i < 24; i++){
            std::cout << "<< Provincia N " << i+1 << " >>\n";
        for(int j = 0; j < 12; j++){
            if(mProvincias[i][j] != 0){
                std::cout << "Mes " << j+1 << ": " << mProvincias[i][j] << " billetes vendidos.\n";
            }
        }
    }
}

float buscarPremioGanador(int numero){
    float premio;
    int pos = 0;
    Sorteo reg;
    while(reg.leerDeDisco(pos++)){
        if(reg.getNumeroGanador() == numero){
            premio = reg.getImportePremio();
            return premio;
        }
    }
    return -1;
}

void gananciaLoteria(){
    Billete reg;
    Ganadores ganadores;
    int pos = 0;
    float acuBilletes = 0;
    float acuPremios = 0;
    float ganancia;

    while(reg.leerDeDisco(pos++)){
        acuBilletes += reg.getPrecioBillete();
    }

    pos = 0;
    while(ganadores.leerDeDisco(pos++)){
        acuPremios += buscarPremioGanador(ganadores.getNumeroGanador());
    }

    ganancia = acuBilletes - acuPremios;

    if(ganancia>0) std::cout << "Ganancia: $" << ganancia << "\n";
    else std::cout << "Perdida: $" << ganancia << "\n";
}

bool buscarNumBillete(int numero){
    int pos = 0;
    Billete reg;
    while(reg.leerDeDisco(pos++)){
        if(reg.getNumero() == numero){
            return true;
        }
    }
    return false;
}



void leerSorteos(){
    int pos = 0;
    Sorteo reg;
    while(reg.leerDeDisco(pos++)){
        std::cout << "Codigo Sorteo: " << reg.getCodigoSorteo() << "\n";
        std::cout << "Numero Ganador: " << reg.getNumeroGanador() << "\n";
        std::cout << "Importe Premio: $" << reg.getImportePremio() << "\n";
        std::cout << "Fecha: " << reg.getDia() << "/"<< reg.getDia() << "\n";
    }
}

void leerBilletes(){
    int pos = 0;
    Billete reg;
    while(reg.leerDeDisco(pos++)){
        std::cout << "Codigo Sorteo: " << reg.getCodigoSorteo() << "\n";
        std::cout << "Numero Billete: " << reg.getNumero() << "\n";
        std::cout << "Codigo Provincia: " << reg.getCodigoProvincia() << "\n";
        std::cout << "Precio del Billete: " << reg.getPrecioBillete() << "\n";
        std::cout << "Fecha: " << reg.getDia() << "/" << reg.getMes() << "\n";

    }
}
