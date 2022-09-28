void cargarCadena(char *pal, int tam){
    int i;
    fflush(stdin);
    for(i=0; i<tam; i++)
    {
        pal[i]=std::cin.get();
        if(pal[i]=='\n') break;
    }
    pal[i]='\0';
    fflush(stdin);
}

class Sorteo
{
    private:
        int _codigoSorteo;
        int _numeroGanador;
        float _importePremio;
        int _dia, _mes;

    public:

        int getCodigoSorteo(){ return _codigoSorteo; }
        int getNumeroGanador(){ return _numeroGanador; }
        float getImportePremio(){ return _importePremio; }
        int getDia(){ return _dia; }
        int getMes(){ return _mes; }


        void setCodigoSorteo(int codigo){ _codigoSorteo = codigo; }
        void setNumero(int num){ _numeroGanador = num; }
        void setImportePremio(int premio){ _importePremio = premio; }
        void setDia(int d){ _dia = d; }
        void setMes(int m){ _mes = m; }

        bool leerDeDisco(int posicion){
            FILE* pFile = fopen("sorteos.dat", "rb");
            if(pFile == NULL) return false;

            fseek(pFile, posicion * sizeof *this, SEEK_SET);
            int leyo = fread(this, sizeof *this, 1, pFile);
            fclose(pFile);
            return leyo;
        }

        bool resetArchivo(){
            FILE* pFile = fopen("ganadores.dat", "wb");
            if(pFile == NULL) return false;
            fclose(pFile);
            return true;
        }

        bool grabarEnDisco(){
            FILE* pFile = fopen("sorteos.dat", "ab");
            if(pFile == NULL) return false;

            int grabo = fwrite(this, sizeof *this, 1, pFile);
            fclose(pFile);
            return grabo;
        }

        void cargarSorteo(){


            std::cout << "Ingrese el codigo de sorteo: ";
            std::cin >> _codigoSorteo;

            std::cout << "Ingrese el numero ganador: ";
            std::cin >> _numeroGanador;
            while(_numeroGanador < 0){
                std::cout << "No puede ser negativo. Vuelva a ingresar: ";
                std::cin >> _numeroGanador;
            }
            std::cout << "Ingrese el importe del premio: ";
            std::cin >> _importePremio;
            while(_importePremio < 0){
                std::cout << "No puede ser negativo. Vuelva a ingresar: ";
                std::cin >> _importePremio;
            }
            std::cout << "Ingrese el dia y mes: ";
            std::cin >> _dia >> _mes;
            while(_dia < 0 || _mes < 0 || _dia > 31 || _mes > 12){
                std::cout << "Fecha incorrecta. Vuelva a ingresar: ";
                std::cin >> _dia >> _mes;
            }

            system("pause");
            system("cls");
        }


};

class Billete
{
    private:
        int codigoSorteo;
        int numero;
        int codigoProvincia;
        float precioBillete;
        int dia, mes;

    public:

        int getCodigoSorteo(){ return codigoSorteo; }
        int getNumero(){ return numero; }
        int getCodigoProvincia(){ return codigoProvincia; }
        float getPrecioBillete(){ return precioBillete; }
        int getDia(){ return dia; }
        int getMes(){ return mes; }


        void setCodigoSorteo(int codigo){ codigoSorteo = codigo; }
        void setNumero(int num){ numero = num; }
        void setPrecioBillete(float precio){ precioBillete = precio; }
        void setCodigoProvincia(int codProvincia){ codigoProvincia = codProvincia; }
        void setDia(int d){ dia = d; }
        void setMes(int m){ mes = m; }

        bool leerDeDisco(int posicion){
            FILE* pFile = fopen("billete.dat", "rb");
            if(pFile == NULL) return false;

            fseek(pFile, posicion * sizeof *this, SEEK_SET);
            int leyo = fread(this, sizeof *this, 1, pFile);
            fclose(pFile);
            return leyo;
        }

        bool resetArchivo(){
            FILE* pFile = fopen("ganadores.dat", "wb");
            if(pFile == NULL) return false;
            fclose(pFile);
            return true;
        }

        bool grabarEnDisco(){
            FILE* pFile = fopen("billete.dat", "ab");
            if(pFile == NULL) return false;

            int grabo = fwrite(this, sizeof *this, 1, pFile);
            fclose(pFile);
            return grabo;
        }

        void cargarBillete(){

            std::cout << "Ingrese el numero del billete: ";
            std::cin >> numero;
            std::cout << "Ingrese el codigo de sorteo: ";
            std::cin >> codigoSorteo;
            std::cout << "Ingrese el precio del billete: ";
            std::cin >> precioBillete;
            std::cout << "Ingrese el codigo de provincia: ";
            std::cin >> codigoProvincia;
            std::cout << "Ingrese el dia y mes: ";
            std::cin >> dia >> mes;

            system("pause");
            system("cls");
        }
};

class Ganadores
{
    private:
        int codigoSorteo;
        int numeroGanador;
        int mesSorteo;
        int codigoProvincia;

    public:

        void setCodigoSorteo(int codSorteo){ codigoSorteo = codSorteo; }
        void setNumeroGanador(int numGanador){ numeroGanador = numGanador; }
        void setMesSorteo(int mes){ mesSorteo = mes; }
        void setCodigoProvincia(int codProvincia){ codigoProvincia = codProvincia; }

        int getNumeroGanador(){ return numeroGanador; }


        bool leerDeDisco(int posicion){
            FILE* pFile = fopen("ganadores.dat", "rb");
            if(pFile == NULL) return false;

            fseek(pFile, posicion * sizeof *this, SEEK_SET);
            int leyo = fread(this, sizeof *this, 1, pFile);
            fclose(pFile);
            return leyo;
        }

        bool resetArchivo(){
            FILE* pFile = fopen("ganadores.dat", "wb");
            if(pFile == NULL) return false;
            fclose(pFile);
            return true;
        }

        bool grabarEnDisco(){
            FILE* pFile = fopen("ganadores.dat", "ab");
            if(pFile == NULL) return false;

            int grabo = fwrite(this, sizeof *this, 1, pFile);
            fclose(pFile);
            return grabo;
        }

        void mostrar(){
            std::cout << "Codigo sorteo: " << codigoSorteo << std::endl;
            std::cout << "Numero ganador: " << numeroGanador << std::endl;
            std::cout << "Mes sorteo: " << mesSorteo << std::endl;
            std::cout << "Codigo Provincia: " << codigoProvincia << std::endl << std::endl;
        }

};
