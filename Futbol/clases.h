
void cargarCadena(char *pal, int tam){
    int i;
    fflush(stdin);
    for(i=0; i<tam; i++)
    {
        pal[i]=cin.get();
        if(pal[i]=='\n') break;
    }
    pal[i]='\0';
    fflush(stdin);
}


class Jugador
{
    private:
        char codigoJugador[5];
        char nombreJugador[30];
        int edadJugador;
        char codigoEquipo[3];

    public:

        const char* getCodigoJugador(){ return codigoJugador;}
        const char* getNombreJugador(){return nombreJugador; }
        const char* getCodigoEquipo(){ return codigoEquipo; }
        int getEdadJugador(){ return edadJugador; }

        bool leerDeDisco(int posicion){
            FILE* pFile = fopen("jugador.dat", "rb");
            if(pFile == NULL) return false;
            fseek(pFile, posicion * sizeof *this, SEEK_SET);
            int leyo = fread(this, sizeof *this, 1, pFile);
            fclose(pFile);
            return leyo;
        }

        bool grabarEnDisco(){
            FILE* pFile = fopen("jugador.dat", "ab");
            if(pFile == NULL) return false;

            int grabo = fwrite(this, sizeof *this, 1, pFile);
            fclose(pFile);
            return grabo;
        }

        void cargar(const char codJugador[5] = {}){
            strcpy(codigoJugador, codJugador);
            std::cout << "Nombre: ";
            cargarCadena(nombreJugador, 29);
            std::cout << "Edad: ";
            std::cin >> edadJugador;
            std::cout << "Equipo: ";
            cargarCadena(codigoEquipo, 2);
        }

        void mostrar(){
            std::cout << "Codigo: " << codigoJugador << std::endl;
            std::cout << "Nombre: " << nombreJugador << std::endl;
            std::cout << "Edad: " << edadJugador << std::endl;
            std::cout << "Equipo: " << codigoEquipo << std::endl << std::endl;
        }
};

class Partido
{
    private:
        int numeroPartido;
        char codigoJugador[5];
        int dia;
        int mes;
        int goles;
        bool expulsado;

    public:
        int getNumeroPartido(){ return numeroPartido; }
        const char* getCodigoJugador(){ return codigoJugador; }
        int getDiaPartido(){ return dia; }
        int getMesPartido(){ return mes; }
        int getGoles(){ return goles; }
        bool getExpulsado(){ return expulsado; }

        bool leerDeDisco(int posicion){
            FILE* pFile = fopen("partido.dat", "rb");
            if(pFile == NULL) return false;
            fseek(pFile, posicion * sizeof *this, SEEK_SET);
            int leyo = fread(this, sizeof *this, 1, pFile);
            fclose(pFile);
            return leyo;
        }

        bool grabarEnDisco(){
            FILE* pFile = fopen("partido.dat", "ab");
            if(pFile == NULL) return false;

            int grabo = fwrite(this, sizeof *this, 1, pFile);
            fclose(pFile);
            return grabo;
        }

        void cargar(){
            std::cout << "Numero partido: ";
            std::cin >> numeroPartido;
            std::cout << "Codigo jugador: ";
            cargarCadena(codigoJugador, 4);
            std::cout << "Dia: ";
            std::cin >> dia;
            std::cout << "Mes: ";
            std::cin >> mes;
            std::cout << "Goles: ";
            std::cin >> goles;
            std::cout << "Expulsado(1.si - 0.no): ";
            std::cin >> expulsado;
        }

        void mostrar(){
            std::cout << "Numero partido: " << numeroPartido << std::endl;
            std::cout << "Codigo jugador: " << codigoJugador << std::endl;
            std::cout << "Fecha: " << dia << "/" << mes << std::endl;
            std::cout << "Goles: " << goles << std::endl;
            std::cout << "Expulsado: " << expulsado << std::endl << std::endl;
        }
};


class JugadorSinJugar
{
    private:
        char codigoJugador[5];
        char nombreJugador[30];
        char codigoEquipo[3];
    public:

        void setCodigoJugador(const char* codigoJugador){ strcpy(this->codigoJugador, codigoJugador); }
        void setNombreJugador(const char* nombreJugador){ strcpy(this->nombreJugador, nombreJugador); }
        void setCodigoEquipo(const char* codigoEquipo){ strcpy(this->codigoEquipo, codigoEquipo); }

        bool leerDeDisco(int posicion){
            FILE* pFile = fopen("jugadorSinJugar.dat", "rb");
            if(pFile == NULL) return false;
            fseek(pFile, posicion * sizeof *this, SEEK_SET);
            int leyo = fread(this, sizeof *this, 1, pFile);
            fclose(pFile);
            return leyo;
        }

        bool resetArchivo(){
            FILE* pFile = fopen("jugadorSinJugar.dat", "wb");
            if(pFile == NULL) return false;
            fclose(pFile);
            return true;
        }

        bool grabarEnDisco(){
            FILE* pFile = fopen("jugadorSinJugar.dat", "ab");
            if(pFile == NULL) return false;
            int grabo = fwrite(this, sizeof *this, 1, pFile);
            fclose(pFile);
            return grabo;
        }

        void mostrar(){
            std::cout << "Codigo jugador: " << codigoJugador << std::endl;
            std::cout << "Nombre jugador: " << nombreJugador << std::endl;
            std::cout << "Codigo equipo: " << codigoEquipo << std::endl << std::endl;
        }

};


